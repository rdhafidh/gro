#ifndef CAMERAIMAGEPROVIDER_H
#define CAMERAIMAGEPROVIDER_H

#include <QObject>
#include <QThread>
#include <memory>

class CameraImageWorker;
class CameraImageProvider final : public QObject {
  Q_OBJECT
  std::unique_ptr<CameraImageWorker> camw;
  QThread thread;

 public:
  CameraImageProvider();
  ~CameraImageProvider();
   void setup(const QString &hostname);

 Q_SIGNALS:
  void emitResult(const QByteArray &buffer);
  void emitConnectError();
  void emitServerCameraNotFound();
  void emitServerCameraError();
  
  void doStartWork();

 public Q_SLOTS:
  void doFetchImage();
};

class CameraImageWorker final : public QObject {
  Q_OBJECT

  QString hostname; 
 public:
  CameraImageWorker(QObject *parent = 0);
  ~CameraImageWorker() = default;
  void setup(const QString &hostname);
  bool isHostNameSame(const QString &host);

 Q_SIGNALS:
  void emitResult(const QByteArray &buffer);
  void emitConnectError();
  void emitServerCameraNotFound();
  void emitServerCameraError();

 public Q_SLOTS:
  void doWork();
};

#endif  // CAMERAIMAGEPROVIDER_H
