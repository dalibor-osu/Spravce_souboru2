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

void FileSize(char path[], char* outStrSize, char* outStrModified)					// zapise velikost souboru do outStr
	{
	const char* fileSize = 0;
	char modified[10];
	string s(path);								// deklarace stringu s (naplni se path)
	struct stat stat_buf;						// struktura z knihovny stat.h
	int rc = stat(s.c_str(), &stat_buf);		// ziska vlastnosti souboru

	float sizef = stat_buf.st_size;				// ziska velikost souboru v bajtech
	string size = to_string(sizef / 1024);		// prekonvertuje cislo na text + vydeli cislo 1000 (kb)

	strftime(modified, 10, "%d.%m.%y", localtime(&stat_buf.st_mtime));


	if (sizef == 0 || (int)sizef % 4096 == 0)
	{
		fileSize = " ";
	}
	else
	{
		fileSize = size.c_str();					// udela ze stringu size pole fileSize
	}
	memcpy(outStrSize, fileSize, 256);
	memcpy(outStrModified, modified, 10);
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
	char fileLastModified[10];

	if (dir1 != NULL)		// kontroluje slozku 1
	{
		while ((file = readdir(dir1)) != NULL)
		{	
			if (radek < 39 + directoryPrintOffset[0] && radek >= directoryPrintOffset[0])
			{
				if (strlen(file->d_name) <= 50)
				{
					memcpy(directoryPrint[radek - directoryPrintOffset[0]], file->d_name, strlen(file->d_name) + 1);
				}
				else
				{
					memcpy(directoryPrint[radek - directoryPrintOffset[0]], file->d_name, 50);
				}

				GetFilePath(directory1, file->d_name, filePath);
				FileSize(filePath, fileSize, fileLastModified);

				for (int i = strlen(directoryPrint[radek - directoryPrintOffset[0]]); i <= 60; i++)
				{
					directoryPrint[radek - directoryPrintOffset[0]][i] = ' ';
				}

				strcat(directoryPrint[radek - directoryPrintOffset[0]], fileSize);

				for (int i = 60 + strlen(fileSize); i <= 90; i++)
				{
					directoryPrint[radek - directoryPrintOffset[0]][i] = ' ';
				}

				strcat(directoryPrint[radek - directoryPrintOffset[0]], fileLastModified);

				for (int i = strlen(directoryPrint[radek - directoryPrintOffset[0]]); i <= 100; i++)
				{
					directoryPrint[radek - directoryPrintOffset[0]][i] = ' ';
				}

				directoryPrint[radek - directoryPrintOffset[0]][100] = '|';
				directoryPrint[radek - directoryPrintOffset[0]][101] = '\0';
			}

			if(radek - directoryPrintOffset[0] == 39)
			{
				memcpy(directoryPrint[39], "...", 3);
			}
			
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
			if (radek < 39 + directoryPrintOffset[1] && radek >= directoryPrintOffset[1])
			{
				if (radek - directoryPrintOffset[1] >= directoryFileCount[0])
				{
					for (int i = 0; i <= 100; i++)
					{
						directoryPrint[radek - directoryPrintOffset[1]][i] = ' ';
					}

					directoryPrint[radek - directoryPrintOffset[1]][100] = '|';
					directoryPrint[radek - directoryPrintOffset[1]][101] = '\0';
				}

				if (strlen(file->d_name) >= 50)
				{
					strncat(directoryPrint[radek - directoryPrintOffset[1]], file->d_name, 50);
				}
				else
				{
					strncat(directoryPrint[radek - directoryPrintOffset[1]], file->d_name, strlen(file->d_name));		// pripise na konec textu file->d_name, konec pozna podle \0
				}
				
				GetFilePath(directory2, file->d_name, filePath);
				FileSize(filePath, fileSize, fileLastModified);

				for (int i = strlen(directoryPrint[radek - directoryPrintOffset[1]]); i <= 160; i++)
				{
					directoryPrint[radek - directoryPrintOffset[1]][i] = ' ';
				}

				strcat(directoryPrint[radek - directoryPrintOffset[1]], fileSize);

				for (int i = strlen(fileSize) + 160; i < 200; i++)
				{
					directoryPrint[radek - directoryPrintOffset[1]][i] = ' ';
				}

				directoryPrint[radek - directoryPrintOffset[1]][199] = '\0';
			}

			if (radek - directoryPrintOffset[1] == 39)
			{
				for (int i = strlen(directoryPrint[39]); i < 104; i++)
				{
					if (i < 101)
					{
						directoryPrint[39][i] = ' ';
					}
					else
					{
						directoryPrint[39][i] = '.';
					}
				}


			}

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

	for (int i = 0; i <= cursorPosition[1] + directoryPrintOffset[cursorPosition[0]]; i++)
	{
		file = readdir(directory);
	}

	if (file->d_type == DT_DIR)				// zkontroluje jestli vybrany soubor je slozka	
	{
		strcat(outStr, "\\");
		strcat(outStr, file->d_name);

		cursorPosition[1] = 2;
		directoryPrintOffset[cursorPosition[0]] = 0;
		Reprint();
	}

	closedir(directory);
}

void PrintBottom()
{
	cout << endl;
	cout << "[Pohyb: sipky]     [Smazat: \"D\"]     [Kopirovat: \"C\"]     [Presunout: \"M\"]     [Prejmenovat: \"R\"]     [Vytvorit: \"+\"]     [Konec: \"K\"]" << endl;
}

void Reprint()		// smaze obrazovku a vypise ji znova
{
	system("cls");	// vymaze konzoli
	PrintTop();		
	PrintDirectory();
	PrintBottom();
}

void GetFileName(char* outStr)			// ziska jmeno souboru na kterem je kurzor
{
	DIR* directory;
	struct dirent* file;

	if (cursorPosition[0] == 0)
	{
		directory = opendir(directory1);
		
		for (int i = 0; i <= cursorPosition[1] + directoryPrintOffset[cursorPosition[0]]; i++)
		{
			file = readdir(directory);
		}
	}
	else
	{
		directory = opendir(directory2);

		for (int i = 0; i <= cursorPosition[1] + directoryPrintOffset[cursorPosition[0]]; i++)
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

void FileRename()		// prejmenuje soubor
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

void FileDelete()		// smaze soubor
{
	char fileName[256];
	GetFileName(fileName);

	char filePath[256];
	GetFilePath(filePath, fileName);

	int potvrzeni;

	cout << "Opravdu chtete smazat soubor: ";

	SetConsoleTextAttribute(hConsole, 12);
	cout << fileName;

	SetConsoleTextAttribute(hConsole, 15);
	cout << "? [y/n]: ";

	while (true)		// opakuje se dokud uzivatel nestiskne klavesu n nebo y
	{
		potvrzeni = getch();

		if (potvrzeni == 121 || potvrzeni == 89)
		{
			DeleteFile(filePath);
			break;
		}

		if (potvrzeni == 110 || potvrzeni == 78)
		{
			break;
		}
		
	}
	
}


