#include "cameraimageprovider.h"
#include <grpcclientbase.h>
#include "proto/image.grpc.pb.h" 

CameraImageProvider::CameraImageProvider() : QObject() { 
  camw = std::make_unique<CameraImageWorker>();
  camw->moveToThread(&thread);
  connect(camw.get(), &CameraImageWorker::emitConnectError, this,
          &CameraImageProvider::emitConnectError);
  connect(camw.get(), &CameraImageWorker::emitResult, this,
          &CameraImageProvider::emitResult);
  connect(camw.get(), &CameraImageWorker::emitServerCameraError, this,
          &CameraImageProvider::emitServerCameraError);
  connect(camw.get(), &CameraImageWorker::emitServerCameraNotFound, this,
          &CameraImageProvider::emitServerCameraNotFound);
  
  connect(&thread, &QThread::started,this,&CameraImageProvider::doStartWork);
  connect(this,&CameraImageProvider::doStartWork,camw.get (),&CameraImageWorker::doWork);
}

CameraImageProvider::~CameraImageProvider() {
  if (thread.isRunning()) {
    thread.requestInterruption();
    thread.quit();
    thread.wait(900);
  }
  camw->disconnect ();
}

void CameraImageProvider::setup(const QString &hostname) {
  if (camw->isHostNameSame(hostname)) return;
  if (thread.isRunning()) {
    thread.requestInterruption();
    thread.quit();
    thread.wait(900);
  }
  camw->setup(hostname);
}

void CameraImageProvider::doFetchImage() {
  if (!thread.isRunning()) {
    thread.start();
  }
  this->doStartWork ();
}

CameraImageWorker::CameraImageWorker(QObject *parent) : QObject(parent) {}

void CameraImageWorker::setup(const QString &hostname) {
  this->hostname = hostname;
}

bool CameraImageWorker::isHostNameSame(const QString &host) {
  return hostname == host;
}

void CameraImageWorker::doWork() { 
  int errorcode = 0;
  std::string rpl =
      GrpcClientBase::askImage(errorcode, this->hostname.toStdString());
  switch (errorcode) {
    case ImageProto::ImageResponse_EnumResponse_RESPONSE_OK:
      this->emitResult(QByteArray::fromStdString(rpl));
      break;
    case ImageProto::ImageResponse_EnumResponse_RESPONSE_CAMERA_NOT_FOUND:
      this->emitServerCameraNotFound();
      break;
    case ImageProto::ImageResponse_EnumResponse_RESPONSE_ERROR:
      this->emitServerCameraError();
      break;
    default:
      this->emitConnectError();
      break;
  }
}
