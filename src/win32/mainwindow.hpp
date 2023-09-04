#pragma once
#include <windows.h>
#include <memory>
#include "requestmanager.hpp"
namespace zrestgui
{
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE hInstance, HWND parent,int nCmdShow);
		virtual ~MainWindow();

	protected:
		static LRESULT CALLBACK requestProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void afficheListe(HWND hwnd, HWND parent);
		void effaceSelection(HWND hwnd);
	private:
		HWND m_hWnd;
		std::unique_ptr<zrestgui::RequestManager> pRequestManager;

	};
}
