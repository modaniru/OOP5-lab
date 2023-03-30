//
// Created by Данил Мокшанцев on 19.03.2023.
//

#ifndef LABA5_THIRDEXAMPLE_H
#define LABA5_THIRDEXAMPLE_H


#include "Func.h"
#include "iostream"

using namespace std;

class Animal{
public:
    virtual void sound(){}
    virtual bool isA(string className){
        return className == "Animal";
    }
    virtual string className() = 0;
};

class Cat: public Animal{
public:
    string className() override{
        return "Cat";
    }
    void sound() override{
        cout<<"meow-meow"<<endl;
    }
    bool isA(string className) override{
        return className == "Cat" || Animal::isA(className);
    }
    //Cat cat;
    //cat.isA("Animal"); false
    virtual void catchMouse(){cout<<"catch mouse"<<endl;}
};
class Dog: public Animal{
public:
    string className() override{
        return "Dog";
    }
    void sound() override{
        cout << "wow-wow"<<endl;
    }
    bool isA(string className) override{
        return className == "Dog" || Animal::isA(className);
    }
    void catchCat(){cout<<"catch cat"<<endl;}
};
class SwedishCat: public Cat{
public:
    string className() override{
        return "SwedishCat";
    }
    void sound() override{
        cout << "swedish meow-meow"<<endl;
    }
    bool isA(string className) override{
        return className == "SwedishCat" || Cat::isA(className);
    }
    void catchMouse() override{cout<<"swedish catch mouse"<<endl;}

};

class ThirdExample: public Func{
public:
    Animal* creator(int i){
        if(i == 0){
            return new Cat();
        }
        else if(i == 1){
            return new SwedishCat();
        }
        else{
            return new Dog();
        }
    }

    Animal** generator(){
        ::srand(NULL);
        int size = 10;
        Animal** array = new Animal*[size];
        for(int i = 0; i < size; i++){
            array[i] = creator(rand()%3);
        }
        return array;
    }

    //Опасное приведение
    void toCat(Animal* animal){
        Cat* cat = static_cast<Cat*>(animal);
    }

    void doFunc(){
        Animal** array = generator();
        for(int i = 0; i < 10; i++){
            array[i]->sound();
        }
        //приведение типов нужно для того, чтобы кастить указатель на родительский класс в дочерний
        //тем самым дает возможность вызывать метод дочерних классов (если этот класс можно закастить до желаемого)
        cout<<endl;
        for(int i = 0; i < 10; i++){
            if(array[i]->isA("Cat")){
                static_cast<Cat*>(array[i])->catchMouse();
            }
            else if(array[i]->isA("Dog")){
                static_cast<Dog*>(array[i])->catchCat();
            }
            else{
                cout<<"error"<<endl;
            }
        }
        cout<<endl;
        //dynamic
        for(int i = 0; i < 10; i++){
            SwedishCat* swedishCat = dynamic_cast<SwedishCat*>(array[i]);
            if(swedishCat != nullptr){
                swedishCat->catchMouse();
                continue;
            }
            Cat* cat = dynamic_cast<Cat*>(array[i]);
            if(cat != nullptr){
                cat->catchMouse();
                continue;
            }
            Dog* dog = dynamic_cast<Dog*>(array[i]);
            if(dog != nullptr){
                dog->catchCat();
                continue;
            }
            cout<<"error";
        }
    }
};


#endif //LABA5_THIRDEXAMPLE_H
