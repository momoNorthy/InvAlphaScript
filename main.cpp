#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <random>
#include <vector>

#define VARIABLE_NONEXISTENT 0xffffffff
#define MEM_MAX_SIZE 16
#define KW_IF 0
#define KW_INT 1
#define KW_PRINT 2

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

class Memory
{
    typedef std::size_t mem_index;
public:
    Memory();
    void alloc(const std::string& variable_name, const int& value);
    mem_index queryVariable(const std::string& variable_name); //如果没有查询到，返回-2147483648。
    void setNumber(const int& index, const int& value); // 赋值
    void debug_print();
private:
    std::vector<int> content;
    std::vector<int> if_used;
    std::size_t max_size = MEM_MAX_SIZE;

    std::default_random_engine engine;
    std::uniform_int_distribution<std::size_t> ran_dist = std::uniform_int_distribution<std::size_t>(0, MEM_MAX_SIZE - 1);

    std::unordered_map<std::string, mem_index> variable_mapper;
};

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

Memory::Memory()
{
    engine.seed(std::time(0));
    for (std::size_t i = 0; i < max_size; i++)
    {
        content.push_back(0);
        if_used.push_back(0);
    }
}

void Memory::alloc(const std::string& variable_name, const int& value)
{
    std::size_t index = 0;
    while (true)
    {
        index = ran_dist(engine);
        if (if_used[index])
            continue;
        else
            break;
    }

    if_used[index] = 1;
    variable_mapper[variable_name] = index;
    content[index] = value;
}

Memory::mem_index Memory::queryVariable(const std::string& variable_name)
{
    auto iterator = variable_mapper.find(variable_name);
    if (iterator == variable_mapper.end())
        return VARIABLE_NONEXISTENT;
    else
        return iterator->second;
}

void Memory::setNumber(const int& index, const int& value)
{
    content[index] = value;
}

void Memory::debug_print()
{
    for (std::size_t i = 0; i < MEM_MAX_SIZE; i++)
        std::cout << content[i] << ' ';
    std::cout << std::endl;
}
