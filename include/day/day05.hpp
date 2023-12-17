#include "common.hpp"

using mapping_t = std::function<long(long)>;
using rules_t = std::vector<std::vector<mapping_t>>;
using range = std::pair<long, long>;
struct rule {
    long dst;
    long src;
    long rng;
    rule (const std::string& s) {
        std::stringstream ss(s);
        ss >> dst >> src >> rng;
    };
    range span() const {return std::make_pair(src, src + rng - 1);};
};


struct day05 { 
    day05();

    long transform(long seed);
    long transform_range(const range& rng);
    
    long part_one(); 
    long part_two();

    std::vector<long> seeds;
    std::vector<std::vector<rule>> rules;
    std::vector<range> ranges;
};

