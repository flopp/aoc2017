#include <cassert>
#include <deque>
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
    int64_t target;
    int64_t value;
    std::string line;
};

struct Process {
    Process(int64_t id, const std::vector<Instruction>& instructions) :
        _instructions(instructions),
        _mem(26, 0) {
        _mem['p' - 'a'] = id;
    }
    
    bool compute(Process* other) {
        if (_pc < 0 || _pc >= (int64_t)_instructions.size()) {
            return false;
        }
        
        const auto& inst = _instructions[_pc];
        switch (inst.type) {
            case Type::SET:
                _mem[inst.target] = inst.const_value ? inst.value : _mem[inst.value];
                ++_pc;
                break;
            case Type::ADD:
                _mem[inst.target] += inst.const_value ? inst.value : _mem[inst.value];
                ++_pc;
                break;
            case Type::MUL:
                _mem[inst.target] *= inst.const_value ? inst.value : _mem[inst.value];
                ++_pc;
                break;
            case Type::MOD:
                _mem[inst.target] %= (inst.const_value ? inst.value : _mem[inst.value]);
                ++_pc;
                break;
            case Type::SND:
#ifdef PART1
                _send = _mem[inst.target];
#else
                ++_send;
                other->_msg.push_back(_mem[inst.target]);
#endif
                ++_pc;
                break;
            case Type::RCV:
#ifdef PART1
                if (_send != 0) {
                    return false;
                }
#else
                if (_msg.empty()) {
                    return false;
                }
                _mem[inst.target] = _msg.front();
                _msg.pop_front();
#endif
                 ++_pc;
                break;
            case Type::JGZ:
                if (_mem[inst.target] > 0) {
                    _pc += inst.const_value ? inst.value : _mem[inst.value];
                } else {
                    ++_pc;
                }
                break;
            case Type::JGZI:
                if (inst.target > 0) {
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
    std::deque<int64_t> _msg;
    int _pc{0};
    int _send{0};
};

int main() {
    std::vector<Instruction> instructions;
    for (std::string line; std::getline(std::cin, line); /**/) {
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
        }
        
        instructions.push_back(inst);
    }
    
    Process p0(0, instructions);
#ifdef PART2
    Process p1(1, instructions);
#endif

    bool r = true;
    while (r) {
#ifdef PART1
        r = p0.compute(nullptr);
#else
        bool r0 = p0.compute(&p1);
        bool r1 = p1.compute(&p0);
        r = r0 || r1;
#endif
    }

#ifdef PART1    
    std::cout << p0._send << std::endl;
#else
    std::cout << p1._send << std::endl;
#endif
    
    return 0;
}
