#ifndef ZREST_LANGUAGES_HPP
#define ZREST_LANGUAGES_HPP
#include <libintl.h>
namespace zrestlang
{
#define _(String) gettext(String)

int init_languages(void);
}
#endif
