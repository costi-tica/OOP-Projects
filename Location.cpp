#include "Location.h"


std::ostream& operator << (std::ostream& out, Location loc) {
    out << "(" << loc.x + 1 << "," << loc.y + 1 << ")";
    return out;
}

bool operator == (Location first, Location second) {
    return first.x == second.x && first.y == second.y;
}

bool operator != (Location first, Location second) {
    return !(first == second);
}

