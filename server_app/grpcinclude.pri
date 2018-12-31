GRPC_ROOTDIR=

HIDDEN_WARNING=
win32-g++{
GRPC_ROOTDIR=D:\masteraplikasi\transferh11nov\sodium\mingw
HIDDEN_WARNING= -Wno-unused-parameter
}
android{
GRPC_ROOTDIR=D:\masteraplikasi\transferh11nov\sodium\android-armv7-a
HIDDEN_WARNING= -Wno-unused-parameter
}
QMAKE_CXXFLAGS += $$HIDDEN_WARNING
win32:DEFINES += _WIN32_WINNT=0x601

SOURCES +=   $$files(proto/*.cc)
HEADERS +=  $$files(proto/*.h)

INCLUDEPATH += $$GRPC_ROOTDIR/include 
LIBS += -L$$GRPC_ROOTDIR/lib -lgrpc++ -lgrpc++_cronet \
        -lgrpc++_error_details -lgrpc++_reflection -lgrpc++_unsecure -lgrpc -lgpr -lcares -laddress_sorting -lprotobuf -lzlibstatic 
win32-g++{
LIBS += -lws2_32
}
