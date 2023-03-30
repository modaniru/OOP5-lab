#include <iostream>
#include "classes/funcs/FirstExample.h"
#include "classes/funcs/SecondExample.h"
#include "classes/funcs/ThirdExample.h"

using namespace std;


int main() {
    //Виртуальные методы
    //Func *example = new FirstExample();
    //Передача, возврат объектов
    Func *example = new SecondExample();
    //Приведение типов
    //Func *example = new ThirdExample();
    example->doFunc();
}

