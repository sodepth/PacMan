#pragma once
#include <iostream>
#include <vector>

namespace PacMan
{
    struct Record
    {
        std::string name;
        int score;
    };
    std::vector<Record> GenerateFakeScores(int count);
    
    void SortDescending(std::vector<Record>& records);
}
