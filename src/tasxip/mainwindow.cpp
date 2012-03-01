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
#include <QSettings>

MainWindow::MainWindow(const QDir &appDir, PluginsProvider *plgProvider, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    plugins(plgProvider)
{
    ui->setupUi(this);

    dataParser = new DataParser(&ipr);

    cfg = new QSettings(appDir.absolutePath() + "/" + "tasxip.cfg", QSettings::IniFormat);

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
    delete cfg;
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
    }

    this->setWindowTitle(QString("TasXIP %1").arg(VERSION));

    ui->gbLog->setHidden(true);
    ui->lbl_px->setHidden(true);
    ui->lbl_tasxip->setHidden(true);
    ui->lbl_bottom->setHidden(true);
    ui->tabSettings->setHidden(true);
    ui->btnbxSettings->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    readSettings();

    changeUiState(Stopped);


    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(sltToolBarActions(QAction*)));

    //Outupt tab
    connect(ui->cmbPluginsNames, SIGNAL(currentIndexChanged(int)), this, SLOT(sltSettingsChanged()));

    //Network tab
    connect(ui->lneProxyAddr, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsChanged()));
    connect(ui->lneProxyPort, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsChanged()));
    connect(ui->lneProxyUser, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsChanged()));
    connect(ui->lneProxyPasswd, SIGNAL(textChanged(QString)), this, SLOT(sltSettingsChanged()));
    connect(ui->chbxAuthRequired, SIGNAL(stateChanged(int)), this, SLOT(sltSettingsChanged()));
}

void MainWindow::changeUiState(UiState state){
    switch(state){
    case Stopped:
        ui->btnStart->setEnabled(true);
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(0);
        break;
    case Processed:
        ui->btnStart->setDisabled(true);
        ui->progressBar->reset();
        ui->progressBar->setMaximum(0);
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
    ui->cmbPluginsNames->setCurrentIndex(cfg->value("loaded_plugin").toInt());

    //Network tab
    ui->lneProxyAddr->setText(cfg->value("proxy_addr").toString());
    ui->lneProxyPort->setText(cfg->value("proxy_port").toString());
    ui->lneProxyUser->setText(cfg->value("proxy_user").toString());
    ui->lneProxyPasswd->setText(cfg->value("proxy_passwd").toString());
    ui->chbxAuthRequired->setChecked(cfg->value("proxy_auth_req").toBool());
}

void MainWindow::writeSettings(){
    //Outupt tab
    cfg->setValue("loaded_plugin", ui->cmbPluginsNames->currentIndex());

    //Network tab
    cfg->setValue("proxy_addr", ui->lneProxyAddr->text());
    cfg->setValue("proxy_port", ui->lneProxyPort->text());
    cfg->setValue("proxy_user", ui->lneProxyUser->text());
    cfg->setValue("proxy_passwd", ui->lneProxyPasswd->text());
    cfg->setValue("proxy_auth_req", ui->chbxAuthRequired->isChecked());
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
    ui->btnbxSettings->setDisabled(true);
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

void MainWindow::sltSettingsChanged(){
    ui->btnbxSettings->setEnabled(true);
}
