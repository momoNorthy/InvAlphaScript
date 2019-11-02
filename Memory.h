#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <unordered_map>
#include "defs.h"

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
