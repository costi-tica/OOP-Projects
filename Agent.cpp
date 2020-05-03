#include "Agent.h"
#include <iostream>
#include <cmath>


Agent::Agent(char name, Location loc, int skyline, Gun* gun, Shield* shield, int victims) : name_(name), location_(loc), skyline_(skyline), gun_(gun), shield_(shield), victims_(victims){
    if(gun_ == NULL || shield_ == NULL){
        random_items();
    }
    std::cout << "Agent " << name_ << " has entered the field with " << gun_->name() << " and " << shield_->name() << " shield\n";
    std::cout << "Power: " << gun_->power() << "\nStrength: " << shield_->strength() << "\nSkyline: " << skyline_;
    shield_->bonus_combo(gun_);
    std::cout << "\n\n";
}

Agent::~Agent() {
    delete gun_;
    delete shield_;
}

bool Agent::kills(const Agent& target) {
    int new_shield_strength = target.shield_->strength() - gun_->power();
    if (new_shield_strength <= 0){
        ++victims_;
        return true;
    }
    target.shield_->reset_strength(new_shield_strength);
    std::cout << "Agent " << target.name_ << " has " << target.shield_->strength() << " strength left after being shoot by " << name_ << "\n";
    return false;
}

//cauta cea mai apropiata victima care se afla si in raza de actiune a armei
int Agent::closest_target(const std::vector<Agent*>& agents){
    double min_dist = skyline_;
    int index = -1;
    for (unsigned int i = 0; i < agents.size(); ++i){
        Agent* agent = agents[i];
        if (agent != this){
            double distance = sqrt( pow(agent->location_.x - location_.x, 2) + pow(agent->location_.y - location_.y, 2) );
            if (distance <= min_dist && gun_->valid_shoot(location_, agent->location()) && distance <= gun_->distance()){
                index = i;
                min_dist = distance;
            }
        }
    }
    return index;
}


//agentii se misca in functie de cadran, in sens invers acelor de ceasornic.
//Eu preferam sa primeasca o pozitie random din raza de vizine in functie de cardran (spre centru),
//probabil ca inca ar mai fi determinist, dar am ales sa nu risc.
void Agent::move(Map& map){
    int size = map.size();
    map.free_location(location_);
    Location loc;
    std::cout << "Agent " << name_ << " moves from " << location_;

    if (location_.x <= size / 2 && location_.y <= size / 2){
        loc.x = location_.x + skyline_;
        loc.y = location_.y;
        if (map.location_available(loc)){
            location_.x += skyline_;
        } else {
            location_.y += skyline_;
        }
    } else if (location_.x <= size / 2 && location_.y > size / 2){
        loc.x = location_.x;
        loc.y = location_.y - skyline_;
        if (map.location_available(loc)){
            location_.y -= skyline_;
        } else {
            location_.x += skyline_;
        }
    } else if (location_.x > size / 2 && location_.y <= size / 2){
        loc.x = location_.x;
        loc.y = location_.y + skyline_;
        if (map.location_available(loc)){
            location_.y += skyline_;
        } else {
            location_.x -= skyline_;
        }
    } else {
        loc.x = location_.x - skyline_;
        loc.y = location_.y;
        if (map.location_available(loc)){
            location_.x -= skyline_;
        } else {
            location_.y -= skyline_;
        }
    }

    std::cout << " to " << location_ << "\n";
    map.mark_location(location_, name_);
}

void Agent::random_items(){
    switch(rand() % 3) {
    case 0:
        gun_ = new Mjolnir;
        break;
    case 1:
        gun_ = new StormBreaker;
        break;
    case 2:
        gun_ = new Bifrost;
        break;
    }
    switch(rand() % 3) {
    case 0:
        shield_ = new CaptainShield;
        break;
    case 1:
        shield_ = new RedemptionShield;
        break;
    case 2:
        shield_ = new MoonlightShield;
        break;
    }
}

void Agent::is_the_winner(){
    std::cout << "AGENT " << name() << " IS THE WINNER!\n Statistics:\n Strength remained: " << shield_->strength();
    std::cout<< "\n Victims: " << victims_ << "\n Final location: " << location_ << "\n";
}


