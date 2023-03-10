#ifndef LABA5_ANIMAL_H
#define LABA5_ANIMAL_H
#include "iostream"


class Animal {
public :
    Animal(){
    std::cout<<"Animal()"<<std::endl;
}
    void eat(){
    std::cout<<"Animal eating"<<std::endl;
}
    void someFunc(){
    std::cout<<"ONLY ANIMAL FUNC"<<std::endl;
}
    ~Animal(){
    std::cout<<"~Animal()"<<std::endl;
}
};

#endif
