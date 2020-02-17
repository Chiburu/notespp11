QT -= gui

TEMPLATE = lib
DEFINES += NOTESPP11_LIBRARY

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

SOURCES += \
    version.cpp

HEADERS += \
    notes/global.hpp \
    notespp11_global.h \
    version.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32: QMAKE_CXXFLAGS += /utf-8 /bigobj

#
# Notes C API Settings
#
# 環境変数の準備
#
# NOTES_C_API_PATH: Notes C APIのルートパスを指定します。
# NOTES_EXEC_PATH: Notes/Dominoのプログラムディレクトリを指定します。
#  Linux: Dominoサーバへのパス、通常/opt/ibm/domino/notes/latest/linux
#  Mac: Notesクライアントへのパス、通常'/Applications/IBM Notes.app/Contents/MacOS'
#  Windows: 不要、リンク時はAPIのインポートライブラリを使用。実行時にパスで解決する。
#
include(../../notes-c-api.pri)

#
# バージョン設定
#
TargetProduct = NotesPP11
TargetDescription = NotesPP11 Library
TargetVersion = 0.0.0
TargetCompany = Chiburu Systems
TargetDomain = chiburu.com
TargetCopyright = 2020 Chiburu Systems
include(../../version.pri)
