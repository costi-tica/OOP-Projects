#ifndef SHIELD_H
#define SHIELD_H

#include "Gun.h"


class Shield : public Item{
protected:
    int strength_;
public:
    Shield(const char* name, const char* material, int strength) : Item(name, material), strength_(strength) { };

    virtual ~Shield() = 0;
    virtual void bonus_combo(Gun*) = 0;

    int strength() const { return strength_; };
    void reset_strength(int);
};

class CaptainShield : public Shield{
public:
    CaptainShield() : Shield("Captain", "vibranium", 25) { }
    ~CaptainShield();

    void bonus_combo(Gun*);
};

class RedemptionShield : public Shield{
public:
    RedemptionShield() : Shield("Redemption", "adamantium", 18) { }
    ~RedemptionShield();

    void bonus_combo(Gun*);
};

class MoonlightShield : public Shield{
public:
    MoonlightShield() : Shield("Moonlight", "yttrium", 20) { }
    ~MoonlightShield();

    void bonus_combo(Gun*);
};


#endif // SHIELD_H
