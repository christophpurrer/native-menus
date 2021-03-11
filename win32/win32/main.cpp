#include "../../shared/Menu.h"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <windows.h>

// https://stackoverflow.com/a/47312126
class dbg_stream_for_cout : public std::stringbuf {
  public:
    ~dbg_stream_for_cout() { sync(); }
    int sync() {
        ::OutputDebugStringA(str().c_str());
        str(std::string()); // Clear the string buffer
        return 0;
    }
};
dbg_stream_for_cout g_DebugStreamFor_cout;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void createAppMenu(HWND);

static std::unordered_map<int32_t, std::string> sMenuIdToMenuKey;

// https://zetcode.com/gui/winapi/menus/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Win32App";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(1));

    RegisterClassW(&wc);
    auto hwnd = CreateWindowW(wc.lpszClassName, L"Win32", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100,
                              100, 350, 250, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    case WM_CREATE: {
        createAppMenu(hwnd);
        std::cout.rdbuf(&g_DebugStreamFor_cout);
        break;
    }

    case WM_COMMAND: {
        auto it = sMenuIdToMenuKey.find(wParam);
        if (it != sMenuIdToMenuKey.end()) {
            std::cout << "menuItem: " << it->second << std::endl;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void createAppMenu(HWND hwnd) {
    auto applicationMenus = createApplicationMenu();
    HMENU hMenubar = CreateMenu();
    int32_t menuId = 1023;
    for (auto const& applicationMenu : applicationMenus) {
        HMENU hMenu = CreateMenu();
        for (auto& menuEntry : applicationMenu.entries) {
            auto menuEntryItem = dynamic_cast<MenuEntry*>(menuEntry.get());
            if (menuEntryItem) { //
                auto flags = MF_STRING;
                if (!menuEntryItem->enabled) {
                    flags |= MF_DISABLED;
                }
                AppendMenuW(
                    hMenu, flags, menuId,
                    std::wstring(menuEntryItem->title.begin(), menuEntryItem->title.end()).c_str());
                sMenuIdToMenuKey[menuId++] = menuEntryItem->title;
            }
            auto menuEntrySeparator = dynamic_cast<Separator*>(menuEntry.get());
            if (menuEntrySeparator) {
                AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
            }
        }
        AppendMenuW(
            hMenubar, MF_POPUP, (UINT_PTR)hMenu,
            std::wstring(applicationMenu.title.begin(), applicationMenu.title.end()).c_str());
    }
    SetMenu(hwnd, hMenubar);
}