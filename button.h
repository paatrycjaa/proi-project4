/**
*Name : button.h
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#include <vector>
#include <string>
#include "shell.h"
#include "saveXML.h"

//Wyjątki
class NExist{};                                                                    //przycisk nie istnieje
class Exist{};                                                                     //przycisk juz istnieje
class NFunc{};                                                                     //nie ma numeru takiej funkcji
class Full{};                                                                      //zapelnione podmenu


// klasa bazowa - interfejs reprezentujacy przycisk
class Button {

public:
    virtual ~Button(){};                                                                        //destruktor
    virtual void pressButton() = 0;                                                             //wcisnieie przycisku
    virtual void printButton() = 0;                                                             //wydrukowanie przycisku
    virtual std::string getButtonName() = 0;                                                    //zwraca nazwe buttona
    virtual int getIfFree() = 0;                                                                //sprawdza czy przycisk nie prowadzi do niepustego podmenu
    virtual void saveButton(SaveXML* file, int howDeep) = 0;                                    //zapisuje przycisk do XML
    virtual int getShouldSave() = 0;                                                            //zwraca stan menu przycisku
private:
    std::string buttonName;

};

//klasa opisujaca Menu
class Menu{

public:
    Menu(int x, int s): howDeep(x), save(s){};                                                  //konstruktor
    ~Menu();
    void action();                                                                              //wlaczenie menu
    void addChoiceButton(std::string name, int x);                                              //dodanie przycisku jednoznacznego wyboru
    void addMenuButton(std::string name);                                                       //dodanie przycisku menu
    //void deleteChoiceButton(std::string name);
    void deleteMenuButton(std::string name);                                                    //usuniecie przycisku
    void displayHelp();                                                                         //wyswietlenie pomocy
    void printMenu();                                                                           //wyswietlenie menu
    void saveMenu(SaveXML* file);                                                               //zapisanie przyciskow menu
    void saveAll();                                                                             //zapisanie manu do XML
    void comeBack();                                                                            //powrot do menu
    int howMany();                                                                              //ile przyciskow
    int getSave();                                                                              //jaki stan menu, 1 - zapis, 2 - wyjscie, 0 - przegladanie

private:
    std::vector<Button*> buttons;                                                               //wektor zawierajacy wskazniki klasy Button
    std::array<std::string, 8> instructions = {"add-choice-button", "add-menu-button", "delete-button", "press-button", "back", "end", "help", "save"};         //instrukcje
    int howDeep;                                                                                //poziom menu (1 -pierwotny)
    int save;                                                                                   //stan menu

    int getInt(int x1, int x2) const;                                                           //pobranie inta
    void clearBufor() const;                                                                    //czyszczenie bufora
    int findButton(std::string name) const;                                                     //znalezienie przycisku

};

class ChoiceButton : public Button {                                                            //pochodna klasy bazowej Button

public:
    ChoiceButton(std::string name, int x);                                                      //konstruktor
    ~ChoiceButton(){};                                                                          //destruktor
    virtual void pressButton();                                                                 //wcisniecie przycisku
    virtual void printButton();                                                                 //drukowanie przycisku
    virtual std::string getButtonName();                                                        //nazwa przycisku
    virtual int getIfFree(){return 0;};                                                         //czy prowadzi do niepustego menu. -> choice nie prowadzi do zadnego, wiec 0
    virtual int getShouldSave(){return 0;};                                                     //w jakim menu jest stanie -> choice nie posiada menu, wiec 0
    virtual void saveButton(SaveXML* file, int howDeep);                                        //zapisanie przycisku do XML
    void callFunction();                                                                        //wywolanie funkcji obslugi

private:
    std::string buttonName;                                                                     //nazwa
    int whichFunction;                                                                          //numer obslugiwanej funkcji
};

class MenuButton : public Button {                                                              //pochodna klasy bazowej

public:
    MenuButton(std::string name, int howDeep, int save);                                        //konstruktor
    ~MenuButton();                                                                              //destruktor
    virtual void pressButton();                                                                 //wcisniecie przycisku
    virtual void printButton();                                                                 //wydrukowanie przycisku
    virtual std::string getButtonName();                                                        //nazwa przycisku
    virtual int getIfFree();                                                                    //czy prowadzi do niepustego menu
    virtual int getShouldSave();                                                                //w jakim menu jest stanie
    virtual void saveButton(SaveXML* file, int howDeep);                                        //zapisanie przycisku do XML

private:
    Menu *menu;                                                                                 //wskaznik na menu, do ktorego prowadzi przycisk
    std::string buttonName;                                                                     //nazwa przycisku
};


#endif // BUTTON_H_
