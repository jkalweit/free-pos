CONFIG += c++11 printsupport

TEMPLATE = app

QT += qml quick widgets printsupport

SOURCES += main.cpp \
    FreePosServer.cpp \
    SimpleServer.cpp \
    singleapplication.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    FreePosServer.h \
    SimpleServer.h \
    singleapplication.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../free-pos-common/release/ -lfree-pos-common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../free-pos-common/debug/ -lfree-pos-common
else:unix: LIBS += -L$$OUT_PWD/../free-pos-common/ -lfree-pos-common

INCLUDEPATH += $$PWD/../free-pos-common
DEPENDPATH += $$PWD/../free-pos-common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-pos-common/release/libfree-pos-common.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-pos-common/debug/libfree-pos-common.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-pos-common/release/free-pos-common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../free-pos-common/debug/free-pos-common.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../free-pos-common/libfree-pos-common.a

OTHER_FILES += \
    TODO.txt
