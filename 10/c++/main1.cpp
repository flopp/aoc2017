#include <iostream>
#include <string>
#include <vector>

void rotate(std::vector<int>& v, int left, int right) {
    for (/**/; left < right; ++left, --right) {
        std::swap(v[left % v.size()], v[right % v.size()]);
    }
}

int main(int argc, char* argv[]) {
    auto size = 256;
    if (argc == 2) {
        size = std::stoi(argv[1]);
    }
    
    std::vector<int> list;
    for (auto i = 0; i < size; ++i) {
        list.push_back(i);
    }
    
    auto pos = 0;
    auto skip = 0;
    
    for (int length; std::cin >> length; /**/) {
        if (std::cin.peek() == ',') {
            std::cin.ignore();
        }
        
        rotate(list, pos, pos + length - 1);
        pos = (pos + length + skip) % list.size();
        ++skip;
    }
    
    std::cout << (list[0] * list[1]) << std::endl;
    return 0;
}
