#ifndef BST_H
#define BST_H

#include "Modify.h"

//Dictionarul este construit ca un arbore binar de cautare
//si de aceea exista si clasa Node.

template<class K,class V,class M>
class Map{
    int size_;
    Node<K,V>* root_;

    void cleanup(Node<K,V>*);
    void copy_helper(Node<K,V>*&, const Node<K,V>* const&);
    std::ostream& inorder(std::ostream&, const Node<K,V>* const&) const;
public:
    Map() : size_(0), root_(NULL) { }
    ~Map();
    Map(const Map<K,V>&);

    Map<K,V>& operator = (const Map<K,V>&);
    const V& operator [] (const K&);

    template<class Key,class Val>
    friend std::ostream& operator << (std::ostream&, const Map<Key,Val>&);

    void insert_pair(K, V);
    void delete_pair(K);
    bool find_key(K) const;
    int size() const { return size_; }
    void modify_values(M&);
};

template<class K,class V, class M>
Map<K,V,M>::~Map(){
    cleanup(root_);
}

template<class K,class V, class M>
Map<K,V,M>::Map(const Map<K,V>& other) : size_(other.size_) {
    copy_helper(root_, other.root_);
}

template<class K,class V, class M>
const V& Map<K,V,M>::operator [] (const K& key){
    Node<K,V>* temp = root_;
    while (temp){
        if (temp->key_ == key){
            return temp->value_;
        }
        if (key < temp->key_){
            temp = temp->left_;
        } else {
            temp = temp->right_;
        }
    }
    throw std::out_of_range("Invalid Key!");
}

template<class K,class V, class M>
Map<K,V>& Map<K,V,M>::operator = (const Map<K,V>& other){
    if (this != &other){
        cleanup(root_);
        size_ = other.size_;
        copy_helper(root_, other.root_);
    }
    return *this;
}

//cautarea unei chei in arbore
template<class K,class V, class M>
bool Map<K,V,M>::find_key(K key) const {
    Node<K,V>* temp = root_;
    while (temp){
        if (temp->key_ == key){
            return true;
        }
        if (key < temp->key_){
            temp = temp->left_;
        } else {
            temp = temp->right_;
        }
    }
    return false;
}

//metoda "inorder" este folosita pentru afisarea perechilor in ordine crescatoare cheilor.
template<class K,class V, class M>
std::ostream& Map<K,V,M>::inorder(std::ostream& out, const Node<K,V>* const& node) const {
    if (node){
        inorder(out, node->left_);
        out << "(" << node->key_ << ", " << node->value_ << ") ";
        inorder(out, node->right_);
    }
    return out;
}

template<class K, class V>
std::ostream& operator << (std::ostream& out, const Map<K,V>& map){
    return map.inorder(out, map.root_);
}

//inserare in BST
template<class K,class V, class M>
void Map<K,V,M>::insert_pair(K key, V value){
    ++size_;
    if (!root_){
        try{
            root_ = new Node<K,V>(key, value);
        } catch (std::bad_alloc& xa){
            std::cout << "Allocation failure!";
        }
        return;
    }
    Node<K,V>* temp = root_;
    while (temp){
        if (key < temp->key_){
            if (!temp->left_){
                try{
                    temp->left_ = new Node<K,V>(key, value);
                } catch (std::bad_alloc& xa){
                    std::cout << "Allocation failure!";
                }
                temp = NULL;
            } else
                temp = temp->left_;
        } else if (key > temp->key_){
            if (!temp->right_){
                try{
                    temp->right_ = new Node<K,V>(key, value);
                } catch (std::bad_alloc& xa){
                    std::cout << "Allocation failure!";
                }
                temp = NULL;
            } else
                temp = temp->right_;
        } else {
            temp->value_ = value;
            temp = NULL;
            --size_;
        }
    }
}

//stergere din BST cu mentinerea proprietatii de arbore binar de cautare
template<class K,class V, class M>
void Map<K,V,M>::delete_pair(K key){
    Node<K,V>* curr = root_, *father = NULL;
    if (!root_){
        return;
    }
    while (curr != NULL && curr->key_ != key){
        father = curr;
        if (key < curr->key_){
            curr = curr->left_;
        } else {
            curr = curr->right_;
        }
    }
    if (curr){
        if (!curr->left_ && !curr->right_){
            if (curr == root_){
                root_ = NULL;
            } else if (father->left_ == curr){
                father->left_ = NULL;
            } else {
                father->right_ = NULL;
            }
            delete curr;
            --size_;
        } else if (curr->left_ && curr->right_){
            Node<K,V>* successor = curr->right_;
            while (successor->left_){
                successor = successor->left_;
            }
            K new_key = successor->key_;
            V new_val = successor->value_;
            delete_pair(successor->key_);
            curr->key_ = new_key;
            curr->value_ = new_val;
        } else {
            Node<K,V>* child = (curr->left_) ? curr->left_ : curr->right_;
            if (curr == root_){
                root_ = child;
            } else {
                if (father->left_ == curr){
                    father->left_ = child;
                } else {
                    father->right_ = child;
                }
            }
            delete curr;
            --size_;
        }
    }
}

//transformarea prin obiect-functie
//obiectul Modify creste sau scade toate valorile dictionarului cu un numar dat la crearea obiectului Modify
//ex: Modify increase_by_10(10)
//    dict.modify_values(increase_by_10)
template<class K,class V, class M>
void Map<K,V,M>::modify_values(M& modifier){
    modifier(root_);
}

//stergerea tuturor nodurilor din arbore
template<class K,class V, class M>
void Map<K,V,M>::cleanup(Node<K,V>* node){
    if (node){
        cleanup(node->left_);
        cleanup(node->right_);
        if (node == root_){
            root_ = NULL;
        }
        delete node;
    }
}

//functie recursiva pentru copierea intregii structuri a unui BST intr-un alt arbore
template<class K,class V, class M>
void Map<K,V,M>::copy_helper(Node<K,V>*& to_node, const Node<K,V>* const& from_node){
    if (from_node){
        try{
            to_node = new Node<K,V>(from_node->key_, from_node->value_);
        } catch (std::bad_alloc& xa){
            std::cout << "Allocation failure!";
        }
        copy_helper(to_node->left_, from_node->left_);
        copy_helper(to_node->right_, from_node->right_);
    }
}


#endif // BST_H

