#pragma once
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;

class Doc:public Entidad {
private:
	char direcciones;
	
public:
	Doc()
	{
		
		x = 500;
		y = 220;
		dx = dy = 0;
		fila = columna = 0;
		
	}
	~Doc(){}

	void Mostrar(Graphics^ g, Bitmap^ img, int Mapa[26][34])
	{
		alto = img->Height / 4;
		ancho = img->Width / 6;

		Rectangle molde = Rectangle(columna * ancho, fila * alto, ancho, alto);
		Rectangle zoom = Rectangle(x, y, ancho * 3, alto * 3);
		g->DrawImage(img, zoom, molde, GraphicsUnit::Pixel);
		//Contorno del Personaje
		//g->DrawRectangle(Pens::CadetBlue, getRectangle());

		Rectangle  Jugador1 = Rectangle(x + 32 + dx, y + 80, ancho, alto * 0.5);
		Rectangle  Jugador2 = Rectangle(x + 32, y + dy + 80, ancho, alto * 0.5);

		DibujarCeldas(g, Mapa, Jugador1, Jugador2);

		

	}
	void DibujarCeldas(Graphics^ Buffer, int Mapa[26][34], Rectangle Jugador1, Rectangle  Jugador2) {

		//Contorno del Personaje
		//Buffer->DrawRectangle(Pens::Red, Jugador1);
		//Buffer->DrawRectangle(Pens::Yellow, Jugador2);

		int X = 0, Y = 0;
		for (int i = 0; i < 26; i++)
		{
			X = 0;
			for (int j = 0; j < 34; j++)
			{
				Rectangle Rec1 = Rectangle(X, Y, 32, 32);


				if (Mapa[i][j] == 1) {

					//Buffer->DrawRectangle(Pens::White, X, Y, 32, 32); //columana = 34 y fila=26
				}
				else {
					//Buffer->DrawRectangle(Pens::White, X, Y, 32, 32);
					//Buffer->FillRectangle(Brushes::Black, X, Y, 32, 32);
					if (Jugador1.IntersectsWith(Rec1))dx = 0;
					if (Jugador2.IntersectsWith(Rec1))dy = 0;
				}
				X = X + 32;
			}
			Y = Y + 32;
		}
		x = dx + x;
		y = dy + y;
	}

	void Mover(Direccion direccion, Graphics^ g)
	{
		switch (direccion)
		{
		case Direccion::Arriba:
			if (y - dy > 0) {
				dy = -15;
				dx = 0;
			}
			fila = 3;
			columna++;
			if (columna == 3)
				columna = 0;
			direcciones = 'W';
			break;
		case Direccion::Abajo:
			if (y + alto + dy < g->VisibleClipBounds.Bottom) {
				dx = 0;
				dy = 15;
			}
			fila = 0;
			columna++;
			if (columna == 3)
				columna = 0;
			direcciones = 'S';
			break;
		case Direccion::Izquierda:
			if (x - dx > 0) {
				dy = 0;
				dx = -15;
			}
			fila = 1;
			columna++;
			if (columna == 3)
				columna = 0;
			direcciones = 'A';
			break;
		case Direccion::Derecha:
			if (x + ancho + dx < g->VisibleClipBounds.Right) {
				dy = 0;
				dx = 15;
			}
			fila = 2;
			columna++;
			if (columna == 3)
				columna = 0;
			direcciones = 'D';
			break;
		case Direccion::Ninguna:
			dx = dy = 0;
			switch (direcciones)
			{
			case 'S':
				fila = 0;
				//columna = 0;
				break;
			case 'W':
				fila = 3;
				//columna = 0;
				break;
			case 'D':
				fila = 2;
				//columna = 0;
				break;
			case 'A':
				fila = 1;
				//columna = 0;
				break;
			default:
				break;
			}
			break;
		}


	}

	Rectangle getRectangle() {

		Rectangle ColisionVirus = Rectangle(x+24, y, ancho*1.5, alto*3);

		return ColisionVirus;
		
	}


	char getDireccion() { return direcciones; }

};