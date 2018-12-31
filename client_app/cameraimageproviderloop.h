#ifndef CAMERAIMAGEPROVIDERLOOP_H
#define CAMERAIMAGEPROVIDERLOOP_H

#include <QBasicTimer>
#include <QObject>
#include <QScopedPointerDeleteLater>  
#include <cameraimageprovider.h>

class CameraImageProviderLoop : public QObject {
  Q_OBJECT
  QBasicTimer timer; 
  QScopedPointer<CameraImageProvider,QScopedPointerDeleteLater> camdy; 
 public:
  explicit CameraImageProviderLoop(QObject *parent = nullptr);
  ~CameraImageProviderLoop()=default;

  Q_INVOKABLE void setup(const QString &hostname);
 Q_SIGNALS:
  void emitResult(const QByteArray &buffer);
  void emitConnectError();
  void emitServerCameraNotFound();
  void emitServerCameraError();

 public Q_SLOTS:
  void startAsking();
  void stopAsking();

 protected:
  void timerEvent(QTimerEvent *evt) override;
   
};

#endif  // CAMERAIMAGEPROVIDERLOOP_H
