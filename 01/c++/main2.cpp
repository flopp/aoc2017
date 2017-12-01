#include <iostream>
#include <string>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        int sum = 0;
        int len = line.size();
        for (int i = 0; i < len; ++i) {
            if (line[i] == line[(i + len/2) % len]) {
                sum += (line[i] - '0');
            }
        }
        std::cout << sum << std::endl;
    }
    return 0;
}
