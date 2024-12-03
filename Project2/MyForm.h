#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <numeric>
#include <sstream>
#include <winsock2.h>  // For socket programming
#include "ReaderThread.h"

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib for Windows sockets

WSADATA wsaData;
SOCKET sock;
sockaddr_in serverAddr;
static std::string fullMessage;

namespace Project2 {
	using namespace System;
	using namespace System::Text;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox10;
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			closesocket(sock);
			WSACleanup();
		}

	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column10;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private:
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->checkBox3);
			this->groupBox1->Controls->Add(this->checkBox2);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(761, 121);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"CHOOSE SUBSCRIPTIONS";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(548, 52);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(180, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"SUBSCRIBE";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(342, 54);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(103, 20);
			this->checkBox3->TabIndex = 2;
			this->checkBox3->Text = L"Stock prices";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(180, 54);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(82, 20);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = L"Currency";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(31, 54);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(80, 20);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Weather";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Location = System::Drawing::Point(12, 147);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(761, 115);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Tag = L"";
			this->groupBox2->Text = L"WEATHER";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(591, 39);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Humidity:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(404, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Pressure:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(220, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Temperature:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(28, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Condition:";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(594, 58);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(134, 22);
			this->textBox4->TabIndex = 3;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(407, 58);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(134, 22);
			this->textBox3->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(223, 58);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(134, 22);
			this->textBox2->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(31, 58);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(134, 22);
			this->textBox1->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->groupBox3->Controls->Add(this->label9);
			this->groupBox3->Controls->Add(this->label10);
			this->groupBox3->Controls->Add(this->textBox9);
			this->groupBox3->Controls->Add(this->textBox10);
			this->groupBox3->Location = System::Drawing::Point(12, 407);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(392, 115);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"CURRENCY";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(220, 35);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(39, 16);
			this->label9->TabIndex = 19;
			this->label9->Text = L"USD:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(28, 35);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(39, 16);
			this->label10->TabIndex = 18;
			this->label10->Text = L"EUR:";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(223, 54);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(134, 22);
			this->textBox9->TabIndex = 17;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(31, 57);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(134, 22);
			this->textBox10->TabIndex = 16;
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->groupBox4->Controls->Add(this->label5);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->textBox5);
			this->groupBox4->Controls->Add(this->textBox6);
			this->groupBox4->Controls->Add(this->textBox7);
			this->groupBox4->Controls->Add(this->textBox8);
			this->groupBox4->Location = System::Drawing::Point(12, 277);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(761, 115);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"STOCK PRICE";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(591, 36);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(34, 16);
			this->label5->TabIndex = 15;
			this->label5->Text = L"Low:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(404, 36);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(41, 16);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Hight:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(220, 36);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(52, 16);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Current:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(25, 36);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(42, 16);
			this->label8->TabIndex = 12;
			this->label8->Text = L"Type:";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(594, 55);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(134, 22);
			this->textBox5->TabIndex = 11;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(407, 58);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(134, 22);
			this->textBox6->TabIndex = 10;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(223, 58);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(134, 22);
			this->textBox7->TabIndex = 9;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(28, 58);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(134, 22);
			this->textBox8->TabIndex = 8;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(645, 485);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(128, 37);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Clear";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(780, 534);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma region
		void UpdateTextBoxAndMessageBox() {
			// Розділяємо fullMessage на окремі рядки
			std::vector<std::string> lines;
			std::string line;
			std::istringstream stream(fullMessage);

			while (std::getline(stream, line)) {
				lines.push_back(line);
			}

			// Перевірка, який чекбокс вибрано, і оновлення відповідних TextBox
			if (checkBox1->Checked && !checkBox2->Checked && !checkBox3->Checked) {
				// Якщо обрано перший чекбокс (п'ять рядків)
				if (lines.size() >= 5) {
					textBox1->Text = gcnew System::String(lines[4].c_str());  // 5-й рядок (індексація з 0)
					textBox2->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox3->Text = gcnew System::String(lines[2].c_str());  // 3-й рядок
					textBox4->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
				}
			}
			else if (checkBox2->Checked && !checkBox1->Checked && !checkBox3->Checked) {
				// Якщо обрано другий чекбокс (три рядки)
				if (lines.size() >= 3) {
					textBox9->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox10->Text = gcnew System::String(lines[2].c_str()); // 3-й рядок
				}
			}
			else if (checkBox3->Checked && !checkBox2->Checked && !checkBox1->Checked) {
				// Якщо обрано третій чекбокс (чотири рядки)
				if (lines.size() >= 4) {
					textBox8->Text = gcnew System::String(lines[0].c_str());  // 1-й рядок
					textBox7->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox6->Text = gcnew System::String(lines[2].c_str());  // 3-й рядок
					textBox5->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
				}
			}
			else if (checkBox1->Checked && checkBox2->Checked && !checkBox3->Checked) {
				// Якщо обрано перший чекбокс і другий (п'ять рядків плюс три рядки)
				if (lines.size() >= 8) {
					textBox1->Text = gcnew System::String(lines[4].c_str());  // 5-й рядок (індексація з 0)
					textBox2->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox3->Text = gcnew System::String(lines[2].c_str());  // 3-й рядок
					textBox4->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
					textBox9->Text = gcnew System::String(lines[6].c_str());  // 7-й рядок
					textBox10->Text = gcnew System::String(lines[7].c_str()); // 8-й рядок
				}
			}
			else if (checkBox1->Checked && !checkBox2->Checked && checkBox3->Checked) {
				// Якщо обрано перший чекбокс і третій (п'ять рядків плюс чотири рядки)
				if (lines.size() >= 9) {
					textBox1->Text = gcnew System::String(lines[4].c_str());  // 5-й рядок (індексація з 0)
					textBox2->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox3->Text = gcnew System::String(lines[2].c_str());  // 3-й рядок
					textBox4->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
					textBox8->Text = gcnew System::String(lines[5].c_str());  // 6-й рядок
					textBox7->Text = gcnew System::String(lines[6].c_str());  // 7-й рядок
					textBox6->Text = gcnew System::String(lines[7].c_str());  // 8-й рядок
					textBox5->Text = gcnew System::String(lines[8].c_str());  // 9-й рядок
				}
			}
			else if (!checkBox1->Checked && checkBox2->Checked && checkBox3->Checked) {
				// Якщо обрано другий і третій (чотири рядки плюс три рядки)
				if (lines.size() >= 7) {
					textBox9->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox10->Text = gcnew System::String(lines[2].c_str()); // 3-й рядок
					textBox8->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
					textBox7->Text = gcnew System::String(lines[4].c_str());  // 5-й рядок
					textBox6->Text = gcnew System::String(lines[5].c_str());  // 6-й рядок
					textBox5->Text = gcnew System::String(lines[6].c_str());  // 7-й рядок
				}
			}
			else if (checkBox1->Checked && checkBox2->Checked && checkBox3->Checked) {
				// Якщо обрано всі (5 + 3 + 4)
				if (lines.size() >= 12) {
					textBox1->Text = gcnew System::String(lines[4].c_str());  // 5-й рядок (індексація з 0)
					textBox2->Text = gcnew System::String(lines[1].c_str());  // 2-й рядок
					textBox3->Text = gcnew System::String(lines[2].c_str());  // 3-й рядок
					textBox4->Text = gcnew System::String(lines[3].c_str());  // 4-й рядок
					textBox9->Text = gcnew System::String(lines[6].c_str());  // 7-й рядок
					textBox10->Text = gcnew System::String(lines[7].c_str()); // 8-й рядок
					textBox8->Text = gcnew System::String(lines[8].c_str());  // 9-й рядок
					textBox7->Text = gcnew System::String(lines[9].c_str());  // 10-й рядок
					textBox6->Text = gcnew System::String(lines[10].c_str());  // 11-й рядок
					textBox5->Text = gcnew System::String(lines[11].c_str());  // 12-й рядок
				}
			}

			// Виведення повідомлення в MessageBox
			//MessageBox::Show(gcnew System::String(fullMessage.c_str()), "Received Message", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Очищення fullMessage
			fullMessage.clear();
		}


private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	// Ініціалізація Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		MessageBox::Show("WSAStartup failed. Error: " + WSAGetLastError(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	// Створення сокету
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		MessageBox::Show("Socket creation failed. Error: " + WSAGetLastError(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		WSACleanup();
		return;
	}

	// Налаштування адреси сервера (замініть на вашу IP-адресу та порт)
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345); // Порт
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP сервера

	// Підключення до сервера
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		MessageBox::Show("Connection to server failed. Error: " + WSAGetLastError(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		closesocket(sock);
		WSACleanup();
		return;
	}

	MessageBox::Show("Connected to server.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);

	// Генерація команд для підписок
	std::vector<std::string> subscriptions;

	if (this->checkBox1->Checked) {
		subscriptions.push_back("weather");
	}
	if (this->checkBox2->Checked) {
		subscriptions.push_back("currency");
	}
	if (this->checkBox3->Checked) {
		subscriptions.push_back("stock");
	}

	// Якщо жодна підписка не вибрана
	if (subscriptions.empty()) {
		MessageBox::Show("Please select at least one subscription type.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	// Об'єднуємо вибрані підписки у форматі "subscribe:weather,currency,stock"
	std::string subscriptionCommand = "";
	for (size_t i = 0; i < subscriptions.size(); ++i) {
		if (i > 0) {
			subscriptionCommand += ",";  // Додаємо коми між елементами
		}
		subscriptionCommand += subscriptions[i];  // Додаємо елемент підписки
	}

	// Виводимо команду для перевірки (опціонально)
	//MessageBox::Show("Generated command: " + gcnew System::String(subscriptionCommand.c_str()), "Command", MessageBoxButtons::OK, MessageBoxIcon::Information);

	// Відправлення команди на сервер
	int bytesSent = send(sock, subscriptionCommand.c_str(), subscriptionCommand.size(), 0);

	if (bytesSent == SOCKET_ERROR) {
		MessageBox::Show("Failed to send subscription request. Error: " + WSAGetLastError(),
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		closesocket(sock);
		WSACleanup();
		return;
	}

	//MessageBox::Show("Subscription request sent.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);

	// Створення параметрів потоку
	ThreadParams params = { sock, &fullMessage };

	// Створення потоку за допомогою CreateThread
	HANDLE hThread = CreateThread(
		NULL,       // Дескриптор безпеки
		0,          // Початковий розмір стека
		ThreadFunc, // Функція потоку
		&params,    // Параметр для функції
		0,          // Прапори створення
		NULL        // Ідентифікатор потоку
	);

	// Перевірка на успішне створення потоку
	if (hThread == NULL) {
		MessageBox::Show("CreateThread failed. Error: " + GetLastError(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		closesocket(sock);
		WSACleanup();
		return;
	}

	if (hThread == NULL) { 
		MessageBox::Show("CreateThread failed. Error: " + GetLastError(), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); 
		closesocket(sock); WSACleanup(); return; 
	} 
	// Очікування завершення потоку 
	WaitForSingleObject(hThread, INFINITE); 
	CloseHandle(hThread); 
	// Викликаємо нову функцію для оновлення TextBox і виведення повідомлення
	UpdateTextBoxAndMessageBox();
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Очищення текстових полів, пов'язаних із checkBox1
	textBox1->Clear();
	textBox2->Clear();
	textBox3->Clear();
	textBox4->Clear();

	// Очищення текстових полів, пов'язаних із checkBox2
	textBox9->Clear();
	textBox10->Clear();

	// Очищення текстових полів, пов'язаних із checkBox3
	textBox8->Clear();
	textBox7->Clear();
	textBox6->Clear();
	textBox5->Clear();
}
};
}