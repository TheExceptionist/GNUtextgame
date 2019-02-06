#ifndef CONSOLE_H
#define CONSOLE_H

#include "defs.h"

enum
{
    FALSE,
    TRUE  
};

enum
{
    ACCEPT,
    STORE,
    ACCEPT_INT,
    EXIT_CODE = -100
};

enum
{
    FORE_BLACK = 30,
    FORE_RED,
    FORE_GREEN,
    FORE_YELLOW,
    FORE_BLUE,
    FORE_MAGENTA,
    FORE_CYAN,
    FORE_WHITE
};

enum
{
    BACK_BLACK = 40,
    BACK_RED,
    BACK_GREEN,
    BACK_YELLOW,
    BACK_BLUE,
    BACK_MAGENTA,
    BACK_CYAN,
    BACK_WHITE
};

enum
{
    RESET,
    BOLD,
    UNDERLINE = 4,
    INVERSE = 7,
    BOLD_OFF = 21,
    UNDERLINE_OFF = 24,
    INVERSE_OFF = 27
};

enum
{
    NO_RANGE = -333
};

static const std::string ESCAPE = "\033";
static const std::string ESCAPE_COLOR = "\033[";

namespace e_std
{
    typedef uint8_t e_byte;
    typedef uint16_t e_halfword;
    typedef uint32_t e_word;
    typedef uint64_t e_doubleword;

    typedef int8_t e_int8;
    typedef int16_t e_int16;
    typedef int32_t e_int32;
    typedef int64_t e_int64;

    typedef const char* e_str;
    typedef e_byte e_bool;

	bool accept(const std::string question, const std::string match);
	void store(const std::string question, std::string* storeTo);
    int acceptIntln(const std::string question, const int range_bottom, const int range_top);
    int acceptInt(const std::string question, const int range_bottom, const int range_top);
    int loopAccept(const std::string question, const std::string match, std::string* storeTo, const int type, const int range_bottom = NO_RANGE, const int range_top = NO_RANGE);
    void println(const std::string str);
    void print(const std::string str);
    int randInt(int min, int max);
    void setColor(const int fore_color, const int back_color);
    void setFore(const int fore_color);
    void setTextAppearance(const int choice);
    void resetText();
    void fill(const int num_spaces, const char c);
    void offset(const int amount);
    void printOffset(const int amount, const std::string str);
    void printlnOffset(const int amount, const std::string str);
    void resetColor();
    //Unix systems only
    void clear();
}
#endif