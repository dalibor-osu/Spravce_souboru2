#include "Spravce_souboru2.h"

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// deklarace globalnich promennych
char directoryPrint[40][200];
int directoryFileCount[2];

void GetFilePath(char directory[], char fileName[], char* outStr)
{
	char filePath[256];

	memcpy(filePath, directory, strlen(directory) + 1);
	strncat(filePath, "\\", 2);
	strncat(filePath, fileName, strlen(fileName) + 1);
	
	memcpy(outStr, filePath, 256);

}

void FileSize(char path[], char* outStr)
	{
	string s(path);
	struct stat stat_buf;
	int rc = stat(s.c_str(), &stat_buf);
	float sizef = stat_buf.st_size;
	string size = to_string(sizef / 1000);
	const char* fileSize = size.c_str();
	memcpy(outStr, fileSize, 256);
}

void ClearPrintArray()
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

	struct dirent* file;
	DIR* dir1 = opendir(directory1);
	int radek = 0;
	char filePath[256];
	char fileSize[256];

	if (dir1 != NULL)
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

			strncat(directoryPrint[radek], file->d_name, strlen(file->d_name));

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

	for  (int i = 2; i < 40; i++)
	{
		if (cursorPosition[1] == i)
		{
			if (cursorPosition[0] == 0)
			{
				SetConsoleTextAttribute(hConsole, 12);

				for (int j = 0; j < 100; j++)
				{
					cout << directoryPrint[i][j];
				}

				SetConsoleTextAttribute(hConsole, 15);

				for (int k = 100; k < 200; k++)
				{
					cout << directoryPrint[i][k];
				}

				cout << endl;
			}

			if (cursorPosition[0] == 1)
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
			cout << directoryPrint[i] << endl;
		}
	}
}

void PrintTop()
{
	char top[200];
	char dots[4] = { '.', '.', '.', '\0'};
	int j = 3;

	for (int i = 0; i < 200; i++)
	{
		cout << "-";
	}
	cout << endl;
	
	if (strlen(directory1) > 80)
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
			top[j] = directory1[i];
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

void GoBack(char *outStr)
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

void OpenDirectory(char* outStr)
{
	DIR* directory = opendir(outStr);
	struct dirent* file;

	for (int i = 0; i <= cursorPosition[1]; i++)
	{
		file = readdir(directory);
	}

	if (file->d_type == DT_DIR)
	{
		strcat(outStr, "\\");
		strcat(outStr, file->d_name);

		cursorPosition[1] = 2;
		Reprint();
	}
	closedir(directory);
}

void Reprint()
{
	system("cls");
	PrintTop();
	PrintDirectory();
}

void GetFileName(char* outStr)
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

void GetFilePath(char* outStr, char* fileName)
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

void FileCopy()
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



