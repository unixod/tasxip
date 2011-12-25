#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataparser.h"
#include <QFileDialog>

void MainWindow::_netSetup(){
    dataParser = new DataParser;

    nam = new QNetworkAccessManager(this);

    //Request Setup
    req = new QNetworkRequest(QUrl("http://mrlg.tas-ix.uz/index.cgi"));
    req_params = "query=1";

    //SIGNAL-SLOT Connections
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(_sltReplyFinshed(QNetworkReply*)));
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::_netCleanup(){
    delete dataParser;
    delete req;
}

void MainWindow::_saveDumpedData(){
    _sltLog(tr("Saving..."));
    QString dumpFileName = QFileDialog::getSaveFileName(this, "Save As:", "ipfilter.dat", "*.*");
    if(!dumpFileName.isEmpty()){
        dataParser->flushToFile(dumpFileName);
        _sltLog(tr("Saved to: %1").arg(dumpFileName));

    } else _sltLog(tr("Saving canceled."));
}

//PRIVATE SLOTS----------------------------------------------------------------
void MainWindow::on_btnStart_clicked(){
    _changeUiState(Processed);

    QNetworkReply *reply = nam->post(*req, req_params);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(_sltDownloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(_sltReplyError(QNetworkReply::NetworkError)));
}

void MainWindow::_sltReplyFinshed(QNetworkReply *reply){

    if(reply->size() > 0){
        _sltLog(tr("Processing received data..."));
        dataParser->parse(reply);
        _sltLog(tr("+-- parsed ip ranges count %1:").arg(dataParser->parsedCount()));
        _sltLog(tr("+-- output ip ranges count %1:").arg(dataParser->resultCount()));

        _saveDumpedData();

        _sltLog(tr("Complete."));
    }

    _changeUiState(Stopped);

    reply->deleteLater();
}

void MainWindow::_sltReplyError(QNetworkReply::NetworkError code){
    QNetworkReply *reply;
    if((reply = qobject_cast<QNetworkReply *>(sender()))){
        _sltLog(QString("Error code: %1").arg(code));
        _sltLog(reply->errorString());
        reply->deleteLater();
    }
}
