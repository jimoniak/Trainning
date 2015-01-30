/**
 * \file constantes.hpp
 * \brief Fichier contenant les varaibles globales et ou constantes du programme
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * .
 */


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
