#include "day03.hpp"

uint16_t day03::get_num(coord c) {
    uint16_t cur_num = 0; 
    size_t index = 0;
    while (isdigit(input[c.first][c.second - index]) && !seen.contains({c.first, c.second - index})) {
        cur_num += std::pow(10, index) * (input[c.first][c.second - index] - '0');
        seen.insert({c.first, c.second - index});
        index++;
        if (c.second - index < 0) break;
    }
    index = ((size_t)(c.second + 1) >= input[c.first].size()) ? 0 : 1;
    while (isdigit(input[c.first][c.second + index]) && !seen.contains({c.first, c.second + index})) {
        cur_num = 10 * cur_num + (input[c.first][c.second + index] - '0');
        seen.insert({c.first, c.second + index});
        index++;
        if (c.second + index >= input[c.first].size()) break;
    }
    return cur_num;
}

day03::day03() {
    input = readFile("input/day03.in"); 
    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input[0].size(); j++) {
           if (!isdigit(input[i][j]) && input[i][j] != '.')
               symbols.emplace_back(i,j);
        }
    }
}

uint32_t day03::part_one() {
    return std::accumulate(symbols.begin(), symbols.end(), 0,
                           [=, this](uint32_t acc, const auto& c) {                        
                                for (auto i = -1; i <= 1; ++i)
                                    for (auto j = -1; j <= 1; ++j) 
                                        if (isdigit(input[c.first + i][c.second + j]))
                                            acc += get_num({c.first + i, c.second +j});
                                return acc;
                           });
}

uint64_t day03::part_two() {
    seen.clear();
    return std::accumulate(symbols.begin(), symbols.end(), 0,
                           [=, this](uint64_t acc, const auto& c) {
                                if (input[c.first][c.second] == '*') {
                                    std::vector<uint16_t> adj;
                                    for (auto i = -1; i <= 1; ++i)
                                        for (auto j = -1; j <= 1; ++j)
                                            if (isdigit(input[c.first + i][c.second + j]) && !seen.contains({c.first + i, c.second + j}))
                                                adj.push_back(get_num({c.first + i, c.second + j}));
                                    if (adj.size() == 2) acc += adj[0] * adj[1];
                                    seen.clear();
                                }
                                return acc;
                           });
}

int main() {
    day03 day03;
    profile_day(day03);
}
