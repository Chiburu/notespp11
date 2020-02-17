
# プラットフォーム共通設定

INCLUDEPATH += $$(NOTES_C_API_PATH)/include
DEPENDPATH += $$(NOTES_C_API_PATH)/include
LIBS += -lnotes

DEFINES += PRODUCTION_VERSION

# Linux、Windows共通設定
!macx {
  DEFINES += W32 W DTRACE
}

# Linux、Mac共通設定
!win32 {
  DEFINES += HANDLE_IS_32BITS LARGE64_FILES OVERRIDEDEBUG

  # Windows以外はNotes/Dominoの実行環境をNotesPathに指定する。
  LIBS += -L$$(NOTES_EXEC_PATH)
}

# Windows設定
win32 {
  DEFINES += NT _CRT_SECURE_NO_WARNINGS DUMMY
  QMAKE_CXXFLAGS += -wd4503 -wd4005

  contains(QMAKE_TARGET.arch, x86_64) {
    DEFINES += W64 ND64 _AMD64_ ND64SERVER

  # Windowsではインポートライブラリの場所を以下に指定する。
    LIBS += -L$$(NOTES_C_API_PATH)/lib/mswin64
  }
  else {
    DEFINES += ND32 _X86_
  # Windowsではインポートライブラリの場所を以下に指定する。
    LIBS += -L$$(NOTES_C_API_PATH)/lib/mswin32
  }
}

# Mac設定
else:macx {
  DEFINES += MAC MAC_OSX MAC_CARBON NO_NULL_VTABLE_ENTRY \
    __CF_USE_FRAMEWORK_INCLUDES__ TARGET_API_MAC_CARBON
  DEFINES += LONGIS64BIT
}

# Linux設定
else:unix {
  DEFINES += UNIX LINUX LINUX86 GCC3 GCC4 GCC_LBLB_NOT_SUPPORTED \
    PTHREAD_KERNEL _REENTRANT USE_THREADSAFE_INTERFACES \
    _POSIX_THREAD_SAFE_FUNCTIONS HAS_IOCP HAS_BOOL HAS_DLOPEN \
    USE_PTHREAD_INTERFACES _LARGEFILE_SOURCE _LARGEFILE64_SOURCE
  specs = $$split(QMAKESPEC, /)
  contains(specs, gcc_64): {
    DEFINES += ND64 LINUX64 LINUX86_64 NDUNIX64 LONGIS64BIT
  }

  # Linuxでは以下の指定も必要。
  LIBS += -Wl,-rpath,$$(NOTES_EXEC_PATH)
}
