#include <iostream>
#include <string>

int f(const std::string& input, int offset) {
    int sum = 0;
    const int length = input.size();
    for (int i = 0; i < length; ++i) {
        if (input[i] == input[(i + offset) % length]) {
            sum += (input[i] - '0');
        }
    }
    return sum;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
#ifdef PART1
        std::cout << f(line, 1) << std::endl;
#else
        std::cout << f(line, line.size() / 2) << std::endl;
#endif
    }
    return 0;
}
