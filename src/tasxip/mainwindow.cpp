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
#include "pluginsprovider.h"
#include "plugin.h"
#include "plugininfodlg.h"
#include "settings.h"

MainWindow::MainWindow(PluginsProvider *plgProvider, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    plugins(plgProvider)
{
    ui->setupUi(this);

    dataParser = new DataParser(&ipr);

    //Ui Setup
    uiSetup();

    //Newtwork Setup
    netSetup();

    prevLoadedPlugin.first = -1;
    prevLoadedPlugin.second = 0;
}

MainWindow::~MainWindow(){
    netCleanup();

    delete ui;
    delete dataParser;
    delete prevLoadedPlugin.second;
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::uiSetup(){
    QStringList names = plugins->names();
    QString tmp;
    int idx;
    foreach(const QString &name, names){
        if(name != tmp)
            idx = 0;
        else
            ++idx;

        ui->cmbPluginsNames->addItem(name, idx);
        tmp = name;
    }

    this->setWindowTitle(QString("TasXIP %1").arg(VERSION));

    ui->gbLog->setHidden(true);
    ui->lbl_px->setHidden(true);
    ui->lbl_tasxip->setHidden(true);
    ui->lbl_bottom->setHidden(true);
    ui->tabSettings->setHidden(true);
    ui->btnbxSettings->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    changeUiState(Stopped);

    readSettings();

    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(sltToolBarActions(QAction*)));

    //Outupt tab
    connect(ui->cmbPluginsNames, SIGNAL(currentIndexChanged(int)), this, SLOT(sltSettingsUIChanged()));

    //Network tab
    connect(ui->chbxProxyEnabled, SIGNAL(stateChanged(int)), this, SLOT(sltSettingsUIChanged()));
    connect(ui->lneProxyAddr, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsUIChanged()));
    connect(ui->lneProxyPort, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsUIChanged()));
    connect(ui->lneProxyUser, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsUIChanged()));
    connect(ui->lneProxyPasswd, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsUIChanged()));
    connect(ui->chbxAuthRequired, SIGNAL(stateChanged(int)), this, SLOT(sltSettingsUIChanged()));
}

void MainWindow::changeUiState(UiState state){
    switch(state){
    case Stopped:
        ui->btnStart->setEnabled(true);
        ui->tabOutput->setEnabled(true);
        ui->tabNetwork->setEnabled(true);
        ui->btnbxSettings->setDisabled(true);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(0);
        break;
    case Processed:
        ui->btnStart->setDisabled(true);
        ui->tabOutput->setDisabled(true);
        ui->tabNetwork->setDisabled(true);
        ui->progressBar->reset();
        ui->progressBar->setMaximum(0);
        break;
    case SettingsNotSaved:
        ui->btnStart->setDisabled(true);
        ui->btnbxSettings->setEnabled(true);
        break;
    }
}

Plugin * MainWindow::currentPlugin(){
    int selItem = ui->cmbPluginsNames->currentIndex();

    if(prevLoadedPlugin.first != selItem){
        QString plgName = ui->cmbPluginsNames->itemText(selItem);
        int plgIdx = ui->cmbPluginsNames->itemData(selItem).toInt();

        prevLoadedPlugin.first = selItem;
        delete prevLoadedPlugin.second;
        prevLoadedPlugin.second = plugins->load(plgName, plgIdx);
    }

    return prevLoadedPlugin.second;
}

void MainWindow::readSettings(){
    //Outupt tab
    ui->cmbPluginsNames->setCurrentIndex(Settings::get(Settings::LoadedPlugin).toInt());

    //Network tab
    ui->chbxProxyEnabled->setChecked(Settings::get(Settings::ProxyEnabled, Settings::Network).toBool());
    ui->lneProxyAddr->setText(Settings::get(Settings::ProxyAddress, Settings::Proxy).toString());
    ui->lneProxyPort->setText(Settings::get(Settings::ProxyPort, Settings::Proxy).toString());
    ui->lneProxyUser->setText(Settings::get(Settings::ProxyUser, Settings::Proxy).toString());
    ui->lneProxyPasswd->setText(Settings::get(Settings::ProxyPassword, Settings::Proxy).toString());
    ui->chbxAuthRequired->setChecked(Settings::get(Settings::ProxyAuthReq, Settings::Proxy).toBool());
}

void MainWindow::writeSettings(){
    //Outupt tab
    Settings::set(Settings::LoadedPlugin) = ui->cmbPluginsNames->currentIndex();

    //Network tab
    Settings::set(Settings::ProxyEnabled, Settings::Network) = ui->chbxProxyEnabled->isChecked();
    Settings::set(Settings::ProxyAddress, Settings::Proxy) = ui->lneProxyAddr->text();
    Settings::set(Settings::ProxyPort, Settings::Proxy) = ui->lneProxyPort->text();
    Settings::set(Settings::ProxyUser, Settings::Proxy) = ui->lneProxyUser->text();
    Settings::set(Settings::ProxyPassword, Settings::Proxy) = ui->lneProxyPasswd->text();
    Settings::set(Settings::ProxyAuthReq, Settings::Proxy) = ui->chbxAuthRequired->isChecked();

    emit sigSettingsChanged();
}

//PRIVATE SLOTS----------------------------------------------------------------
void MainWindow::on_tbtnPluginInfo_clicked(){
    PluginInfoDlg::showModal(currentPlugin());
}

void MainWindow::on_btnbxSettings_clicked(QAbstractButton * button){
    if(QDialogButtonBox *snd = qobject_cast<QDialogButtonBox *>(sender())){
        switch(snd->standardButton(button)){
        case QDialogButtonBox::Apply:
            writeSettings();
            break;
        case QDialogButtonBox::Reset:
            readSettings();
            break;
        default:
            break;
        }
    }
    changeUiState(Stopped);
}

void MainWindow::sltToolBarActions(QAction *action){
    if(action->isChecked()){
        QList<QAction *> lst_a = ui->mainToolBar->actions();
        foreach(QAction *a, lst_a){
            if(a != action) a->setChecked(false);
        }
    }
}

void MainWindow::sltLog(const QString &log_str){
    ui->txtbLog->append(log_str);
}

void MainWindow::sltDownloadProgress(qint64 val, qint64 total){
    if(total > 0){
        ui->progressBar->setMaximum(total);
        ui->progressBar->setValue(val);
    }
}

void MainWindow::sltSettingsUIChanged(){
    changeUiState(SettingsNotSaved);
}
