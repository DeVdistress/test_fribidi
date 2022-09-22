#include <cstring>
#include <iostream>
#include <fribidi/fribidi.h>

template <typename T>
T from_utf32(const char32_t code_point, T dest) noexcept
{
    auto index = code_point < 0x7FF ? (code_point < 0x7F ? 0u : 1u) : (code_point < 0xFFFF ? 2u : code_point < 0x1FFFFF ? 3u : 4u);
    switch (index)
    {
        case 0: // 1 byte
        {
            *dest++ = static_cast<uint8_t>(code_point & 0xFF);
            break;
        }
        case 1: // 2 bytes
        {
            const auto trunc1 = code_point >> 6u;
            const auto trunc2 = code_point % 64u;
            *dest++ = 192u | (trunc1 & 0b111111);
            *dest++ = 128u | (trunc2 & 0b111111);
            break;
        }
        case 2: // 3 bytes
        {
            const auto trunc1 = code_point >> 12u;
            const auto trunc2 = code_point >> 6u;
            const auto trunc3 = code_point % 64u;
            *dest++ = 224u | (trunc1 & 0b1111);
            *dest++ = 128u | (trunc2 & 0b111111);
            *dest++ = 128u | (trunc3 & 0b111111);
            break;
        }
        case 3: // 4 bytes
        {
            const auto trunc4 = code_point % 64u;
            const auto trunc3 = code_point >> 6u;
            const auto trunc2 = code_point >> 12u;
            const auto trunc1 = code_point >> 18u;
            *dest++ = 240u | (trunc1 & 0b1111);
            *dest++ = 128u | (trunc2 & 0b111111);
            *dest++ = 128u | (trunc3 & 0b111111);
            *dest++ = 128u | (trunc4 & 0b111111);
            break;
        }
        default:;
    }

    return dest;
}

template <typename T>
T from_utf16(const char16_t code_point, T dest) noexcept
{
    switch ((code_point < 0x7FF) ? (code_point < 0x7F) ? 0 : 1 : 2)
    {
        case 0: // 1 byte
        {
            *dest++ = static_cast<uint8_t>(code_point & 0xFF);
            break;
        }
        case 1: // 2 bytes
        {
            const auto trunc1 = code_point >> 6u;
            const auto trunc2 = code_point % 64u;
            *dest++ = 192u | (trunc1 & 0b111111);
            *dest++ = 128u | (trunc2 & 0b111111);
            break;
        }
        case 2: // 3 bytes
        {
            const auto trunc1 = code_point >> 12u;
            const auto trunc2 = code_point >> 6u;
            const auto trunc3 = code_point % 64u;
            *dest++ = 224u | (trunc1 & 0b1111);
            *dest++ = 128u | (trunc2 & 0b111111);
            *dest++ = 128u | (trunc3 & 0b111111);
            break;
        }
        default:;
    }

    return dest;
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    std::wstring text_ = std::wstring(L"MIN2 - ﺎﺒًﺣﺮﻣ MAX10!");
    //std::wstring text_ = std::wstring(L"مرحبا");
    FriBidiChar* text = (FriBidiChar*)(text_.c_str());

    FriBidiChar *reordered_str = new FriBidiChar[text_.size()*2];
    std::memset(reordered_str, 0, (text_.size() * 2 * sizeof(FriBidiChar)));
    FriBidiParType direction = FRIBIDI_PAR_RTL;

    fribidi_boolean res = fribidi_log2vis(text, text_.size(), &direction, reordered_str, nullptr, nullptr, nullptr);

    //wchar_t *new_mas = new wchar_t[text_.size() * 2];
    //std::memset(new_mas, 0, (text_.size() * 2 * sizeof(wchar_t)));
    //for (int tik = 0; tik < text_.size() * 2; tik++) {
    //    new_mas[tik] = (wchar_t)reordered_str[tik];
    //}
    //
    //std::wstring output = std::wstring(new_mas);
    std::wstring output = std::wstring((wchar_t*)reordered_str);
    std::wcout << L"---------" << std::endl;
    std::wcout << output << std::endl;
    std::wcout << L"---------" << std::endl;
    for(auto el:output)
        std::wcout << L"'" << el << L"'";
    std::wcout << std::endl;
    std::wcout << L"---------" << std::endl;
    std::wcout << text_ << std::endl;
    std::wcout << L"---------" << std::endl;
    for(auto el:text_)
        std::wcout << L"'" << el << L"'";
    std::wcout << std::endl;
}
