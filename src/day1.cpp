#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "fmt/core.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fmt::print("usage: day1 <day1_input>\n");
    }

    std::ifstream input{argv[1]};
    std::vector<int> calories;
    std::copy(std::istream_iterator<int>(input), std::istream_iterator<int>(),
              std::back_inserter(calories));

    std::vector<int> calorie_sums;
    auto calories_end = std::end(calories);
    auto current_start = std::begin(calories);
    auto current_end = std::find(current_start, calories_end, 0);
    for (;;) {
        calorie_sums.emplace_back(std::accumulate(current_start, current_end, 0));
        if (current_end == calories_end) break;
        current_start = std::next(current_end);
        current_end = std::find(current_start, calories_end, 0);
    }
    
    std::sort(std::begin(calorie_sums), std::end(calorie_sums), std::greater<int>());
    std::vector<int> top_three_sums(3);
    std::partial_sum(std::begin(calorie_sums), std::next(std::begin(calorie_sums), 3), 
                     std::begin(top_three_sums));
    fmt::print("Most calories: {}\n", top_three_sums[0]);
    fmt::print("Top 3 calories sum: {}\n", top_three_sums[2]);

    return 0;
}
