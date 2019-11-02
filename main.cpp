#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <random>
#include <vector>

#include "defs.h"
#include "Memory.h"
#include "utils.h"

std::unordered_map<std::string, int> keyword_mapper;
void initKM()
{
    keyword_mapper["if"] = KW_IF;
    keyword_mapper["int"] = KW_INT;
    keyword_mapper["print"] = KW_PRINT;
}

void init()
{
    initKM();
}

int main()
{
    init();

    Memory memory;
    memory.alloc("a", 100);
    memory.debug_print();

    std::string line;
    std::string word_buffer;
    std::istringstream issm;
    while (std::getline(std::cin, line))
    {
        std::string variable_name;
        int number = 0;

        /*

        int a = 1
        a = 2
        if a == 0 [
            print~"hello world"
        ]

        */
        issm = std::istringstream(line);
        issm >> word_buffer;
        auto iterator = keyword_mapper.find(word_buffer);
        if (iterator == keyword_mapper.end()) //不是关键字，那么就是变量
        {
            std::size_t index = memory.queryVariable(word_buffer);
            if (index == VARIABLE_NONEXISTENT)
                throw "VARIABLE_NONEXISTENT";
            else // 读取等于号
            {
                issm >> word_buffer;
                if (word_buffer == "=") // 等于号后面肯定跟着整数
                {
                    issm >> word_buffer;
                    number = translateStrToNum(word_buffer);
                    memory.setNumber(index, number);
                }
                else
                    throw "变量后面必须跟等于号";
            }
        }
        else
        {
            switch (iterator->second)
            {
            case KW_INT: // int a = 1 不管重复定义
                issm >> word_buffer;
                variable_name = word_buffer;
                issm >> word_buffer;
                issm >> word_buffer;
                number = translateStrToNum(word_buffer);
                memory.alloc(word_buffer, number);
                break;
            case KW_IF:

                break;
            default:
                break;
            }
        }
    }
    memory.debug_print();
    return 0;
}