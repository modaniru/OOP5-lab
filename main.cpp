#include <iostream>
#include "classes/Animal.h"
#include "classes/Cat.h"

int main() {
    Cat *cat = new Cat();
    Animal *animal = new Cat();

    std::cout<<std::endl;

    cat->eat(); /* так как метод eat() у родительского класса Animal не виртуальный, на 11 строчке будет вызвана функция
 *  класса Cat, так как он ее переопределяет(перекрывает)
 *  но на 15 строчке вызовется метод eat() класса Animal
 * */
    animal->eat();
    cat->someFunc(); // наследуемая функция от класса Animal

    std::cout<<std::endl;

    /*Так как диструктор у родительского класса не виртуальный, это приводит к утечке памяти, если в классах потомках
     * дополнительно выделяется память. В нашем случае, в строчке 22, переменная класса Animal, в которой лежит ее
     * наследник, */
    delete animal;
    delete cat;
    return 0;
}
