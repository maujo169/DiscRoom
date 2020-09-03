#pragma once
#include "Player.h"
#include "Disc.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Controller
{
private:
	/*GAME*/
	int level;
	int seg = 100;
	int vidas = 5;
	/*PLAYER*/				
	Player* player;							
	Bitmap^ Bplayer;
	bool dead;

	/*DISC*/
	int add; // Add disks certain interval of time
	int cantD;
	Disc** discs;
	Bitmap^ disc1;
	Bitmap^ disc2;

	/*BLOOD*/														
	Bitmap^ Bblood;

	/*BACKGROUNDS*/													
	Bitmap^ Marco1;
	Bitmap^ Fondo1;
	Bitmap^ Marco2;
	Bitmap^ Fondo2;
	Bitmap^ Marco3;
	Bitmap^ Fondo3;
	Bitmap^ Marco4;
	Bitmap^ Fondo4;
	Bitmap^ Marco5;
	Bitmap^ Fondo5;

public:

	int minH = 45;
	int minV = 45;
	int maxH = 625;
	int maxV = 600;

	Controller()
	{
		Bplayer = gcnew Bitmap("Resources\\Player.png");
		Bblood = gcnew Bitmap("Resources\\Sangre.png");
		Marco1 = gcnew Bitmap("Resources\\Borde_Mapa_1.1.png");
		Marco2 = gcnew Bitmap("Resources\\Borde_Mapa_1.2.png");
		Marco3 = gcnew Bitmap("Resources\\Borde_Mapa_1.3.png");
		Marco4 = gcnew Bitmap("Resources\\Borde_Mapa_1.4.png");
		Marco5 = gcnew Bitmap("Resources\\Borde_Mapa_1.5.png");
		Fondo1 = gcnew Bitmap("Resources\\Base_Mapa_1.1.jpg");
		Fondo2 = gcnew Bitmap("Resources\\Base_Mapa_1.2.jpg");
		Fondo3 = gcnew Bitmap("Resources\\Base_Mapa_1.3.jpg");
		Fondo4 = gcnew Bitmap("Resources\\Base_Mapa_1.4.jpg");
		Fondo5 = gcnew Bitmap("Resources\\Base_Mapa_1.5.jpg");
		disc1 = gcnew Bitmap("Resources\\Disco1.png");
		disc2 = gcnew Bitmap("Resources\\Disco2.png");

		level = 1;

		player = new Player();

		add = 0;
		cantD = 0;
		discs = new Disc * [cantD];

		dead = false;
	}
	~Controller() {}
	
	void SetLevel(int level) { this->level = level; }
	int GetLevel() { return level; }
	void SetDead(bool dead) { this->dead = dead; }
	bool GetDead() { return dead; }

	void AddDiscsCenter()
	{
		Random j;
		Disc** aux = new Disc * [cantD + 1];
		for (int i = 0; i < cantD; i++)
		{
			aux[i] = discs[i];
		}
		aux[cantD] = new Disc(maxH, maxV, Location::Center, j.Next(1, 4));
		cantD++;
		discs = aux;
	}
	void AddDiscsFrame()
	{
		Disc** aux = new Disc * [cantD + 1];
		for (int i = 0; i < cantD; i++)
		{
			aux[i] = discs[i];
		}
		aux[cantD] = new Disc(maxH, maxV, Location::Frame, 0);
		cantD++;
		discs = aux;
	}

	void ShowMap(Graphics^ g, int xMax, int yMax)
	{
		if (level == 1)
		{
			g->DrawImage(Fondo1, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 2)
		{
			g->DrawImage(Fondo2, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 3)
		{
			g->DrawImage(Fondo3, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 4)
		{
			g->DrawImage(Fondo4, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 5)
		{
			g->DrawImage(Fondo5, 0, 0, xMax - 15, yMax - 38);
		}
	}
	void ShowBlood(Graphics^ g)
	{
		g->DrawImage(Bblood, player->GetX() - 40, player->GetY() - 30, 90, 90);
	}
	void ShowPlayer(Graphics^ g)
	{
		player->Show(g, Bplayer, dead);
	}
	void ShowDiscs(Graphics^ g)
	{
		for (int i = 0; i < cantD; i++)
		{
			discs[i]->Show(g, disc2);
		}
	}
	void ShowFrame(Graphics^ g, int xMax, int yMax)
	{
		if (level == 1)
		{
			g->DrawImage(Marco1, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 2)
		{
			g->DrawImage(Marco2, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 3)
		{
			g->DrawImage(Marco3, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 4)
		{
			g->DrawImage(Marco4, 0, 0, xMax - 15, yMax - 38);
		}
		if (level == 5)
		{
			g->DrawImage(Marco5, 0, 0, xMax - 15, yMax - 38);
		}
	}

	void GameKeys(Keys key)
	{
		if (key == Keys::NumPad1)
			level = 1;
		if (key == Keys::NumPad2)
			level = 2;
		if (key == Keys::NumPad3)
			level = 3;
		if (key == Keys::NumPad4)
			level = 4;
		if (key == Keys::NumPad5)
			level = 5;
	}
	void MovePlayer(Keys key)
	{
		if (key == Keys::W)
			player->Move(DIR::UP, minH, minV, maxH, maxV);
		if (key == Keys::S)
			player->Move(DIR::DOWN, minH, minV, maxH, maxV);
		if (key == Keys::A)
			player->Move(DIR::LEFT, minH, minV, maxH, maxV);
		if (key == Keys::D)
			player->Move(DIR::RIGTH, minH, minV, maxH, maxV);
	}
	void MoveDiscs()
	{
		for (int i = 0; i < cantD; i++)
		{
			discs[i]->Move(maxH, maxV, minH, minV);
		}
	}
	void MotionLess(Keys key)
	{
		player->Move(DIR::NOTHING, minH, minV, maxH, maxV);
	}

	void ChangePlayer()
	{
		dead = true;
		if (dead)
		{
			//p = 1
			player->setBloque(player->getBloque() + 1); //p = 2
			Console::WriteLine(player->getBloque());
			player->SetColumn(player->getCS());
			player->setCS(player->getCS() + 3);
			if (player->getBloque() == player->getI())
			{
				player->setCS(3);
				player->SetColumn(0);
				player->setI(player->getI() + 4);
				if (player->getBloque() == player->getJ())
				{
					player->SetRow(0);
					player->setJ(player->getJ() + 4);
				}
				else
				{
					player->SetRow(4);
				}
			}
		}
	}

	bool Collision(Graphics^ g)
	{
		bool verif = false;
		Rectangle rPlayer = Rectangle(player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight());
		Rectangle rDiscs;
		for (int i = 0; i < cantD; i++)
		{
			rDiscs = Rectangle(discs[i]->GetX(), discs[i]->GetY(), discs[i]->GetWidth(), discs[i]->GetHeight());
			if (rPlayer.IntersectsWith(rDiscs))
			{
				ChangePlayer();
				vidas--;
				seg = 100;
				ShowBlood(g);
				player->SetX(300);
				player->SetY(300);
				verif = true;
			}
			else
			{
				dead = false;
			}
		}
		return verif;
	}

	Random j;
	int numDiscs = j.Next(8, 12);
	int n = 0;

	void Loop(Graphics^ g, int xMax, int yMax, Timer^ timer1)
	{
		ShowMap(g, xMax, yMax);
		ShowPlayer(g);
		if (n < numDiscs / 2)
		{
			add++;
			if (add == 20)
			{
				AddDiscsCenter();
				AddDiscsFrame();
				add = 0;
				n++;
			}
		}
		ShowDiscs(g);
		MoveDiscs();
		Collision(g);
		ShowFrame(g, xMax, yMax);
		
		//Time
		seg+=10;
		
		if (seg == 3000)
		{
			level++;
			if (level == 6)
			{
				timer1->Enabled = false;
				MessageBox::Show("GANASTE");
			}
			vidas = 5;
			seg = 100;
			timer1->Stop();
			MessageBox::Show("NIVEL " + level);
			timer1->Start();
		}
		if (level == 4 || level == 3)
		{
			String^ v = "VIDAS: " + vidas;
			g->DrawString(v, gcnew Font("Arial", 12), Brushes::White, 100, 75);
			String^ t = "TIEMPO: " + seg / 100;
			g->DrawString(t, gcnew Font("Arial", 12), Brushes::White, 300, 75);
			String^ l = "NIVEL: " + level;
			g->DrawString(l, gcnew Font("Arial", 12), Brushes::White, 500, 75);
		}
		else
		{
			String^ v = "VIDAS: " + vidas;
			g->DrawString(v, gcnew Font("Arial", 12), Brushes::White, 100, 5);
			String^ t = "TIEMPO: " + seg / 100;
			g->DrawString(t, gcnew Font("Arial", 12), Brushes::White, 300, 5);
			String^ l = "NIVEL: " + level;
			g->DrawString(l, gcnew Font("Arial", 12), Brushes::White, 500, 5);
		}
		if (vidas < 1)
		{
			timer1->Enabled = false;
			MessageBox::Show("Perdiste >:v ");
		}

	}
};
