#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>
#include <stdio.h>

//Starter code copied from https://github.com/kevinmoran/BeginnerDirect3D11/tree/master/00.%20Opening%20a%20Win32%20Window under The Unlicense

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    static int saveState = 0;
    LRESULT result = 0;
    switch(msg)
    {
        case WM_KEYDOWN: //https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
        {
            if(wparam == VK_ESCAPE)
                DestroyWindow(hwnd);
            if(wparam >= 'A' && wparam <= 'Z') //between a and z
                saveState ^= (1 << (wparam - 'A')); //invert bit corresponding to pressed key
            if(wparam == VK_SPACE) //write save state to file
            {
                FILE *file;
                fopen_s(&file, "saveState.txt", "w+");
                fprintf(file, "%d", saveState);
                fclose(file);
            }
            if(wparam == VK_CONTROL) //load save state from file
            {
                FILE *file;
                fopen_s(&file, "saveState.txt", "r");
                fscanf_s(file, "%d", &saveState);
                fclose(file);
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
            result = DefWindowProcW(hwnd, msg, wparam, lparam);
    }
    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
    // Open a window
    HWND hwnd;
    {
        WNDCLASSEXW winClass = {};
        winClass.cbSize = sizeof(WNDCLASSEXW);
        winClass.style = CS_HREDRAW | CS_VREDRAW;
        winClass.lpfnWndProc = &WndProc;
        winClass.hInstance = hInstance;
        winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
        winClass.hCursor = LoadCursorW(0, IDC_ARROW);
        winClass.lpszClassName = L"MyWindowClass";
        winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

        if(!RegisterClassExW(&winClass)) {
            MessageBoxA(0, "RegisterClassEx failed", "Fatal Error", MB_OK);
            return GetLastError();
        }

        RECT initialRect = { 0, 0, 1024, 768 };
        AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
        LONG initialWidth = initialRect.right - initialRect.left;
        LONG initialHeight = initialRect.bottom - initialRect.top;

        hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
                                winClass.lpszClassName,
                                L"Tracking Keyboard Input",
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                initialWidth, 
                                initialHeight,
                                0, 0, hInstance, 0);

        if(!hwnd) {
            MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
            return GetLastError();
        }
    }

    bool isRunning = true;
    while(isRunning)
    {
        MSG message = {};
        while(PeekMessageW(&message, 0, 0, 0, PM_REMOVE))
        {
            if(message.message == WM_QUIT)
                isRunning = false;
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }

        Sleep(1);
    }

    return 0;
}