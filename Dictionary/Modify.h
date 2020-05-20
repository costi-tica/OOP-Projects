#ifndef MODIFY_H
#define MODIFY_H

#include <Node.h>
#include <iostream>
#include <cassert>
#include <new>

//obiectele Modify primesc pa paramatru o valoare de tip V, reprezentand valoare cu care se maresc toate valorile din dictionar,
//se poate face si scadere
//ex: Modify increase_by_5(5)
//sau Modify decrease_by_7(-7)
template<class K,class V>
class Modify{
    V val_;

    void mdf_helper(Node<K,V>* const&);
public:
    Modify(V val = 0): val_(val) { }
    ~Modify();

    void operator () (Node<K,V>* const&);
};

template<class K,class V>
Modify<K,V>::~Modify(){ }


template<class K,class V>
void Modify<K,V>::operator () (Node<K,V>* const& root){
    mdf_helper(root);
}

template<class K,class V>
void Modify<K,V>::mdf_helper(Node<K,V>* const& node){
    if(node){
        mdf_helper(node->left_);
        assert(node);
        node->value_ += val_;
        mdf_helper(node->right_);
    }
}

#endif // KEYCMP_H
