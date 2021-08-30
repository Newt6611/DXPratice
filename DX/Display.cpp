#include "Display.h"
#include "imgui_impl_win32.h"
#include "Log.h"
#include "Renderer.h"

Display* Display::m_Instance;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_SIZE:
        Display::Get()->OnResize();
        break;
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
	wc.style = CS_VREDRAW | CS_OWNDC | CS_HREDRAW | CS_DBLCLKS;
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
        WS_SIZEBOX | WS_BORDER | WS_SYSMENU, 200, 200, m_width, m_height, NULL, NULL,
        m_instance, NULL);

    if (m_handle != NULL)
    {
        ShowWindow(m_handle, SW_SHOWNORMAL);
        UpdateWindow(m_handle);
    }
    else 
    {
        LogError("Failed When Creating Window !");
    }
}

void Display::OnResize()
{
    if (Renderer::Get()->GetSwapChain())
    {
        Renderer* renderer = Renderer::Get();
        ID3D11RenderTargetView* renderTargetView = renderer->GetRenderTargetView()->GetRenderTargetView();

        renderer->GetContext()->OMSetRenderTargets(0, 0, 0);
        renderTargetView->Release();

        HRESULT result = renderer->GetSwapChain()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        if (result != S_OK)
        {
            LogError("Error When SwapChain Resizing Buffer !");
        }

        ID3D11Texture2D* buffer;
        result = renderer->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
        if (result != S_OK)
        {
            LogError("Error When Getting SwapChain BackBuffer !");
        }

        result = renderer->GetDevice()->CreateRenderTargetView(buffer, NULL, &renderTargetView);
        if (result != S_OK)
        {
            LogError("Error When Creating RenderTargetView !");
        }

        buffer->Release();

        renderer->GetContext()->OMSetRenderTargets(1, &renderTargetView, NULL);
        
        auto viewport = CD3D11_VIEWPORT(0.f, 0.f, static_cast<float>(Display::Get()->GetWidth()), static_cast<float>(Display::Get()->GetHeight()));
        renderer->GetContext()->RSSetViewports(1, &viewport);

    }
}