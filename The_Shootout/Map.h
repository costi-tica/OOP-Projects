#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Location.h"


class Map{
private:
    int size_;
    char** battle_field_;
    const char symbol_;
public:
    Map(int, char);
    ~Map();

    int size() const { return size_; }

    bool location_available(Location) const ;
    Location random_location() const;
    void mark_location(Location, char);
    void free_location(Location);

    friend std::ostream& operator << (std::ostream& out, const Map& map);
};

#endif // MAP_H
