#include "Headers/Leaderboard.h"
#include <vector>

namespace PacMan
{
    std::vector<Record> GenerateFakeScores(int _count) {
        std::vector<Record> record;
        static const std::vector<std::string> names = { "Alice","Bob","Sigma","Skebob","Chupep","Sakutin" };
        for (int i = 0; i < _count; ++i) {
            int idx = std::rand() % names.size();
            int points = 1 + std::rand() % 10;
            record.push_back({ names[idx], points });
        }
        return record;
    }

    void SortDescending(std::vector<Record>& _record) {
        for (size_t i = 0; i + 1 < _record.size(); ++i) {
            size_t max_i = i;
            for (size_t j = i+1; j < _record.size(); ++j)
                if (_record[j].score > _record[max_i].score)
                    max_i = j;
            std::swap(_record[i], _record[max_i]);
        }
    }

    

}
