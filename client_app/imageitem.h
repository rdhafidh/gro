#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QQuickPaintedItem>
#include <memory> 
#include <QPainter>
#include <QImage>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT 
    QImage img;
public:
    ImageItem(QQuickItem *parent=nullptr);
    ~ImageItem()=default;
    
signals:
    
public slots:
    void setImageBuffer(const QByteArray &buffer); 
protected:
    void paint (QPainter *painter)override;
};

#endif // IMAGEITEM_H
