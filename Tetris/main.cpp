#include"Game.h"



int main()
{
	
	system("mode 100,40"); //встановлюємо розміри консолі
	
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);    //приховуємо курсор
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	
	srand(time(NULL));

	Game tetris;

	tetris.TableChampion(); //зчитуємо таблицю лідерів
	
	while (true)
	{		
		SetColor(0, 7);		
		switch (tetris.Menu())
		{
		case 0:
			tetris.SetScore(0);
			tetris.StartGame();
			break;
		case 1:
			tetris.LoadGame();
			tetris.StartGame();
			break;
		case 2:
			tetris.TableChampionShow();
			break;
		case 3:
			tetris.TableChampion();
			exit(0);
		}
	}

	system("pause");
	return 0;
}