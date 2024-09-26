TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

DISTFILES += \
    test.txt

LIBS += -lwinmm

#CONFIG(debug, debug | release) {
#    DESTDIR = $$OUT_PWD/debug
#} else {
#    DESTDIR = $$OUT_PWD/release
#}
#QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt.exe $$shell_quote($$DESTDIR/$$shell_quote($$TARGET).exe) --no-compiler-runtime
