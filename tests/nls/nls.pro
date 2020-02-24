QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
  nlstest.cpp \
  test_countString1.cpp \
  test_countString2.cpp \
  test_lmbcsToUnicode.cpp \
  test_unicodeToLmbcs.cpp

HEADERS += \
  nlstest.h

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
# ライブラリはutf-8エンコーディング、ヘッダーオンリーなので、Windows(Visual C++)では以下のフラグが必須。
#
win32: QMAKE_CXXFLAGS += /utf-8 /bigobj

#
# プロジェクト内のライブラリをインクルードする。
INCLUDEPATH += ../../include
DEPENDPATH += ../../include
