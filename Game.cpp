#include "Game.h"
#include <cmath>
#include <cstring>

Game::Game(int num_of_agents, int size, char symbol) : num_of_agents_(num_of_agents), round_(0){
    int char_ind = 65;
    while (size < 25){
        std::cout << "The battle field should be at least 25x25!\n Please enter the size again: ";
        std::cin >> size;
    }
    map_ = new Map(size, symbol);
    for (int i = 0; i < num_of_agents_; ++i){
        Agent* agent = new Agent(char(char_ind), map_->random_location(), 5 + rand() % 4); //raza de vizibilitate este random intre 5 si 8
        map_->mark_location(agent->location(), agent->name());
        agents_.push_back(agent);

        ++char_ind;
        if (char_ind == 91){
            char_ind = 97;
        }
    }
    std::cout << "The battle field is ready!\n" << *map_;
}

Game::~Game(){
    while (!agents_.empty()) {
        Agent* agent = agents_.back();
        agents_.pop_back();
        delete agent;
    }
    delete map_;
}

void Game::Play(int num_of_rounds){
    for (int i = 0; i < num_of_rounds; ++i){
        ++round_;
        std::cout << "Round " << round_ << ":\n";
        int j = 0;
        while (j < agents_.size()){
            Agent* agent = agents_[j];
            int target_index = agent->closest_target(agents_);
            if (target_index == -1){
                agent->move(*map_);
                ++j;
            } else if (agent->kills(*agents_[target_index])){
                std::cout << agent->name() << " kills " << agents_[target_index]->name() << "\n";
                map_->free_location(agents_[target_index]->location());
                delete_agent(target_index);
                if (target_index > j){
                    ++j;
                }
            } else {
                ++j;
            }
        }
        std::cout << "\n" << *map_ << "\n";
        if (agents_.size() == 1){
            agents_[0]->is_the_winner();
            break;
        }
    }
    if (agents_.size() != 1){
        int choice;
        std::cout << "Do you want to continue?\n   1.YES        2.NO\n";
        std::cin >> choice;
        if (choice == 1){
            int new_rounds;
            std::cout << "How many rounds? ";
            std::cin >> new_rounds;
            Play(new_rounds);
        }
    }
}


void Game::delete_agent(int index){
    Agent* agent = agents_[index];
    agents_.erase(agents_.begin() + index);
    delete agent;
}
