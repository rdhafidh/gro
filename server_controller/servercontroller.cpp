#include "servercontroller.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

ServerController::ServerController(QObject *parent) : QObject(parent),mcontroller(new ServerControllerWorker)
{
    qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus"); 
    mcontroller->moveToThread (&thread);
    connect(mcontroller.get (),&ServerControllerWorker::readAllError,this,&ServerController::readAllError);
    connect(mcontroller.get (),&ServerControllerWorker::readAllOutput,this,&ServerController::readAllOutput);
    connect(mcontroller.get (),&ServerControllerWorker::startControlling,this,&ServerController::startControlling);
    connect (mcontroller.get (),&ServerControllerWorker::finishControlling,this,&ServerController::finishControlling);
    connect(mcontroller.get (),&ServerControllerWorker::killingDone,this,&ServerController::killingDone);
    connect(mcontroller.get (),&ServerControllerWorker::killingDone,this,[this](){
        if(thread.isRunning ()){
            thread.requestInterruption ();
            thread.quit ();
            thread.wait (800);
        }
    });
    connect(mcontroller.get (),&ServerControllerWorker::killExitDone,this,[this](){
        if(thread.isRunning ()){
            thread.requestInterruption ();
            thread.quit ();
            thread.wait (800);
        }  
    });
    
    connect (this,&ServerController::askToKill,mcontroller.get (),&ServerControllerWorker::forceKilling);
    connect(this,&ServerController::askToStart,mcontroller.get (),&ServerControllerWorker::startProcessing);
    connect(this,&ServerController::setNewPort,mcontroller.get (),&ServerControllerWorker::setPort);
    connect(this,&ServerController::closeExit,mcontroller.get (),&ServerControllerWorker::killonExit);
}

ServerController::~ServerController()
{
    selesaiThread ();
    mcontroller->disconnect ();
}

void ServerController::setPort(const QString &port)
{
    this->setNewPort (port);
}

void ServerController::forceKilling()
{ 
    this->askToKill ();
}

void ServerController::selesaiThread()
{
    closeExit ();  
}

void ServerController::startProcessing()
{
    if(!thread.isRunning ()){
        thread.start ();
    }
    this->askToStart ();
} 

ServerControllerWorker::ServerControllerWorker(QObject *parent):QObject(parent),process(new QProcess(this))
{
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process.get(),&QProcess::readyReadStandardOutput,this,
            &ServerControllerWorker::handleAllOutput);
    connect(process.get(),&QProcess::readyReadStandardError,this,
            &ServerControllerWorker::handleAllOutError);
    connect(process.get(),&QProcess::started,this,&ServerControllerWorker::startControlling);
    connect(process.get (),SIGNAL(finished(int,QProcess::ExitStatus)),this,SIGNAL(finishControlling(int,QProcess::ExitStatus)));
    
}

void ServerControllerWorker::setPort(const QString &p)
{
    port=p;
}

void ServerControllerWorker::killonExit()
{
    if(process->isOpen ()){
        process->kill (); 
        this->killExitDone ();
    }
}

void ServerControllerWorker::forceKilling()
{
    if(process->isOpen ()){
        process->close ();
        this->killingDone ();
    }
}

void ServerControllerWorker::startProcessing()
{ 
    QStringList cmd;
    
#ifdef Q_OS_WIN
        auto prog=QDir::toNativeSeparators(qApp->applicationDirPath ()+"/grpc_camera.exe");
#else
        auto prog=QDir::toNativeSeparators(qApp->applicationDirPath ()+"/grpc_camera");    
#endif 
        
    cmd<<port;
    process->start (prog,cmd);
}

void ServerControllerWorker::handleAllOutput()
{
    this->readAllOutput (process->readAllStandardOutput ());
}

void ServerControllerWorker::handleAllOutError()
{
    this->readAllError (process->readAllStandardError ());
}
