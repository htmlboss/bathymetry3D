// https://github.com/emilk/loguru
#pragma warning( push )
#pragma warning( disable : 4100) // unreferenced parameters
#pragma warning( disable : 4996) // security warnings, strcpy and such

// silences warnings about "nonstandard" function
#define strdup _strdup
#include <loguru/loguru.cpp>
#undef strdup
#pragma warning( pop )
