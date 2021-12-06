#pragma once

// knihovny
#include <iostream>
#include "dirent.h"
#include <string.h>
#include <conio.h>
#include "unistd.h"
#include <fileapi.h>
#include <sys/stat.h>
#include <string>

// globalni promenne
extern char directory1[256];
extern char directory2[256];
extern char directoryPrint[40][200];
extern int directoryFileCount[2];
extern int cursorPosition[2];

// funkce
void PrintDirectory();
void PrintTop();
void GoBack(char* outStr);
void OpenDirectory(char* outStr);
void Reprint();
void FileCopy();
