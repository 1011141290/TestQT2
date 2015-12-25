TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += static

QMAKE_CXXFLAGS += -fpermissive

//DEFINES += ARMA_USE_BLAS
//DEFINES += ARMA_USE_LAPACK
DEFINES += BOOST_THREAD_USE_LIB
DEFINES += ARMA_32BIT_WORD


//INCLUDEPATH += $$PWD/code/include

INCLUDEPATH += $$PWD/include/boost-1_59
INCLUDEPATH += $$PWD/include/arma-6_2
INCLUDEPATH += $$PWD/include/dlib-18.18


win32:LIBS += $$PWD/lib/blasLapack/blas_win32_MT.lib
win32:LIBS += $$PWD/lib/blasLapack/lapack_win32_MT.lib

win32:LIBS += $$PWD/lib/boost/libboost_system-mgw48-mt-d-1_59.a
win32:LIBS += $$PWD/lib/boost/libboost_thread-mgw48-mt-d-1_59.a

//win32:LIBS += $$PWD/lib/boost/libboost_thread-vc120-mt-1_59.lib

SOURCES += \
    ArmaTester.cpp \
    Cluster.cpp \
    ClusterMembership.cpp \
    ClusterMembershipSet.cpp \
    ClusterSet.cpp \
    DataSet.cpp \
    EvalIndex.cpp \
    GAmatrix.cpp \
    GAmatrixSet.cpp \
    OnceRunResult.cpp \
    RandomDice.cpp \
    Record2.cpp \
    RecordSet2.cpp \
    Runner.cpp \
    RunnerTester.cpp \
    stdafx.cpp \
    TestDlib.cpp \
    TestingBoost.cpp \
    TestMatrix.cpp \
    TestPtime.cpp \
    TestVector.cpp \
    XDataTester.cpp \
    LogFile.cpp \
    AverResult.cpp

HEADERS += \
    ArmaTester.h \
    Cluster.h \
    ClusterMembership.h \
    ClusterMembershipSet.h \
    ClusterSet.h \
    DataSet.h \
    EvalIndex.h \
    GAmatrix.h \
    GAmatrixSet.h \
    OnceRunResult.h \
    RandomDice.h \
    Record2.h \
    RecordSet2.h \
    resource.h \
    Runner.h \
    RunnerTester.h \
    stdafx.h \
    targetver.h \
    TestDlib.h \
    TestMatrix.h \
    TestPtime.h \
    TestVector.h \
    XDataTester.h \
    LogFile.h \
    AveResult.h

