#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::ostringstream oss;
    oss << std::cin.rdbuf();
    std::string utf8 = oss.str();
    int len = MultiByteToWideChar(
        CP_UTF8,            
        0,
        utf8.c_str(),
        (int)utf8.size(),
        nullptr,
        0
    );
    if (len == 0) return 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (len + 1) * sizeof(wchar_t));
    if (!hMem) return 1;
    wchar_t* ptr = static_cast<wchar_t*>(GlobalLock(hMem));
    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8.c_str(),
        (int)utf8.size(),
        ptr,
        len
    );
    ptr[len] = L'\0';
    GlobalUnlock(hMem);
    if (!OpenClipboard(nullptr)) {
        GlobalFree(hMem);
        return 1;
    }
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return 0;
}
