#pragma once

#include "WindowWatch.h"
#include "LayeredFormUtil.h"
#include "ModInfo.h"
#include "ModToolbox.h"

typedef struct HWND__ *HWND;

namespace WinMate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// EntryButton 摘要
	/// </summary>
	public ref class EntryButton : public System::Windows::Forms::Form
	{
	public:
		EntryButton(void);

	public:
		HWND m_target;		// Current manipulating target hWnd
		HWND m_hWnd;		// EntryButton self window hWnd
		bool m_hovering;	// If cursor is hovering on EntryButton, or the contentMenu
		bool m_hidden;

		WindowWatch^ wwatch;
		ModToolbox^ modBox;		// The popup containing manipulating options

	public:
		LayeredFormUtil^ alphaFx;

		void AttachTo(void* hWnd);

	private:
		Bitmap ^ imgNormal;
		Bitmap ^ imgHover;
		ModInfo ^ m_modInfo;		// current ModInfo

		int m_btnXoffset;			// EntryButton.X = Target.Right - EntryButton.Width - m_btnXoffset

	protected:
		~EntryButton()
		{
			if (components)
			{
				delete components;
			}
		}
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
			this->SuspendLayout();
			// 
			// EntryButton
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(35, 25);
			this->ControlBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"EntryButton";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"EntryButton";
			this->MouseEnter += gcnew System::EventHandler(this, &EntryButton::EntryButton_MouseEnter);
			this->MouseLeave += gcnew System::EventHandler(this, &EntryButton::EntryButton_MouseLeave);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &EntryButton::EntryButton_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		void OnTargetResize(void *win, System::Drawing::Rectangle ^rect);
		void OnForegroundChanged(void *win);

		System::Void EntryButton_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			alphaFx->SetImage(imgHover);
		}
		System::Void EntryButton_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			alphaFx->SetImage(imgNormal);
		}
		System::Void EntryButton_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
};
}
