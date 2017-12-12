#pragma once

#include "EntryButton.h"

namespace WinMate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm ժҪ
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �ڴ˴���ӹ��캯������
			//
			entryBtn = gcnew EntryButton();
			entryBtn->Show();
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  tmrAutoAttach;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// ����������������
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tmrAutoAttach = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(23, 24);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(105, 41);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// tmrAutoAttach
			// 
			this->tmrAutoAttach->Enabled = true;
			this->tmrAutoAttach->Tick += gcnew System::EventHandler(this, &MainForm::tmrAutoAttach_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		EntryButton ^entryBtn;
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tmrAutoAttach_Tick(System::Object^  sender, System::EventArgs^  e);
	};
}
