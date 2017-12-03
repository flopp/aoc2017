#include <iostream>
#include <map>
#include <string>
#include <vector>

// squares in 'layer' and below
int squares(int layer) {
    return (2 * layer + 1) * (2 * layer + 1);
}

// largest layer that contains 'square'
int layer(int square) {
    if (square == 1) {
        return 0;
    }
    for (int l = 0; true; ++l) {
        if (square <= squares(l)) {
            return l;
        }
    }
    return -1;
}

// side center squares of 'layer'
std::vector<int> centers(int layer) {
    if (layer == 0) {
        return {1};
    }

    const int ring = squares(layer) - squares(layer - 1);
    const int east = squares(layer - 1) + layer;
    return {east, east + ring/4, east + ring/2, east + 3*ring/4};
}

int part1(int input) {
    int l = layer(input);
    // compute minimum distance to any side center point
    int min = -1;
    for (auto c: centers(l)) {
        int m = std::abs(c - input);
        if (min < 0 || m < min) {
            min = m;
        }
    }
    return l + min;
}

struct Pos {
    int layer, x, y;

    void next() {
        if (x == layer) { // east
            if (y == -layer) { // south-east => move east/next layer
                ++x;
                ++layer;
            } else if (y == layer) { // north-east => move west
                --x;
            } else { // otherwise => move north
                ++y;
            }
        } else if (x == -layer) { // west
            if (y > -layer) { // not south-west => move south
                --y;
            } else { // south-west => move east
                ++x;
            }
        } else if (y == layer) { // north => move west
            --x;
        } else if (y == -layer) { // south => move east
            ++x;
        }
    }
    
    int computeValue(const std::map<std::pair<int, int>, int>& values) const {
        int v = 0;
        for (auto dx: {-1, 0, +1}) {
            for (auto dy: {-1, 0, +1}) {
                auto p = values.find({x+dx, y+dy});
                if (p != values.end()) {
                    v += p->second;
                }
            }
        }
        return v;
    }
};

int part2(int input) {
    std::map<std::pair<int, int>, int> values;
    values[{0,0}] = 1;
    Pos p{0, 0, 0};
    
    for (;;) {
        p.next();
        int v = p.computeValue(values);
        if (v > input) {
            return v;
        }
        values[{p.x, p.y}] = v;
    }
    return -1;
}

int main() {
    for (int input; std::cin >> input; /**/) {
#ifdef PART1
        std::cout << part1(input) << std::endl;
#else
        std::cout << part2(input) << std::endl;
#endif
    }
    return 0;
}
