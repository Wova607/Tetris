#include "Tetroids.h"

void SetColor(int textColor, int bgColor)
{
	HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleColor, (WORD)((textColor << 4) | bgColor));
}

void SetCoord(int x, int y)
{
	COORD win;
	win.X = x;
	win.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), win);
}


void BaseFigure::ShowFigure(int x, int y)
{

	for (int i = 0; i < size; i++)
	{
		SetCoord(x, y);
		for (int j = 0; j < size; j++)
		{
			if (figure[i][j] == '[' || figure[i][j] == ']')
			{
				SetColor(15, 0);
				cout << figure[i][j];
			}
			
			if (figure[i][j] == '\0')
			{
				SetColor(0, 7);
				cout << figure[i][j];
			}

		}
		cout << endl;
		y++;
	}
	SetColor(0, 7);
}

void BaseFigure::ClearFigure()
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (figure[i][j] == '[' || figure[i][j] == ']')
			{
				figure[i][j] = '\0';
			}
		}
	}
}

void BaseFigure::CreateFigure()
{
	figure = new char*[size];
	for (int i = 0; i < size; i++)
	{
		figure[i] = new char[size];
	}
}

void BaseFigure::DestroyFigure()
{
	for (int i = 0; i < size; i++)
	{
		delete[] figure[i];
	}
	delete[] figure;
	figure = nullptr;
}

Strip::Strip()
{
	posRotation = rand() % 4;
	CreateFigure();
	DrowFigure();
}

void Strip::DrowFigure()
{
	if (posRotation == 2 || posRotation > 3)
		posRotation = 0;
	if (posRotation == 3)
		posRotation = 1;

	switch (posRotation)
	{
	case 0:
		for (int i = 0; i < size / 2; i++)
		{
			figure[i][0] = '[';
			figure[i][1] = ']';
		}
		break;

	case 1:
		for (int j = 0; j < size; j++)
		{
			if (j % 2 == 0)
				figure[0][j] = '[';
			else
				figure[0][j] = ']';
		}
		break;

	}
}

Сorner::Сorner()
{
	posRotation = rand() % 4;
	CreateFigure();
	DrowFigure();
}

void Сorner::DrowFigure()
{
	if (posRotation == 4)
		posRotation = 0;

	switch (posRotation)
	{
	case 0:
		for (int i = 0; i < size / 2; i++)
		{
			figure[i][0] = '[';
			figure[i][1] = ']';
		}

		figure[3][2] = '[';
		figure[3][3] = ']';
		break;
	case 1:

		for (int j = 0; j < size; j++)
		{
			if (j % 2 == 0)
				figure[3][j] = '[';

			else
				figure[3][j] = ']';
		}
		for (int j = 0; j < 6; j++)
		{
			figure[2][j] = '\0';

		}

		figure[2][6] = '[';
		figure[2][7] = ']';
		break;
	case 2:

		figure[0][0] = '[';
		figure[0][1] = ']';

		for (int i = 0; i < size / 2; i++)
		{
			figure[i][2] = '[';
			figure[i][3] = ']';
		}
		break;
	case 3:
		for (int j = 0; j < size; j++)
		{
			if (j % 2 == 0)
				figure[0][j] = '[';

			else
				figure[0][j] = ']';
		}
		figure[1][0] = '[';
		figure[1][1] = ']';
		break;

	}
}

void Сorner::ShowFigure(int x, int y)
{
	if (posRotation == 2)
	{
		for (int i = 0; i < size; i++)
		{
			SetCoord(x, y);
			for (int j = 0; j < size; j++)
			{
				if (figure[i][j] == '[' || figure[i][j] == ']')
				{
					SetColor(15, 0);
					if (i > 0 && j == 2)
						SetCoord(x + 2, y);
					if (i > 0 && j == 3)
						SetCoord(x + 3, y);
					cout << figure[i][j];
				}


				if (figure[i][j] == '\0')
				{
					SetColor(0, 7);
					if (i > 0 && j == 2)
						SetCoord(x + 2, y);
					if (i > 0 && j == 3)
						SetCoord(x + 3, y);
					cout << figure[i][j];
				}


			}
			cout << endl;
			y++;
		}
		SetColor(0, 7);
	}
	else
		BaseFigure::ShowFigure(x, y);
}


Square::Square()
{
	posRotation = 0;
	CreateFigure();
	DrowFigure();
}

void Square::DrowFigure()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j % 2 == 0)
				figure[i][j] = '[';
			else
				figure[i][j] = ']';
		}

	}

}

Ze::Ze()
{
	posRotation = rand() % 4;
	CreateFigure();
	DrowFigure();
}

void Ze::DrowFigure() 
{

	if (posRotation == 2 || posRotation > 3)
		posRotation = 0;
	if (posRotation == 3)
		posRotation = 1;

	switch (posRotation)
	{
	case 0:
		figure[0][0] = '\0';   //для вирівнювання фігури
		figure[0][1] = '\0';

		for (int j = 2; j < 6; j++) //верхня полоска
		{
			if (j % 2 == 0)
				figure[0][j] = '[';
			else
				figure[0][j] = ']';
		}


		for (int j = 0; j < size / 2; j++) //нижня полоска
		{
			if (j % 2 == 0)
				figure[1][j] = '[';
			else
				figure[1][j] = ']';
		}

		break;
	case 1:
		figure[0][0] = '[';
		figure[0][1] = ']';
		for (int j = 0; j < 4; j++)
		{
			if (j % 2 == 0)
				figure[1][j] = '[';
			else
				figure[1][j] = ']';
		}

		figure[2][2] = '[';
		figure[2][3] = ']';
		break;
	}


}

void Ze::ShowFigure(int x, int y)
{
	if (posRotation == 1)
	{
		for (int i = 0; i < size; i++)
		{
			SetCoord(x, y);
			for (int j = 0; j < size; j++)
			{
				if (figure[i][j] == '[' || figure[i][j] == ']')
				{
					SetColor(15, 0);
					if (i == 2 && j == 2)
						SetCoord(x + 2, y);
					if (i == 2 && j == 3)
						SetCoord(x + 3, y);
					cout << figure[i][j];
				}


				if (figure[i][j] == '\0')
				{
					SetColor(0, 7);
					if (i > 0 && j == 2)
						SetCoord(x + 2, y);
					if (i > 0 && j == 3)
						SetCoord(x + 3, y);
					cout << figure[i][j];
				}


			}
			cout << endl;
			y++;
		}
		SetColor(0, 7);
	}
	else
		BaseFigure::ShowFigure(x, y);
}

Te::Te()
{
	posRotation = rand() % 4;
	CreateFigure();
	DrowFigure();
}

void Te::DrowFigure()
{
	if (posRotation == 4)
		posRotation = 0;

	switch (posRotation)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (j % 2 == 0)
					figure[i][j] = '[';
				else
					figure[i][j] = ']';
			}

		}

		figure[1][2] = '[';  //хвостик
		figure[1][3] = ']';

		break;
	case 1:
		figure[0][0] = '\0';//для вирівнювання фігури
		figure[0][1] = '\0';



		figure[0][2] = '[';  //хвостик
		figure[0][3] = ']';

		for (int j = 0; j < 6; j++) //основа
		{
			if (j % 2 == 0)
				figure[1][j] = '[';
			else
				figure[1][j] = ']';
		}


		break;
	case 2:
		figure[0][0] = '\0';//для вирівнювання фігури
		figure[0][1] = '\0';

		figure[1][0] = '[';  //хвостик
		figure[1][1] = ']';

		for (int i = 0; i < 3; i++)
		{
			for (int j = 2; j < 4; j++) //основа
			{
				if (j % 2 == 0)
					figure[i][j] = '[';
				else
					figure[i][j] = ']';
			}
		}

		break;
	case 3:

		for (int j = 0; j < 6; j++) //основа
		{
			if (j % 2 == 0)
				figure[0][j] = '[';
			else
				figure[0][j] = ']';
		}

		figure[1][2] = '[';  //хвостик
		figure[1][3] = ']';

		break;

	}
}

void Te::ShowFigure(int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		SetCoord(x, y);
		for (int j = 0; j < size; j++)
		{
			if (figure[i][j] == '[' || figure[i][j] == ']')
			{
				SetColor(15, 0);
				if (posRotation == 2)
				{
					if (i == 2 && j == 2)
						SetCoord(x + 2, y);
					if (i == 2 && j == 3)
						SetCoord(x + 3, y);
				}
				if (posRotation == 3)
				{
					if (i == 1 && j == 2)
						SetCoord(x + 2, y);
					if (i == 1 && j == 3)
						SetCoord(x + 3, y);
				}
				cout << figure[i][j];
			}


			if (figure[i][j] == '\0')
			{
				SetColor(0, 7);
				if (posRotation == 2)
				{
					if (i > 0 && j == 2)
						SetCoord(x + 2, y);
					if (i > 0 && j == 3)
						SetCoord(x + 3, y);
				}
				if (posRotation == 3)
				{
					if (i == 1 && j == 2)
						SetCoord(x + 2, y);
					if (i == 1 && j == 3)
						SetCoord(x + 3, y);
				}
				cout << figure[i][j];
			}


		}
		cout << endl;
		y++;
	}
	SetColor(0, 7);

}
