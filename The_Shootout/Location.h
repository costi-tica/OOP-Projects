#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

struct Location{
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& out, Location loc);

bool operator == (Location, Location);
bool operator != (Location, Location);


#endif // LOCATION_H
