/**
*Name : shell.h
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <vector>
#include <string>
#include <array>

//klasa wczytujaca polecenia z terminala - shell

class Read{

public:
    Read();                                                                             //konstruktor
    ~Read(){};                                                                          //destruktor
    void readLine();                                                                    //wczytanie linii
    int howManyWords();                                                                 //ile wczytanych slow
    bool ifInstruction(std::string instruction);                                        //czy jest instrukcja
    bool ifExist(std::string button);                                                   //czy nazwa istnieje
    bool ifNumber();                                                                    //czy to liczba calkowita
    std::string returnName();                                                           //zwraca nazwe
    int returnNumber();                                                                 //zwraca numer

private:
    std::vector<std::string> words;                                                     //wektor przechowujacy wczytane slowa

};



#endif // SHELL_H_
