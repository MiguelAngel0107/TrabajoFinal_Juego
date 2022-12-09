#pragma once
#include "MyForm.h"
#include "Nivel2.h"

namespace TrabajoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Inicio
	/// </summary>
	public ref class Inicio : public System::Windows::Forms::Form
	{
	public:
		Inicio(void)
		{
			InitializeComponent();
			g = panel1->CreateGraphics();
			bmpFondoI = gcnew Bitmap("fondoInicio.jpg");
			bfc = BufferedGraphicsManager::Current;
			bf = bfc->Allocate(g, panel1->ClientRectangle);
		}

	protected:

		~Inicio()
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
		Bitmap^ bmpFondoI;
		BufferedGraphics^ bf;
		BufferedGraphicsContext^ bfc;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button3;





		   Graphics^ g;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Inicio::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(251, 122);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(357, 55);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Inicio del Juego";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(315, 257);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(207, 36);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Nivel 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Inicio::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(315, 323);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(207, 36);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Nivel 2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Inicio::button2_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(800, 523);
			this->panel1->TabIndex = 3;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(756, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(32, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"?";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Inicio::button3_Click);
			// 
			// Inicio
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 523);
			this->Controls->Add(this->panel1);
			this->Name = L"Inicio";
			this->Text = L"Inicio";
			this->Load += gcnew System::EventHandler(this, &Inicio::Inicio_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Inicio_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		TrabajoFinal::MyForm^ juego = gcnew TrabajoFinal::MyForm();
		
		this->Visible = false;
		juego->ShowDialog();
		this->Visible = true;
		
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		TrabajoFinal::Nivel2^ juego = gcnew TrabajoFinal::Nivel2();
		this->Visible = false;
		juego->ShowDialog();
		this->Visible = true;
		
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		bf->Graphics->Clear(Color::WhiteSmoke);
		bf->Graphics->DrawImage(bmpFondoI, 0, 0, bmpFondoI->Width, bmpFondoI->Height);
		bf->Render(g);
	}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Instrucciones: Para ganar necesitas curar a todos los enfermos dandoles 10 pastillas a cada uno,"+ 
		"y a la vez tienes que evitar chocar con los virus");
}
};
}
