#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddMenus2(HWND);

#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3
#define IDM_IMPORT_MAIL 11

#define APPWM_ICONNOTIFY (WM_APP + 1)

// https://zetcode.com/gui/winapi/menus/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {

    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Messengefffr";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(1));

    RegisterClassW(&wc);
    auto hwnd = CreateWindowW(wc.lpszClassName, L"Simple menu", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                              100, 100, 350, 250, 0, 0, hInstance, 0);

    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)wc.hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)wc.hIcon);

    // Notification
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.uCallbackMessage = APPWM_ICONNOTIFY;
    nid.hIcon = wc.hIcon;
    // This text will be shown as the icon's tooltip.
    // StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), "d");

    // Show the notification.
    Shell_NotifyIcon(NIM_ADD, &nid);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case APPWM_ICONNOTIFY:

        break;

    case WM_CREATE: {
        HICON hIcon = static_cast<HICON>(
            LoadImage(NULL, TEXT("Icon\\small.ico"), IMAGE_ICON, 0, 0,
                      LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE | LR_LOADFROMFILE));
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        AddMenus(hwnd);
        break;
    }

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case IDM_FILE_NEW:
        case IDM_FILE_OPEN:

            AddMenus2(hwnd);
            break;

        case IDM_FILE_QUIT:

            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }

        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AddMenus(HWND hwnd) {

    HMENU hMenubar;
    HMENU hMenu;
    HMENU hSubMenu = CreatePopupMenu();

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, L"&Import");
    AppendMenuW(hSubMenu, MF_STRING, IDM_IMPORT_MAIL, L"Import &mail");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
    SetMenu(hwnd, hMenubar);
}

void AddMenus2(HWND hwnd) {

    HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quieeet");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Fileeee");
    SetMenu(hwnd, hMenubar);
}