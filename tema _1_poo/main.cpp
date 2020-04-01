#include <iostream>
#include "Polinom.h"
#include <fstream>
using namespace std;

ifstream fin("date.txt");

int main()
{
    Polinom p1, p2, p3;
    fin >> p1 >> p2;
    cout << "p1 = " << p1 << endl << "p2 = " << p2 << endl;
    cout << "p1 + p2 = " << p1 + p2 << endl;
    cout << "p1 * 2 = " << p1 * 2 << endl << "2 * p1 = " << 2 * p1 << endl << "p1 * p2 = " << p1 * p2 << endl;
    cout << "p1(2) = " << p1.value(2) << endl;
    try{
        cout << "p1[3] = " << p1[3] << endl;
    } catch (int x){
        cout << "p1[3] = " << x << endl;
    }
    cout << "Gradul lui p1 = " << p1.get_degree() << endl;
    cout << "p1 / p2 = " << p1 / p2 << endl;
    p3 = p1;
    fin >> p1;
    cout << "noul p1 = " << p1 << endl << "p3 =" << p3 << endl;
    p1[1] = 66;
    cout << "p1 = " << p1;
}
