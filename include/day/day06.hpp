#include "common.hpp"

using race = std::pair<uint32_t, uint32_t>;

struct day06 {
    day06();

    uint64_t part_one();
    long part_two();

    std::vector<race> races;
};
