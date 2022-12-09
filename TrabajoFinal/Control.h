#pragma once
#include "Doc.h"
#include "Paciente.h"
#include "Pastillas.h"
#include "Virus.h"
#include <vector>

using namespace System::Drawing;
using namespace System;

class Controlador {
private:
	vector<Pastilla*>Pastillas;
	vector<Virus*>virus;
	vector<Paciente*>paciente;
	int cantP=0;
	int c = 0;
	int sanos = 0;
	int vidas = 5;
public:
	Controlador(){
		
	}
	~Controlador(){}

	void createEnemies() {

		Virus* a = new Virus(95, 185);
		Virus* b = new Virus(95, 480);
		Virus* c = new Virus(280, 185);
		Virus* d = new Virus(480, 480);
		Virus* e = new Virus(280, 480);

		virus.push_back(a);
		virus.push_back(b);
		virus.push_back(c);
		virus.push_back(d);
		virus.push_back(e);

	}
	void createPacientes() {

		Paciente* a = new Paciente(95, 185);
		Paciente* b = new Paciente(100, 480);
		Paciente* c = new Paciente(280, 185);
		Paciente* d = new Paciente(480, 480);
		Paciente* e = new Paciente(280, 480);

		paciente.push_back(a);
		paciente.push_back(b);
		paciente.push_back(c);
		paciente.push_back(d);
		paciente.push_back(e);
		

	}
	void DibujarPaciente(Graphics^g, Bitmap^p) {
		for (int i = 0; i < paciente.size(); i++)
		{
			paciente[i]->Mostrar(g, p);
		}
	}
	void addBullet(Pastilla* b) {
		Pastillas.push_back(b);
		cantP++;
	}

	void drawEveryThing(Graphics^ g, Bitmap^ bmpEnemy, Bitmap^ bmpBullet, int Mapa[26][34]) {
		for (int i = 0; i < virus.size(); i++)
		{
			virus[i]->Mostrar(g, bmpEnemy);
		}
		for (int i = 0; i < Pastillas.size(); i++)
		{
			Pastillas[i]->Mostrar(g, bmpBullet);
		}
	}

	void moveEveryThing(Graphics^ g, int Mapa[26][34]) {
		for (int i = 0; i < virus.size(); i++)
		{
			virus[i]->Mover(g, Mapa);
		}
		for (int i = 0; i < Pastillas.size(); i++)
		{
			Pastillas[i]->Mover(g);
		}
	}

	void Colision(Graphics^ g, Bitmap^ Vimg, Bitmap^ Pimg) {
		//verificar
		for (int i = 0; i < Pastillas.size(); i++)
		{
			if (Pastillas[i]->GetX() <= 0 || Pastillas[i]->GetX() >= g->VisibleClipBounds.Width ||
				Pastillas[i]->GetY() <= 0 || Pastillas[i]->GetY() >= g->VisibleClipBounds.Height) {
				Pastillas[i]->setVisibility(false);
			}
		}

		// colision bullet vs enemy
		for (int i = 0; i < paciente.size(); i++)
		{
			for (int j = 0; j < Pastillas.size(); j++)
			{
				if (paciente[i]->getRectangle().IntersectsWith(Pastillas[j]->getRectangle(Pimg))) {
					c = c + 1;
					paciente[i]->CambioColor(c);
					if (c == 10) { c = 0; }
					Pastillas[j]->setVisibility(false);
				}
			}
		}
		//borrar
		for (int i = 0; i < Pastillas.size(); i++)
		{
			if (!Pastillas[i]->getVisibility()) { //if(Bullets[i]->getVisibility()==false)
				Pastillas.erase(Pastillas.begin() + i);
				cantP--;
			}
		}

	}
	void ColisionDoc(Bitmap^ Vimg, Rectangle R) {
		// colision bullet vs enemy
		for (int i = 0; i < virus.size(); i++)
		{
			if (virus[i]->getRectangle(Vimg).IntersectsWith(R)) {
				vidas--;
			}
		}
	}
	bool Curados() {
		for (int i = 0; i < paciente.size(); i++)
		{
			if (paciente[i]->getCurados() == true) {
				sanos++;
			}

		}
		return sanos;
	}

	int Vidas() { return vidas; }

	int getCantP() { return cantP; }
};
