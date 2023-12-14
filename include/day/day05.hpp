#include "common.hpp"

using mapping_t = std::function<int(int)>;
using rules_t = std::vector<std::vector<mapping_t>>;

struct day05 { 
    day05();

    uint16_t part_one(); 
    //uint64_t part_two();

    rules_t rules;
    std::vector<uint16_t> seeds;
};
