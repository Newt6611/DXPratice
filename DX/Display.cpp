#include "Display.h"
#include "imgui_impl_win32.h"
#include "Log.h"
#include "Renderer.h"
#include <d3d11.h>
#include <dxgi.h>

Display* Display::m_Instance;

void Display::Init(int width, int height)
{
    m_width = width;
    m_height = height;
    InitWindow();
}

Display::~Display()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Display::InitWindow()
{   
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LogError("Failed When Init SDL !");
    }

    uint32_t windowFlags = SDL_WINDOW_SHOWN;
    windowFlags |= SDL_WINDOW_RESIZABLE;
    m_Window = SDL_CreateWindow("My Render Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, windowFlags);
    if (m_Window == nullptr)
    {
        LogError("Failed When Creating SDL Window !");
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(m_Window, &wmInfo);
    m_handle = (HWND)wmInfo.info.win.window;
    m_instance = (HINSTANCE)wmInfo.info.win.hinstance;

    if (m_handle == NULL)
    {
        LogError("Handle Is Null !");
    }
}

void Display::OnResize()
{
    if (Renderer::Get()->GetSwapChain())
    {
        Renderer* renderer = Renderer::Get();
        ID3D11RenderTargetView* renderTargetView = renderer->GetRenderTargetView()->GetRenderTargetView();
        IDXGISwapChain* swapchain = renderer->GetSwapChain();

        renderer->GetContext()->OMSetRenderTargets(0, 0, 0);

        renderTargetView->Release();

        HRESULT result = swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        if (result != S_OK)
        {
            LogError("Error When SwapChain Resizing Buffer !");
        }

        ID3D11Texture2D* buffer;
        result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
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
        
        DXGI_SWAP_CHAIN_DESC desc;
        swapchain->GetDesc(&desc);
        m_width = desc.BufferDesc.Width;
        m_height = desc.BufferDesc.Height;
    }
}