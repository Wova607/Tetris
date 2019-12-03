#include "Field.h"

Field::Field()
{
	countDestroyLine = 0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int j = 0; j < sizeJ; j++)
		{
			field[i][j] = ' ';
			field[i][0] = '|';
			field[i][1] = '|';
			field[i][sizeJ - 1] = '|';
			field[i][sizeJ - 2] = '|';
			field[sizeI - 1][j] = '-';
			field[0][j] = '-'; 
		}
	}
}

void Field::Show(int x, int y)
{
	for (int i = 0; i < sizeI; i++)
	{
		
		SetCoord(x, y);
		for (int j = 0; j < sizeJ; j++)
		{
			if (field[i][j] == '|' || field[i][j] == '-')
				SetColor(3, 3);
			else if (field[i][j] == '[' || field[i][j] == ']')
				SetColor(8, 15);
			else
				SetColor(0, 0);
			cout << field[i][j];
		}
		y++;
		cout << endl;
	}
		
	SetColor(10,9);
	x = 2;
	y = 2;
	SetCoord(x,y);
	cout << "Controls key:\n";

	SetColor(0, 7);

	y = 4;
	SetCoord(x,y);
	cout << "Move right" << endl;
	SetCoord(++x, ++y);
	cout<<"key \"arrow right\"\n";
	y++;
	SetCoord(2, ++y);
	cout << "Move left" << endl;
	SetCoord(3, ++y);
	cout<<"key \"arrow left\"\n";
	y++;
	SetCoord(2, ++y);
	cout << "Acceleration" << endl;
	SetCoord(3, ++y);
	cout << "key \"arrow down\"\n";
	y++;
	SetCoord(2, ++y);
	cout << "Rotation" << endl;
	SetCoord(3, ++y);
	cout << "key \"space\"\n";
	y++;
	SetCoord(2, ++y);
	cout << "Pause" << endl;
	SetCoord(3, ++y);
	cout << "key \"Esc\"\n";
	
	SetColor(0, 7);
}

bool Field::CanMoveLeft(BaseFigure *tetroid, int x, int y)
{
	int Ifig,Jfig;

	for (int i = tetroid->size-1; i >=0; i--)
	{
		for (int j = 0; j < tetroid->size; j++)
		{
			if (tetroid->figure[i][j]=='[')
			{
				Ifig = i+y; Jfig = j+x;  //індекси матриці переводимо в координати 
				Jfig--; //перевіряєм зсув на 1
				if (field[Ifig-2][Jfig -20] == '|' || field[Ifig - 2][Jfig - 20] == '[' || field[Ifig - 2][Jfig - 20] == ']') //координати переводимо в індекси матриці
				{
					return false;
				}
				
			}
		}
		
	}
	return true;

}

bool Field::CanMoveRight(BaseFigure* tetroid, int x, int y)
{

	int Ifig, Jfig;

	for (int i = tetroid->size - 1; i >= 0; i--)
	{
		for (int j = tetroid->size - 1; j >= 0; j--)
		{
			if (tetroid->figure[i][j] == ']')
			{
				Ifig = i + y; Jfig = j + x;  //індекси матриці переводимо в координати 
				Jfig++; //перевіряєм зсув на 1
				if (field[Ifig - 2][Jfig - 20] == '|' || field[Ifig - 2][Jfig - 20] == '[' || field[Ifig - 2][Jfig - 20] == ']') //координати переводимо в індекси матриці
				{
					return false;
				}
			}
		}

	}
	return true;

}

void Field::FrizzFigure(BaseFigure* freezTetroin, int x, int y)
{
	int xJ = x - 20;
	int yI = y - 2;
	for (int i = 0; i < freezTetroin->size; i++)
	{
		for (int j = 0; j < freezTetroin->size; j++)
		{
			if (freezTetroin->figure[i][j] == '[' || freezTetroin->figure[i][j] == ']')
			{
				this->field[yI + i][xJ + j] = freezTetroin->figure[i][j];
			}
		}
	}

}

bool Field::StopMove(BaseFigure *tetroid, int x, int y)
{
	int xJ = x - 20;
	int yI = y - 1;
	for (int i = 0; i < tetroid->size; i++)
	{
		for (int j = 0; j < tetroid->size; j++)
		{
			if (tetroid->figure[i][j] == '[' || tetroid->figure[i][j] == ']')
			{
				
				if (this->field[yI + i][xJ + j] == '[' || this->field[yI + i][xJ + j] == ']' || this->field[yI + i][xJ + j] == '-' || this->field[yI + i][xJ + j] == '|')
					return true;
			}
		}
	}
	return false;
}


bool Field::DestroyLine()
{
	bool destroyLine = false;

	int full;
	for (size_t i = 3; i < sizeI - 1; i++)
	{
		full = 0;
		for (size_t j = 2; j < sizeJ - 2; j++)
		{

			if (field[i][j] == '[' || field[i][j] == ']')
				full++;

		}
		if (full == 36) 
		{
			for (size_t j = 2; j < sizeJ - 2; j++)
				field[i][j] = ' ';
			destroyLine = true;
			countDestroyLine++;
			if (startLine!=0)
				startLine = i;
			
		}

	}
	return destroyLine;

}

void Field::CopyField()
{

	for (countDestroyLine; countDestroyLine > 0; countDestroyLine--)
	{
		for (size_t i = startLine; i > 3; i--)
		{
			for (size_t j = 2; j < sizeJ - 2; j++)
			{
				field[i][j] = field[i - 1][j];
			}
			
		}
	}
}

InfField::InfField()
{
	for (int i = 0; i < sizeI; i++)
	{
		for (int j = 0; j < sizeJ; j++)
		{
			field[i][j] = ' ';
			field[i][0] = '|';
			field[i][1] = '|';
			field[i][sizeJ - 1] = '|';
			field[i][sizeJ - 2] = '|';
			field[sizeI - 1][j] = '-';
			field[0][j] = '-';
			field[9][j] = '-';
		}
	}
}

void InfField::Show(int x, int y,BaseFigure* tetroid, int level, int score)
{
	
	int startX = x, startY = y;
	for (int i = 0; i < sizeI; i++)
	{
		
		SetCoord(x, y);
		for (int j = 0; j < sizeJ; j++)
		{
			if (field[i][j] == '|' || field[i][j] == '-')
				 SetColor(3, 3);
			
			else
				SetColor(0, 0);
			cout << field[i][j];
		}
		
		y++;
		cout << endl;
	}
	
	SetColor(0, 4);
	SetCoord(startX + 4, startY + 1);
	cout << "NEXT FIGURE:\n";
	
	tetroid->ShowFigure(startX +7, startY +3); //виводимо наступну фігуру
		
	SetCoord(startX + 4, startY + 11);   //виводимо бали і левел
	SetColor(7, 0);
	cout << "LEVEL :" << level << endl;     
	
	SetCoord(startX + 4, startY + 12);
	cout << "SCORE :" << score << endl;
	
	SetColor(0, 7);
}


