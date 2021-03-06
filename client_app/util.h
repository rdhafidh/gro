#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <string>

class Util
{
public:
    Util()=default;
    ~Util()=default;
    static bool readFile(const QString &name, std::string &buffer);
    static bool saveFile(const QString &fname,const std::string &buffer);
     
    static bool logging(const QString &buffer);
    static QByteArray readLog();
    static bool resetLog();
    
};

#endif // UTIL_H
