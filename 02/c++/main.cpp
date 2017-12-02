#include <iostream>
#include <string>
#include <vector>

std::vector<int> split(const std::string& s) {
    std::vector<int> res;
    int i = -1;
    for (auto c: s) {
        if (isspace(c)) {
            if (i >= 0) {
                res.push_back(i);
                i = -1;
            }
        } else {
            if (i < 0) {
                i = 0;
            }
            i = i * 10 + int(c - '0');
        }
    }
    if (i >= 0) {
        res.push_back(i);
    }
    return res;
}

int diff_max_min(const std::vector<int>& ints) {
    int min = -1;
    int max = -1;
    for (auto i: ints) {
        if (min < 0) {
            min = i;
            max = i;
        } else if (i < min) {
            min = i;
        } else if (i > max) {
            max = i;
        }
    }
    return max - min;
}

int div_dividable(const std::vector<int>& ints) {
    for (auto i = 0u; i < ints.size(); ++i) {
        for (auto j = 0u; j < ints.size(); ++j) {
            if ((i != j) && 
                ((ints[i] % ints[j]) == 0)) {
                return ints[i] / ints[j];
            }
        }
    }
    return 0;
}

int main() {
    int sum = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
#ifdef PART1
        sum += diff_max_min(split(line));
#else
        sum += div_dividable(split(line));
#endif
    }
    std::cout << sum << std::endl;
    
    return 0;
}
