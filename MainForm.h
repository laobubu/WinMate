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
	/// MainForm 摘要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void) : exiting(false)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
			entryBtn = gcnew EntryButton();
			entryBtn->Show();
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NotifyIcon^  notifyIcon;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnExit;

	protected:


	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// notifyIcon
			// 
			this->notifyIcon->Text = L"WinMate";
			this->notifyIcon->Visible = true;
			this->notifyIcon->Click += gcnew System::EventHandler(this, &MainForm::notifyIcon_Click);
			this->notifyIcon->BalloonTipClicked += gcnew System::EventHandler(this, &MainForm::notifyIcon_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(425, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"WinMate is working now. \r\nHover your cursor on a titlebar of window, and click th"
				L"e entry button.";
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(362, 56);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(75, 23);
			this->btnExit->TabIndex = 1;
			this->btnExit->Text = L"Exit";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 91);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"WinMate";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		EntryButton ^entryBtn;
		bool exiting;

		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void notifyIcon_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->Visible) this->Hide();
			else this->Show();
		}
		System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			if (this->exiting) return;

			notifyIcon->BalloonTipTitle = L"WinMate is running";
			notifyIcon->BalloonTipText = L"To exit WinMate, click the [Exit] button.";
			notifyIcon->ShowBalloonTip(500);

			e->Cancel = true;
			this->Hide();
		}
		System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e) {
			this->exiting = true;
			this->Close();
		}
};
}
