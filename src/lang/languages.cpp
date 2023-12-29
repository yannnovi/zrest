#include "languages.hpp"
#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <libintl.h>
#endif
#include <locale.h>
#include <iostream>
int zrestlang::init_languages(void)
{
  #ifndef WIN32
  setlocale (LC_ALL, "fr_CA");
  bindtextdomain ("zrestlang", "locale/");
  textdomain ("zrestlang");
  #endif
  return 0;
}

#ifdef WIN32
char* zrestlang::gettext(const char* str) {
  return strdup(str);
}
#endif