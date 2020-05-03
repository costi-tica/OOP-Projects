#ifndef GUN_H
#define GUN_H

#include <Item.h>

class Agent;

class Gun : public Item{
protected:
    int power_;
    int distance_;
public:
    Gun(const char* name, const char* material, int power, int distance) : Item(name, material), power_(power), distance_(distance) { };

    virtual ~Gun() = 0;
    virtual bool valid_shoot(Location, Location) = 0;

    int power() const { return power_; }
    int distance() const { return distance_; }
    void add_power(int);
};

class StormBreaker : public Gun{
public:
    StormBreaker() : Gun("StormBreaker", "yttrium", 18, 10) { }
    ~StormBreaker();

    bool valid_shoot(Location, Location);
};

class Bifrost : public Gun{
public:
    Bifrost() : Gun("Bifrost", "adamantium", 15, 9) { }
    ~Bifrost();

    bool valid_shoot(Location, Location);
};

class Mjolnir : public Gun{
public:
    Mjolnir() : Gun("Mjolnir", "vibranium", 13, 11) { }
    ~Mjolnir();

    bool valid_shoot(Location, Location);
};


#endif // GUN_H
