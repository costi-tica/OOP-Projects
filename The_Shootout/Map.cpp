#include "Map.h"

Map::Map(int size, char symbol) : size_(size), symbol_(symbol) {
    battle_field_ = new char*[size_];
    for (int i = 0; i < size_; ++i){
        battle_field_[i] = new char[size_];
        for (int j = 0; j < size_; ++j){
            battle_field_[i][j] = symbol_;
        }
    }
}

Map::~Map(){
    for (int i = 0; i < size_; i++){
        delete[] battle_field_[i];
    }
    delete[] battle_field_;
}

std::ostream& operator << (std::ostream& out, const Map& map) {
    for (int i = 0; i < map.size_; ++i){
        out << "\t\t\t";
        for (int j = 0; j < map.size_; ++j){
            out << map.battle_field_[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

bool Map::location_available(Location loc) const{
    return battle_field_[loc.x][loc.y] == symbol_;
}

Location Map::random_location() const{
    Location loc;
    loc.x = rand() % size_;
    loc.y = rand() % size_;
    while (!location_available(loc)){
       loc.x = rand() % size_;
       loc.y = rand() % size_;
    }
    return loc;
}

void Map::mark_location(Location loc, char symbol){
    battle_field_[loc.x][loc.y] = symbol;
}

void Map::free_location(Location loc){
    battle_field_[loc.x][loc.y] = symbol_;
}





