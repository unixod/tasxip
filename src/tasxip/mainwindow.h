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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "rangeset.h"

class PluginsProvider;
class Plugin;

namespace Ui {
    class MainWindow;
}

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class DataParser;
class DataDumper;

class MainWindow : public QMainWindow{
    Q_OBJECT


    enum UiState{
        Stopped,
        Processed
    };

public:
    explicit MainWindow(PluginsProvider *, QWidget *parent = 0);
    ~MainWindow();

private:
    void _changeUiState(UiState);
    void _uiSetup();
    void _netSetup();
    void _netCleanup();
    void _saveDumpedData();
    Plugin * _currentPlugin();

private slots:
    void on_btnStart_clicked();
    void _sltReplyFinshed(QNetworkReply *);
    void _sltReplyError(QNetworkReply::NetworkError);
    void _sltDownloadProgress(qint64, qint64);
    void _sltLog(const QString &);
    void _sltToolBarActions(QAction *);
//    void _sltFilterFmtChanged();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *nam;
    QNetworkRequest *req;
    QByteArray req_params;

    DataParser *dataParser;
    DataDumper *dataDumper;
    RangeSet<unsigned int> ipr;

    PluginsProvider *plugins;
    std::pair<int, Plugin*> prevLoadedPlugin;
};

#endif // MAINWINDOW_H
