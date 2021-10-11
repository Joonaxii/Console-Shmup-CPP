#pragma once
#include <iostream>
#include "fcntl.h"

enum EncodingType {

    ANSI = O_TEXT,
    UTF_8 = _O_U8TEXT,
    UTF_16 = _O_U16TEXT,
};