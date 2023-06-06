QT += core gui widgets sql
TEMPLATE = app
CONFIG += c++11
SOURCES = mainwindow.cpp \
    data_time.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    memo.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    progresssettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    slidersettingseditor.cpp \
    radiobuttonsettingseditor.cpp \
    to_do_event.cpp \
    togglesettingseditor.cpp \
    textfieldsettingseditor.cpp \
    tabssettingseditor.cpp \
    snackbarsettingseditor.cpp \
    dialogsettingseditor.cpp \
    drawersettingseditor.cpp \
    scrollbarsettingseditor.cpp \
    appbarsettingseditor.cpp \
    autocompletesettingseditor.cpp \
    menusettingseditor.cpp
HEADERS = mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    data_time.h \
    fabsettingseditor.h \
    memo.h \
    raisedbuttonsettingseditor.h \
    flatbuttonsettingseditor.h \
    iconbuttonsettingseditor.h \
    progresssettingseditor.h \
    circularprogresssettingseditor.h \
    slidersettingseditor.h \
    radiobuttonsettingseditor.h \
    to_do_event.h \
    togglesettingseditor.h \
    textfieldsettingseditor.h \
    tabssettingseditor.h \
    snackbarsettingseditor.h \
    dialogsettingseditor.h \
    drawersettingseditor.h \
    scrollbarsettingseditor.h \
    appbarsettingseditor.h \
    autocompletesettingseditor.h \
    menusettingseditor.h
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = examples-exe
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    memo.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    snackbarsettingsform.ui \
    radiobuttonsettingsform.ui \
    togglesettingsform.ui \
    textfieldsettingsform.ui \ 
    tabssettingsform.ui \
    dialogsettingsform.ui \
    drawersettingsform.ui \
    scrollbarsettingsform.ui \
    appbarsettingsform.ui
