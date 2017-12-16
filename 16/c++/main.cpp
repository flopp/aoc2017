#include <iostream>
#include <regex>
#include <string>
#include <vector>

struct Command {
    char type;
    char p1;
    char p2;
};

int main(int /*argc*/, char* argv[]) {
    auto re_spin = std::regex{"^s(\\d+)$"};
    auto re_swap = std::regex{"^x(\\d+)/(\\d+)$"};
    auto re_pair = std::regex{"^p([a-p])/([a-p])$"};
    
    std::vector<Command> commands;
    for (std::string cmd; std::getline(std::cin, cmd, ','); /**/) {
        std::smatch m;
        if (std::regex_match(cmd, m, re_spin)) {
            commands.push_back(Command{'s', char(stoi(m[1])), '\0'});
        } else if (std::regex_match(cmd, m, re_swap)) {
            commands.push_back(Command{'x', char(stoi(m[1])), char(stoi(m[2]))});
        } else if (std::regex_match(cmd, m, re_pair)) {
            commands.push_back(Command{'p', std::string(m[1])[0], std::string(m[2])[0]});
        } else {
            std::cout << "bad cmd: " << cmd << std::endl;
        }
    }
    
    std::string programs = argv[1];
#ifdef PART1
    const std::size_t loops = 1;
#else
    const std::size_t loops = 1000000000;
#endif

    std::vector<std::string> seen;
    for (std::size_t loop = 0; loop < loops; ++loop) {
        for (const auto& p: seen) {
            if (p == programs) {
                std::cout << seen[loops % loop] << std::endl;
                return 0;
            }
        }
        seen.push_back(programs);
        
        for (const auto& cmd: commands) {
            switch (cmd.type) {
                case 's':
                    programs = programs.substr(programs.size() - cmd.p1) +
                               programs.substr(0, programs.size() - cmd.p1);
                    break;
                case 'x':
                    std::swap(programs[cmd.p1], programs[cmd.p2]);
                    break;
                case 'p':
                    auto p = programs.begin();
                    auto q = programs.begin();
                    while (*p != cmd.p1) { ++p; }
                    while (*q != cmd.p2) { ++q; }
                    std::swap(*p, *q);
                    break;
            }
        }
    }
    
    std::cout << programs << std::endl;
    
    return 0;
}
