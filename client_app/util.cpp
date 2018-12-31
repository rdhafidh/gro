#include "util.h" 
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QtGlobal>
#include <cstdio>
#include <iostream>

bool Util::readFile(const QString &name,  std::string &buffer) {
  QFile fn(name);
  if (!fn.open(QIODevice::ReadOnly)) {
    return false;
  } 
  buffer = fn.readAll().toStdString();
  fn.close();
  return true;
}

bool Util::saveFile(const QString &fname, const std::string &buffer) {
  QFile fn(fname);
  if (!fn.open(QIODevice::WriteOnly)) {
    return false;
  }
  fn.write(buffer.c_str(), buffer.size());
  fn.close();
  return true;
} 

bool Util::logging(const QString &buffer) {
  QString pathfile = "";
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  auto pth = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  pathfile = pth + "/";
#endif
  pathfile += "logging.log";
  QFile fl(pathfile);
  if (!fl.open(QIODevice::WriteOnly | QIODevice::Append)) {
    return false;
  }
  QDateTime tm = QDateTime::currentDateTime();
  std::string buf = tm.toString("d/M/yyyy hh:m:s").toStdString() + " : " +
                    buffer.toStdString();
  buf.insert(0, "\n");
  buf += "\n";
  fl.write(buf.c_str(), buf.size());
  fl.close();
  return true;
}

QByteArray Util::readLog() {
  QString pathfile = "";
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  auto pth = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  pathfile = pth + "/";
#endif
  pathfile += "logging.log";
  QFile fl(pathfile);
  if (!fl.open(QIODevice::ReadOnly)) {
    return "";
  }
  QByteArray data = "";
  while (!fl.atEnd()) {
    data += fl.readLine();
  }
  return data;
}

bool Util::resetLog() {
  QString pathfile = "";
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  auto pth = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  pathfile = pth + "/";
#endif
  pathfile += "logging.log";
  return std::remove(pathfile.toStdString().c_str()) == 0;
}
