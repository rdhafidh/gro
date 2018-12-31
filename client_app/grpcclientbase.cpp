#include "grpcclientbase.h"

#include <grpcpp/grpcpp.h>
#include "proto/image.grpc.pb.h"
#include <QByteArray>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using ImageProto::ImageLogging;
using ImageProto::ImageRequest;
using ImageProto::ImageResponse;

class ImageClient {
 public:
  ImageClient(std::shared_ptr<Channel> channel)
      : stub_(ImageLogging::NewStub(channel)) {} 
  std::string AskImage(int &error_c) { 
    ImageRequest request; 
    ImageResponse reply; 
    ClientContext context;
 
    Status status = stub_->AskImage(&context, request, &reply);
 
    if (status.ok()) {
      error_c = reply.restype();
      return reply.data();
    }
    error_c = status.error_code();
    error_c = -error_c;
    return "";
  }

 private:
  std::unique_ptr<ImageLogging::Stub> stub_;
};

GrpcClientBase::GrpcClientBase() {}

std::string GrpcClientBase::askImage(int &errorCode,
                                     const std::string &hostname) {
  ImageClient greeter(grpc::CreateChannel(hostname.c_str(),
                                          grpc::InsecureChannelCredentials()));

  return greeter.AskImage (errorCode);  
}
