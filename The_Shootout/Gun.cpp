#include "Gun.h"


Gun::~Gun(){
    //std::cout<<" g ";
}
StormBreaker::~StormBreaker(){
    //std::cout<<" s ";
}
Bifrost::~Bifrost(){
    //std::cout<<" b ";
}
Mjolnir::~Mjolnir(){
    //std::cout<<" m ";
}

void Gun::add_power(int bonus){
    power_ += bonus;
}

bool StormBreaker::valid_shoot(Location from_loc, Location to_loc){ //nu poate sa traga pe axa x pe care se afla
    return from_loc.x != to_loc.x;
}
bool Bifrost::valid_shoot(Location from_loc, Location to_loc){ //nu poate sa traga pe axa y pe care se afla
    return from_loc.y != to_loc.y;
}
bool Mjolnir::valid_shoot(Location from_loc, Location to_loc){ //nu poate sa traga intr-o locatie aflata imediat langa agent pe axele x si y
    return !((to_loc.x == from_loc.x && to_loc.y == from_loc.y - 1) || (to_loc.x == from_loc.x - 1 && to_loc.y == from_loc.y) ||
             (to_loc.x == from_loc.x && to_loc.y == from_loc.y + 1) || (to_loc.x == from_loc.x + 1 && to_loc.y == from_loc.y));
}// Aici nu stiu ce altceva puteam sa implementez inafara de locatiile in care pot sa traga,
// din punct de vedere vizual se puteaua face multe, dar asa cu o matrice cu liniute si litere am fost limitat la asta
