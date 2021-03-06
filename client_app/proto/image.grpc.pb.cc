// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: image.proto

#include "image.pb.h"
#include "image.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace ImageProto {

static const char* ImageLogging_method_names[] = {
  "/ImageProto.ImageLogging/AskImage",
};

std::unique_ptr< ImageLogging::Stub> ImageLogging::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ImageLogging::Stub> stub(new ImageLogging::Stub(channel));
  return stub;
}

ImageLogging::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AskImage_(ImageLogging_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ImageLogging::Stub::AskImage(::grpc::ClientContext* context, const ::ImageProto::ImageRequest& request, ::ImageProto::ImageResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AskImage_, context, request, response);
}

void ImageLogging::Stub::experimental_async::AskImage(::grpc::ClientContext* context, const ::ImageProto::ImageRequest* request, ::ImageProto::ImageResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AskImage_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::ImageProto::ImageResponse>* ImageLogging::Stub::AsyncAskImageRaw(::grpc::ClientContext* context, const ::ImageProto::ImageRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::ImageProto::ImageResponse>::Create(channel_.get(), cq, rpcmethod_AskImage_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::ImageProto::ImageResponse>* ImageLogging::Stub::PrepareAsyncAskImageRaw(::grpc::ClientContext* context, const ::ImageProto::ImageRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::ImageProto::ImageResponse>::Create(channel_.get(), cq, rpcmethod_AskImage_, context, request, false);
}

ImageLogging::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ImageLogging_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ImageLogging::Service, ::ImageProto::ImageRequest, ::ImageProto::ImageResponse>(
          std::mem_fn(&ImageLogging::Service::AskImage), this)));
}

ImageLogging::Service::~Service() {
}

::grpc::Status ImageLogging::Service::AskImage(::grpc::ServerContext* context, const ::ImageProto::ImageRequest* request, ::ImageProto::ImageResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ImageProto

