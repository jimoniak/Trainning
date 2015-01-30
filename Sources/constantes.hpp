
#ifndef CONST
#define CONST

#include <string>

#endif // CONST

#ifdef GLOBAL
#define Global
#else
#define Global extern
#endif

Global int HFENETRE;
Global int LFENETRE;
Global std::string nomOS;
Global bool debug;

#ifdef _WIN32
#define WINDOW
#endif

#ifdef  __linux__
#define LINUX
#endif
