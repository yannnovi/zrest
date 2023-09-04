#ifndef REQUESTMANAGER_HPP
#define REQUESTMANAGER_HPP
#include <windows.h>
namespace zrestgui
{
	class RequestManager
	{
	public:
		RequestManager(HINSTANCE hInstance, HWND parent);
		virtual ~RequestManager();
		
	protected:
		static LRESULT CALLBACK requestProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hWnd;
	};

}
#endif
