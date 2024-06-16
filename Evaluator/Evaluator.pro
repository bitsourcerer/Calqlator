CONFIG -= qt

TEMPLATE = lib
DEFINES += EVALUATOR_LIBRARY EVALUATOR_EXPORTS

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dllmain.cpp \
	src/common.cpp src/Evaluator.cpp src/Parser.cpp \
	src/SyntaxTree.cpp src/Precedence.cpp src/Expression.cpp \
	src/utility.cpp

HEADERS += \
    API.h \
	framework.h \
	include/common.h include/Evaluator.h include/Parser.hpp \
	include/SyntaxTree.hpp include/Precedence.hpp include/Expression.hpp \
	include/utility.hpp \
        Stack.hpp \
    includes.h

INCLUDEPATH += include/
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# ./%{JS: Util.asciify("build-%{Project:Name}-%{Kit:FileSystemName}-%{BuildConfig:Name}")}
