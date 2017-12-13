#pragma once

#include "ModInfo.h"

namespace WinMate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ModToolbox 摘要
	/// </summary>
	public ref class ModToolbox : public System::Windows::Forms::Form
	{
	public:
		ModToolbox(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

		void UseModInfo(ModInfo ^ modInfo) {
			m_modInfo = modInfo;
			m_modInfo->DisplayTo(this);
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~ModToolbox()
		{
			if (components)
			{
				delete components;
			}
		}
		ModInfo ^ m_modInfo;

	private: System::Windows::Forms::Label^  label1;

	public: 
		System::Windows::Forms::CheckBox^  topmost;
		System::Windows::Forms::TrackBar^  alphaTrackBar;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->topmost = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->alphaTrackBar = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alphaTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// topmost
			// 
			this->topmost->AutoSize = true;
			this->topmost->Location = System::Drawing::Point(12, 12);
			this->topmost->Name = L"topmost";
			this->topmost->Size = System::Drawing::Size(90, 16);
			this->topmost->TabIndex = 0;
			this->topmost->Text = L"Keep on Top";
			this->topmost->UseVisualStyleBackColor = true;
			this->topmost->CheckedChanged += gcnew System::EventHandler(this, &ModToolbox::topmost_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Alpha";
			// 
			// alphaTrackBar
			// 
			this->alphaTrackBar->LargeChange = 20;
			this->alphaTrackBar->Location = System::Drawing::Point(54, 35);
			this->alphaTrackBar->Maximum = 100;
			this->alphaTrackBar->Name = L"alphaTrackBar";
			this->alphaTrackBar->Size = System::Drawing::Size(156, 45);
			this->alphaTrackBar->SmallChange = 10;
			this->alphaTrackBar->TabIndex = 2;
			this->alphaTrackBar->TickFrequency = 25;
			this->alphaTrackBar->Scroll += gcnew System::EventHandler(this, &ModToolbox::alphaTrackBar_Scroll);
			// 
			// ModToolbox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(222, 160);
			this->ControlBox = false;
			this->Controls->Add(this->alphaTrackBar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->topmost);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ModToolbox";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->TopMost = true;
			this->Deactivate += gcnew System::EventHandler(this, &ModToolbox::ModToolbox_Leave);
			this->Leave += gcnew System::EventHandler(this, &ModToolbox::ModToolbox_Leave);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->alphaTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ModToolbox_Leave(System::Object^  sender, System::EventArgs^  e) {
		this->Hide();
	}
	private: System::Void topmost_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void alphaTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
		m_modInfo->Alpha = alphaTrackBar->Value;
	}
};
}
