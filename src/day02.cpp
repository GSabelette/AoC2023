#include "day02.hpp"

day02::day02() {
    auto input = readFile("input/day02.in");
    for (auto& l : input) 
        games.emplace_back(l);
}

game::game(const std::string& s) {
    std::stringstream sstream(s);
    std::string tmp;
    sstream >> tmp >> id >> tmp; //past the :
    do {
        draw cur_draw{0,0,0};
        do {
            std::string clr;
            uint16_t cnt = 0;
            sstream >> cnt >> tmp;
            cur_draw[tmp[0] - 'g' > 0 ? 0 : tmp[0] - 'g' == 0 ? 1 : 2] = cnt; 
        } while (tmp.back() == ',');
        draws.push_back(cur_draw);
    } while (tmp.back() == ';');
}

uint16_t day02::evaluate(auto f) {
    return std::accumulate(games.begin(), games.end(), 0, [&](uint16_t acc, const auto& game) {return acc + f(game);});
}

uint16_t day02::part_one() {
    auto f = [](const auto& game) {
        return std::accumulate(game.draws.begin(), game.draws.end(), 1, 
                               [&game](bool b, const auto& draw) {
                                    for (size_t i = 0; i < draw.size(); ++i)
                                        b = (b && draw[i] <= (12+i)); 
                                    return b * game.id;
                               });
    };
    return evaluate(f);
}

uint16_t day02::part_two() {
    auto f = [] (const auto& game) {
        draw max_draw{0,0,0};
        std::for_each(game.draws.begin(), game.draws.end(),
                               [&max_draw](const auto& draw) {
                                    for (size_t i = 0; i < draw.size(); ++i) 
                                        max_draw[i] = std::max(max_draw[i], draw[i]); 
                               });
        return std::accumulate(max_draw.begin(), max_draw.end(), 1, std::multiplies<uint16_t>());
    };
    return evaluate(f);
}

int main() {
    day02 day02;
    profile_day(day02);
}
