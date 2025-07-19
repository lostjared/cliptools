#include <windows.h>
#include <iostream>
#include <string>

static std::string toUtf8(const std::wstring &w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(
        CP_UTF8, 0,
        w.data(), (int)w.size(),
        nullptr, 0,
        nullptr, nullptr
    );
    std::string s(n, '\0');
    WideCharToMultiByte(
        CP_UTF8, 0,
        w.data(), (int)w.size(),
        &s[0], n,
        nullptr, nullptr
    );
    return s;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    if (!OpenClipboard(nullptr)) return 1;
    HGLOBAL h = GetClipboardData(CF_UNICODETEXT);
    if (!h) { CloseClipboard(); return 1; }
    wchar_t *w = static_cast<wchar_t*>(GlobalLock(h));
    if (!w) { CloseClipboard(); return 1; }
    std::wstring text(w);
    GlobalUnlock(h);
    CloseClipboard();

    std::cout << toUtf8(text);
    return 0;
}
