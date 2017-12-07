#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <vector>

struct Tower {
    int weight;
    int subWeights = 0;
    int totalWeight() const {
        return weight + subWeights;
    }
    std::map<std::string, Tower*> children;
};

int main() {
    // parse input
    std::map<std::string, Tower*> towers;
    std::map<std::string, Tower*> open;
    static const std::regex re_leaf("^([a-z]+)\\s*\\((\\d+)\\)\\s*$");
    static const std::regex re_node("^([a-z]+)\\s*\\((\\d+)\\)\\s+->\\s+([a-z].*)\\s*$");
    for (std::string line; std::getline(std::cin, line); /**/) {
        std::smatch m;
        if (std::regex_match(line, m, re_leaf)) {
            Tower* t = new Tower;
            std::istringstream iss{m[2]};
            iss >> t->weight;
            towers[m[1]] = t;
        } else if (std::regex_match(line, m, re_node)) {
            Tower* t = new Tower;
            std::istringstream iss{m[2]};
            iss >> t->weight;
            towers[m[1]] = t;
            std::istringstream iss2{m[3]};
            for (std::string child; iss2 >> child; /**/) {
                if (child[child.size() - 1] == ',') {
                    child = child.substr(0, child.size() - 1);
                }
                t->children[child] = nullptr;
            }
            open[m[1]] = t;
        }
    }
    
    // build actual 'tree'
    while (open.size() > 1) {
        for (auto it = open.begin(); it != open.end(); /**/) {
            bool all_children_closed = true;
            for (auto c = it->second->children.begin(); c != it->second->children.end(); ++c) {
                if (open.find(c->first) != open.end()) {
                    all_children_closed = false;
                    break;
                }
            }
            if (all_children_closed) {
                int w = -1;
                bool unbalanced = false;
                for (auto c = it->second->children.begin(); c != it->second->children.end(); ++c) {
                    Tower* t = towers[c->first];
                    c->second = t;
                    it->second->subWeights += t->totalWeight();
                    if (w < 0) {
                        w = t->totalWeight();
                    } else {
                        if (w != t->totalWeight()) {
                            unbalanced = true;
                        }
                    }
                }
                if (unbalanced) {
                    std::cout << "unbalanced" << std::endl;
                    for (auto c = it->second->children.begin(); c != it->second->children.end(); ++c) {
                        std::cout << c->first << " " << c->second->totalWeight() << " " << c->second->weight << " " << c->second->subWeights << std::endl;
                    }
                }
                it = open.erase(it);
            } else {
                ++it;
            }
        }
    }
    std::cout << open.begin()->first << std::endl;
    
    return 0;
}
