#pragma once
#include <conio.h>
#include <iostream>
#include "Entidad.h"
using namespace System;
using namespace System::Drawing;
using namespace std;



class Paciente : public Entidad {
private:
	bool curados=false;
public:
	Paciente(int X, int Y)
	{
		x = X;
		y = Y;
		fila = columna = 0;

	}
	~Paciente() {}

	
	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		alto = img->Height /1;
		ancho = img->Width /2;

		Rectangle molde = Rectangle(columna * ancho, fila * alto, ancho, alto);
	    Rectangle zoom = Rectangle(x, y, ancho * 2.5, alto * 2.5);
		g->DrawImage(img, zoom, molde, GraphicsUnit::Pixel);


		Rectangle ColisionPaciente = Rectangle(x+30, y+25, ancho*1.2, alto*1.8);
		//g->DrawRectangle(Pens::White, ColisionPaciente);
	}
	void CambioColor(int cant) {
		if (cant == 10) {
			columna = 1;
			curados=true;
		}
		
	}

	bool getCurados() { return curados; };

	Rectangle getRectangle() {

		Rectangle ColisionPaciente = Rectangle(x + 30, y + 25, ancho * 1.2, alto * 1.8);
		return ColisionPaciente;
		
	}
};


