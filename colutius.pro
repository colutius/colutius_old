QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cc \
    src/server.cc \
    src/socket.cc \
    src/ui/config.cc \
    src/ui/loginwidget.cc \
    src/ui/mainwidget.cc \

HEADERS += \
    src/server.hh \
    src/socket.hh \
    src/ui/config.hh \
    src/ui/loginwidget.hh \
    src/ui/mainwidget.hh \

FORMS += \
    src/ui/config.ui \
    src/ui/loginwidget.ui \
    src/ui/mainwidget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resource/resource.qrc

DISTFILES += \
    src/resource/img/logo.rc

RC_FILE += \
    src/resource/img/logo.rc