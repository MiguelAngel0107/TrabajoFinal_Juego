#pragma once
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;

class Virus :public Entidad {
private:
	char direcciones;
	bool visibility;
public:
	Virus(int X, int Y)
	{
		x = X;
		y = Y;
		dx = dy = 3;
		fila = rand() % 2;
		columna = rand() % 3;
		direcciones = rand()%2;
		visibility = true;
		
	}
	~Virus() {}

	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		alto = (img->Height) / 2;
		ancho = (img->Width ) / 3;

		Rectangle molde = Rectangle(columna * ancho, fila * alto, ancho, alto);

		g->DrawImage(img, x, y, molde, GraphicsUnit::Pixel);


		
	}

	void Mover(Graphics^ g, int Mapa[26][34]) {

		Rectangle ColisionVirus = Rectangle(x + 40, y + 20 + dy, ancho * 0.5, alto * 0.7);
		Rectangle ColisionVirus1 = Rectangle(x + 40 + dx, y + 20, ancho * 0.5, alto * 0.7);
		
		//Contorno del Personaje
		//g->DrawRectangle(Pens::Red, ColisionVirus);
		//g->DrawRectangle(Pens::Yellow, ColisionVirus);

		int X = 0, Y = 0;
		for (int i = 0; i < 26; i++)
		{
			X = 0;
			for (int j = 0; j < 34; j++)
			{
				Rectangle Rec1 = Rectangle(X, Y, 32, 32);


				if (Mapa[i][j] == 1) {

					//g->DrawRectangle(Pens::White, X, Y, 32, 32); //columana = 34 y fila=26
				}
				else {
					//g->DrawRectangle(Pens::White, X, Y, 32, 32);
					//Buffer->FillRectangle(Brushes::Black, X, Y, 32, 32);
					if (ColisionVirus1.IntersectsWith(Rec1)) dx *= -1;
					if (ColisionVirus.IntersectsWith(Rec1)) dy *= -1;
				}
				X = X + 32;
			}
			Y = Y + 32;
		}
		x = dx + x;
		y = dy + y;



	}
	Rectangle getRectangle(Bitmap^ img) {
		Rectangle ColisionVirus = Rectangle(x + 40, y + 20, ancho * 0.5, alto * 0.7);
		return ColisionVirus;
	}
	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }
};