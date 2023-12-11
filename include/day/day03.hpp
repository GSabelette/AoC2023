#include "common.hpp"
#include "day.hpp"

using coord = std::pair<uint16_t, uint16_t>;

struct day03 { 
    day03();
 
    uint16_t get_num(coord c);

    uint32_t part_one(); 
    uint64_t part_two();
    std::vector<std::string> input;
    std::vector<coord> symbols;
    std::set<coord> seen;
};
