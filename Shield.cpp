#include "Shield.h"


Shield::~Shield() {
}
RedemptionShield::~RedemptionShield(){
}
MoonlightShield::~MoonlightShield(){
}
CaptainShield::~CaptainShield(){
}

void Shield::reset_strength(int new_strength){
    strength_ = new_strength;
}

// felul in care scutul influenteaza agentul
void CaptainShield::bonus_combo(Gun* gun){
    if (material() == gun->material()){
        gun->add_power(7);
        reset_strength(strength_ + 7);
        std::cout << "\nCombo applied! +7 POWER \n \t       +7 STRENGTH";
    }
}

void RedemptionShield::bonus_combo(Gun* gun){
    if (strength() == gun->power()){
        gun->add_power(5);
        reset_strength(strength_ + 3);
        std::cout << "\nCombo applied! +5 POWER \n \t       +3 STRENGTH";
    }
}

void MoonlightShield::bonus_combo(Gun* gun){
    if (gun->distance() < 10){
        reset_strength(strength_ + 15);
        std::cout << "\nCombo applied! +15 STRENGTH";
    }
}
