#ifndef LABA5_CAT_H
#define LABA5_CAT_H
#include "Animal.h"
#include "iostream"


class Cat: public Animal{
public:
    Cat(): Animal(){
        std::cout<<"Cat(): Animal()"<<std::endl;
    }
    void eat(){
        Animal::eat();
        std::cout<<"\tCat eating"<<std::endl;
    }
    ~Cat(){
        std::cout<<"~Cat()"<<std::endl;
    }
};


#endif
