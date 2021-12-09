#include "Spravce_souboru2.h"

using namespace std;

char directory1[256];
char directory2[256];
int cursorPosition[2];
int directoryPrintOffset[2];
int selectedFiles[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
	// pocatecni zapsani do globalnich promennych
	getcwd(directory1, 256);		// zapise cestu programu do directory1 a directory2
	getcwd(directory2, 256);

	cursorPosition[0] = 0;			// okno kurzoru
	cursorPosition[1] = 2;			// radek kurzoru

	directoryPrintOffset[0] = 0;	// offset pro okno 0
	directoryPrintOffset[1] = 0;	// offset pro okno 1

	int end = 0;
	int input;
	int skip;

	PrintTop();
	PrintDirectory();
	PrintBottom();

	while (end != 1)
	{
		input = getch();				// podobne jako scanf, vraci cele cislo odpovidajici klavese
		//printf("%d", input);

		switch (input)
		{
		case 8:		// klavesa backspace
			if (cursorPosition[0] == 0)
			{
				GoBack(directory1);
			}

			if (cursorPosition[0] == 1)
			{
				GoBack(directory2);
			}

			cursorPosition[1] = 2;
			std::fill_n(selectedFiles, 10, 0);
			Reprint();

			break;
				
		case 13:		// klavesa enter
			if (cursorPosition[0] == 0)
			{
				std::fill_n(selectedFiles, 10, 0);
				OpenDirectory(directory1);
			}
			else
			{
				std::fill_n(selectedFiles, 10, 0);
				OpenDirectory(directory2);
			}

			break;

		case 43:		// klavesa +
			FileCreate();
			std::fill_n(selectedFiles, 10, 0);
			Reprint();
			break;

		case 72:    // klavesa up

			if (directoryPrintOffset[cursorPosition[0]] == 0)
			{
				if (cursorPosition[1] > 2)
				{
					cursorPosition[1]--;
					Reprint();
				}
			}
			else
			{
				cursorPosition[1]--;

				if (cursorPosition[1] < 2)
				{
					cursorPosition[1] = 2;
					directoryPrintOffset[cursorPosition[0]]--;
					Reprint();
				}
				else
				{
					Reprint();
				}
			}

			break;

		case 80:    // klavesa down
			if (cursorPosition[1] + directoryPrintOffset[cursorPosition[0]] < directoryFileCount[cursorPosition[0]] - 1)
			{
				cursorPosition[1]++;

				if (cursorPosition[1] > 38)
				{
					cursorPosition[1] = 38;
					directoryPrintOffset[cursorPosition[0]]++;
				}
				Reprint();
			}

			break;

		case 77:    // klavesa right
			if (cursorPosition[0] < 1)
			{
				cursorPosition[0]++;
				cursorPosition[1] = 2;
				std::fill_n(selectedFiles, 10, 0);
				Reprint();
			}
			break;

		case 75:    // klavesa left
			if (cursorPosition[0] > 0)
			{
				cursorPosition[1] = 2;
				cursorPosition[0]--;
				std::fill_n(selectedFiles, 10, 0);
				Reprint();
			}
			break;

		case 99:		// klavesa c
			if (selectedFiles[0] == 0)
			{
				FileCopy();
				Reprint();
			}
			else
			{
				int i = 0;
				while (selectedFiles[i] != 0)
				{
					cursorPosition[1] = selectedFiles[i];
					FileCopy();
					i++;
					cursorPosition[1] = 2;
				}
				std::fill_n(selectedFiles, 10, 0);
				Reprint();
			}
			break;

		case 100:		// klacesa d
			skip = 0;
			if (selectedFiles[0] == 0)
			{
				FileDelete(&skip);
				Reprint();
			}
			else
			{
				int i = 0;
				while (selectedFiles[i] != 0)
				{
					cursorPosition[1] = selectedFiles[i] - i + skip;
					FileDelete(&skip);
					i++;
					cursorPosition[1] = 2;
					Reprint();
				}
				std::fill_n(selectedFiles, 10, 0);
				Reprint();
			}
			break;

		case 107:		// klavesa k
			end = 1;
			break;

		case 109:		// klavesa m
			if (selectedFiles[0] == 0)
			{
				FileMove();
				Reprint();
			}
			else
			{
				int i = 0;
				while (selectedFiles[i] != 0)
				{
					cursorPosition[1] = selectedFiles[i] - i;
					FileMove();
					i++;
					cursorPosition[1] = 2;
				}
				std::fill_n(selectedFiles, 10, 0);
				Reprint();
			}


			break;

		case 114:		// klavesa r
			FileRename();
			std::fill_n(selectedFiles, 10, 0);
			Reprint();
			break;

		case 115:		// klavesa s
			if (SelectAnother() == 1)
			{
				SortSelectedFiles();
				Reprint();
			}

			break;
		default:
			break;
		}

	}
	return 0;
}
