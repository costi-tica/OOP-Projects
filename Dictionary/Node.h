#ifndef NODE_H
#define NODE_H

template<class K,class V>
class Modify;

template<class K,class V,class M = Modify<K,V>>
class Map;

template<class K,class V>
class Node{
    K key_;
    V value_;
    Node<K,V>* left_;
    Node<K,V>* right_;
public:
    Node(const K&, const V&, Node<K,V>* = NULL, Node<K,V>* = NULL);
    friend class Map<K,V>;
    friend class Modify<K,V>;
};

//constructor
template<class K,class V>
Node<K,V>::Node(const K& key, const V& value, Node<K,V>* left, Node<K,V>* right) : key_(key), value_(value), left_(left), right_(right) { }

#endif // NODE_H
