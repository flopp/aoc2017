#include <cassert>
#include <iostream>
#include <string>
#include <map>

typedef std::pair<int, int> XY;
void reverse(XY& dir) {
    dir.first *= -1;
    dir.second *= -1;
}
void turn_left(XY& dir) {
    std::swap(dir.first, dir.second);
    dir.second *= -1;
}
void turn_right(XY& dir) {
    std::swap(dir.first, dir.second);
    dir.first *= -1;
}

enum class State {
    Clean,
    Weakened,
    Infected,
    Flagged
};

    
int main() {
    std::map<XY, State> nodes;
    XY p;
    XY d{0, -1}; /* 0 -1 = north; 1 0 = east; 0 1 = south; -1 0 = west */
    
    int y = 0;
    for (std::string line; std::getline(std::cin, line); /**/) {
        int x = 0;
        for (auto c: line) {
            if (c == '#') {
                nodes.insert({XY{x, y}, State::Infected});
            } else if (c == '.') {
                nodes.insert({XY{x, y}, State::Clean});
            } else {
                assert(false);
            }
            ++x;
        }
        ++y;
    }
    p.first = (y-1)/2;
    p.second = p.first;
    
#ifdef PART1
    const int loops = 10000;
#else
    const int loops = 10000000;
#endif
    int infections = 0;
    for (int loop = 0; loop < loops; ++loop) {
        auto state = nodes.find(p);
        if (state == nodes.end()) {
            state = nodes.insert({p, State::Clean}).first;
        }
        switch (state->second) {
            case State::Clean:
                turn_left(d);
#ifdef PART1
                state->second = State::Infected;
                ++infections;
#else
                state->second = State::Weakened;
#endif
                break;
            case State::Infected:
                turn_right(d);
#ifdef PART1
                state->second = State::Clean;
#else
                state->second = State::Flagged;
#endif
                break;
            case State::Weakened:
                state->second = State::Infected;
                ++infections;
                break;
            case State::Flagged:
                reverse(d);
                state->second = State::Clean;
                break;
        }
        p.first += d.first;
        p.second += d.second;
    }
    
    std::cout << infections << std::endl;
    
    return 0;
}
