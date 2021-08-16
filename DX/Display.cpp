#include "Display.h"
#include "imgui_impl_win32.h"

Display* Display::m_Instance;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
        
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Display::Init(int width, int height)
{
    m_width = width;
    m_height = height;
    InitWindow();
}

Display::~Display()
{
}

void Display::InitWindow()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_instance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"MDX";
    wc.hIconSm = NULL;
    
    RegisterClassEx(&wc);

    m_handle = CreateWindowEx(WS_EX_ACCEPTFILES, L"MDX", L"MyWindow",
        WS_BORDER, 200, 200, m_width, m_height, NULL, NULL, 
        m_instance, NULL);

    if (m_handle != NULL)
    {
        ShowWindow(m_handle, SW_SHOWNORMAL);
    }
    else 
    {
        LogError("Failed When Creating Window !");
    }
}
