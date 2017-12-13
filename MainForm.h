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
		MainForm(void) : exiting(false) , hideBalloon(false)
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
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  btnRunBackground;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnRunBackground = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// notifyIcon
			// 
			this->notifyIcon->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			this->notifyIcon->Text = L"WinMate";
			this->notifyIcon->Visible = true;
			this->notifyIcon->BalloonTipClicked += gcnew System::EventHandler(this, &MainForm::notifyIcon_Click);
			this->notifyIcon->Click += gcnew System::EventHandler(this, &MainForm::notifyIcon_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(132, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(263, 48);
			this->label1->TabIndex = 0;
			this->label1->Text = L"WinMate is working now.\r\n\r\nHover the cursor over a window\'s titlebar, \r\nand click"
				L" the magic wand button.";
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(362, 130);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(75, 23);
			this->btnExit->TabIndex = 2;
			this->btnExit->Text = L"Exit";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(114, 164);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// btnRunBackground
			// 
			this->btnRunBackground->Location = System::Drawing::Point(208, 130);
			this->btnRunBackground->Name = L"btnRunBackground";
			this->btnRunBackground->Size = System::Drawing::Size(148, 23);
			this->btnRunBackground->TabIndex = 1;
			this->btnRunBackground->Text = L"Run in Background";
			this->btnRunBackground->UseVisualStyleBackColor = true;
			this->btnRunBackground->Click += gcnew System::EventHandler(this, &MainForm::btnRunBackground_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 165);
			this->Controls->Add(this->btnRunBackground);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"WinMate";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		EntryButton ^entryBtn;
		bool exiting;
		bool hideBalloon;

		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void notifyIcon_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->Visible) this->Hide();
			else this->Show();
		}
		System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			if (this->exiting) return;

			if (!hideBalloon) {
				notifyIcon->BalloonTipTitle = L"WinMate is running";
				notifyIcon->BalloonTipText = L"To exit WinMate, click the [Exit] button.";
				notifyIcon->ShowBalloonTip(500);
				hideBalloon = true;
			}

			e->Cancel = true;
			this->Hide();
		}
		System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e) {
			this->exiting = true;
			this->Close();
		}
		System::Void btnRunBackground_Click(System::Object^  sender, System::EventArgs^  e) {
			this->hideBalloon = true;
			this->exiting = false;
			this->Close();
		}
};
}
