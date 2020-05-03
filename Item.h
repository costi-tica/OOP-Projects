#ifndef ITEM_H
#define ITEM_H
#include "Location.h"

class Item{
private:
    const char* name_;
    const char* material_;
public:
    Item(const char* name, const char* material) : name_(name), material_(material) { }

    virtual ~Item() = 0;

    const char* material() const { return material_; }
    const char* name() const { return name_; }
};


#endif // ITEM_H
