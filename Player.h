#pragma once
#include "Entidad.h"
class Player :
	public Entidad
{
	int columSprite = 3;
	int p = 1; // Representa a que personaje estoy dibujando
	Rectangle molde;
	int j = 9;
	int i = 5;
	bool stop = true;
public:
	Player()
	{
		vx = vy = 15;
		height = width = 30;
		x = 300;
		y = 300;
		row = 0; column = 0;
		Console::WriteLine(p);
	}
	~Player() {}

	int getBloque()
	{
		return p;
	}
	void setBloque(int n)
	{
		p = n;
	}
	int getI()
	{
		return i;
	}
	void setI(int n)
	{
		i = n;
	}
	int getJ()
	{
		return j;
	}
	void setJ(int n)
	{
		j = n;
	}
	int getCS()
	{
		return columSprite;
	}
	void setCS(int n)
	{
		columSprite = n;
	}

	void Show(Graphics^ g, Bitmap^ bit, bool muerto)
	{
		height = bit->Height / 8;
		width = bit->Width / 12;
		molde = Rectangle(column * width, row * height, width, height);
		height = width = 30;
		Rectangle ajustar = Rectangle(x, y, width, height);
		bit->MakeTransparent(bit->GetPixel(0, 0));
		g->DrawImage(bit, ajustar, molde, GraphicsUnit::Pixel);
		if (stop)
		{
			if (p == 1)
			{
				column = 1;
			}
			if (p == 2)
			{
				column = 4;
			}
			if (p == 3)
			{
				column = 7;
			}
			if (p == 4)
			{
				column = 10;
			}
		}
		else
		{
			column++;
		}
		if (column == columSprite)
		{
			column = columSprite - 3;
		}
	}
	void Move(DIR direccion, int xMIN, int yMIN, int xMAX, int yMAX)
	{
		switch (direccion)
		{
		case UP: vx = 0; vy = -15;
			if (y + vy > yMIN)
			{
				y += vy;
			}
			row = 3;
			stop = false;
			break;
		case DOWN: vx = 0; vy = 15;
			if (y + height < yMAX)
			{
				y += vy;
			}
			row = 0;
			stop = false;
			break;
		case LEFT: vx = -15; vy = 0;
			if (x + vx > xMIN)
			{
				x += vx;
			}
			row = 1;
			stop = false;
			break;
		case RIGTH: vx = 15; vy = 0;
			if (x + width < xMAX)
			{
				x += vx;
			}
			row = 2;
			stop = false;
			break;
		case NOTHING: vx = vy = 0; stop = true;
			break;
		}
	}
};

