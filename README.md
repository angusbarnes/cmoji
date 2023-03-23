# 🚀 Cmoji
Printing emoji's to `stdout` can be an issue in C++. Lets fix that.

## The Problem
If you've ever tried to print emoji's to `stdout` using the C++ in built `iostream` functions, you may have noticed weird behaviour.
Specifically, you may notice mangled text output, strange character encodings, or messed up terminal formatting. This is primarily an issue on windows but can rear its head on any system. 

## Why does this happen?
There are a number of reasons this may occur:
1. Your source files are not utf-8 encoded --> This means your raw emoji input in the source file may get currupted when the file is saved. On modern operating systems this is not often an issue
2. The compiler may be mangling the emojis. This is an issue that microsofts `cl` compiler exhibits, it is incapable of processing the raw UTF-8 bytes it finds in strings if they are not escaped properly
3. Your terminal does not support UTF-8 by default. Most modern terminals do support UTF-8, however the C++ `stdout` is not always set to engage UTF-8 mode on some operating systems (Looking at you windows 👀)

## The Fix

On windows you can try activating the UTF-8 mode on the current terminal host using the `SetConsoleOutputCP()` function provided by `windows.h`. You can do the following:
```C++
#include <iostream>
#include <windows.h>

int main(void) {
  SetConsoleCP(CP_UTF8);
  // Printing emoji's should just work now
  std::cout << "🚀" << std::endl;
}
```
You can read more about `SetConsoleOutputCP()` [here](https://learn.microsoft.com/en-us/windows/console/setconsoleoutputcp)

This fix works but is not very satisfying and also requires you to write operating system dependent code. I have found that a more reliable method is to simply use escape sequences. This method seems to work consistently on every OS and compiler I have tested.

For example, we can encode the rocket emoji (🚀) using the escape squence `u8"\U0001F680"`. In practice this looks like the following:
```C++
int main(void) {
  // It just works
  std::cout << u8"\U0001F680" << std::endl;
}
```

Now finding every single escape sequence that you might want to use is a huge pain, so I have created a header file in this repository that contains #defines for a large subset of the emoji character set. To use it simply `#include "cmoji.h"` and access each emoji using their names: `std::cout << CMOJI_ROCKET << std::cout`.

Alternatively, if you don't like this approach (and dont want to selectively each escape sequence manually), you can check out [emojicpp](https://github.com/99x/emojicpp). Its a lightweight header that provides all the emoji escape squences and can scan strings to replace `:emoji:` tags with the specified emoji.

If you find any emoji that are missing from my header, feel free to add them and open a pull request and I'll try to get them pulled in as soon as possible.
