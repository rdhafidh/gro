#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "proto/image.grpc.pb.h"
  
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using ImageProto::ImageLogging;
using ImageProto::ImageRequest;
using ImageProto::ImageResponse;
 
class ServerHandler final : public ImageLogging::Service {
  std::string readSingleFrame() {
    if (!cap.isOpened()) {
      return std::string();
    }
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      return std::string();
    }
    std::vector<uint8_t> buffer;
    cv::imencode(".png", frame, buffer); 
    std::string str;
    std::move(buffer.begin (),buffer.end (),std::back_inserter(str));
    return str;
  }
  
  Status AskImage(ServerContext*, const ImageProto::ImageRequest*,
                  ImageProto::ImageResponse* response) override {
    if (!cap.isOpened()) {
      if (!cap.open(0, cv::CAP_ANY)) {
        response->set_restype(
            ImageProto::ImageResponse_EnumResponse_RESPONSE_CAMERA_NOT_FOUND);
      } else {
        response->set_data(readSingleFrame());
        response->set_restype(
            ImageProto::ImageResponse_EnumResponse_RESPONSE_OK);
      }
    } else {
      response->set_data(readSingleFrame());
      response->set_restype(ImageProto::ImageResponse_EnumResponse_RESPONSE_OK);
    }
    return Status::OK;
  } 
  cv::VideoCapture cap;
};


void RunServer(const std::string &port) {
  std::string server_address("0.0.0.0:");
  server_address+=port;
  ServerHandler service;

  ServerBuilder builder; 
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials()); 
  builder.RegisterService(&service); 
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
 
  server->Wait();
}

int main(int , char**agv) {
  std::string portd="50051";
  if(agv[1]!=nullptr){
	  portd.assign(agv[1]);
  }
  RunServer(portd);
  return 0;
}
