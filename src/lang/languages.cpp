#include "languages.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>
#include <iostream>
int zrestlang::init_languages(void)
{
  setlocale (LC_ALL, "fr_CA");
  bindtextdomain ("zrestlang", "locale/");
  textdomain ("zrestlang");
  return 0;
}