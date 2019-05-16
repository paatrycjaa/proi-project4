/**
*Name : main.cpp
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

//Program symulujacy menu okienkowe

#include "button.h"

int main(){

    Menu mroot = Menu(1,0);                                             // 1 - pierwotne menu, 0 - stan przegladania
    mroot.displayHelp();
    mroot.action();
;
}
