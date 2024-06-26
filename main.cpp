#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "Define.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void Update(DWORD dt)
{

}

void Render()
{

}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hInstance;

    wc.lpfnWndProc = (WNDPROC)WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    HWND hWnd =
        CreateWindow(
            WINDOW_CLASS_NAME,
            MAIN_WINDOW_TITLE,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            ScreenWidth,
            ScreenHeight,
            NULL,
            NULL,
            hInstance,
            NULL);

    if (!hWnd)
    {
        OutputDebugString(L"[ERROR] CreateWindow failed");
        DWORD ErrCode = GetLastError();
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}

int Run()
{
    MSG msg;
    int done = 0;
    ULONGLONG frameStart = GetTickCount64();
    DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

    while (!done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) done = 1;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ULONGLONG now = GetTickCount64();
        ULONGLONG dt = now - frameStart;

        if (dt >= tickPerFrame)
        {
            frameStart = now;
            Update(dt);
            Render();
        }
        else
            Sleep(tickPerFrame - dt);
    }

    return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

    SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    Run();

    return 0;
}
