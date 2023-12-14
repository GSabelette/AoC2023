#include "day06.hpp"

day06::day06() {
    std::stringstream ss(view_file("input/day06.in"));
    auto skip_non_digits = [](std::stringstream& ss) {while (!std::isdigit(ss.peek())) ss.ignore();};
    
    std::vector<uint64_t> v1, v2;

    skip_non_digits(ss);
    std::ranges::copy(std::views::istream<uint64_t>(ss), std::back_inserter(v1));
    ss.clear(); skip_non_digits(ss);
    std::ranges::copy(std::views::istream<uint64_t>(ss), std::back_inserter(v2));
    
    for (auto [val1, val2] : std::views::zip(v1, v2)) races.emplace_back(val1, val2);
}

template <typename R>
long beats_max(const R& r) {
    double r1 = -(-r.first - std::sqrt(r.first * r.first - 4 * r.second)) / 2;
    double r2 = -(-r.first + std::sqrt(r.first * r.first - 4 * r.second)) / 2;
    return std::floor(std::nexttoward(r1, r2)) - std::ceil(std::nexttoward(r2, r1)) + 1; 
}

uint64_t day06::part_one() {
    return std::accumulate(races.begin(), races.end(), 1,
                            [=,this](uint64_t acc, const race& r) {
                                return acc * beats_max(r);
                            });
}

long day06::part_two() {
    std::string tmp1, tmp2;
    std::for_each(races.begin(), races.end(),
                 [&tmp1, &tmp2](const auto& r) {
                    tmp1 += std::to_string(r.first);
                    tmp2 += std::to_string(r.second);
                 });
    return beats_max(std::pair<long, long>(std::stol(tmp1), std::stol(tmp2)));
}

int main() {
    day06 day06;
    profile_day(day06);
}
