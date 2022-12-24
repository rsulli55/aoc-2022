#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "fmt/core.h"

int priority_lower(char c) {
    return static_cast<int>(c) - static_cast<int>('a') + 1;
}

int priority(char c) {
    if (std::islower(c)) {
        return priority_lower(c);
    }
    return static_cast<int>(c) - static_cast<int>('A') + 1 + priority_lower('z');
}

int part1(std::vector<std::string>& rucksacks) {
    std::vector<int> priorities(rucksacks.size());
    std::transform(std::begin(rucksacks), std::end(rucksacks), 
            std::begin(priorities),
            [](const auto& sack) {
                const auto& start = std::begin(sack);
                const auto mid = std::next(start, sack.size() / 2);
                const auto& finish = std::end(sack);
                const auto it = std::find_first_of(start, mid, mid, finish);
                return priority(*it);
            });
    const auto sum_of_prios = std::accumulate(std::begin(priorities), std::end(priorities), 0);
    return sum_of_prios;
}

int part2(std::vector<std::string>& rucksacks) {
    // sort the rucksacks
    std::for_each(std::begin(rucksacks), std::end(rucksacks), 
            [](std::string& str) {
                std::sort(std::begin(str), std::end(str));
            });
    std::vector<char> shared_items;
    shared_items.reserve(rucksacks.size() / 3);
    for (auto it = std::begin(rucksacks); it != std::end(rucksacks);
            it = std::next(it, 3)) {
        std::vector<char> elf1_and_elf2_intersection;
        std::set_intersection(std::begin(*it), std::end(*it), 
            std::begin(*std::next(it, 1)), std::end(*std::next(it,1)),
            std::back_inserter(elf1_and_elf2_intersection));
        const auto e1_e2_end = std::unique(std::begin(elf1_and_elf2_intersection), 
                    std::end(elf1_and_elf2_intersection));
    std::vector<char> full_intersection;
        std::set_intersection(std::begin(elf1_and_elf2_intersection), e1_e2_end, 
            std::begin(*std::next(it, 2)), std::end(*std::next(it, 2)),
            std::back_inserter(full_intersection));
        if (full_intersection.size() != 1) {
            fmt::print("Problem with\n");
            fmt::print("  Sack1 {} \n", *it);
            fmt::print("  Sack2 {} \n", *std::next(it, 1));
            fmt::print("  Sack3 {} \n", *std::next(it, 2));
            fmt::print("  full_intersection: ");
            for (const auto c: full_intersection) {
                fmt::print("{}, ", c);
                fmt::print("\n");
            }
        }
        shared_items.push_back(full_intersection[0]);
    }

    std::vector<int> priorities(shared_items.size());
    std::transform(std::begin(shared_items), std::end(shared_items),
            std::begin(priorities), priority);
    const auto sum_of_prios = std::accumulate(std::begin(priorities), std::end(priorities), 0);
    return sum_of_prios;
}
    




int main(int argc, char* argv[]) {
    if (argc != 2) {
        fmt::print("usage: day3 <day3_input>\n");
    }

    std::ifstream input{argv[1]};
    std::vector<std::string> rucksacks;

    std::copy(std::istream_iterator<std::string>(input), 
              std::istream_iterator<std::string>(),
              std::back_inserter(rucksacks));

    const auto answer1 = part1(rucksacks);
    const auto answer2 = part2(rucksacks);

    /* for (const auto c : "abcyzABCYZ") { */
    /*     fmt::print("letter {} has priority {}\n", c, priority(c)); */
    /* } */

    fmt::print("Part 1 answer = {}\n", answer1);
    fmt::print("Part 2 answer = {}\n", answer2);

    return 0;
}
