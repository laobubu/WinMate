#pragma once

#include "WindowWatch.h"
#include "LayeredFormUtil.h"
#include "ModInfo.h"

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

	public:
		System::Windows::Forms::ContextMenuStrip^  contextMenu;
		System::Windows::Forms::ToolStripMenuItem^  menuTopmost;

	public:
		LayeredFormUtil^ alphaFx;

		void AttachTo(void* hWnd);

	private:
		Bitmap ^ imgNormal;
		Bitmap ^ imgHover;
		ModInfo ^ m_modInfo;		// current ModInfo

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
			this->components = (gcnew System::ComponentModel::Container());
			this->contextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->menuTopmost = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// contextMenu
			// 
			this->contextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->menuTopmost });
			this->contextMenu->Name = L"contextMenu";
			this->contextMenu->Size = System::Drawing::Size(153, 48);
			// 
			// menuTopmost
			// 
			this->menuTopmost->Name = L"menuTopmost";
			this->menuTopmost->Size = System::Drawing::Size(152, 22);
			this->menuTopmost->Text = L"Always on Top";
			this->menuTopmost->Click += gcnew System::EventHandler(this, &EntryButton::menuTopmost_Click);
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
			this->contextMenu->ResumeLayout(false);
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
		System::Void menuTopmost_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void EntryButton_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			IntPtr key(m_target);
			auto m_AllModInfo = GetModInfoDict();

			if (!m_AllModInfo->ContainsKey(key)) {
				m_AllModInfo->Add(key, gcnew ModInfo(m_target));
			}
			
			m_modInfo = m_AllModInfo[key];
			m_modInfo->DisplayTo(this);
			
			contextMenu->Show(this, e->X, e->Y);
		}
};
}
