#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <servercontroller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ServerController ctl;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
protected:
    void changeEvent(QEvent *e);
    void closeEvent (QCloseEvent *e);
    
private slots:
    void on_pushButton_start_clicked();
    
    void on_pushButton_stop_clicked();
     
    void readAllOutput(const QByteArray &out);
    void readAllError(const QByteArray &err);
    void startControlling();
    void finishControlling(int code, QProcess::ExitStatus status);
    
    void on_pushButton_clearlog_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
