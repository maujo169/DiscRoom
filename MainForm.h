#pragma once
#include "Controller.h"
namespace DiscRoom {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			timer1->Enabled = true;
			game = gcnew Controller();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^	 timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		Controller^ game;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(684, 661);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Disc Room";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		Graphics^ canvas = this->CreateGraphics();
		BufferedGraphicsContext^ espacioBuffer = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacioBuffer->Allocate(canvas, this->ClientRectangle);
		buffer->Graphics->Clear(Color::White);
		
		game->Loop(buffer->Graphics, this->Width, this->Height, timer1);
		
		buffer->Render(canvas);
		delete buffer;
		delete espacioBuffer;
		delete canvas;
	}
	private: System::Void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
	{
		game->MovePlayer(e->KeyCode);
		game->GameKeys(e->KeyCode);
	}
	private: System::Void MainForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
	{
		game->MotionLess(e->KeyCode);
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		MessageBox::Show("NIVEL 1");
	}
	};
}
