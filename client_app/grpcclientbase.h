#ifndef GRPCCLIENTBASE_H
#define GRPCCLIENTBASE_H

#include <iostream>

class GrpcClientBase
{
public:
    GrpcClientBase();
    static std::string askImage(int &errorCode,const std::string &hostname);
};

#endif // GRPCCLIENTBASE_H
