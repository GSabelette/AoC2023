#include "day05.hpp"

long map(const rule& r, long x) {
    if (x >= r.src && x <= (r.src + r.rng - 1)) return x + r.dst - r.src;
    else return x;
}

mapping_t rule_to_mapping(const rule& r) {
    return [r](long in) {
        if (in >= r.src && in <= (r.src + r.rng - 1)) return in + r.dst - r.src;
        else return in;
    };
}

mapping_t str_to_mapping(const std::string& s) {
    rule r(s);
    return rule_to_mapping(r);
}

day05::day05() {
    auto input = readFile("input/day05.in");
    std::vector<rule> v;
    for (const auto& l : input) {
        if (!l.empty() && isdigit(l[0])) 
            v.emplace_back(l);
        else if (l.empty() && !v.empty()) {
            rules.emplace_back(v);
            v.clear();
        }
    }
    rules.emplace_back(v);
    std::stringstream ss(input[0]);
    ss.ignore(7, ':');
    long seed;
    while(ss >> seed) {
        seeds.push_back(seed);
    }
}

long day05::transform(long seed) {
    for (const auto& v : rules)
        for (const auto& r : v) {
            auto tmp = map(r, seed);
            if (tmp != seed) {
                seed = tmp;
                break;
            }
        }
    return seed;
}

long day05::part_one() {
    return std::ranges::min(seeds | std::views::transform(
        [=,this](long seed) {
            return transform(seed);
        }));
}

bool is_convertible(const range& range, const rule& r) {
    return ((range.first >= r.src && range.first < r.src + r.rng - 1) ||
            (range.second > r.src && range.second < r.src + r.rng));
}

range converted_range(const range& rng, const rule& r) {
    return range((std::max(rng.first, r.src) + r.dst - r.src),
                 (std::min(rng.second, r.src + r.rng - 1) + r.dst - r.src));
}

std::vector<range> unconverted_ranges(const range& rng, const rule& r) {
    std::vector<range> ret;
    if (rng.first < r.src) 
        ret.emplace_back(rng.first, r.src - 1);
    if (rng.second >= r.src + r.rng) 
        ret.emplace_back(r.src + r.rng, rng.second);
    return ret;
}

long day05::transform_range(const range& rng) {
    std::vector<range> transformed;
    std::deque<range> untransformed {rng};
    for (const auto& ruleset : rules) {
        for (const auto& r : ruleset) {
            for (const auto& rng : untransformed) {
                auto new_untransformed = unconverted_ranges(rng, r);
                std::copy(new_untransformed.begin(), new_untransformed.end(), std::back_inserter(untransformed));
                transformed.emplace_back(converted_range(rng, r));
                untransformed.erase(rng);
            }
        }
    }
    return std::ranges::min(transformed | std::ranges::min);
}

long day05::part_two() {
    return 0;
    return std::ranges::min(ranges | std::views::transform(
        [=, this](const auto& rng) {
            std::vector<range> unconverted {rng};
            std::vector<range> converted;
            for (const auto& ruleset : rules) {
                for (const auto& rule : ruleset) {

                }
            }
        }));
    

    /*return std::ranges::min(...,
        [](long seed, long range) {
            std::vector<long> v(seed, seed+range); 
            
        });*/
}

int main() {
    day05 day05;
    profile_day(day05);
    //for (const auto& s : day05.seeds) std::cout << s << ",";
    
    return 0;
}
