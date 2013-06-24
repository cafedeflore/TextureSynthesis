#-------------------------------------------------
#
# Project created by QtCreator 2013-06-04T19:28:15
#
#-------------------------------------------------

QT       += core gui

TARGET = textureSynthesis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    texture.cpp \
    imageConversion.cpp \
    neighbor.cpp \
    test.cpp \
    texture.cpp \
    test.cpp \
    rectneighbor.cpp \
    neighbor.cpp \
    mainwindow.cpp \
    main.cpp \
    l2texture.cpp \
    l2neighbor.cpp \
    imageConversion.cpp

HEADERS  += mainwindow.h \
    texture.h \
    imageConversion.h \
    neighbor.h \
    texture.h \
    test.h \
    rectneighbor.h \
    neighbor.h \
    mainwindow.h \
    l2texture.h \
    l2neighbor.h \
    imageConversion.h

FORMS    += mainwindow.ui

INCLUDEPATH+= D:\usr\opencv\build\include \
D:\usr\opencv\build\include\opencv \
D:\usr\opencv\build\include\opencv2 \
D:\usr\ANN\include

#LIBS+= D:\usr\opencv\build\x86\vc10\lib\opencv_core243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_imgproc243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_highgui243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_ml243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_video243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_features2d243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_calib3d243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_objdetect243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_contrib243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_legacy243d.lib \
#D:\usr\opencv\build\x86\vc10\lib\opencv_flann243d.lib

LIBS+= D:\usr\opencv\build\x86\vc10\lib\opencv_core243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_imgproc243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_highgui243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_ml243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_video243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_features2d243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_calib3d243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_objdetect243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_contrib243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_legacy243.lib \
D:\usr\opencv\build\x86\vc10\lib\opencv_flann243.lib \
D:\usr\ANN\ANN.lib

OTHER_FILES += \
    textureSynthesis.pro
