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
    delete ui;
    delete dataParser;
    delete prevLoadedPlugin.second;

    netCleanup();
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
    ui->gbSettings->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    changeUiState(Stopped);

    //SIGNAL-SLOT Connections
    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(sltToolBarActions(QAction*)));
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

//PRIVATE SLOTS----------------------------------------------------------------
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

void MainWindow::on_tbtnPluginInfo_clicked(){
    PluginInfoDlg::showModal(currentPlugin());
}
