#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
    class MainWindow;
}

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class DataParser;

class MainWindow : public QMainWindow{
    Q_OBJECT
    QNetworkAccessManager *nam;
    QNetworkRequest *req;
    QByteArray req_params;
    DataParser *dataParser;

    enum UiState{
        Stopped,
        Processed
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void _saveDumpedData();

private:
    void _changeUiState(UiState);
    void _uiSetup();
    void _netSetup();
    void _netCleanup();

private slots:
    void on_btnStart_clicked();
    void _sltReplyFinshed(QNetworkReply *);
    void _sltReplyError(QNetworkReply::NetworkError);
    void _sltDownloadProgress(qint64, qint64);
    void _sltLog(const QString &);
    void _sltToolBarActions(QAction *);
};

#endif // MAINWINDOW_H
