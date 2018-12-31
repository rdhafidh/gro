#include "cameraimageproviderloop.h" 
#include <QTimerEvent>

CameraImageProviderLoop::CameraImageProviderLoop(QObject *parent)
    : QObject(parent),camdy(new CameraImageProvider) {
  connect(camdy.get(), &CameraImageProvider::emitResult, this,
          &CameraImageProviderLoop::emitResult);
  connect(camdy.get(), &CameraImageProvider::emitConnectError, this,
          &CameraImageProviderLoop::emitConnectError);
  connect(camdy.get(), &CameraImageProvider::emitServerCameraError, this,
          &CameraImageProviderLoop::emitServerCameraError);
  connect(camdy.get(), &CameraImageProvider::emitServerCameraNotFound, this,
          &CameraImageProviderLoop::emitServerCameraNotFound); 
  
  connect(camdy.get(), &CameraImageProvider::emitConnectError, this,
          &CameraImageProviderLoop::stopAsking);
  connect(camdy.get(), &CameraImageProvider::emitServerCameraError, this,
          &CameraImageProviderLoop::stopAsking);
  connect(camdy.get(), &CameraImageProvider::emitServerCameraNotFound, this,
          &CameraImageProviderLoop::stopAsking); 
}

void CameraImageProviderLoop::setup(const QString &hostname) {
  camdy->setup(hostname);
}

void CameraImageProviderLoop::startAsking() {
  timer.start(500, this);
  camdy->doFetchImage();
}

void CameraImageProviderLoop::stopAsking() {
  if (timer.isActive()) {
    timer.stop();
  }
}

void CameraImageProviderLoop::timerEvent(QTimerEvent *evt) {
  if (evt->timerId() == timer.timerId()) {
    camdy->doFetchImage();
  } else {
    QObject::timerEvent(evt);
  }
}
