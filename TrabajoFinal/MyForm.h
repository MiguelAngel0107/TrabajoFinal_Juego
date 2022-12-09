#pragma once
#include <ctime>
#include "Doc.h"
#include "Paciente.h"
#include "Pastillas.h"
#include "Control.h"
#include "Map.h"

namespace TrabajoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			srand(time(NULL));
			g = this->CreateGraphics();
			bfc = BufferedGraphicsManager::Current;
			bf = bfc->Allocate(g, this->ClientRectangle);
			doctor = new Doc();
			doctorImg = gcnew Bitmap("doctor.png");	
			enfermoImg = gcnew Bitmap("enfermos.png");
			pastillaImg = gcnew Bitmap("pastilla.png");
			virusImg = gcnew Bitmap("Virus.png");
			bmpFondo = gcnew Bitmap("nivel1.jpg");
			control = new Controlador();
			control->createEnemies();
			control->createPacientes();

		}

	protected:

		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	
	protected:

	private:
		Graphics^ g;
		Doc* doctor;
		Bitmap^ doctorImg;

		Bitmap^ enfermoImg;

		Pastilla* pastilla;
		Bitmap^ pastillaImg;

		Bitmap^ virusImg;

		Bitmap^ bmpFondo;

		Controlador* control;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label1;


		   BufferedGraphicsContext^ bfc;
		   BufferedGraphics^ bf;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(0, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(60, 24);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"label1";
			   this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->Location = System::Drawing::Point(0, 22);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(60, 24);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"label2";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1088, 832);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			   this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			   this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		//bf->Graphics->Clear(Color::DarkGray);
		
		//clear
		bf->Graphics->Clear(Color::WhiteSmoke);
		label1->Text = "Bolas Lanzadas: " + control->getCantP();
		label2->Text = "Vidas: " + control->Vidas();
		
		//Colision
		control->Colision(bf->Graphics, virusImg, pastillaImg);
		control->ColisionDoc(virusImg, doctor->getRectangle());


		//Mostrar
		bf->Graphics->DrawImage(bmpFondo, 0, 0, bmpFondo->Width *2, bmpFondo->Height *2);
		control->DibujarPaciente(bf->Graphics, enfermoImg);
		control->drawEveryThing(bf->Graphics, virusImg, pastillaImg, Mapa1);
		control->moveEveryThing(bf->Graphics, Mapa1);


		doctor->Mostrar(bf->Graphics, doctorImg, Mapa0);
		


		bf->Render(g);
		//delete bf, bfc;
		delete bfc, bf;

		if (control->Vidas() < 0) {
			this->timer1->Enabled = false;
			MessageBox::Show("PERDISTE");
			this->Close();
		}
		if (control->Curados() == 5) {
			this->timer1->Enabled = false;
			MessageBox::Show("GANASTE");
			this->Close();
		}
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

		if (e->KeyCode == Keys::Up) {
			doctor->Mover(Direccion::Arriba, g);
		}
		else if (e->KeyCode == Keys::Down) {
			doctor->Mover(Direccion::Abajo, g);
		}
		else if (e->KeyCode == Keys::Left) {
			doctor->Mover(Direccion::Izquierda, g);
		}
		else if (e->KeyCode == Keys::Right) {
			doctor->Mover(Direccion::Derecha, g);
		}
		else if (e->KeyCode == Keys::Space) {
			Pastilla* p = new Pastilla(doctor->GetX(), doctor->GetY(), doctor->getDireccion());
			control->addBullet(p);
		}
		else if (e->KeyCode == Keys::Escape) {
			this->timer1->Enabled = false;
			this->Close();
		}

	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		g = this->CreateGraphics();
	}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		doctor->Mover(Direccion::Ninguna, g);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->timer1->Enabled = false;
		this->Close();
	}
};
}
