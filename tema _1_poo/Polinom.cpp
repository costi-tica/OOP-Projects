#include "Polinom.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

ifstream fin_add("date.txt");
//                                      ***************CONSTRUCTORI**************
// Constructor fara parametrii
Polinom::Polinom(){
    length = 0;
    coefs = NULL;
}
// Constructor cu parametrii
Polinom::Polinom(int grad_maxim, float list_of_coefs[]) : length(0){
    coefs = new pair<float,int>[grad_maxim];
    for (int i = 0; i <= grad_maxim; ++i){
        if (list_of_coefs[i] != 0){
            coefs[length].first = list_of_coefs[i];
            coefs[length].second = i;
            length++;
        }
    }
    if (length < grad_maxim){           // <= eventual
        this->resize_coefs();
    }
}
// Destructor
Polinom::~Polinom(){
    if (coefs != NULL){
        delete[] coefs;
    }
    coefs = NULL;
    //cout << "distrus\n";
}
Polinom::Polinom(const Polinom &other){
    length = other.length;
    coefs = new pair<float,int>[length];
    for (int i = 0; i < length; i++){
        coefs[i] = other.coefs[i];
    }
    //cout << "copiat\n";
}

// Calcul polinom intr-un punct
float Polinom::value(int val){
    float rez = 0;
    for (int i = 0; i < length; ++i){
        rez += coefs[i].first * pow(val, coefs[i].second);
    }
    return rez;
}
// Obtine grad polinom
int Polinom::get_degree(){
    return coefs[length - 1].second;
}

// Supraincarcare operatori de intrare si iesire       *********************SUPRAINCARCARI*********************
ostream& operator << (ostream& output, const Polinom &p){
    if (p.length == 0){
        output << 0;
    }
    for (int i = 0; i < p.length; ++i){
        output << p.coefs[i].first << "*X^" << p.coefs[i].second;
        if (i < p.length - 1){
            output << " + ";
        }
    }
    return output;
}
istream& operator >> (istream& input, Polinom &p){
    int grad_maxim;
    if (input == cin)
        cout << "Gradul maxim este: ";
    input >> grad_maxim;
    if (p.length != 0){
        delete[] p.coefs;
        p.length = 0;
    }
    p.coefs = new pair<float,int>[grad_maxim];
    for (int i = 0; i <= grad_maxim; ++i){
        float coef;
        if (input == cin)
            cout << "Coeful gradului " << i << ": ";
        input >> coef;
        if (coef != 0){
            p.coefs[p.length].first = coef;
            p.coefs[p.length].second = i;
            p.length++;
        }
    }
    if (p.length < grad_maxim){           // <= eventual
        p.resize_coefs();
    }
    return input;
}

Polinom& Polinom::operator = (const Polinom &other){
    if (this != &other){
        length = other.length;
        if (coefs != NULL){
            delete[] coefs;
        }
        coefs = new pair<float,int>[length];
        for (int i = 0; i < length; ++i){
            coefs[i] = other.coefs[i];
        }
    }
    //cout << "atribuit\n";
    return *this;
}

// Adunare
Polinom& Polinom::operator += (const Polinom &other){
    *this = *this + other;
    return *this;
}
Polinom Polinom::operator + (const Polinom &other){
    if (length == 0){
        return other;
    }
    if (other.coefs == NULL){
        return *this;
    }
    int i = 0, j = 0;
    Polinom temp;
    temp.coefs = new pair<float,int>[length + other.length];
    while (i < length && j < other.length){
        if (coefs[i].second == other.coefs[j].second){
            if (coefs[i].first + other.coefs[j].first != 0){
                temp.coefs[temp.length].first = coefs[i].first + other.coefs[j].first;
                temp.coefs[temp.length].second = coefs[i].second;
                temp.length++;
            }
            i++;
            j++;
        }
        else if (coefs[i].second < other.coefs[j].second){
            temp.coefs[temp.length] = coefs[i];
            temp.length++;
            i++;
        }
        else{
            temp.coefs[temp.length] = other.coefs[j];
            temp.length++;
            j++;
        }
    }
    while (i < length){
        temp.coefs[temp.length] = coefs[i];
        i++;
        temp.length++;
    }
    while (j < other.length){
        temp.coefs[temp.length] = other.coefs[j];
        j++;
        temp.length++;
    }
    if (temp.length < length + other.length){    // <= eventual
        temp.resize_coefs();
    }
    return temp;
}

// Inmultire cu scalar
Polinom Polinom::operator * (float x){
    Polinom temp;
    if (x == 0){
        return temp;
    }
    temp.init_temp(length);
    for (int i = 0; i < length; ++i){
        temp.coefs[i].first = coefs[i].first * x;
        temp.coefs[i].second = coefs[i].second;
    }
    return temp;
}
Polinom operator * (float x, Polinom &other){
    Polinom temp;
    if (x == 0){
        return temp;
    }
    temp.init_temp(other.length);
    for (int i = 0; i < other.length; ++i){
        temp.coefs[i].first = other.coefs[i].first * x;
        temp.coefs[i].second = other.coefs[i].second;
    }
    return temp;
}
// Imnmultire cu polinom
Polinom Polinom::operator * (const Polinom &other){
    // returneaza polinomul null daca unul din polinoame e null
    Polinom final;
    Polinom temp;
    temp.init_temp(other.length);
    for (int i = 0; i < length; ++i){
        for (int j = 0; j < other.length; ++j){
            temp.coefs[j].first = coefs[i].first * other.coefs[j].first;
            temp.coefs[j].second = coefs[i].second + other.coefs[j].second;
        }
        final += temp;
    }
    return final;
}
float& Polinom::operator [] (int n){ // caz nu gaseste trebuie tratat cu eceptii?
    for (int i = 0; i < length; ++i){
        if (coefs[i].second == n){
            return coefs[i].first;
        }
    }
    throw 0;
}
Polinom Polinom::operator / (const Polinom &other){
    Polinom deimp = *this, cat, temp;
    if (length == 0){
        return cat;
    }
    temp.init_temp(1);
    while (deimp.coefs[deimp.length - 1].second >= other.coefs[other.length - 1].second){
        temp.coefs[0].second = deimp.coefs[deimp.length - 1].second - other.coefs[other.length - 1].second;
        temp.coefs[0].first = deimp.coefs[deimp.length - 1].first / other.coefs[other.length - 1].first;
        cat = cat + temp;
        temp.coefs[0].first *= -1;
        deimp += temp * other;
    }
    return cat;
}

//                  **********************PENTRU FUNCTIONALITATE********************
void Polinom::resize_coefs(){
    pair<float,int>* temp_sec = new pair<float,int>[length];
    for (int i = 0; i < length; ++i){
        temp_sec[i] = coefs[i];
    }
    delete[] coefs;
    coefs = temp_sec;
}
void Polinom::init_temp(int new_size){
    length = new_size;
    coefs = new pair<float,int>[new_size];
}
























