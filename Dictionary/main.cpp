#include <iostream>

#include "Map.h"
#include <cstring>

using namespace std;

int main()
{
    Map<int,int> p, p1, p2;

    p.insert_pair(7, 2);
    p.insert_pair(4, 5);
    p.insert_pair(5, 4);
    p.insert_pair(10, 0);
    p.insert_pair(9, 1);
    p.insert_pair(8, 8);
    p.insert_pair(1, 7);
    p.insert_pair(12, 3);
    cout << "p = " << p << endl;
    p.delete_pair(10);
    cout << "dupa stergere p = " << p << endl;
    p.insert_pair(10, 6);
    cout << "dupa inserare p = " << p << endl;
    try{
        cout << p[5] << endl;
    } catch (const std::out_of_range& error){
        cout << error.what() << endl;
    }
    try{
        cout << p[13] << endl;
    } catch (const std::out_of_range& error) {
        std::cerr << error.what() << endl;
    }
    p1 = p;
    cout << "p1 = " << p1 << endl;
    p1.delete_pair(7);
    p1.delete_pair(5);
    cout << "dupa stergere p1 = " << p1 << endl;
    cout << "s-a inserat cheia 4 in p1? " << p1.find_key(4) << endl;
    cout << "s-a inserat cheia 2 in p1? " << p1.find_key(2) << endl;
    cout << "numarul de parechi ale lui p1? " << p1.size() << endl;
    p2 = p1;
    cout << "p = " << p << endl;
    cout << "p2 = p1 = " << p2 << endl;
    cout << "p si p1 au exact aceleasi chei? " << p.same_keys(p1) << endl;
    cout << "p1 si p2 au exact aceleasi chei? " << p1.same_keys(p2) << endl;

    Map<string, int> p3;
    p3.insert_pair("a", 1);
    p3.insert_pair("bc", 2);
    p3.insert_pair("def", 3);
    p3.insert_pair("ghij", 4);
    cout << "p3 = " << p3 << endl;


    return 0;
}
