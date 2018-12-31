#include "utilqml.h"
#include <util.h>

UtilQML::UtilQML(QObject *parent) : QObject(parent) {}
  
bool UtilQML::saveFile(const QString &fname, const QByteArray &buffer) {
  return Util::saveFile(fname, buffer.toStdString ());
}

bool UtilQML::logging(const QString &buffer) { return Util::logging(buffer); }

QByteArray UtilQML::readLog() { return Util::readLog(); }

bool UtilQML::resetLog() { return Util::resetLog(); }
