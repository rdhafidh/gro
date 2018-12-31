#include "imageitem.h"
#include <QImage>
#include <QQuickWindow>
#include <QSGImageNode>
#include <iostream>

ImageItem::ImageItem(QQuickItem *parent) : QQuickPaintedItem(parent) {
  setFlag(QQuickItem::ItemHasContents);
  if (!img.load(":/images/ic_perm_media_black_48dp.png", "PNG")) {
    std::cout << "\nsystem image load failed\n";
  }
}

void ImageItem::setImageBuffer(const QByteArray &buffer) {
  img = QImage::fromData(buffer, "PNG");
  if (img.isNull()) {
    if (!img.load(":/images/ic_perm_media_black_48dp.png", "PNG")) {
      std::cout << "\nsystem image load failed\n";
    }
  }
  update();
}

void ImageItem::paint(QPainter *painter) {
  painter->drawImage(x()-25, y(),
                     img.scaled(implicitWidth(), implicitHeight()));
}
