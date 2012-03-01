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
class QSettings;
class QAbstractButton;


class MainWindow : public QMainWindow{
    Q_OBJECT

    enum UiState{
        Stopped,
        Processed,
        SettingsNotSaved
    };

public:
    explicit MainWindow(const QDir &appDir, PluginsProvider *, QWidget *parent = 0);
    ~MainWindow();


private:
    void changeUiState(UiState);
    void uiSetup();
    void netSetup();
    void netCleanup();
    void saveDumpedData();
    Plugin * currentPlugin();
    void readSettings();
    void writeSettings();

signals:
    void sigSettingsChanged();

private slots:
    void on_btnStart_clicked();
    void on_tbtnPluginInfo_clicked();
    void on_btnbxSettings_clicked(QAbstractButton *);
    void sltReplyFinshed(QNetworkReply *);
    void sltReplyError(QNetworkReply::NetworkError);
    void sltDownloadProgress(qint64, qint64);
    void sltLog(const QString &);
    void sltToolBarActions(QAction *);
    void sltSettingsUIChanged();
    void sltNetConfigure();


private:
    Ui::MainWindow *ui;

    QSettings *cfg;

    QNetworkAccessManager *nam;
    QNetworkRequest *req;
    QByteArray req_params;

    DataParser *dataParser;
    RangeSet<unsigned int> ipr;

    PluginsProvider *plugins;
    std::pair<int, Plugin*> prevLoadedPlugin;
};

#endif // MAINWINDOW_H
