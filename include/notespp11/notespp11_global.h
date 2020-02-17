#ifndef NOTESPP11_GLOBAL_H
#define NOTESPP11_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NOTESPP11_LIBRARY)
#  define NOTESPP11_EXPORT Q_DECL_EXPORT
#else
#  define NOTESPP11_EXPORT Q_DECL_IMPORT
#endif

#endif // NOTESPP11_GLOBAL_H
