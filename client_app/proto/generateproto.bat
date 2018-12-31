set GRPC_TOOL_DIR=D:\masteraplikasi\transferh11nov\sodium\mingw\bin
set PROTO_FILE=image.proto
%GRPC_TOOL_DIR%\protoc.exe --grpc_out=. --cpp_out=. --plugin=protoc-gen-grpc=%GRPC_TOOL_DIR%\grpc_cpp_plugin.exe -I . %PROTO_FILE%
