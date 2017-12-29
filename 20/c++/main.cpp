#include <iostream>
#include <set>
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
    
    bool operator==(const XYZ& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z);
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
    
    bool possible_collision(const Particle& o) const {
        return 
            _poss(a.x, v.x, p.x, o.a.x, o.v.x, o.p.x) &&
            _poss(a.y, v.y, p.y, o.a.y, o.v.y, o.p.y) &&
            _poss(a.z, v.z, p.z, o.a.z, o.v.z, o.p.z);
    }
    
    bool _poss(int64_t aa, int64_t vv, int64_t pp, int64_t oaa, int64_t ovv, int64_t opp) const {
        if (aa > oaa) {
            return !((vv > ovv) && (pp > opp));
        } else if (aa < oaa) {
            return !((vv < ovv) && (pp < opp));
        } else if (vv > ovv) {
            return !(pp > opp);
        } else if (vv < ovv) {
            return !(pp < opp);
        } else {
            return pp == opp;
        }
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
    
#ifdef PART1
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
#else
    std::vector<int> remaining;
    for (int i = 0; i < particles.size(); ++i) {
        remaining.push_back(i);
    }
    
    while (true) {
        int possible = 0;
        std::set<int> collisions;
        for (int i = 0; i < remaining.size(); ++i) {
            const auto& pi = particles[remaining[i]];
            for (int j = i+1; j < remaining.size(); ++j) {
                const auto& pj = particles[remaining[j]];
                if (pi.p == pj.p) {
                    collisions.insert(remaining[i]);
                    collisions.insert(remaining[j]);
                    continue;
                }
                
                if (pi.possible_collision(pj)) {
                    ++possible;
                }
            }
        }
        if ((possible == 0) && collisions.empty()) {
            break;
        }
        
        std::vector<int> new_remaining;
        for (auto r: remaining) {
            if (collisions.find(r) == collisions.end()) {
                new_remaining.push_back(r);
            }
        }
        remaining = new_remaining;
        
        for (auto& p: particles) {
            p.next();
        }
    }
    std::cout << remaining.size() << std::endl;
#endif

    return 0;
}
