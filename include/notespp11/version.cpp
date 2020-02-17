#include "version.h"

#define STRING(str) #str

namespace notespp11 {

uint Version::major()
{
  return PROJECT_VER_MAJ;
}

uint Version::minor()
{
  return PROJECT_VER_MIN;
}

uint Version::patch()
{
  return PROJECT_VER_PAT;
}

const char *Version::ver()
{
  return STRING(PROJECT_VERSION);
}

} // namespace notespp11
