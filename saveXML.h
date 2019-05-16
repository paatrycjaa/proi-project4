/**
*Name : saveXML.h
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#ifndef SAVEXML_H_
#define SAVEXML_H_

#include <fstream>
#include <iostream>
#include <string>

//Klasa pozwalajaca na zapisanie informacji do pliku XML

class SaveXML {

public:
    SaveXML(){};                                                                                                    //konstruktor
    ~SaveXML();                                                                                                     //destruktor
    SaveXML(const SaveXML&){};                                                                                      //konstrukor kopiujacy
    bool checkIfOpened();                                                                                           //czy poprawnie otwarty plik
    void saveMarker(std::string object);                                                                            //zapisanie markera
    void saveEndMarker(std::string obejct);                                                                         //zapisanie koncowego markera
    void saveNameMarker(std::string object, std::string name);                                                      //zapisanie markera  atrybutem name
    void saveTabulates (int number);                                                                                //zapisani tab
    void saveEnter();                                                                                               //nowa linia
    friend void operator<< (SaveXML &s, const std::string name);                                                    //funkcja zaprzyjazniona, przeciazenie operatora

private:
    std::fstream fileXML;                                                                                           //plik, na ktorym wykonywane sa metody

};



#endif // SAVEXML_H_
