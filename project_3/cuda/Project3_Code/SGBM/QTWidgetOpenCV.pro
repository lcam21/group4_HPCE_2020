#-------------------------------------------------
#
# Project created by QtCreator 2019-08-21T14:19:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTWidgetOpenCV
TEMPLATE = app

unix:INCLUDEPATH += /usr/local/lib
unix:INCLUDEPATH += /usr/lib

unix:LIBS += `pkg-config opencv4 --cflags --libs`
unix:LIBS += -L/usr/lib
unix:LIBS += -L/usr/local/lib


unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_calib3d -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lgomp

unix:INCLUDEPATH += /usr/local/include/opencv4/
unix:DEPENDPATH += /usr/local/include/opencv4/


win32:INCLUDEPATH += ..\install\include

win32:LIBS += ..\install\x86\mingw\bin\libopencv_core410.dll
win32:LIBS += ..\install\x86\mingw\bin\libopencv_highgui410.dll
win32:LIBS += ..\install\x86\mingw\bin\libopencv_imgcodecs410.dll
win32:LIBS += ..\install\x86\mingw\bin\libopencv_imgproc410.dll
win32:LIBS += ..\install\x86\mingw\bin\libopencv_features2d410.dll
win32:LIBS += ..\install\x86\mingw\bin\libopencv_calib3d410.dll

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        diff_and_error.cpp \
        histogram.cpp \
        main.cpp \
        mainwindow.cpp \
        stereoalgo.cpp \
    sgbm.cpp

HEADERS += \
        diff_and_error.h \
        histogram.h \
        mainwindow.h \
        stereoalgo.h \
    sgbm.h

FORMS += \
        mainwindow.ui

#unix|win32: LIBS += -lueye_api

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

# remove possible other optimization flags
QMAKE_CXXFLAGS_DEBUG -= -O
QMAKE_CXXFLAGS_DEBUG -= -O1
QMAKE_CXXFLAGS_DEBUG -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_DEBUG *= -O3 -fopenmp

#QMAKE_CXXFLAGS += -mfpu=neon -mfloat-abi=hard

DISTFILES += \
    README.md \
    cuda_interface.cu

# cuda source
CUDA_SOURCES += cuda_interface.cu

# Path to cuda toolkit install
CUDA_DIR = /usr/local/cuda
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64

# GPU architecture
CUDA_ARCH = sm_30

# NVCC flags
NVCCFLAGS = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

# Path to libraries
LIBS += -lcudart -lcuda

# join the includes in a line
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS $$CUDA_INC $$LIBS ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
cuda.dependcy_type = TYPE_C
cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS      ${QMAKE_FILE_NAME}

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o

# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cuda
