#ifndef UTILQML_H
#define UTILQML_H

#include <QObject>

class UtilQML : public QObject
{
    Q_OBJECT
public:
    explicit UtilQML(QObject *parent = nullptr); 
    Q_INVOKABLE bool saveFile(const QString &fname,const QByteArray &buffer);
     
    Q_INVOKABLE bool logging(const QString &buffer);
    Q_INVOKABLE QByteArray readLog();
    Q_INVOKABLE bool resetLog();
signals:
    
public slots:
};

#endif // UTILQML_H
