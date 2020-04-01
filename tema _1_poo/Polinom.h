#ifndef POLINOM_H
#define POLINOM_H
#include <iostream>

class Polinom{
private:
    std::pair<float,int>* coefs;    // <coef,grad>
    int length;
public:
    Polinom();
    Polinom(int grad_maxim, float list_of_coefs[]);
    Polinom(const Polinom &other);
    ~Polinom();

    friend std::ostream& operator << (std::ostream& output, const Polinom &p);
    friend std::istream& operator >> (std::istream& input, Polinom &p);

    float value(int val);
    int get_degree();
    Polinom& operator += (const Polinom &other);
    Polinom& operator = (const Polinom &other);
    Polinom operator + (const Polinom &other);
    Polinom operator * (float x);
    friend Polinom operator * (float x, Polinom &other);
    Polinom operator * (const Polinom &other);
    Polinom operator / (const Polinom &other);
    float& operator [] (int n);

    // aditionale
    void resize_coefs();
    void init_temp(int new_size);
};

#endif // POLINOM_H
