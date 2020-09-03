#pragma once

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGTH,
	NOTHING
};

using namespace System;
using namespace System::Drawing;

class Entidad
{
protected:
	int x, y, vx, vy, row, column;
	float width, height;
public:
	Entidad() {}
	~Entidad() {}

	int GetX() { return x; }
	int GetY() { return y; }
	int GetVX() { return vx; }
	int GetVY() { return vy; }
	float GetHeight() { return height; }
	float GetWidth() { return width; }
	int GetRow() { return row; }
	int GetColumn() { return column; }

	void SetX(int n) { x = n; }
	void SetY(int n) { y = n; }
	void SetVX(int n) { vx = n; }
	void SetVY(int n) { vy = n; }
	void SetHeight(float n) { height = n; }
	void SetWidth(float n) { width = n; }
	void SetRow(int n) { row = n; }
	void SetColumn(int n) { column = n; }

	virtual void Show(Graphics^ g, Bitmap^ bit) {}
	virtual void Move(DIR direccion) {}
};