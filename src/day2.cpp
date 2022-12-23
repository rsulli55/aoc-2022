#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "fmt/core.h"

enum class OppPlay : char { Rock = 'A', Paper = 'B', Scissors = 'C' };
enum class OurPlay : char { Rock = 'X', Paper = 'Y', Scissors = 'Z' };
struct Round {
    OppPlay opponent;
    OurPlay us;
};

std::istream& operator>>(std::istream& is, OppPlay& opp) {
    char play;
    is >> play;
    opp = static_cast<OppPlay>(play);
    return is;
}

std::istream& operator>>(std::istream& is, OurPlay& us) {
    char play;
    is >> play;
    us = static_cast<OurPlay>(play);
    return is;
}

std::istream& operator>>(std::istream& is, Round& round) {
    char ws;
    is >> round.opponent;
    is >> round.us;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Round& round) {
    os << "Round: " << static_cast<char>(round.opponent) << ' ' << static_cast<char>(round.us);
    return os;
}

int round_score1(const Round& round) {
    const int play_score = [&]() {
        switch(round.us) {
            case OurPlay::Rock:
                return 1;
            case OurPlay::Paper:
                return 2;
            case OurPlay::Scissors:
                return 3;
            default:
                return 0;
        }
    }();

    if ( (round.us == OurPlay::Rock && round.opponent == OppPlay::Rock) || 
         (round.us == OurPlay::Paper && round.opponent == OppPlay::Paper) || 
         (round.us == OurPlay::Scissors && round.opponent == OppPlay::Scissors) ) {
        return play_score + 3;
    }

    if ( (round.us == OurPlay::Rock && round.opponent == OppPlay::Scissors) || 
         (round.us == OurPlay::Paper && round.opponent == OppPlay::Rock) || 
         (round.us == OurPlay::Scissors && round.opponent == OppPlay::Paper) ) {
        return play_score + 6;
    }

    return play_score;
}

int round_score2(const Round& round) {
    // OurPlay::Rock is lose
    // OurPlay::Paper is tie
    // OurPlay::Scissors is win
    const int result_score = [&]() {
        switch(round.us) {
            case OurPlay::Rock:
                return 0;
            case OurPlay::Paper:
                return 3;
            case OurPlay::Scissors:
                return 6;
            default:
                return 0;
        }
    }();
    
    // we play rock if
    // need to lose and opp plays paper
    // need to tie and opp plays rock
    // need to win and opp plays Scissors
    if ( (round.us == OurPlay::Rock && round.opponent == OppPlay::Paper) || 
         (round.us == OurPlay::Paper && round.opponent == OppPlay::Rock) || 
         (round.us == OurPlay::Scissors && round.opponent == OppPlay::Scissors) ) {
        return result_score + 1;
    }

    // we play paper if
    // need to lose and opp plays scissors
    // need to tie and opp plays paper
    // need to win and opp plays Rock
    if ( (round.us == OurPlay::Rock && round.opponent == OppPlay::Scissors) || 
         (round.us == OurPlay::Paper && round.opponent == OppPlay::Paper) || 
         (round.us == OurPlay::Scissors && round.opponent == OppPlay::Rock) ) {
        return result_score + 2;
    }
    
    // otherwise we play scissors
    return result_score + 3;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fmt::print("usage: day2 <day2_input>\n");
    }
    std::ifstream input{argv[1]};

    std::stringstream stream;
    /* stream.str("B X\nB Z\nB Z\nA Y\nB X\nA Y\n"); */
    /* stream.str("A Y\nB X\nC Z\n"); */
    std::vector<Round> rounds;
    std::copy(std::istream_iterator<Round>(input), std::istream_iterator<Round>(),
              std::back_inserter(rounds));

    /* for (const auto& round : rounds) { */
    /* fmt::print("{}\n", round); */
    /* std::cout << round << " with score: " << round_score(round) << '\n'; */
    /* } */

    std::vector<int> scores(rounds.size());
    std::transform(std::begin(rounds), std::end(rounds), std::begin(scores), round_score1);
    const auto total_score1 = std::accumulate(std::begin(scores), std::end(scores), 0);

    std::transform(std::begin(rounds), std::end(rounds), std::begin(scores), round_score2);
    const auto total_score2 = std::accumulate(std::begin(scores), std::end(scores), 0);


    fmt::print("Total score part1: {}\n", total_score1);
    fmt::print("Total score part2: {}\n", total_score2);

    return 0;
}
