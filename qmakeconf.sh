#!/bin/bash

MODULES="QT += widgets sql"

CONFIG="CONFIG += debug_and_release"

RELEASE_DIR="Release:DESTDIR = release"
DEBUG_DIR="Debug:DESTDIR = debug"

UI_DIR="UI_DIR = src/gui/ui"

INCLUDEPATH="INCLUDEPATH += /usr/include/QuaZip-Qt5-1.4/ src/"
LIBS="LIBS += -lquazip1-qt5"

qmake -project "$MODULES" "$CONFIG" "$RELEASE_DIR" "$DEBUG_DIR" "$UI_DIR" "$INCLUDEPATH" "$LIBS"
qmake
