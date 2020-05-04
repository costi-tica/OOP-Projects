#include <iostream>
#include <ctime>

#include "Game.h"


using namespace std;

/*
    Cateva lucruri de stiut:

        -Game game(numar agenti, dimensiune harta, char principal), by defalut sunt (30, 25, '-')
        -game.Play(numar runde), by defalut 5
        -agentii au ca nume litere mari si mici, prin urmare daca se introduc peste 52 de agenti acestia o sa aiba ca nume alte caractere din ascii,
                dar asta nu impacteaza cu nimic programul, e doar bine de stiut
        -agentii au o raza de vizibilitate random intre 5 si 8 si primesc random o arma si un scut
        -in functie de combinatia dintre arma si scut agentul poate primi un bonus (metoda virtuala in Shield)
        -modul in care trage arma este dat de o metoda bool care verifica daca target-ul se afla in zona de tragere (metoda virtuala in Gun)
        -armele au power, distance si material + nume
        -scuturile au strength si material + nume
        -se poate intampla foarte rar in unele rulari ca doi agenti sa ramana pe harta
                si sa nu se intalneasca din cauza tipului de miscare circulara si modului in care trage arma
        -cu 30 de agenti pe o harta de dim 25 e nevoie in medie de 10 runde pentru a ramane un singur agent
*/

int main()
{
    srand(time(NULL));
    Game game(30, 25);
    game.Play(2);

    return 0;
}
