#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>


bool is_valid(const std::string& line) {
    std::istringstream iss{line};
    std::set<std::string> unique;
    for (std::string s; iss >> s; /**/) {
#ifdef PART2
        std::sort(s.begin(), s.end());
#endif
        if (unique.find(s) != unique.end()) {
            return false;
        }
        unique.insert(s);
    }
    return true;
}


int main() {
    int count = 0;
    for (std::string input; std::getline(std::cin, input); /**/) {
        if (is_valid(input)) {
            ++count;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
