#include <iostream>
#include <map>
#include <regex>
#include <string>

bool cmp(int v1, const std::string& c, int v2) {
    if (c == "==") {
        return (v1 == v2);
    } else if (c == "!=") {
        return (v1 != v2);
    } else if (c == "<") {
        return (v1 < v2);
    } else if (c == "<=") {
        return (v1 <= v2);
    } else if (c == ">") {
        return (v1 > v2);
    } else if (c == ">=") {
        return (v1 >= v2);
    } else {
        std::cout << "bad cmp '" << c << "'" << std::endl;
        return false;
    }
}

int main() {
    auto registers = std::map<std::string, int>{};
    auto re_instruction_inc = std::regex{"^\\s*([a-z]+)\\s+inc\\s+(-?\\d+)\\s+if\\s+([a-z]+)\\s+([<>=!]{1,2})\\s+(-?\\d+)\\s*$"};
    auto re_instruction_dec = std::regex{"^\\s*([a-z]+)\\s+dec\\s+(-?\\d+)\\s+if\\s+([a-z]+)\\s+([<>=!]{1,2})\\s+(-?\\d+)\\s*$"};
    
    auto max = int{0};
    for (std::string line; std::getline(std::cin, line); /**/) {
        std::smatch m;
        if (std::regex_match(line, m, re_instruction_inc)) {
            if (cmp(registers[m[3]], m[4], std::stoi(m[5]))) {
                registers[m[1]] += std::stoi(m[2]);
                max = std::max(max, registers[m[1]]);
            }
        } else if (std::regex_match(line, m, re_instruction_dec)) {
            if (cmp(registers[m[3]], m[4], std::stoi(m[5]))) {
                registers[m[1]] -= std::stoi(m[2]);
                max = std::max(max, registers[m[1]]);
            }
        }
    }
    std::cout << "max intermediate value = " << max << std::endl;
    
    max = registers.begin()->second;
    for (auto r = registers.begin(); r != registers.end(); ++r) {
        max = std::max(max, r->second);
    }
    std::cout << "max end value = " << max << std::endl;
    
    return 0;
}
