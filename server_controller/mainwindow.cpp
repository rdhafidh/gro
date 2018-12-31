#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (&ctl,&ServerController::readAllError,this,&MainWindow::readAllError);
    connect(&ctl,&ServerController::readAllOutput,this,&MainWindow::readAllOutput);
    connect(&ctl,&ServerController::startControlling,this,&MainWindow::startControlling);
    connect(&ctl,&ServerController::finishControlling,this,&MainWindow::finishControlling);
    connect(&ctl,&ServerController::killingDone,this,[this](){
       ui->textEdit_log->append ("\nprocess killed\n");
       this->ui->pushButton_start->setEnabled (true);
       this->ui->pushButton_stop->setEnabled (false);
    });
    ui->pushButton_start->setEnabled (true);
    ui->pushButton_stop->setEnabled (false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    ctl.selesaiThread ();
    e->accept();
}

void MainWindow::on_pushButton_start_clicked()
{
    QString port=ui->lineEdit_port->text ();
    bool ok=false;
    port.toInt (&ok);
    if(!ok){
        QMessageBox::information (this,tr("Galat"),tr("Informasi port harus angka"),QMessageBox::Ok);
        return;
    }
    ctl.setPort (port);
    ctl.startProcessing ();
}

void MainWindow::on_pushButton_stop_clicked()
{
    ctl.forceKilling ();
}

void MainWindow::readAllOutput(const QByteArray &out)
{
    ui->textEdit_log->append (QString::fromStdString (out.toStdString ()));
}

void MainWindow::readAllError(const QByteArray &err)
{
    ui->textEdit_log->append (QString::fromStdString (err.toStdString ()));
}

void MainWindow::startControlling()
{
    ui->pushButton_start->setEnabled (false);
    ui->pushButton_stop->setEnabled (true);
}

void MainWindow::finishControlling(int code, QProcess::ExitStatus status)
{
    ui->textEdit_log->append (tr("\nexit code : %1 and status %2\n").arg (code).arg (status));
    ui->pushButton_start->setEnabled (true);
    ui->pushButton_stop->setEnabled (false);
}

void MainWindow::on_pushButton_clearlog_clicked()
{
    ui->textEdit_log->clear ();
}
