#pragma once
#include <string>

int translateStrToNum(const std::string& str)
{
    int number = 0; // 目前仅支持正数
    int digit = 0; // 代表数位
    for (const auto& ch : str)
    {
        number *= 10;
        digit = ch - 48;
        number += digit;
    }
    return number;
}