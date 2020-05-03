#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Agent.h"
#include <vector>
#include <iostream>



class Game{
private:
    int num_of_agents_;
    Map* map_;
    std::vector<Agent*> agents_;
    int round_;
public:
    Game(int = 30, int = 25, char = '-');
    ~Game();

    void Play(int = 5);
    void delete_agent(int);
};

#endif // GAME_H
