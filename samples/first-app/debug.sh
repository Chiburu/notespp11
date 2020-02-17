#!/bin/sh

# ビルドしたファイルを実行環境にコピーして、スタートアップ登録する。
# 要 ルート権限
# sudo ./debug.sh

lotus=/opt/ibm/domino
domino_exec=$lotus/notes/latest/linux
prog_bin=$lotus/bin

exe_file=first-app
bin_folder=/media/psf/Home/Documents/QtProjects/build/notespp11-Desktop9_Qt_5_12_4_GCC_64bit-Debug/samples/first-app

cp $bin_folder/$exe_file $domino_exec/$exe_file
ln -s $prog_bin/tools/startup $prog_bin/$exe_file

# 以下、ターミナルで実行
# su notes
# cd /local/notesdata
# /opt/ibm/domino/bin/first-app

