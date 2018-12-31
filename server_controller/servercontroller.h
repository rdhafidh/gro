#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QThread>
#include <QScopedPointer>
class ServerControllerWorker;
class ServerController : public QObject
{
    Q_OBJECT
    QThread thread; 
    QScopedPointer<ServerControllerWorker> mcontroller;
public:
    explicit ServerController(QObject *parent = nullptr);
    ~ServerController(); 
    void setPort(const QString &port);
    
public Q_SLOTS:
    void forceKilling();
   void selesaiThread();
   void startProcessing(); 
   
Q_SIGNALS:
    void readAllOutput(const QByteArray &out);
    void readAllError(const QByteArray &err);
    void startControlling();
    void finishControlling(int code, QProcess::ExitStatus status);
    void killingDone();
    
    void askToKill();
    void askToStart();
    void setNewPort(const QString &port);
    void closeExit();
    
public slots:
};

class ServerControllerWorker: public QObject
{
    Q_OBJECT
    QScopedPointer<QProcess,QScopedPointerDeleteLater> process;
    QString port;
public:
    explicit ServerControllerWorker(QObject *parent =nullptr);
    ~ServerControllerWorker()=default;
   
Q_SIGNALS:
    void readAllOutput(const QByteArray &out);
    void readAllError(const QByteArray &err);
    void startControlling();
    void finishControlling(int code, QProcess::ExitStatus status);
    void killingDone();
    void killExitDone();
    
public Q_SLOTS:
    void forceKilling();
    void startProcessing(); 
    void setPort(const QString &p);
    void killonExit();
    
private Q_SLOTS:
    void handleAllOutput();
    void handleAllOutError();
};

#endif // SERVERCONTROLLER_H
