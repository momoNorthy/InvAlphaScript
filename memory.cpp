#include "Memory.h"

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
