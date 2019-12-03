#include"Tetroids.h"
#include"Game.h"
#include"Field.h"


Game::Game()
{
	tetroid = nullptr;
	speed = 1000;
	level = 1;
	score = 0;
	nextLevel = 2000;
	start = true;
	loadGame = false;
}

void Game::StartGame()
{
	Field mainField;
	InfField infField;
	system("cls");

	if (loadGame)   //загрузка гри з файла
	{

		for (int i = 0; i < mainField.sizeI; i++)
		{
			for (int j = 0; j < mainField.sizeJ; j++)
			{
				mainField.field[i][j] = newField[i][j]; //копіювання філд
			}
		}

	}
	else   //якщо ні то запитаємо ім"я гравця
	{
		SetColor(15, 12);
		SetCoord(30, 10);
		cout << "Enter payer name: ";
		getline(cin, playerName);
		if (playerName.empty())
			playerName = "NoName";
	}
	SetColor(7, 0);

	bool gameOver = false;
	BaseFigure *nextTetroid = nullptr;
	bool firstStart = true, toMenu = false;


	while (!gameOver)
	{
		mainField.Show(20, 2); //розміщаємо основне поле

		if (mainField.DestroyLine())  //перемалбовуємо після знищення лінії
		{
			mainField.Show(20, 2);
			Sleep(700);
			score += mainField.countDestroyLine * 100;
			mainField.CopyField();
			mainField.Show(20, 2);

		}
		if (score >= nextLevel)  //зміна левела і швидкості
		{
			level++;
			speed -= 50;
			nextLevel += 2000;
		}

		if (!firstStart) //якщо це не перша фігура на полі
			tetroid = nextTetroid;

		switch (rand() % 5) //генерим наступну фігуру
		{
		case 0:
			nextTetroid = new Strip;
			break;
		case 1:
			nextTetroid = new Square;
			break;
		case 2:
			nextTetroid = new Сorner;
			break;
		case 3:
			nextTetroid = new Ze;
			break;
		case 4:
			nextTetroid = new Te;
			break;
		}

		if (firstStart)   //перший раз генеруєм тут тетроїд
		{
			switch (rand() % 5)
			{
			case 0:
				tetroid = new Strip;
				break;
			case 1:
				tetroid = new Square;
				break;
			case 2:
				tetroid = new Сorner;
				break;
			case 3:
				tetroid = new Ze;
				break;
			case 4:
				tetroid = new Te;
				break;
			}
			firstStart = false;
		}


		infField.Show(58, 2, nextTetroid, GetLevel(), GetScore()); //інформаційне поле

		int x = 38, y = 3; //стартові координати для фігури 

		bool stop = false, acceleration = false;

		//рух тетроїда
		while (!stop)
		{
			int tempY; //для перевірки можливості прискорення

			tetroid->ShowFigure(x, y);

			if (mainField.StopMove(tetroid, x, y)) //якщо нема куди рухатись тоді гра закінчена
				gameOver = true;

			if (acceleration)  //якщо прискорення
			{
				acceleration = false;
				Sleep(speed / 2);
			}
			else
				Sleep(speed);

			//превірка натисненої клавіші		
			while (_kbhit())
			{
				tetroid->ClearFigure();
				tetroid->ShowFigure(x, y);
				int key = _getch();
				switch (key)
				{
				case 224:
					key = _getch();
					switch (key)
					{
					case 75: //ліворуч
						tetroid->DrowFigure();

						if (!mainField.CanMoveLeft(tetroid, x, y))
						{
							tetroid->ShowFigure(x, y);
							break;
						}
						x -= 2;  //-2 для парного зсуву
						tetroid->ShowFigure(x, y);
						Sleep(50);
						break;

					case 77: //праворуч

						tetroid->DrowFigure();

						if (!mainField.CanMoveRight(tetroid, x, y)) //якщо нема можливості зсунути виходим
						{
							tetroid->ShowFigure(x, y);  //щоб було гарно
							break;
						}
						x += 2;             //+2 для парного зсуву
						tetroid->ShowFigure(x, y);
						Sleep(50);
						break;

					case 80:   //прискорення
						tetroid->DrowFigure();
						tempY = y + 1;
						if (mainField.StopMove(tetroid, x, tempY))
						{
							tetroid->ShowFigure(x, y);
							break;
						}

						tetroid->ShowFigure(x, ++y);

						acceleration = true;
						break;
					}

					break;
				case 32:  //пробіл поворот фігури

					tetroid->DestroyFigure();
					tetroid->CreateFigure();
					tetroid->posRotation++;
					tetroid->DrowFigure();
					if (mainField.StopMove(tetroid, x, y)) //Якщо при повороті зупиниться рух тоді відміняємо зміни і виходимо
					{
						tetroid->DestroyFigure();
						tetroid->CreateFigure();
						tetroid->posRotation--;
						tetroid->DrowFigure();
						tetroid->ShowFigure(x, y);
						break;
					}

					tetroid->ShowFigure(x, y);

					break;
				case 27:   //пауза 
					switch (Pause())
					{
					case 0:
						SaveGame(mainField);  //збереження
					case 1:
						mainField.Show(20, 2);  //продовження гри
						infField.Show(58, 2, nextTetroid, GetLevel(), GetScore());
						break;
					case 2:
						toMenu = true;  //виходимо звідси
						break;
					}

					break;

				default:
					continue;
					break;
				}

			}
			if (toMenu)
				break;
			tetroid->ClearFigure();
			tetroid->ShowFigure(x, y);
			tetroid->DestroyFigure();
			tetroid->CreateFigure();
			tetroid->DrowFigure();
			tetroid->ShowFigure(x, ++y);

			stop = mainField.StopMove(tetroid, x, y); //перевіряємо досягнення дна 

			if (stop)
			{
				mainField.FrizzFigure(tetroid, x, y); //фігура фіксується на полі
				score += 18;
			}

		}

		if (toMenu)
		{
			tablChemp.insert(pair<int, string>(score, playerName)); //записуємо пару бали-грвець
			break;
		}

	}



	if (gameOver)  //у випадку кінця гри
	{
		tablChemp.insert(pair<int, string>(score, playerName));
		system("cls");
		SetCoord(40, 20);
		SetColor(4, 15);
		cout << "GAME OVER!" << endl;
		SetColor(0, 7);
		Sleep(2000);
		system("cls");
		Menu();
	}

}

int Game::Menu()
{
	const int size = 4;
	string menu[size];
	int y = 5, x = 40;

	menu[0] = "START NEW GAME\n";
	menu[1] = "CONTINUE  GAME\n";
	menu[2] = "LEADERBOARD\n";
	menu[3] = "EXIT\n";
	int m_index = 0;

	system("cls");
	SetCoord(44, 5);
	cout << "MENU" << endl;
	while (true)
	{
		y = 6;
		x = 40;

		for (size_t i = 0; i < size; i++)
		{

			if (m_index == i)
			{
				SetColor(15, 0);
				if (i == 2)
					SetCoord(41, y++);
				else if (i == 3)
					SetCoord(44, y++);
				else
					SetCoord(40, y++);
			}

			else
			{
				SetColor(0, 7);
				if (i == 2)
					SetCoord(41, y++);
				else if (i == 3)
					SetCoord(44, y++);
				else
					SetCoord(40, y++);
			}


			cout << right << menu[i];
		}

		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72: {m_index == 0 ? m_index = size - 1 : m_index--; break; }
			case 80: {m_index == size - 1 ? m_index = 0 : m_index++; break; }
			}
			break;
		case 13:
			return m_index;
		}
		SetColor(0, 7);
		system("cls");
		SetCoord(44, 5);

		cout << "MENU" << endl;
	}
}

int Game::Pause()
{
	const int size = 3;
	string menu[size];
	int y = 5, x = 40;

	menu[0] = "SAVE GAME\n";
	menu[1] = "RETURN TO GAME\n";
	menu[2] = "RETURN TO THE MAIN MENU\n";
	int m_index = 0;

	system("cls");
	SetCoord(45, 5);
	cout << "PAUSE" << endl;
	while (true)
	{
		y = 6;

		for (size_t i = 0; i < size; i++)
		{

			if (m_index == i)
			{
				SetColor(15, 0);
				if (i == 0)
					SetCoord(43, y++);
				else if (i == 1)
					SetCoord(42, y++);
				else
					SetCoord(38, y++);
			}

			else
			{

				SetColor(0, 7);
				if (i == 0)
					SetCoord(43, y++);
				else if (i == 1)
					SetCoord(42, y++);
				else
					SetCoord(38, y++);
			}


			cout << menu[i];
		}

		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72: {m_index == 0 ? m_index = size - 1 : m_index--; break; }
			case 80: {m_index == size - 1 ? m_index = 0 : m_index++; break; }
			}
			break;
		case 13:
			return m_index;
		}
		SetColor(0, 7);
		system("cls");
		SetCoord(45, 5);

		cout << "PAUSE" << endl;
	}

}

void Game::SaveGame(Field field)
{
	char file[] = "Users.txt";   //Зберігаємо сам список збережених користувачів
	ofstream inUsFile(file, ios_base::app);
	inUsFile << playerName;
	inUsFile << "\n";
	inUsFile.close();

	string UserName = playerName + ".txt";
	ofstream inFile(UserName, ios_base::out | ios_base::trunc);
	inFile << score;
	inFile << "\n";

	for (int i = 0; i < field.sizeI; i++)
	{
		for (int j = 0; j < field.sizeJ; j++)
		{
			inFile << field.field[i][j];

		}
		inFile << '\n';
	}

	inFile.close();
}

void  Game::LoadGame()
{

	char buff[1000];
	string buffStr, index;
	set<string>usersList;
	int iArr, jArr;
	ifstream outUsFile("Users.txt");
	while (!outUsFile.eof())   //Зчитуємо список користувачів що зберігались
	{
		outUsFile.getline(buff, 100, '\n');
		buffStr = buff;
		if (buffStr.empty())
			break;

		usersList.insert(buffStr);
	}
	outUsFile.close();

	playerName = UsersMenu(usersList);
	string FileName = playerName + ".txt";  //вибираємо файл з збереженням користувача
	ifstream outFile(FileName);
	if (!outFile.is_open())
	{
		system("cls");
		SetCoord(40, 20);
		SetColor(4, 15);
		cout << "File don't open!" << endl;
		SetColor(0, 7);
		Sleep(2000);
		system("cls");
		return;
	}

	outFile.getline(buff, 50, '\n');// читаємо очкі
	score = atoi(buff);
	level = score / nextLevel + 1;   //рахуєм решту показників
	speed -= 50 * level + 50;
	int str = 0;
	while (!outFile.eof())  //читаємо поле гри
	{

		for (int i = 0; i < 25; i++)
		{

			outFile.getline(buff, 1000, '\n');
			buffStr = buff;
			if (buffStr.empty())
				break;

			for (int j = 0; j < 40; j++)
			{
				newField[i][j] = buffStr[j];
			}
			buffStr.clear();
		}
	}
	outFile.close();
	loadGame = true;

}

void Game::TableChampion()
{
	char tabl[] = "TablChemp.txt";
	multimap<int, string>::iterator it;


	if (start) //зчитуємо з файла при старті програми
	{
		ifstream outFile(tabl);
		char name[50], point[50];
		string nameBuff;

		if (!outFile.is_open())
		{
			start = false;
			return;
		}

		while (!outFile.eof())
		{
			outFile.getline(point, 50, ':');
			outFile.getline(name, 50, '\n');

			nameBuff = name;
			if (nameBuff.empty())
				break;
			tablChemp.insert(pair<int, string>(atoi(point), nameBuff));
		}
		outFile.close();
		start = false;

	}
	else  //записуємо при виході
	{
		ofstream inFile(tabl, ios_base::out | ios_base::trunc);


		for (it = tablChemp.begin(); it != tablChemp.end(); it++)
		{
			inFile << it->first;
			inFile << ":";
			inFile << it->second;
			inFile << "\n";

		}
		inFile.close();
	}

}

void Game::TableChampionShow()
{
	system("cls");
	SetCoord(42, 5);
	SetColor(2, 0);
	cout << "CHAMPIONS TABLE" << endl;
	SetColor(0, 7);
	int y = 7, i = 1;
	multimap<int, string>::reverse_iterator it;
	if (tablChemp.empty())
	{
		SetCoord(42, 5);
		cout << "Table is empty!\n";
	}
	else
	{
		for (it = tablChemp.rbegin(); it != tablChemp.rend(); it++)
		{
			SetCoord(41, y++);
			cout << i++ << ". " << it->second << "   " << it->first << endl;
		}
	}
	SetCoord(2, y + 10);
	cout << "Press any key to continue\n";
	_getch();
}

int Game::GetLevel()
{
	return level;
}

int Game::GetScore()
{
	return score;
}

void Game::SetScore(int sc)
{
	score = sc;
}

string Game::UsersMenu(set<string>list)
{
	int m_index = 0;
	string element;
	system("cls");
	SetCoord(42, 5);
	SetColor(2, 7);
	cout << "Select users name\n";
	SetColor(0, 7);

	set<string>::iterator itr;

	while (true)
	{
		
		int y = 5;
		int menuY = y;
		itr = list.begin();
		for (size_t i = 0; i < list.size(); i++)
		{

			if (m_index == i)
			{
				SetColor(2, 0);
				SetCoord(42, ++y);
				cout << "-->";
				element = *itr; //запам"ятовуємо вибраний елемент
			}
			else
			{
				SetColor(0, 7);
				SetCoord(42, ++y);
				cout << "  ";
			}

			SetCoord(47, ++menuY);
			cout << *itr;
			
			itr++;
		}

		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72: {m_index == 0 ? m_index = list.size() - 1 : m_index--; break; }
			case 80: {m_index == list.size() - 1 ? m_index = 0 : m_index++; break; }
			}
			break;
		case 13:
			SetColor(0, 7);
			return element;
		}
		SetColor(0, 7);
		system("cls");
		SetCoord(42, 5);
		SetColor(2, 7);
		cout << "Select users name\n";
		SetColor(0, 7);
	}
	SetColor(0, 7);
}


Game::~Game()
{
	if (tetroid != nullptr)
	{
		delete tetroid;
		tetroid = nullptr;
	}

}
