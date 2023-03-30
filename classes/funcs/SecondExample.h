//
// Created by Данил Мокшанцев on 19.03.2023.
//

#ifndef LABA5_SECONDEXAMPLE_H
#define LABA5_SECONDEXAMPLE_H

#include "iostream"
#include "Func.h"

using namespace std;

class Base{
private:
    int value;
public:
    Base(){
        cout<<"Base()"<<endl;
        value = 0;
    }
    Base(int value): value(value){
        cout<<"Base(int value)"<<endl;
    }
    Base(const Base &base): value(base.value){
        cout<<"Base(const Base &base)"<<endl;
    }
    Base(Base* base): value(base->value){
        cout<<"Base(Base* base)"<<endl;
    }
    virtual bool instanceOf(string className){
        return className == "Base";
    }
    void setValue(int value){
        this->value = value;
    }
    int getValue(){
        return value;
    }
    virtual ~Base(){
        cout<<"~Base()"<<endl;
        cout<<"\tvalue = "<<value<<endl;
    }
};

class Desk: public Base{
private:
    int deskValue;
public:
    Desk(): Base(){
        cout<<"Desk()"<<endl;
    }
    Desk(int value, int deskValue): Base(value), deskValue(deskValue){
        cout<<"Desk(int value, int deskValue)"<<endl;
    }
    Desk(const Desk& desk): Base(desk), deskValue(desk.deskValue){
        cout<<"Desk(const Desk& desk)"<<endl;
    }
    Desk(Desk* desk): Base(desk), deskValue(desk->deskValue){
        cout<<"Desk(Desk* desk)"<<endl;
    }
    bool instanceOf(string className) override{
        return className == "Desk" || Base::instanceOf(className);
    }
    ~Desk() override{
        cout<<"~Desk()"<<endl;
    }
};



class SecondExample: public Func{
public:
    void f1(Base base){
        cout<<"f1(Base base)"<<endl;
        cout<<"\t is a Desk? "<<base.instanceOf("Desk")<<endl;
    }
    void f2(Base& base){
        cout<<"f2(Base& base)"<<endl;
        cout<<"\t is a Desk? "<<base.instanceOf("Desk")<<endl;
    }
    void f3(Base* base){
        cout<<"f3(Base* base)"<<endl;
        cout<<"\t is a Desk? "<<base->instanceOf("Desk")<<endl;
    }
    void f4(unique_ptr<Base> point){
        point->setValue(1000);
        return; //объект удалится, так как мы делегировали управление этим объектом на ф-ию
    }
    unique_ptr<Base> f5(unique_ptr<Base> point){
        point->setValue(1000);
        return move(point);
    }

    void f6(shared_ptr<Base> point){
        point->setValue(500);
    }
    shared_ptr<Base> f7(int value){
        shared_ptr<Base> base = make_shared<Base>(value);
        return base;
    }
    //Тут создаем статику
    Base func1(){
        cout<<"func1()"<<endl;
        Base base = Base();
        return base;
    }
    Base* func2(){
        cout<<"func2()"<<endl;
        Base base = Base();
        return &base;
    }
    Base& func3(){
        cout<<"func3()"<<endl;
        Base base = Base(10);
        return base;
    }
    //тут создаем динамику
    Base func4(){
        cout<<"func4()"<<endl;
        Base* base = new Base();
        return *base;
        //вызывается конструктор копирования для возвращаемого значения.
        // утечка памяти, где-то висит у нас указатель на оригинальный объект
    }
    Base* func5(){
        cout<<"func5()"<<endl;
        Base* base = new Base();
        return base;
        //возвращаем указатель, за цикл жизни объекта отвечает вызывающая ф-я
    }
    Base& func6(){
        cout<<"func6()"<<endl;
        Base* base = new Base();
        return *base;
        //назначается ссылке, наш base, обязанность на удаление передаем вызывающей ф-ии
    }

    void doFunc(){
        //Пример передачи объектов в функцию
        {
            Base *base = new Base();
            f1(*base);
            f2(*base);
            f3(base);
            delete base;
            cout << endl << endl;
            Desk *desk = new Desk();
            //Произойдет вызов только родительского конструктора копирования => внутри нельзя будет сделать приведение типов
            f1(*desk);
            //а в этих копироваться ничего не будет, в функциях лишь будет указываться на ячейку памяти доступную Base
            // => приведение типов доступно
            f2(*desk);
            f3(desk);
            delete desk;
        }
        cout<<endl<<endl<<endl;
        //Пример возвращения объектов, которые в функциях статические
        {
            //Не вызывает диструктор в функции func1(), жизненный цикл объекта зависит от вызывающего блока ф-ии
            Base base1 = func1();
            //cout<<base1.instanceOf("Base")<<endl;

            //ф-я возвращает адресс ячейки памяти, где лежал объект. За жизненный цикл объекта отвечала именно ф-я.
            // => имеем указатель на освобожденную ячейку памяти
            //UB
            Base *base2 = func2();

            //В функции на стеке создается объект, который не успевает скопироваться в передаваемое значение
            //Но все-равно вызывается к-р копирования, аналогично с func2()
            //UB
            Base& base3 = func3();
        }
        cout<<endl<<endl<<endl;
        //Динамика
        {
            Base base4 = func4();
            cout<<base4.instanceOf("Base")<<endl;
            Base *base5 = func5();
            cout<<base5->instanceOf("Base")<<endl;
            Base& base6 = func6();

            delete base5;
        }
        cout<<endl<<endl;
        //unique_ptr
        {
            unique_ptr<Base> base = make_unique<Base>(10);
            cout<<base->getValue()<<endl;
            f4(move(base));
            //cout<<base->getValue()<<endl;//ошибочка
            unique_ptr<Base> base1 = make_unique<Base>(10);
            cout<<base1->getValue()<<endl;
            base1 = f5(move(base1));
            cout<<base1->getValue()<<endl;
        }
        cout<<endl<<endl;
        //shared_ptr
        {
            shared_ptr<Base> base = make_shared<Base>(100);
            f6(base);
            cout<<base->getValue()<<endl;
            //Объект создается в функции, и после возврата из функции счетчик у
            // shared_ptr увеличивается, затем уменьшается,
            //что не дает удалить объект
            shared_ptr<Base> base1 = f7(1000);
            cout<<base1->getValue()<<endl;
        }
    }
};


#endif //LABA5_SECONDEXAMPLE_H
