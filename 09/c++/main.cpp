#include <iostream>
#include <string>

int main() {
    for (std::string line; std::getline(std::cin, line); /**/) {
        auto depth = 0;
        auto score = 0;
        auto garbage = 0;
        auto in_garbage = false;        
        for (auto pos = 0u; pos < line.size(); ++pos) {
            auto c = line[pos];
            if (c == '!') {
                ++pos;
            } else if (in_garbage) {
                if (c == '>') {
                    in_garbage = false;
                } else {
                    ++garbage;
                }
                continue;
            } else if (c == '{') {
                ++depth;
                score += depth;
            } else if (c == '}') {
                --depth;
            } else if (c == '<') {
                in_garbage = true;
            }
        }
        std::cout
            << "score   = " << score << std::endl
            << "garbage = " << garbage << std::endl;
    }
    
    return 0;
}
