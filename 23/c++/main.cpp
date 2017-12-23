#include <cassert>
#include <iostream>
#include <string>
#include <vector>

enum class Type {
    SET,
    SUB,
    MUL,
    JNZ,
    JNZI,
};

struct Instruction {
    Type type;
    bool const_value;
    int64_t target;
    int64_t value;
    std::string line;
};

struct Process {
    Process(const std::vector<Instruction>& instructions) :
        _instructions(instructions),
        _mem(8, 0) {
#ifdef PART2
            _mem[0] = 1;
#endif
        }
    
    void print() const {
        for (const auto& m: _mem) {
            std::cout << m << "   ";
        }
        std::cout << std::endl;
    }
    
    bool compute() {
        if (_pc < 0 || _pc >= (int64_t)_instructions.size()) {
            return false;
        }
        
        const auto& inst = _instructions[_pc];
        switch (inst.type) {
            case Type::SET:
                _mem[inst.target] = inst.const_value ? inst.value : _mem[inst.value];
                ++_pc;
                break;
            case Type::SUB:
                _mem[inst.target] -= inst.const_value ? inst.value : _mem[inst.value];
                ++_pc;
                break;
            case Type::MUL:
                _mem[inst.target] *= inst.const_value ? inst.value : _mem[inst.value];
                ++_mul;
                ++_pc;
                break;
            case Type::JNZ:
                if (_mem[inst.target] != 0) {
                    _pc += inst.const_value ? inst.value : _mem[inst.value];
                } else {
                    ++_pc;
                }
                break;
            case Type::JNZI:
                if (inst.target != 0) {
                    _pc += inst.const_value ? inst.value : _mem[inst.value];
                } else {
                    ++_pc;
                }
                break;
        }
        return true;
    }
    
    std::vector<Instruction> _instructions;
    std::vector<int64_t> _mem;
    int _pc{0};
    int _mul{0};
};

int main() {
    std::vector<Instruction> instructions;
    for (std::string line; std::getline(std::cin, line); /**/) {
        Instruction inst;
        inst.line = line;
        std::string s;
        
        s = line.substr(0, 3);
        if (s == "set") { inst.type = Type::SET; }
        else if (s == "sub") { inst.type = Type::SUB; }
        else if (s == "mul") { inst.type = Type::MUL; }
        else if (s == "jnz") { inst.type = Type::JNZ; }
        else { std::cout << "bad type: " << line; }
        
        if (('a' <= line[4]) && (line[4] <= 'h')) {
            inst.target = (line[4] - 'a');
        } else {
            assert(inst.type == Type::JNZ);
            inst.type = Type::JNZI;
            inst.target = (line[4] - '0');
        }
        
        inst.value = 0;
        inst.const_value = true;
        if (line.size() >= 7) {
            if (('a' <= line[6]) && (line[6] <= 'h')) {
                inst.value = line[6] - 'a';
                inst.const_value = false;
            } else {
                inst.value = std::stoi(line.substr(6));
                inst.const_value = true;
            }
        }
        
        instructions.push_back(inst);
    }
    
    Process p0(instructions);

    bool r = true;
    while (r) {
        p0.print();
        r = p0.compute();
    }
    
    std::cout << p0._mul << std::endl;
    
    return 0;
}
