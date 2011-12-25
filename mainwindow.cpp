#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Ui Setup
    _uiSetup();

    //Newtwork Setup
    _netSetup();
}

MainWindow::~MainWindow(){
    delete ui;
    _netCleanup();
}

//PRIVATE METHODS--------------------------------------------------------------
void MainWindow::_uiSetup(){
    ui->gbLog->setHidden(true);
    ui->lbl_px->setHidden(true);
    ui->lbl_tasxip->setHidden(true);
    ui->lbl_bottom->setHidden(true);
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
