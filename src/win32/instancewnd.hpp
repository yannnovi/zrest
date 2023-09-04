#ifndef INSTANCEWND_HPP
#define INSTANCEWND_HPP

template<class T, class U, HWND(U::* m_hWnd)> T*
InstanceFromWndProc(HWND hWnd, UINT uMsg, LPARAM lParam)
{
    // Get the pointer to the class instance.
    T* pInstance;
    if (uMsg == WM_NCCREATE)
    {
        // The pointer has been passed via CreateWindowExW and now needs to be saved via SetWindowLongPtrW.
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pInstance = reinterpret_cast<T*>(pCreateStruct->lpCreateParams);
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pInstance));

        // We are handling the first useful window message, so this is the perfect place to also set the hWnd member variable.
        pInstance->*m_hWnd = hWnd;
    }
    else
    {
        // Get the pointer saved via SetWindowLongPtrW above.
        pInstance = reinterpret_cast<T*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    return pInstance;
}
#endif