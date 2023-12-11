#include <common.hpp>

template <typename T, typename U>
class day {
  public:
    T part_one();
    U part_two();
    void profile_part_one() { 
      std::cout << profile("Part one", [=,this](){return this.part_one();}) << "\n";
      
    }
    void profile_part_two() {
      std::cout << profile("Part two", [=,this](){return this.part_two();}) << "\n";
    }
};
