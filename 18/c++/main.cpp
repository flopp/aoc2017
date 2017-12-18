#include <cassert>
#include <iostream>
#include <string>
#include <vector>

enum class Type {
    SET,
    ADD,
    MUL,
    MOD,
    SND,
    RCV,
    JGZ,
    JGZI,
};

struct Instruction {
    Type type;
    bool const_value;
    int target;
    int value;
    std::string line;
};

int main() {
    std::vector<Instruction> instructions;
    std::vector<int> mem(26, 0);
    int pc = 0;
    
    for (std::string line; std::getline(std::cin, line); /**/) {
        std::cout << line << std::endl;
        Instruction inst;
        inst.line = line;
        std::string s;
        
        s = line.substr(0, 3);
        if (s == "set") { inst.type = Type::SET; }
        else if (s == "add") { inst.type = Type::ADD; }
        else if (s == "mul") { inst.type = Type::MUL; }
        else if (s == "mod") { inst.type = Type::MOD; }
        else if (s == "snd") { inst.type = Type::SND; }
        else if (s == "rcv") { inst.type = Type::RCV; }
        else if (s == "jgz") { inst.type = Type::JGZ; }
        else { std::cout << "bad type: " << line; }
        
        if (('a' <= line[4]) && (line[4] <= 'z')) {
            inst.target = (line[4] - 'a');
        } else {
            assert(inst.type == Type::JGZ);
            inst.type = Type::JGZI;
            inst.target = (line[4] - '0');
        }
        
        std::cout << "target = " << inst.target << std::endl;
        inst.value = 0;
        inst.const_value = true;
        if (line.size() >= 7) {
            if (('a' <= line[6]) && (line[6] <= 'z')) {
                inst.value = line[6] - 'a';
                inst.const_value = false;
            } else {
                inst.value = std::stoi(line.substr(6));
                inst.const_value = true;
            }
            std::cout << "value = " << inst.value << std::endl;
        }
        
        instructions.push_back(inst);
    }
    
    int snd = 0;
    while (true) {
        const auto& inst = instructions[pc];
        std::cout << pc << ": " << inst.line << std::endl;
        switch (inst.type) {
            case Type::SET:
                mem[inst.target] = inst.const_value ? inst.value : mem[inst.value];
                std::cout << "-> " << mem[inst.target] << std::endl;
                ++pc;
                break;
            case Type::ADD:
                mem[inst.target] += inst.const_value ? inst.value : mem[inst.value];
                std::cout << "-> " << mem[inst.target] << std::endl;
                ++pc;
                break;
            case Type::MUL:
                mem[inst.target] *= inst.const_value ? inst.value : mem[inst.value];
                std::cout << "-> " << mem[inst.target] << std::endl;
                ++pc;
                break;
            case Type::MOD:
                if (inst.const_value) {
                    std::cout << mem[inst.target] << " % " << inst.value << std::endl;
                } else {
                    std::cout << mem[inst.target] << " % " << mem[inst.value] << " (mem[" << inst.value << "])" << std::endl;
                }
                mem[inst.target] %= (inst.const_value ? inst.value : mem[inst.value]);
                std::cout << "-> " << mem[inst.target] << std::endl;
                ++pc;
                break;
            case Type::SND:
                snd = mem[inst.target];
                std::cout << "-> " << snd << std::endl;
                ++pc;
                break;
            case Type::RCV:
                if (snd != 0) {
                    std::cout << snd << std::endl;
                    return 0;
                }
                ++pc;
                break;
            case Type::JGZ:
                if (mem[inst.target] > 0) {
                    pc += inst.const_value ? inst.value : mem[inst.value];
                } else {
                    ++pc;
                }
                break;
            case Type::JGZI:
                if (inst.target > 0) {
                    pc += inst.const_value ? inst.value : mem[inst.value];
                } else {
                    ++pc;
                }
                break;
        }
    }
    
    return 0;
}
