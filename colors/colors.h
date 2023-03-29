/*
    MIT License

    Copyright (c) 2023 Angus Barnes

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdio.h>

/* 
* These are functions specific to use on the linux platfrom.
* Unix and POSIX platforms define terminal color modes which can
* be set using escapre sequences on the standard output stream.
* These are not available on windows by default. Modern windows
* builds do support this ANSI color codes via terminal emulation
* however there is not way to detect this currently. As a result,
* windows users who wish to use these color modes must manually enable
* them using WINDOWS_MANUAL_COLOR_ENABLE 1
*/

#if __linux__
    #define __TERMINAL_COLOR_MODE_ENABLED 1
#endif

#if WINDOWS_MANUAL_COLOR_ENABLE
    #define __TERMINAL_COLOR_MODE_ENABLED 1
#endif

#define CM_FOREGROUND_BOLD_BLK "\e[1;30m"
#define CM_FOREGROUND_BOLD_RED "\e[1;31m"
#define CM_FOREGROUND_BOLD_GRN "\e[1;32m"
#define CM_FOREGROUND_BOLD_YEL "\e[1;33m"
#define CM_FOREGROUND_BOLD_BLU "\e[1;34m"
#define CM_FOREGROUND_BOLD_MAG "\e[1;35m"
#define CM_FOREGROUND_BOLD_CYN "\e[1;36m"
#define CM_FOREGROUND_BOLD_WHT "\e[1;37m"

#define CM_FOREGROUND_BLACK "\e[0;30m"
#define CM_FOREGROUND_RED "\e[0;31m"
#define CM_FOREGROUND_GREEN "\e[0;32m"
#define CM_FOREGROUND_YELLOW "\e[0;33m"
#define CM_FOREGROUND_BLUE "\e[0;34m"
#define CM_FOREGROUND_MAGENTA "\e[0;35m"
#define CM_FOREGROUND_CYAN "\e[0;36m"
#define CM_FOREGROUND_WHITE "\e[0;37m"

#define CM_BACKGROUND_BLACK "\e[40m"
#define CM_BACKGROUND_RED "\e[41m"
#define CM_BACKGROUND_GREEN "\e[42m"
#define CM_BACKGROUND_YELLOW "\e[43m"
#define CM_BACKGROUND_BLUE "\e[44m"
#define CM_BACKGROUND_MAGENTA "\e[45m"
#define CM_BACKGROUND_CYAN "\e[46m"
#define CM_BACKGROUND_WHITE "\e[47m"

#define CM_FOREGROUND_RESET "\e[0m"
#define RESET "\e[0m"
#define NEW_LINE "\n"

#if __TERMINAL_COLOR_MODE_ENABLED

// Below are are number of functions which are simply sementically named
// versions of eachother. Functionally all that is required is for the user
// to place one of the color codes on the standard out, however using naming
// such as this allows for easier reading of the code
void cm_foreground_set(char* color_code) {
    fputs(color_code, stdout);
}

void cm_background_set(char* color_code) {
    fputs(color_code, stdout);
}

void cm_foreground_reset() {
    fputs(CM_FOREGROUND_RESET, stdout);
}

// Does not provide error checking on style string
void cm_set_styles(char * style_string) {
    fputs(style_string, stdout);
}

void cm_reset_styles() {
    puts(RESET);
}

void color_print(char * string, char * color_code) {
    fputs(color_code, stdout); 
    fputs(string, stdout); 
    fputs(CM_FOREGROUND_RESET, stdout); 
} 
#endif 

// Outputting ANSI and POSIX codes on terminals which do not support them will
// lead to unknown behaviour. If the color mode is disabled, provide the API to
// prevent compilation errors whilst removing any of the formatting behaviour
#ifndef __TERMINAL_COLOR_MODE_ENABLED
void cm_foreground_set(char* color_code) { }

void cm_background_set(char* color_code) { }

void cm_foreground_reset() { }

void cm_set_styles(char * style_string) { }

void cm_reset_styles() { }

void color_print(char * string, char * color_code) {
    fputs(string, stdout);
}
#endif
