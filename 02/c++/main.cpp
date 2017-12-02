#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<int>{std::istream_iterator<int>{iss}, {}};
}

int diff_max_min(const std::vector<int>& v) {
    int min{v[0]};
    int max{min};
    for (auto i: v) {
        if (i < min) {
            min = i;
        } else if (i > max) {
            max = i;
        }
    }
    return max - min;
}

int div_dividable(const std::vector<int>& v) {
    for (auto i = 0u; i < v.size(); ++i) {
        for (auto j = 0u; j < v.size(); ++j) {
            if ((i != j) && 
                ((v[i] % v[j]) == 0)) {
                return v[i] / v[j];
            }
        }
    }
    return 0;
}

int main() {
    int sum{0};
    for (std::string line; std::getline(std::cin, line); /**/) {
#ifdef PART1
        sum += diff_max_min(split(line));
#else
        sum += div_dividable(split(line));
#endif
    }
    std::cout << sum << std::endl;
    return 0;
}
