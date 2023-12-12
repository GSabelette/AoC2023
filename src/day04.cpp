#include "day04.hpp"

card::card(std::stringstream ss) {
    std::string tmp;
    while (tmp.back() != ':') ss >> tmp;
    auto read = [&](auto& v){ss >> tmp; if (tmp != "|") v.push_back(std::stoi(tmp)); return tmp != "|";};
    while (read(wins));
    while (!ss.eof()) read(draws);
    std::ranges::sort(wins);
    std::ranges::sort(draws);
}

day04::day04() {
    for (const auto& l : readFile("input/day04.in")) cards.emplace_back(std::stringstream(l)); 
    compute_scores();
}

void day04::compute_scores() {
    std::for_each(cards.begin(), cards.end(),
                 [=,this](const card& card) {
                    std::vector<uint16_t> intersect;
                    std::ranges::set_intersection(card.wins, card.draws, std::back_inserter(intersect));
                    scores.push_back(intersect.size());
                 });
}

uint16_t day04::part_one() {
    return std::accumulate(scores.begin(), scores.end(), 0,
                           [](uint16_t acc, uint16_t score) {
                                return acc + (1 << score >> 1);
                           });
}

uint64_t day04::part_two() {
    std::vector<uint32_t> copies(cards.size(), 1);
    for (size_t i = 0; i < cards.size(); ++i)
        for (size_t k = 1; k <= scores[i]; ++k) copies[i + k] += copies[i];
    return std::accumulate(copies.begin(), copies.end(), 0);
}

int main() {
    day04 day04;
    profile_day(day04);
}
