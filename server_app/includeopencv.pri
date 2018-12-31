OPENCVDIR=

win32-g++{
    OPENCVDIR=D:\masteraplikasi\transferh11nov\sodium\mingw
    LIBS += -L$$OPENCVDIR/x86/mingw/lib -lopencv_videoio401 -lopencv_video401 -lopencv_imgcodecs401 -lopencv_imgproc401 -lopencv_core401 
}

android{

}

INCLUDEPATH += $$OPENCVDIR/include 
