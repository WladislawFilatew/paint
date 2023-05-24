#pragma once
#include "figur.h"
#include <vector>
namespace figura {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace std;
	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		List<mcf::figure^> arr;
	private:
		int flag_line = 0;
		int flag_rec = 0;
		int flag_elips = 0;
		int flag_treug = 0;
		int flag_mno = 0;
		bool flag_color = 0;
		bool flag_perem = false; int x_per = 0, y_per = 0;
		bool flag_izm = false;
		int nap_x = 0;
		int nap_y = 0;
		int lx = 1000, ly = 1000;
		int px = -1000, py = -1000;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ karandash;


		   Color color;

	public:
		MyForm(void)
		{
			InitializeComponent();
			this->BackColor = Color::White;
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Button^ rectagle;
	private: System::Windows::Forms::Button^ ellips;
	private: System::Windows::Forms::Button^ line;

	private: System::Windows::Forms::Button^ treug;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
#pragma endregion
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

	}
	private: System::Void karandash_Click(System::Object^ sender, System::EventArgs^ e) {
		flag_mno = 1;
	}
	private: System::Void rectagle_Click(System::Object^ sender, System::EventArgs^ e) {
		flag_rec = 1;
	}
	private: System::Void ellips_Click(System::Object^ sender, System::EventArgs^ e) {
		flag_elips = 1;
	}
	private: System::Void line_Click(System::Object^ sender, System::EventArgs^ e) {
		flag_line = 1;
	}
	private: System::Void treug_Click(System::Object^ sender, System::EventArgs^ e) {
		flag_treug = 1;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//удаление всех элементов
		int kol = arr.Count;
		for (int i = 0; i < kol; i++) {
			arr[i]->Hide();
		}
		lx = ly = 1000;
		px = py = -1000;
		arr.Clear();
	}
	private: System::Void panel2_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		int x = Cursor->Position.X - this->Location.X - panel2->Location.X - 8;
		int y = Cursor->Position.Y - this->Location.Y - panel2->Location.Y - 32;
		if (flag_rec == 1) {
			mcf::rectagle^ pt = gcnew mcf::rectagle(panel2->CreateGraphics(), x, y, 1, 1);
			pt->Show();
			arr.Add(pt);
			flag_rec = 2;
		}
		if (flag_elips == 1) {
			mcf::elips^ pt = gcnew mcf::elips(panel2->CreateGraphics(), x, y, 1, 1);
			pt->Show();
			arr.Add(pt);
			flag_elips = 2;
		}
		if (flag_line == 1) {
			mcf::line^ pt = gcnew mcf::line(panel2->CreateGraphics(), x, y, 1);
			pt->Show();
			arr.Add(pt);
			flag_line = 2;
		}
		if (flag_treug == 1) {
			mcf::treugl^ pt = gcnew mcf::treugl(panel2->CreateGraphics(), x, y, 0, 1, 1);
			pt->Show();
			arr.Add(pt);
			flag_treug = 2;
		}
		if (flag_mno == 1) {
			mcf::mno^ pt = gcnew mcf::mno(panel2->CreateGraphics(), x, y);
			arr.Add(pt);
			flag_mno = 2;
		}
		if (!(flag_rec == 2 || flag_elips == 2 || flag_treug == 2 || flag_mno == 2 || flag_line == 2)) {
			for (int i = 0; i < arr.Count; i++) {
				if (arr[i]->rebro_izm(x, y)) {
					arr.Add(arr[i]);
						arr.RemoveAt(i);
						flag_izm = true;
						x_per = x;
						y_per = y;
						break;
				}
				if (arr[i]->contur(x, y)) {
					arr.Add(arr[i]);
					arr.RemoveAt(i);
					flag_perem = true;
					x_per = x;
					y_per = y;
					break;
				}
			}
		}

	}
	private: System::Void panel2_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		int x = Cursor->Position.X - this->Location.X - panel2->Location.X - 8;
		int y = Cursor->Position.Y - this->Location.Y - panel2->Location.Y - 32;
		if (flag_rec == 2 || flag_elips == 2 || flag_treug == 2) {
			int x_v = arr[arr.Count - 1]->Get_x();
			int y_v = arr[arr.Count - 1]->Get_y();
			arr[arr.Count - 1]->iz_razmer(y - y_v, x - x_v);
		}
		if (flag_line == 2) {
			int x_v = arr[arr.Count - 1]->Get_x();
			int y_v = arr[arr.Count - 1]->Get_y();
			arr[arr.Count - 1]->iz_razmer(x - x_v, y - y_v);
		}
		if (flag_mno == 2) {
			mcf::mno^ k = (mcf::mno^)arr[arr.Count - 1];
			k->Add(x, y);
			arr[arr.Count - 1] = k;
		}
		if (flag_izm && !(flag_rec == 2 || flag_elips == 2 || flag_treug == 2 || flag_mno == 2 || flag_line == 2)) {
			int iz_x = arr[arr.Count - 1]->Get_px() - arr[arr.Count - 1]->Get_x() + (x - x_per);
			int iz_y = arr[arr.Count - 1]->Get_ny() - arr[arr.Count - 1]->Get_y() + (y - y_per);
			arr[arr.Count - 1]->iz_razmer(iz_x,iz_y);
			x_per = x;
			y_per = y;
		}
		if (flag_perem && !(flag_rec == 2 || flag_elips == 2 || flag_treug == 2 || flag_mno == 2 ||  flag_line == 2 || flag_izm)) {
			arr[arr.Count - 1]->go((x - x_per), (y - y_per));
			x_per = x;
			y_per = y;
		}
	}
		   int Min(int a, int b) {
			   if (a < b) return a;
			   return b;
		   }
		   int Max(int a, int b) {
			   if (a > b) return a;
			   return b;
		   }
	private: System::Void panel2_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		flag_rec = 0;
		if (flag_mno == 2) {
			arr[arr.Count - 1]->Show();
			flag_mno = 0;
		}
		flag_elips = 0;
		flag_line = 0;
		flag_treug = 0;
		flag_perem = 0;
		flag_izm = 0;
		if (arr.Count > 0) {
			lx = Min(arr[arr.Count - 1]->Get_px(), lx);
			lx = Min(arr[arr.Count - 1]->Get_x(), lx);
			px = Max(arr[arr.Count - 1]->Get_px(), px);
			px = Max(arr[arr.Count - 1]->Get_x(), px);

			ly = Min(arr[arr.Count - 1]->Get_ny(), lx);
			ly = Min(arr[arr.Count - 1]->Get_y(), lx);
			py = Max(arr[arr.Count - 1]->Get_ny(), py);
			py = Max(arr[arr.Count - 1]->Get_y(), py);
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		arr[arr.Count - 1]->Hide();
		arr.RemoveAt(arr.Count - 1);
		for (int i = 0; i < arr.Count; i++)
			arr[i]->Show();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::White;
		flag_color = true;
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Black;
		flag_color = true;
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Blue;
		flag_color = true;
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Yellow;
		flag_color = true;
	}
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Green;
		flag_color = true;
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Red;
		flag_color = true;
	}
	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::Gray;
		flag_color = true;
	}
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
		color = Color::SkyBlue;
		flag_color = true;
	}
	private: System::Void panel2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (flag_color) {
			int x = Cursor->Position.X - this->Location.X - panel2->Location.X - 8;
			int y = Cursor->Position.Y - this->Location.Y - panel2->Location.Y - 32;
			for (int i = arr.Count - 1; i >= 0; i--) {
				if (arr[i]->clic(x, y)) {
					arr[i]->flag = true;
					arr[i]->Set_color(color);
					arr[i]->Show();
					break;
				}
			}
			flag_color = false;
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < arr.Count; i++) {
			arr[i]->go(nap_x, nap_y);
		}
		px += nap_x;
		lx += nap_x;
		py += nap_y;
		ly += nap_y;
		if (lx <= 10 && nap_x == -1) {
			timer1->Stop();
			nap_x = nap_y = 0;
		}
		if (ly <= 10 && nap_y == -1) {
			timer1->Stop();
			nap_x = nap_y = 0;
		}
		if (px >= panel2->Width - 10 && nap_x == 1) {
			timer1->Stop();
			nap_x = nap_y = 0;
		}
		if (py >= panel2->Height - 10 && nap_y == 1) {
			timer1->Stop();
			nap_x = nap_y = 0;
		}

	}
	private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
		nap_y = -1;
		timer1->Start();
	}
	private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
		nap_x = 1;
		timer1->Start();
	}
	private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
		nap_y = 1;
		timer1->Start();
	}
	private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
		nap_x = -1;
		timer1->Start();
	}
	private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {
		nap_x = 0;
		nap_y = 0;
		timer1->Stop();
	}
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->treug = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->line = (gcnew System::Windows::Forms::Button());
			this->ellips = (gcnew System::Windows::Forms::Button());
			this->rectagle = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->karandash = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->panel1->Controls->Add(this->karandash);
			this->panel1->Controls->Add(this->panel4);
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->treug);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->line);
			this->panel1->Controls->Add(this->ellips);
			this->panel1->Controls->Add(this->rectagle);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(177, 787);
			this->panel1->TabIndex = 0;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->panel4->Controls->Add(this->button15);
			this->panel4->Controls->Add(this->button14);
			this->panel4->Controls->Add(this->button13);
			this->panel4->Controls->Add(this->button11);
			this->panel4->Controls->Add(this->button12);
			this->panel4->Location = System::Drawing::Point(21, 633);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(121, 128);
			this->panel4->TabIndex = 3;
			// 
			// button15
			// 
			this->button15->BackColor = System::Drawing::Color::White;
			this->button15->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button15.BackgroundImage")));
			this->button15->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button15->FlatAppearance->BorderSize = 0;
			this->button15->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button15->Location = System::Drawing::Point(0, 44);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(36, 40);
			this->button15->TabIndex = 9;
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &MyForm::button15_Click);
			// 
			// button14
			// 
			this->button14->BackColor = System::Drawing::Color::White;
			this->button14->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button14.BackgroundImage")));
			this->button14->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button14->FlatAppearance->BorderSize = 0;
			this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button14->Location = System::Drawing::Point(42, 46);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(33, 36);
			this->button14->TabIndex = 8;
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &MyForm::button14_Click);
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::Color::White;
			this->button13->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button13.BackgroundImage")));
			this->button13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button13->FlatAppearance->BorderSize = 0;
			this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button13->Location = System::Drawing::Point(81, 44);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(36, 40);
			this->button13->TabIndex = 7;
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::White;
			this->button11->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button11.BackgroundImage")));
			this->button11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button11->FlatAppearance->BorderSize = 0;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Location = System::Drawing::Point(40, 0);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(36, 40);
			this->button11->TabIndex = 6;
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::White;
			this->button12->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button12.BackgroundImage")));
			this->button12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button12->FlatAppearance->BorderSize = 0;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Location = System::Drawing::Point(40, 88);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(36, 40);
			this->button12->TabIndex = 5;
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->panel3->Controls->Add(this->button9);
			this->panel3->Controls->Add(this->button10);
			this->panel3->Controls->Add(this->button7);
			this->panel3->Controls->Add(this->button8);
			this->panel3->Controls->Add(this->button5);
			this->panel3->Controls->Add(this->button6);
			this->panel3->Controls->Add(this->button4);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Location = System::Drawing::Point(22, 33);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(115, 265);
			this->panel3->TabIndex = 2;
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::Cyan;
			this->button9->FlatAppearance->BorderSize = 0;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Location = System::Drawing::Point(65, 188);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(36, 41);
			this->button9->TabIndex = 10;
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::Gray;
			this->button10->FlatAppearance->BorderSize = 0;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Location = System::Drawing::Point(13, 188);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(36, 41);
			this->button10->TabIndex = 9;
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::Red;
			this->button7->FlatAppearance->BorderSize = 0;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Location = System::Drawing::Point(65, 128);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(36, 41);
			this->button7->TabIndex = 8;
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button8->FlatAppearance->BorderSize = 0;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Location = System::Drawing::Point(13, 128);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(36, 41);
			this->button8->TabIndex = 7;
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Yellow;
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(65, 69);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(36, 41);
			this->button5->TabIndex = 6;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Blue;
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(13, 69);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(36, 41);
			this->button6->TabIndex = 5;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(65, 13);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(36, 41);
			this->button4->TabIndex = 4;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::White;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(13, 13);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(36, 41);
			this->button3->TabIndex = 3;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button2->Location = System::Drawing::Point(92, 543);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 52);
			this->button2->TabIndex = 1;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// treug
			// 
			this->treug->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"treug.BackgroundImage")));
			this->treug->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->treug->Location = System::Drawing::Point(87, 410);
			this->treug->Name = L"treug";
			this->treug->Size = System::Drawing::Size(50, 52);
			this->treug->TabIndex = 0;
			this->treug->UseVisualStyleBackColor = true;
			this->treug->Click += gcnew System::EventHandler(this, &MyForm::treug_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(22, 543);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(61, 52);
			this->button1->TabIndex = 0;
			this->button1->Text = L"del";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// line
			// 
			this->line->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"line.BackgroundImage")));
			this->line->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->line->Location = System::Drawing::Point(21, 411);
			this->line->Name = L"line";
			this->line->Size = System::Drawing::Size(50, 55);
			this->line->TabIndex = 0;
			this->line->UseVisualStyleBackColor = true;
			this->line->Click += gcnew System::EventHandler(this, &MyForm::line_Click);
			// 
			// ellips
			// 
			this->ellips->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ellips.BackgroundImage")));
			this->ellips->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ellips->Location = System::Drawing::Point(87, 341);
			this->ellips->Name = L"ellips";
			this->ellips->Size = System::Drawing::Size(50, 53);
			this->ellips->TabIndex = 0;
			this->ellips->UseVisualStyleBackColor = true;
			this->ellips->Click += gcnew System::EventHandler(this, &MyForm::ellips_Click);
			// 
			// rectagle
			// 
			this->rectagle->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"rectagle.BackgroundImage")));
			this->rectagle->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->rectagle->Location = System::Drawing::Point(21, 341);
			this->rectagle->Name = L"rectagle";
			this->rectagle->Size = System::Drawing::Size(50, 53);
			this->rectagle->TabIndex = 0;
			this->rectagle->UseVisualStyleBackColor = true;
			this->rectagle->Click += gcnew System::EventHandler(this, &MyForm::rectagle_Click);
			// 
			// panel2
			// 
			this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(177, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1091, 787);
			this->panel2->TabIndex = 1;
			this->panel2->Click += gcnew System::EventHandler(this, &MyForm::panel2_Click);
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->panel2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel2_MouseDown);
			this->panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel2_MouseMove);
			this->panel2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panel2_MouseUp);
			// 
			// karandash
			// 
			this->karandash->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"karandash.BackgroundImage")));
			this->karandash->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->karandash->Location = System::Drawing::Point(21, 477);
			this->karandash->Name = L"karandash";
			this->karandash->Size = System::Drawing::Size(50, 53);
			this->karandash->TabIndex = 2;
			this->karandash->UseVisualStyleBackColor = true;
			this->karandash->Click += gcnew System::EventHandler(this, &MyForm::karandash_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(1268, 787);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panel1->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
};
}
