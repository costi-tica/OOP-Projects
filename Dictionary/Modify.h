#ifndef MODIFY_H
#define MODIFY_H

#include <Node.h>
#include <iostream>
#include <cassert>
#include <new>


template<class K,class V>
class Modify{
    void mdf_helper(Node<K,V>* const&, const V&);
public:
    Modify();
    ~Modify();

    void operator () (Node<K,V>* const&, const V&);
};

template<class K,class V>
Modify<K,V>::Modify(){ }

template<class K,class V>
Modify<K,V>::~Modify(){ }

//operatorul "()" primeste ca parametri radacina arborelui si numarul cu care trebuie sa se mareasca valorile dictionarului
template<class K,class V>
void Modify<K,V>::operator () (Node<K,V>* const& root, const V& val){
    mdf_helper(root, val);
}

template<class K,class V>
void Modify<K,V>::mdf_helper(Node<K,V>* const& node, const V& val){
    if(node){
        mdf_helper(node->left_, val);
        assert(node);
        node->value_ += val;
        mdf_helper(node->right_, val);
    }
}

#endif // KEYCMP_H
