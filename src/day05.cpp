#include "day05.hpp"

mapping_t str_to_mapping(const std::string& s) {
    int dst, src, range;
    std::stringstream ss(s);
    ss >> dst >> src >> range;
    return [dst, src, range](int in) {
        if (in >= src && in <= (src + range - 1)) return in + dst - src;
        else return in;
    };
}

day05::day05() {
    auto input = readFile("input/day05.in");
    std::vector<mapping_t> v;
    for (const auto& l : input) {
        if (!l.empty() && isdigit(l[0])) 
            v.emplace_back(str_to_mapping(l));
        else if (l.empty() && !v.empty()) {
            rules.emplace_back(v);
            v.clear();
        }
    }
    rules.emplace_back(v);
    std::stringstream ss(input[0]);
    ss.ignore(':');
    uint16_t seed;
}

uint16_t day05::part_one() {
    std::cout << "rulessize:" << rules.size() << "\n";
    for (const auto& v : rules) {
        std::cout << "vsize" << v.size() << "\n";
        for (const auto& f : v) std::cout << f(50);
    }
    return 0;
}

int main() {
    day05 day05;
    profile_day(day05);
}
