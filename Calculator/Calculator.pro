QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    output.cpp \
    prompt.cpp

HEADERS += \
    mainwindow.hpp \
    output.hpp \
    prompt.hpp

FORMS += \
    mainwindow.ui \
    output.ui \
    prompt.ui

EVALUATORPATH = $$PWD/../Evaluator
INCLUDEPATH += $$EVALUATORPATH
DEPENDPATH += $$EVALUATORPATH

win32 {
CONFIG(debug, debug|release) {
    DLLPATH = $$EVALUATORPATH/bin/debug
        DESTDIR = $$OUT_PWD/debug
} else {
    DLLPATH = $$EVALUATORPATH/bin/release
        DESTDIR = $$OUT_PWD/release
}

LIBS += -L$$DLLPATH -lEvaluator
QMAKE_POST_LINK += $$quote(copy /Y $$DLLPATH/Evaluator.dll $$DESTDIR)
}

unix {
CONFIG(debug, debug|release) {
    SOPATH = $$EVALUATORPATH/bin/debug
    DESTDIR = $$OUT_PWD/debug
} else {
    SOPATH = $$EVALUATORPATH/bin/release
    DESTDIR = $$OUT_PWD/release
}

LIBS += -L$$SOPATH -lEvaluator
QMAKE_POST_LINK += $$quote(cp -f $$SOPATH/libEvaluator.so $$DESTDIR)
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
