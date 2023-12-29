#ifndef ZREST_LANGUAGES_HPP
#define ZREST_LANGUAGES_HPP
#ifndef WIN32
#include <libintl.h>
#endif
namespace zrestlang
{
#ifdef WIN32
char* gettext(const char* str); 
#define _(String) String
#else
#define _(String) gettext(String)
#endif
int init_languages(void);
}
#endif
