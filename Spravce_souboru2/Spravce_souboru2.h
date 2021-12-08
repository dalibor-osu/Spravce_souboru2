﻿#pragma once

// knihovny
#include <iostream>		// tisk do konzole
#include "dirent.h"		// prace se slozkami
#include <string.h>		// lepsi prace s textem
#include <conio.h>		// prace se vstupem od uzivatele
#include "unistd.h"		// prace se soubory (read, write, ...)
#include <fileapi.h>	// prace se soubory
#include <sys/stat.h>	// vlastnosti souboru
#include <string>		// lepsi prace s textem

// globalni promenne
extern char directory1[256];			// cesta ke slozce 1
extern char directory2[256];			// cesta ke slozce 2
extern char directoryPrint[40][200];	// pole k tisku
extern int directoryFileCount[2];		// pocet souboru ve slozkach
extern int cursorPosition[2];			// souradnice kurzoru

// funkce
void PrintDirectory();
void PrintTop();
void GoBack(char* outStr);
void OpenDirectory(char* outStr);
void Reprint();
void FileCopy();
void FileMove();
void FileCreate();
void FileRename();
void FileDelete();
