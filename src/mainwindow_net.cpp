/*
    TasXIP - ipfilter files generator
    Copyright (C) 2011-2012, Eldar Zakirov <unixod@gmail.com>

    This file is part of TasXIP.

    TasXIP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TasXIP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataparser.h"
#include "datadumper.h"
#include <QFileDialog>

void MainWindow::_netSetup(){
    nam = new QNetworkAccessManager(this);

    //Request Setup
    req = new QNetworkRequest(QUrl("http://mrlg.tas-ix.uz/index.cgi"));
    req_params = "query=1";

    //SIGNAL-SLOT Connections
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(_sltReplyFinshed(QNetworkReply*)));
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::_netCleanup(){
    delete req;
}

void MainWindow::_saveDumpedData(){
    _sltLog(tr("Saving..."));
    QString dumpFileName = QFileDialog::getSaveFileName(this, "Save As:", "ipfilter.dat", "*.*");
    if(!dumpFileName.isEmpty()){
        dataDumper->flushToFile(dumpFileName);
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
