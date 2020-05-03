#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include "Shield.h"
#include "Gun.h"
#include "Map.h"

class Agent{
private:
    const char name_;
    Location location_;
    const int skyline_;
    Gun* gun_;
    Shield* shield_;
    int victims_;
public:
    Agent(char, Location, int = 5, Gun* = NULL, Shield* = NULL, int = 0);
    ~Agent();

    Location location() const { return location_; }
    int skyline() const { return skyline_; }
    char name() const { return name_; }
    int num_of_victims() const { return victims_; }

    bool kills(const Agent&);
    void random_items();
    int closest_target(const std::vector<Agent*>&);
    void move(Map&);
    void is_the_winner();
};

#endif // AGENT_H
