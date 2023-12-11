#include "day01.hpp"

day01::day01() {
  input = view_file("input/day01.in");
  input.pop_back();
}

std::array<std::string_view, 9> digits = {
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int str_to_digit(std::string_view s) {
  auto match = std::ranges::find_if(digits, [&s](auto&& digit){
    return s.starts_with(digit);
  });
  if (match == digits.end()) return -1;
  return std::distance(digits.begin(), match) + 1;
}

uint16_t day01::part_one() {
  auto isnotdigit = [](char c){return !isdigit(c);};
  auto first_digit = std::views::drop_while(isnotdigit);
  auto last_digit = std::views::reverse | first_digit;
  auto rgtoi = [](auto&& rg) -> uint16_t {return *rg.begin() - '0';};
  
  return std::ranges::fold_left(input | std::views::split('\n'), 0, 
                                [&](uint16_t acc, auto&& l) {
                                    return acc + 10 * rgtoi(l | first_digit) + rgtoi(l | last_digit);
                                });
}

uint16_t day01::part_two() {
  return std::ranges::fold_left(input | std::views::split('\n'), 0,
                                [&](uint16_t acc, auto&& l) {
                                  int first_match = -1;
                                  int last_match = -1;
                                  auto update = [&first_match, &last_match](int digit) {
                                    if (first_match == -1) first_match = digit;
                                    last_match = digit;
                                  };
                                  for (auto pos : std::views::iota(l.begin(), l.end())) {
                                    if (isdigit(*pos)) update(*pos - '0');
                                    else if (auto digit = str_to_digit(std::string_view(pos, l.end())); digit != -1) {
                                      update(digit);
                                    }
                                  }
                                  return acc + 10 * first_match + last_match;
                                });
}

int main() {
  day01 day01;
  profile_day(day01);
}  
