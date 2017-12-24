#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct Component {
    int pins1, pins2;
    int strength() const {
        return pins1 + pins2;
    }
};

void dfs(
    const std::vector<Component>& comps, 
    std::vector<bool>& used,
    int& max_length,
    int& max_strength,
    int& max_strength_at_max_length,
    int last_pins,
    int length,
    int strength)
{
    for (auto i = 0u; i < comps.size(); ++i) {
        if (used[i]) {
            continue;
        }
        const auto& c = comps[i];
        if (c.pins1 == last_pins) {
            used[i] = true;
            dfs(comps, used,
                max_length, max_strength, max_strength_at_max_length,
                c.pins2, length + 1, strength + c.strength());
            used[i] = false;
        }
        if (c.pins2 == last_pins) {
            used[i] = true;
            dfs(comps, used,
                max_length, max_strength, max_strength_at_max_length,
                c.pins1, length + 1, strength + c.strength());
            used[i] = false;
        }
    }
    
    if (strength > max_strength) {
        max_strength = strength;
    }
    if (length > max_length) {
        max_length = length;
        max_strength_at_max_length = strength;
    } else if (length == max_length) {
        if (strength > max_strength_at_max_length) {
            max_strength_at_max_length = strength;
        }
    }
}

int main() {
    std::vector<Component> components;
    while (std::cin) {
        Component c;
        std::cin >> c.pins1;
        std::cin.ignore();
        std::cin >> c.pins2;
        components.push_back(c);
    }
    
    std::vector<bool> used(components.size(), false);
    int max_length = 0;
    int max_strength = 0;
    int max_strength_at_max_length = 0;
    dfs(components, used,
        max_length, max_strength, max_strength_at_max_length,
        0, 0, 0);
    std::cout << "max_strength=" << max_strength << " (total)" << std::endl;
    std::cout << "max_strength=" << max_strength_at_max_length << " (at max_length=" << max_length << ")" << std::endl;
    
    
    return 0;
}
