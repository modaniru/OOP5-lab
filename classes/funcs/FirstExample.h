//
// Created by Данил Мокшанцев on 19.03.2023.
//

#ifndef LABA5_FIRSTEXAMPLE_H
#define LABA5_FIRSTEXAMPLE_H


#include "Func.h"
#include "iostream"

using namespace std;

class Point {
protected:
    int x;
    int y;
public:
    Point() {
        cout<<"Point()"<<endl;
        x = 0;
        y = 0;
    }

    void fooClass() {
        cout << "fooBaseClass()" << endl;
        ping();
    }

    void goo(){
        cout<<"goo()"<<endl;
        virtualPing();
    }

    void ping() {
        cout << "Point::ping()" << endl;
    }

    void noVirtual(){
        cout<<"Point::noVirtual()"<<endl;
    }

    virtual void virtualPing(){
        cout << "Point::virtualPing()" << endl;
    }

    virtual void loo(){
        cout << "Point::loo()"<<endl;
    }

    virtual ~Point() {
        cout << "~Point()" << endl;
    }
};

class PointHeir : public Point {
public:
    PointHeir() {
        cout << "PointHeir()" << endl;
    }

    void virtualPing() override{
        cout << "PointHeir::virtualPing()" << endl;
    }

    void loo(){
        cout<<"PointHeir::loo()"<<endl;
    }

    void ping() {
        cout << "PointHeir::ping()" << endl;
    }

    virtual void noVirtual(){
        cout<<"PointHeir::noVirtual()"<<endl;
    }


    ~PointHeir() {
        cout << "~PointHeir()" << endl;
    }
};

class FirstExample : public Func {

public:
    void doFunc() {
        //первый пример
        PointHeir *pointHeir = new PointHeir();
        //pointHeir->fooClass();//произойдет вызов родительской функции ping();
        pointHeir->goo();
        delete pointHeir;
        //второй пример
        cout<<endl<<endl;
        Point *point = new PointHeir();
        PointHeir *pointHeir1 = new PointHeir();
        point->noVirtual();//вызов метода базового класса
        pointHeir1->noVirtual();//вызов переопределнного метода класса PointHeir
        point->loo();//вызов PointHeir::loo() т.к родительский метод был вирутальным и класс перекрыл его(хоть и не использовал override)
        pointHeir1->loo();//т.к родительский метод был виртуальным,
        delete pointHeir1;
        delete point;
    }
};


#endif //LABA5_FIRSTEXAMPLE_H
