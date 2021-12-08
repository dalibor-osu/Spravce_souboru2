#include "Spravce_souboru2.h"

using namespace std;

char directory1[256];
char directory2[256];
int cursorPosition[2];

int main()
{
	// pocatecni zapsani do globalnich promennych
	getcwd(directory1, 256);		// zapise cestu programu do directory1 a directory2
	getcwd(directory2, 256);

	cursorPosition[0] = 0;			// okno kurzoru
	cursorPosition[1] = 2;			// radek kurzoru
	int end = 0;
	int input;

	PrintTop();
	PrintDirectory();

	while (end != 1)
	{
		//printf("%d", getch());
		input = getch();				// podobne jako scanf, vraci cele cislo odpovidajici klavese

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
			Reprint();

			break;
				
		case 13:		// klavesa enter
			if (cursorPosition[0] == 0)
			{
				OpenDirectory(directory1);
			}
			else
			{
				OpenDirectory(directory2);
			}

			break;

		case 43:		// klavesa +
			FileCreate();
			Reprint();
			break;

		case 72:    // klavesa up
			if (cursorPosition[1] > 2)
			{
				cursorPosition[1]--;
				Reprint();
			}

			break;

		case 80:    // klavesa down
			if (cursorPosition[1] < directoryFileCount[cursorPosition[0]] - 1)
			{
				cursorPosition[1]++;
				Reprint();
			}

			break;

		case 77:    // klavesa right
			if (cursorPosition[0] < 1)
			{
				cursorPosition[0]++;
				Reprint();
			}
			break;

		case 75:    // klavesa left
			if (cursorPosition[0] > 0)
			{
				cursorPosition[0]--;
				Reprint();
			}
			break;

		case 99:		// klavesa c
			FileCopy();
			Reprint();
			break;

		case 100:		// klacesa d
			FileDelete();
			break;

		case 107:		// klavesa k
			end = 1;
			break;

		case 109:		// klavesa m
			FileMove();
			Reprint();

			break;

		case 114:		// klavesa r
			FileRename();
			Reprint();
			break;

		default:
			break;
		}

	}
	return 0;
}
