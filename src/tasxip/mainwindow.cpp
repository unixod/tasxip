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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataParser = new DataParser(&ipr);
    dataDumper = new DataDumper(&ipr);

    _sltFilterFmtChanged(); //for initialize dataDumper format

    connect(ui->bgrpFormats, SIGNAL(buttonClicked(int)), this, SLOT(_sltFilterFmtChanged()));

    //Ui Setup
    _uiSetup();

    //Newtwork Setup
    _netSetup();
}

MainWindow::~MainWindow(){
    delete ui;
    delete dataParser;
    delete dataDumper;

    _netCleanup();
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::_uiSetup(){
    this->setWindowTitle(QString("TasXIP %1").arg(VERSION));

    ui->gbLog->setHidden(true);
    ui->lbl_px->setHidden(true);
    ui->lbl_tasxip->setHidden(true);
    ui->lbl_bottom->setHidden(true);
    ui->gbCustomizations->setHidden(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    _changeUiState(Stopped);

    //SIGNAL-SLOT Connections
    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(_sltToolBarActions(QAction*)));
}

void MainWindow::_changeUiState(UiState state){
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

//PRIVATE SLOTS----------------------------------------------------------------
void MainWindow::_sltToolBarActions(QAction *action){
    if(action->isChecked()){
        QList<QAction *> lst_a = ui->mainToolBar->actions();
        foreach(QAction *a, lst_a){
            if(a != action) a->setChecked(false);
        }
    }
}

void MainWindow::_sltLog(const QString &log_str){
    ui->txtbLog->append(log_str);
}

void MainWindow::_sltDownloadProgress(qint64 val, qint64 total){
    if(total > 0){
        ui->progressBar->setMaximum(total);
        ui->progressBar->setValue(val);
    }
}

void MainWindow::_sltFilterFmtChanged(){
    QRadioButton *rbtn = qobject_cast<QRadioButton *>(ui->bgrpFormats->checkedButton());

    if(rbtn == ui->rbtnFmtSimple) dataDumper->setFormat(DataDumper::SIMPLE);
    else if(rbtn == ui->rbtnFmtP2P) dataDumper->setFormat(DataDumper::P2P);
}
