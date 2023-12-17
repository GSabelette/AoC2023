#include "day05.hpp"

long map(const rule& r, long x) {
    if (x >= r.src && x <= (r.src + r.rng - 1)) return x + r.dst - r.src;
    else return x;
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
    while(ss >> seed) seeds.push_back(seed);
    for (size_t i = 0; i < seeds.size(); i+=2) ranges.emplace_back(seeds[i], seeds[i+1]);
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

range converted_range(const range& rng, const rule& r) {
    long overlap_size = std::min(rng.first + rng.second, r.src + r.rng) - std::max(rng.first, r.src);  
    return range(std::max(rng.first, r.src) + r.dst - r.src, overlap_size);
}

std::vector<range> unconverted_ranges(const range& rng, const rule& r) {
    std::vector<range> ret;
    if (rng.first < r.src)
        ret.emplace_back(rng.first, r.src - rng.first);
    if (rng.first + rng.second > r.src + r.rng)
        ret.emplace_back(r.src + r.rng, rng.first + rng.second - (r.src + r.rng));
    return ret;
}

long day05::transform_range(const range& rng) {
    auto is_convertible = [](const range& rng, const rule& r){return rngutils::overlap(range(rng.first, rng.first + rng.second - 1), r.span());};
    std::vector<range> transformed;
    std::vector<range> untransformed {rng};
    for (const auto& ruleset : rules) {
        for (const auto& r : ruleset) {
            auto tmp = untransformed;
            untransformed.clear();
            for (const auto& rng : tmp) {
                if (is_convertible(rng, r)) {
                    transformed.emplace_back(converted_range(rng, r));
                    if (transformed.back().second != rng.second) {
                        auto new_untransformed = unconverted_ranges(rng, r);
                        std::copy(new_untransformed.begin(), new_untransformed.end(), std::back_inserter(untransformed));
                    }
                } else untransformed.push_back(rng);
            }
        }
        std::copy(transformed.begin(), transformed.end(), std::back_inserter(untransformed));
        transformed.clear();
    }
    std::ranges::sort(untransformed, [](const auto& r1, const auto& r2) {return r1.first < r2.first;});
    return untransformed[0].first;
}

long day05::part_two() {
    return std::ranges::min(ranges | std::views::transform(
        [=, this](const auto& rng) {
            return transform_range(rng);
        }));
    return 0;
}

int main() {
    day05 day05;
    profile_day(day05);
}
