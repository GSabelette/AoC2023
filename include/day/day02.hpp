#include "common.hpp"
#include "day.hpp"

using draw = std::array<uint16_t, 3>;

struct game {
    uint16_t id;
    std::vector<draw> draws;
    
    game(const std::string& s);
    uint16_t score() const;
};

struct day02 { 
    day02();
 
    uint16_t evaluate(auto f);

    uint16_t part_one(); 
    uint16_t part_two();

    std::vector<game> games;
};
