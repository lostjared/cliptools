#include <windows.h>
#include <string>
#include <iostream>

std::wstring GetClipboardText() {
    if (!OpenClipboard(nullptr))
        return L"";

    std::wstring result;

    if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
        HGLOBAL h = GetClipboardData(CF_UNICODETEXT);
        if (h) {
            auto p = static_cast<const wchar_t*>(GlobalLock(h));
            if (p)
                result = p;
            GlobalUnlock(h);
        }
    }
    else if (IsClipboardFormatAvailable(CF_TEXT)) {
        HGLOBAL h = GetClipboardData(CF_TEXT);
        if (h) {
            auto p = static_cast<const char*>(GlobalLock(h));
            if (p) {
                int len = MultiByteToWideChar(CP_ACP, 0, p, -1, nullptr, 0);
                std::wstring tmp(len, L'\0');
                MultiByteToWideChar(CP_ACP, 0, p, -1, &tmp[0], len);
                result = tmp;
            }
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    return result;
}

int main(int argc, char **argv) {
    std::wstring text = GetClipboardText();
    std::wcout << text;
    return 0;
}
