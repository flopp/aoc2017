#include <iostream>
#include <map>
#include <regex>
#include <string>

bool cmp(int v1, const std::string& c, int v2) {
    if      (c == "==") { return (v1 == v2); }
    else if (c == "!=") { return (v1 != v2); }
    else if (c == "<" ) { return (v1 <  v2); }
    else if (c == "<=") { return (v1 <= v2); }
    else if (c == ">" ) { return (v1 >  v2); }
    else if (c == ">=") { return (v1 >= v2); }

    return false;
}

int main() {
    auto registers = std::map<std::string, int>{};
    auto re_instruction = std::regex{"^\\s*([a-z]+)\\s+(inc|dec)\\s+(-?\\d+)\\s+if\\s+([a-z]+)\\s+([<>=!]{1,2})\\s+(-?\\d+)\\s*$"};
    
    auto max = int{0};
    for (std::string line; std::getline(std::cin, line); /**/) {
        std::smatch m;
        if (std::regex_match(line, m, re_instruction)) {
            if (cmp(registers[m[4]], m[5], std::stoi(m[6]))) {
                registers[m[1]] += ((m[2] == "inc") ? +1 : -1) * std::stoi(m[3]);
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
