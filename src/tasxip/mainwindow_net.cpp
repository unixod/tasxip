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
#include "plugin.h"
#include "pluginsprovider.h"
#include <QFileDialog>

void MainWindow::netSetup(){
    nam = new QNetworkAccessManager(this);

    //Request Setup
    req = new QNetworkRequest(QUrl("http://mrlg.tas-ix.uz/index.cgi"));
    req_params = "query=1";

    //SIGNAL-SLOT Connections
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(sltReplyFinshed(QNetworkReply*)));
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::netCleanup(){
    delete req;
}

void MainWindow::saveDumpedData(){
    sltLog(tr("Saving..."));

    QString outFileName = QFileDialog::getSaveFileName(this, "Save As:", "ipfilter.dat", "*.*");
    QFile outFile(outFileName);

    if(outFile.open(QIODevice::WriteOnly)){
        Plugin *plg = currentPlugin();
        QTextStream out(&outFile);

        out << plg->invoke(ipr);

        sltLog(tr("Saved to: %1").arg(outFileName));

    } else
        sltLog(tr("Saving canceled."));
}

//PRIVATE SLOTS----------------------------------------------------------------
void MainWindow::on_btnStart_clicked(){
    changeUiState(Processed);

    QNetworkReply *reply = nam->post(*req, req_params);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(sltDownloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(sltReplyError(QNetworkReply::NetworkError)));
}

void MainWindow::sltReplyFinshed(QNetworkReply *reply){

    if(reply->size() > 0){
        sltLog(tr("Processing received data..."));
        dataParser->parse(reply);
        sltLog(tr("+-- parsed ip ranges count %1:").arg(dataParser->parsedCount()));
        sltLog(tr("+-- output ip ranges count %1:").arg(dataParser->resultCount()));

        saveDumpedData();

        sltLog(tr("Complete."));
    }

    changeUiState(Stopped);

    reply->deleteLater();
}

void MainWindow::sltReplyError(QNetworkReply::NetworkError code){
    QNetworkReply *reply;
    if((reply = qobject_cast<QNetworkReply *>(sender()))){
        sltLog(QString("Error code: %1").arg(code));
        sltLog(reply->errorString());
        reply->deleteLater();
    }
}
