#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct XYZ {
    int64_t x, y, z;
    
    int64_t dist() const {
        return std::abs(x) + std::abs(y) + std::abs(z);
    }
    
    XYZ& operator+=(const XYZ& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};
std::ostream& operator<<(std::ostream& os, const XYZ& xyz) {
    os << "<" << xyz.x << "," << xyz.y << "," << xyz.z << ">";
    return os;
}

struct Particle {
    uint64_t id;
    XYZ p, v, a;
    
    void parse(const std::string& s) {
        std::istringstream iss(s);
        iss.ignore(3);
        iss >> p.x; iss.ignore(1); iss >> p.y; iss.ignore(1); iss >> p.z;
        iss.ignore(6);
        iss >> v.x; iss.ignore(1); iss >> v.y; iss.ignore(1); iss >> v.z;
        iss.ignore(6);
        iss >> a.x; iss.ignore(1); iss >> a.y; iss.ignore(1); iss >> a.z;
    }
    
    void next() {
        v += a;
        p += v;
    }
    
    int64_t dist() const {
        return p.dist();
    }
};

std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << p.id << " p=" << p.p << " v=" << p.v << " a=" << p.a;
    return os;
}

int main() {
    std::vector<Particle> particles;
    for (std::string line; std::getline(std::cin, line); /**/) {
        Particle p;
        p.id = particles.size();
        p.parse(line);
        particles.push_back(p);
    }
    
    auto min_id = 0;
    auto min_a = particles[0].a.dist();
    auto min_v = particles[0].v.dist();
    auto min_p = particles[0].p.dist();
    
    for (const auto part: particles) {
        auto a = part.a.dist();
        auto v = part.v.dist();
        auto p = part.p.dist();
        if (a < min_a || (a == min_a && v < min_v) || (a == min_a && v == min_v && p < min_p)) {
            min_id = part.id;
            min_a = a;
            min_v = v;
            min_p = p;
        }
    }
    std::cout << particles[min_id] << std::endl;

    return 0;
}
