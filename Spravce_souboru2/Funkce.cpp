#include "Spravce_souboru2.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// prace s konzoli

// deklarace globalnich promennych
char directoryPrint[40][200];
int directoryFileCount[2];

void GetFilePath(char directory[], char fileName[], char* outStr)	// zapise cestu k souboru do outStr
{
	char filePath[256];

	memcpy(filePath, directory, strlen(directory) + 1);		// prekopiruje pamet do filePath z directory o delce strnlen(directory) + 1
	strncat(filePath, "\\", 2);								// na konec texu prida 2 lomitka
	strncat(filePath, fileName, strlen(fileName) + 1);		// na konec textu prida fileName
	
	memcpy(outStr, filePath, 256);							// prekopiruje pamet do osuStr z filePath

}

void FileSize(char path[], char* outStr)					// zapise velikost souboru do outStr
	{
	string s(path);								// deklarace stringu s (naplni se path)
	struct stat stat_buf;						// struktura z knihovny stat.h
	int rc = stat(s.c_str(), &stat_buf);		// ziska vlastnosti souboru
	float sizef = stat_buf.st_size;				// ziska velikost souboru v bajtech
	string size = to_string(sizef / 1000);		// prekonvertuje cislo na text + vydeli cislo 1000 (kb)
	const char* fileSize = size.c_str();		// udela ze stringu size pole fileSize
	memcpy(outStr, fileSize, 256);				
}

void ClearPrintArray()							// vymaze obsah directoryPrint
{
	for (int i = 0; i < 40; i++)
	{
		std::fill_n(directoryPrint[i], 200, 0);
	}
}

void PrintDirectory()	// tiskne obsah slozek
{
	ClearPrintArray();

	directoryFileCount[0] = 0;
	directoryFileCount[1] = 0;

	struct dirent* file;				// struktura z dirent.h, po naplneni obsahuje parametry souboru
	DIR* dir1 = opendir(directory1);	// otevre slozku directory1

	int radek = 0;						
	char filePath[256];
	char fileSize[256];

	if (dir1 != NULL)		// kontroluje slozku 1
	{
		while ((file = readdir(dir1)) != NULL)
		{
			memcpy(directoryPrint[radek], file->d_name, strlen(file->d_name) + 1);	
			GetFilePath(directory1, file->d_name, filePath);
			FileSize(filePath, fileSize);

			for (int i = strlen(file->d_name); i <= 60; i++)
			{
				directoryPrint[radek][i] = ' ';
			}

			strcat(directoryPrint[radek], fileSize);
			
			for (int i = 60 + strlen(fileSize); i <= 100; i++)
			{
				directoryPrint[radek][i] = ' ';
			}


			directoryPrint[radek][100] = '|';
			directoryPrint[radek][101] = '\0';
			radek++;
		}
	}

	closedir(dir1);
	directoryFileCount[0] = radek;

	// slozka 2
	DIR* dir2 = opendir(directory2);
	radek = 0;

	if (dir2 != NULL)
	{
		while ((file = readdir(dir2)) != NULL)
		{
			if (radek >= directoryFileCount[0])
			{
				for (int i = 0; i <= 100; i++)
				{
					directoryPrint[radek][i] = ' ';
				}

				directoryPrint[radek][100] = '|';
				directoryPrint[radek][101] = '\0';
			}

			strncat(directoryPrint[radek], file->d_name, strlen(file->d_name));		// pripise na konec textu file->d_name, konec pozna podle \0

			GetFilePath(directory2, file->d_name, filePath);
			FileSize(filePath, fileSize);

			for (int i = strlen(file->d_name) + 101; i <= 160; i++)
			{
				directoryPrint[radek][i] = ' ';
			}

			strcat(directoryPrint[radek], fileSize);

			for (int i = strlen(fileSize) + 160; i < 200; i++)
			{
				directoryPrint[radek][i] = ' ';
			}

			directoryPrint[radek][199] = '\0';
			radek++;
		}
	}

	closedir(dir2);
	directoryFileCount[1] = radek;

	for  (int i = 2; i < 40; i++)		// vypisuje soubory od radku 2
	{
		if (cursorPosition[1] == i)		// kontroluje, jestli radek kurzoru odpovida radku tisku
		{
			if (cursorPosition[0] == 0)		// kontroluje okno kurzoru
			{
				SetConsoleTextAttribute(hConsole, 12);		// meni barvu textu na cervenou

				for (int j = 0; j < 100; j++)
				{
					cout << directoryPrint[i][j];
				}

				SetConsoleTextAttribute(hConsole, 15);		// vrati se na bilou barvu

				for (int k = 100; k < 200; k++)
				{
					cout << directoryPrint[i][k];
				}

				cout << endl;		// ukonci radek
			}

			if (cursorPosition[0] == 1)		// to same pro druhe okno
			{
				for (int j = 0; j < 100; j++)
				{
					cout << directoryPrint[i][j];
				}

				SetConsoleTextAttribute(hConsole, 12);

				for (int k = 100; k < 200; k++)
				{
					cout << directoryPrint[i][k];
				}

				SetConsoleTextAttribute(hConsole, 15);

				cout << endl;
			}
		}
		else
		{
			cout << directoryPrint[i] << endl;		// vypise cely radek
		}
	}
}

void PrintTop()		// vypise hlavicku
{
	char top[200];
	char dots[4] = { '.', '.', '.', '\0'};
	int j = 3;

	for (int i = 0; i < 200; i++)
	{
		cout << "-";
	}
	cout << endl;
	
	if (strlen(directory1) > 80)		// kontroluje delku cesty
	{
		memcpy(top, dots, 3);

		for (int i = strlen(directory1) - 80; i <= strlen(directory1); i++)
		{
			top[j] = directory1[i];
			j++;
		}
		top[j] = '\0';
	}
	else
	{
		memcpy(top, directory1, strlen(directory1) + 1);
	}

	for (int i = strlen(top) + 1; i <= 100; i++)
	{
		strcat(top, " ");
	}

	top[101] = '\0';

	if (strlen(directory2) > 80)
	{
		j = 103;

		strcat(top, dots);

		for (int i = strlen(directory2) - 80; i <= strlen(directory2); i++)
		{
			top[j] = directory2[i];
			j++;
		}
		top[j] = '\0';
	}
	else
	{
		strcat(top, directory2);
	}

	cout << top << endl;

	for (int i = 0; i < 200; i++)
	{
		cout << "-";
	}

	cout << endl;
}

void GoBack(char *outStr)		// vrati se o slozku zpet
{
	int stringLength = strlen(outStr);
	int slashPosition = strlen(outStr);

	while (outStr[slashPosition] != '\\')
	{
		slashPosition--;
	}

	for (slashPosition; slashPosition <= stringLength; slashPosition++)
	{
		outStr[slashPosition] = NULL;
	}

}

void OpenDirectory(char* outStr)		// otevre slozku na ktere je kruzor
{
	DIR* directory = opendir(outStr);
	struct dirent* file;

	for (int i = 0; i <= cursorPosition[1]; i++)
	{
		file = readdir(directory);
	}

	if (file->d_type == DT_DIR)				// zkontroluje jestli vybrany soubor je slozka	
	{
		strcat(outStr, "\\");
		strcat(outStr, file->d_name);

		cursorPosition[1] = 2;
		Reprint();
	}

	closedir(directory);
}

void Reprint()		// smaze obrazovku a vypise ji znova
{
	system("cls");	// vymaze konzoli
	PrintTop();		
	PrintDirectory();
}

void GetFileName(char* outStr)			// ziska jmeno souboru na kterem je kurzor
{
	DIR* directory;
	struct dirent* file;

	if (cursorPosition[0] == 0)
	{
		directory = opendir(directory1);
		
		for (int i = 0; i <= cursorPosition[1]; i++)
		{
			file = readdir(directory);
		}
	}
	else
	{
		directory = opendir(directory2);

		for (int i = 0; i <= cursorPosition[1]; i++)
		{
			file = readdir(directory);
		}
	}

	memcpy(outStr, file->d_name, strlen(file->d_name) + 1);
	closedir(directory);
}

void GetFilePath(char* outStr, char* fileName)		// spoji cestu k souboru a soubor
{
	if (cursorPosition[0] == 0)
	{
		memcpy(outStr, directory1, strlen(directory1) + 1);
		strcat(outStr, "\\");
		strcat(outStr, fileName);
	}
	else
	{
		memcpy(outStr, directory2, strlen(directory2) + 1);
		strcat(outStr, "\\");
		strcat(outStr, fileName);
	}
}

void FileCopy()		// kopiruje soubor z okna do druheho okna
{
	char fileName[256];
	GetFileName(fileName);

	char filePath[256];
	GetFilePath(filePath, fileName);

	char newFilePath[256];

	if (cursorPosition[0] == 0)
	{
		memcpy(newFilePath, directory2, strlen(directory2) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}
	else
	{
		memcpy(newFilePath, directory1, strlen(directory1) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}

	CopyFile(filePath, newFilePath, 1);
}

void FileMove()		// presune soubor z okna do druheho okna
{
	char fileName[256];
	GetFileName(fileName);

	char filePath[256];
	GetFilePath(filePath, fileName);

	char newFilePath[256];

	if (cursorPosition[0] == 0)
	{
		memcpy(newFilePath, directory2, strlen(directory2) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}
	else
	{
		memcpy(newFilePath, directory1, strlen(directory1) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}
	
	MoveFile(filePath, newFilePath);
}

void FileCreate()		// vytvori soubor
{
	char fileName[256];
	cout << "Zadejte nazev souboru i s koncovkou (napr: soubor.txt):\t";
	cin >> fileName;

	char newFilePath[256];

	if (cursorPosition[0] == 0)
	{
		memcpy(newFilePath, directory1, strlen(directory1) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}
	else
	{
		memcpy(newFilePath, directory2, strlen(directory2) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, fileName);
	}
	
	CreateFile(newFilePath, GENERIC_ALL, FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
}

void FileRename()
{
	char fileName[256];
	GetFileName(fileName);

	char filePath[256];
	GetFilePath(filePath, fileName);

	char newFileName[256];
	char newFilePath[256];

	cout << "Zadejte novy nazev souboru\t";
	cin >> newFileName;

	if (cursorPosition[0] == 0)
	{
		memcpy(newFilePath, directory1, strlen(directory1) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, newFileName);
	}
	else
	{
		memcpy(newFilePath, directory2, strlen(directory2) + 1);
		strcat(newFilePath, "\\");
		strcat(newFilePath, newFileName);
	}

	rename(filePath, newFilePath);
}

void FileDelete()
{
	char fileName[256];
	GetFileName(fileName);

	char filePath[256];
	GetFilePath(filePath, fileName);

	cout << filePath;
}


