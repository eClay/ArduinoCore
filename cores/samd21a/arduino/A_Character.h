#ifndef ARDUINO_CHARACTER_H
#define ARDUINO_CHARACTER_H

#include <ctype.h>

#define isAlpha(c)              (isalpha(c) ? true : false)
#define isAlphaNumeric(c)       (isalnum(c) ? true : false)
#define isAscii(c)              (isascii(c) ? true : false)
#define isControl(c)            (iscntrl(c) ? true : false)
#define isDigit(c)              (isdigit(c) ? true : false)
#define isGraph(c)              (isgraph(c) ? true : false)
#define isHexadecimalDigit(c)   (isxdigit(c) ? true : false)
#define isLowerCase(c)          (islower(c) ? true : false)
#define isPrintable(c)          (isprint(c) ? true : false)
#define isPunct(c)              (ispunct(c) ? true : false)
#define isSpace(c)              (isspace(c) ? true : false)
#define isUpperCase(c)          (isupper(c) ? true : false)
#define isWhitespace(c)         (isblank(c) ? true : false)

#define toAscii(c)              (toascii(c))
#define toLowerCase(c)          (tolower(c))
#define toUpperCase(c)          (toupper(c))

#endif  // ARDUINO_CHARACTER_H
