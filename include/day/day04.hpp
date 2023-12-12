#include "common.hpp"
#include "day.hpp"

struct card {
card(std::stringstream ss);

    std::vector<uint16_t> wins;
    std::vector<uint16_t> draws;
};

struct day04 { 
    day04();

    void compute_scores();

    uint16_t part_one(); 
    uint64_t part_two();

    std::vector<card> cards;
    std::vector<uint16_t> scores;
};
