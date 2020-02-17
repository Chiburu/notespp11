#ifndef NOTESPP11_VERSION_H
#define NOTESPP11_VERSION_H

#include "notespp11_global.h"

namespace notespp11 {

class NOTESPP11_EXPORT Version
{
public:
  static uint major();
  static uint minor();
  static uint patch();
  static const char *ver();
};

} // namespace notespp11

#endif // NOTESPP11_VERSION_H
