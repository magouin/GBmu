QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:PATH = "$$_PRO_FILE_PWD_\\"
unix:PATH = "$$_PRO_FILE_PWD_/"

win32:EXEC_PATH = "$$_PRO_FILE_PWD_\\..\\Windows\\GBmu.exe"
unix:EXEC_PATH = "$$_PRO_FILE_PWD_/../MacosX/GBmu"

win32:ROM_PATH = "$$_PRO_FILE_PWD_\\..\\roms"
unix:ROM_PATH = "$$_PRO_FILE_PWD_/../roms"

VPATH += $$absolute_path("srcs", $$PATH)
INC_PATH = $$absolute_path("incs", $$PATH)

DEFINES += EXEC_PATH=\\\"$$EXEC_PATH\\\"
DEFINES += ROM_PATH=\\\"$$ROM_PATH\\\"

INCLUDEPATH += $$INC_PATH

SOURCES += \
    debugwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    $$absolute_path("debugwindow.h", $$INC_PATH) \
    $$absolute_path("mainwindow.h", $$INC_PATH) \

FORMS += \
    forms/mainwindow.ui

TARGET = GBmu

win32:DESTDIR = "$$_PRO_FILE_PWD_\\.."
unix:DESTDIR = "$$_PRO_FILE_PWD_/.."

target.path = $$DESTDIR
message($$target.path)
!isEmpty($$target.path): INSTALLS += target
