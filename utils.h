#pragma once
#include <string>

int translateStrToNum(const std::string& str)
{
    int number = 0; // Ŀǰ��֧������
    int digit = 0; // ������λ
    for (const auto& ch : str)
    {
        number *= 10;
        digit = ch - 48;
        number += digit;
    }
    return number;
}