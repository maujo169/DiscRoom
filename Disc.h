#pragma once
#include "Entidad.h"
enum Location
{
	Frame, 
	Center
};
class Disc : public Entidad
{
public:
	Disc(int xMax, int yMax, Location loc, int dir)
	{
		Random random;
		this->loc = loc;
		switch (loc)
		{
		case Frame:
			resize = random.Next(40, 90);
			width = height = resize;
			x = y = 45;
			vx = vy = random.Next(25, 30);
			pos = 0;
			row = column = 0;
			break;
		case Center:
			resize = random.Next(40, 90);
			width = height = resize;
			x = (xMax / 2) - width;
			y = (yMax / 2) - height;
			if (dir == 1)
			{
				vx = -random.Next(25, 30);
				vy = -random.Next(25, 30);
			}
			if (dir == 2)
			{
				vx = -random.Next(25, 30);
				vy = random.Next(25, 30);
			}
			if (dir == 3)
			{
				vx = random.Next(25, 30);
				vy = -random.Next(25, 30);
			}
			if (dir == 4)
			{
				vx = random.Next(25, 30);
				vy = random.Next(25, 30);
			}
			row = column = 0;
			break;
		}
	}
	~Disc();
	
	void Show(Graphics^ g, Bitmap^ bit)
	{
		height = bit->Height / 3;
		width = bit->Width / 2;
		molde = Rectangle(column * width, row * height, width, height);
		height = width = resize;
		Rectangle ajustar = Rectangle(x, y, width, height);
		g->DrawImage(bit, ajustar, molde, GraphicsUnit::Pixel);
		column++;
		row++;
		if (column == 2)
			column = 0;
		if (row == 3)
			row = 0;
	}
	void Move(int xMax, int yMax, int xMin, int yMin)
	{
		if (loc == Location::Center)
		{
			if (x + vx + width > xMax || x + vx + width < xMin + 50) vx *= -1;
			if (y + vy + height > yMax || y + vy + height < yMin + 50) vy *= -1;
			x += vx;
			y += vy;
		}
		if (loc == Location::Frame)
		{
			if (x == 45 && y == 45)
				pos = 1;
			if (x >= 625 - resize && y == 45)
				pos = 2;
			if (x >= 625 - resize && y >= 600 - resize)
				pos = 3;
			if (x == 45 && y >= 600 - resize)
				pos = 4;

			if (pos == 1)
				x+=vx;
			if (pos == 2)
				y+=vy;
			if (pos == 3)
				x-=vx;
			if (pos == 4)
				y-=vy;
		}
	}
private:
	int resize;
	int pos;
	Location loc;
	Rectangle molde;
};