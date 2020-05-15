#ifndef KEYCMP_H
#define KEYCMP_H

#include <Node.h>
#include <iostream>
#include <cassert>
#include <new>

//clasa KeyCmp contine doi pointer catre vectori de tip K deoarece la supraincarcarea "()" trebuie
//sa memorez cheile din arbori pentru a le compare ulterior, iar index_ va folosi la adaugarea de chei.

template<class K,class V>
class KeyCmp{
    K* this_key_list_;
    K* other_key_list_;
    int index_;

    void cmp_helper(const Node<K,V>* const&, K* const&);
public:
    KeyCmp(K* this_list = NULL, K* other_list = NULL, int index = 0) : this_key_list_(this_list), other_key_list_(other_list), index_(index) { }
    ~KeyCmp();

    bool operator () (const Node<K,V>* const&, const int&, const Node<K,V>* const&, const int&);
};

template<class K,class V>
KeyCmp<K,V>::~KeyCmp(){
    delete this_key_list_;
    delete other_key_list_;
}

//operatorul "()" primeste ca parametri radacinile arborilor si numarul de elemente ale fiecaruia
template<class K,class V>
bool KeyCmp<K,V>::operator () (const Node<K,V>* const& this_node, const int& this_size, const Node<K,V>* const& other_node, const int& other_size){
    if (this_size != other_size){
        return false;
    }
    try{
        this_key_list_ = new K[this_size];
        other_key_list_ = new K[other_size];
    } catch (std::bad_alloc& xa){
        std::cout << "Allocation failure!";
    }

    cmp_helper(this_node, this_key_list_); //metoda recursiva ajutatoare pentru obtinerea cheilor din arbori in ordine crescatoare
    index_ = 0;
    cmp_helper(other_node, other_key_list_);

    for (int i = 0; i < this_size; ++i){   //compararea efectiva a cheilor
        if (this_key_list_[i] != other_key_list_[i]){
            return false;
        }
    }
    return true;
}

template<class K,class V>
void KeyCmp<K,V>::cmp_helper(const Node<K,V>* const& node, K* const& key_list){
    assert(key_list);
    if(node){
        cmp_helper(node->left_, key_list);
        key_list[index_] = node->key_;
        ++index_;
        cmp_helper(node->right_, key_list);
    }
}

#endif // KEYCMP_H
