/**
*Name : button.cpp
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#include <iostream>
#include <limits>
#include <fstream>
#include <string>


#include "button.h"

using namespace std;

template <int N>                                                                                //szablon funkcji, ktora jest wywolywana dla kazdego buttona jednznacznego wyboru
void functions(){
    cout << "Wywolana funkcja numer:" << N << endl;
}


//MenuButton - metody klasy reprezentujacej przycisk menu

MenuButton::~MenuButton(){                                                                      //destruktor
    delete menu;
}


MenuButton::MenuButton(string name, int howDeep, int save){                                     //konstruktor, w momencie powstania przycisku, powstaje obiekt Menu, do ktorego prowadzi
    buttonName = name;                                                                          //dany przycisk
    menu = new Menu(howDeep + 1, save);
};


int MenuButton::getIfFree(){                                                                    //metoda sprawdzajaca, czy przycisk prowdzi do zapelnionego menu
    if(menu->howMany() == 0){
        return 0;
    }
    return 1;

}

int MenuButton::getShouldSave(){                                                                //metoda sprawdzajaca stan, w jakim znajduje sie menu
    return menu->getSave();
}

void MenuButton::pressButton(){                                                                 //metoda wcisniecia przycisku, prowadzi do otwarcia menu
    menu->action();
}

void MenuButton::printButton(){                                                                 //metoda drukujaca przycisk (nazwe)
    cout <<"[m] " <<buttonName << endl;
}


void MenuButton::saveButton(SaveXML* file, int howDeep){                                        //metoza zapisujaca przycisk do pliku XML
    file->saveNameMarker("menubutton", buttonName);
    menu->saveMenu(file);
    file->saveTabulates(howDeep);
    file->saveEndMarker("menubutton");
}

std::string MenuButton::getButtonName(){                                                        //metoda zwracajaca nazwe przycisku
    return buttonName;
}

//Choice-button - metody klasy reprezentujacej przycisk jednoznacznego wyboru

ChoiceButton::ChoiceButton(string name, int x): buttonName(name), whichFunction(x){             //konstruktor, przyjmuje imię oraz numer funkcji, ktora bedzie wybieral
};


void ChoiceButton::printButton(){                                                               //metoda drukujaca przycisk
    cout << "[c] "<<buttonName << endl;
}

void ChoiceButton::pressButton(){                                                               //metoda wcisniecia przycisku, wywoluje funkcje, ktora podejmuje decyzje
    callFunction();                                                                             //o numerze wykonanej funkcji
}

void ChoiceButton::callFunction(){                                                              //wybranie funkcji
    switch(whichFunction){
        case 0: functions<0>();
            break;
        case 1: functions<1>();
            break;
        case 2: functions<2>();
            break;
        case 3: functions<3>();
            break;
        case 4: functions<4>();
            break;
        case 5: functions<5>();
            break;
        case 6: functions<6>();
            break;
        case 7: functions<7>();
            break;
        case 8: functions<8>();
            break;
        case 9: functions<9>();
            break;
        default:
            cout << "Blad" << endl;
            break;
    }

}

void ChoiceButton::saveButton(SaveXML* file, int howDeep){                                     //metoda zapisujaca przycisk do pliku XML
    file->saveNameMarker("choicebutton", buttonName);
    file->saveTabulates(howDeep+1);
    file->saveMarker("function");
    (*file) << to_string(whichFunction);
    file->saveEndMarker("function");
    file->saveTabulates(howDeep);
    file->saveEndMarker("choicebutton");
}

std::string ChoiceButton::getButtonName(){                                                     //metoda zwracajaca nazwe przycisku
    return buttonName;
}


// Metody klasy reprezentujacej menu

Menu::~Menu(){                                                                                  //destruktor, usuwa przyciski (wektor wskaznikow)
    if(!(buttons.size() == 0)){
        for(auto i = buttons.begin() ; i != buttons.end(); ++i){
            delete *i;
        }
        buttons.clear();
    }

}

int Menu::getSave(){                                                                            //zwraca stan menu
    return save;
}
int Menu::howMany(){                                                                            //zwraca liczbe przyciskow w menu
    int number = 0;
    for(size_t i = 0; i < buttons.size(); ++i){
        number++;
    }
    return number;

}

void Menu::displayHelp(){                                                                       //wyswietla pomoc
    cout << "Witaj w programie tworzącym menu okienkowe" << endl;
    cout << "Wpisz:" << endl;
    cout << "add-choice-button nazwa nr.funkcji /dodanie przycisku jednoznacznego wyboru/" << endl;
    cout << "add-menu-button nazwa /dodanie przycisku podmenu/" << endl;
    cout << "delete-button nazwa /usuniecie przycisku/" << endl;
    cout << "press-button nazwa /wcisniecie przycisku/" << endl;
    cout << "help /wyswietla pomoc" << endl;
    cout << "save /zapisz" << endl;
    cout << "back /wroc" << endl;
    cout << "end /zamknij" << endl;
};


void Menu::action(){                                                                            //glowna funkcja, czyli wlaczenie menu
    //printMenu();
    //int process = 1;
    Read read = Read();

    while(1){
        if(save == 1){                                                                          // w zaleznosci od stanu, menu sie zamyka, lub przechodzi dalej
        	save = 0;                                                                           // save = 1 stan zapisywania
        	comeBack();
            if(save == 2 || (save == 1 && howDeep != 1)){                                       // save = 2 stan wychodzenia
                return;
            }
    	}
    	if(save == 2){
            return;
    	}

        printMenu();                                                                            //wypisanie menu
        read.readLine();

        if(read.howManyWords() == 3 && read.ifInstruction(instructions[0]) && read.ifNumber()){                                             //polecenie add-choice-button
            int number = read.returnNumber();                                                                                               //sprawdzenie poprawnosci polecenia
            try{                                                                                                                            //obsluga wyjatku Exist - istnieje przycisk
                addChoiceButton(read.returnName(), number);
            }
            catch(Exist){
                cout << "Taki przycisk już istnieje w tym podmenu" << endl;
            }
            catch(NFunc){                                                                                                                   //obsluga wyjatku - nieprawidlowa funkcja
                cout << "Istnieja tylko funkcje 1-9" << endl;
            }
        }

        else if(read.howManyWords() == 2 && read.ifInstruction(instructions[1]) ){                                                           //polecenie add-menu-button - sprawdzenie poprawnosci
            try {                                                                                                                            //dodanie prycisku menu
                addMenuButton(read.returnName());
            }
            catch(Exist){                                                                                                                   //obsluga wyjatku - istnieje przycisk
                cout << "Taki przycisk już istnieje w tym podmenu" << endl;
            }
        }

        else if(read.howManyWords() == 2 && read.ifInstruction(instructions[2])){                                                           //polecenie delete-button
            try{                                                                                                                            //sprawdzenie poprawnosci
                deleteMenuButton(read.returnName());
            }
            catch(NExist){                                                                                                                  //obsluga wyjatku - nieistnieje przycisk
                cout << "Taki przycisk nie istnieje w tym podmenu" << endl;
            }
            catch(Full){                                                                                                                    //obsluga wyjatku - zaplenione podemnu
                cout << "Przycisk prowadzi do zapelnionego podmenu" << endl;
            }
        }

        else if(read.howManyWords() == 2 && read.ifInstruction(instructions[3])){                                                           //polecenie press-button
            int temp = findButton(read.returnName());                                                                                       //znalezienie przycisku
            if(temp != -1){
                buttons[temp]->pressButton();                                                                                               //w zaleznosci od stanu menu
                int state =buttons[temp]->getShouldSave() ;                                                                                 //z jakiego wyszlismy
                if(state == 2) {                                                                                                            //dalsze postepowanie
                    save = 2;
                    return;
                }
                else if (state == 1 && howDeep != 1){
                    save = 1;
                    return;
                }
                else if(state == 1 && howDeep == 1) {
                    saveAll();                                                                                                              //przypadek kiedy jestem w pierwotnym menu
                    comeBack();
                }
            }
            else
                cout << "Nie ma takiego przycisku" << endl;
        }

        else if(read.howManyWords() == 1 && read.ifInstruction(instructions[4])){                                                               //polecenie back
            return;                                                                                                                             //powrot do poprzedniego menu
        }

         else if(read.howManyWords() == 1 && read.ifInstruction(instructions[5])){                                                               //polecenie end
            save = 2;                                                                                                                            //wyjscie z menu
            return;
        }

        else if(read.howManyWords() == 1 && read.ifInstruction(instructions[6])){                                                               //polecenie help
            displayHelp();
        }

        else if(read.howManyWords() == 1 && read.ifInstruction(instructions[7])){                                                               //polecenie save
            if(howDeep == 1)                                                                                                                    //kiedy w pierwotnym menu
                saveAll();
            else {
                save = 1;                                                                                                                       //zmiana stanu
                return;
            }
        }

        else{
            cout << "Zla skladnia" << endl;
        }

    }

}

void Menu::saveAll(){                                                                                               //metoda zapisujaca menu do pliku XML
    SaveXML files = SaveXML();
    if( files.checkIfOpened() ){
        files.saveMarker("Menu");
        files.saveEnter();
        saveMenu(&files);
        cout << "Plik zapisany" << endl;
        files.saveEndMarker("Menu");
    }
}

void Menu::saveMenu(SaveXML* file){                                                                                 //metoda zapisujaca kazdy przycisk w menu
    for(auto i = buttons.begin() ; i != buttons.end(); ++i){
        file->saveTabulates(howDeep);
        (*i)->saveButton(file, howDeep);
    }
};

void Menu::comeBack(){                                                                                              //metoda pozwalajaca na powrot do miejsca, w ktorym zapisywalismy
     for(auto i = buttons.begin() ; i != buttons.end(); ++i){
        if( (*i)->getShouldSave() == 1 ){
            (*i)->pressButton();
            int state = (*i)->getShouldSave() ;
            if(state == 2) {                                                                                        // w zaleznosci od stanu wyjscie lub przejscie dalej
                save = 2;
                return;
            }
            else if (state == 1 && howDeep != 1){
                save = 1;
                return;
            }
            else if(state == 1 && howDeep == 1) {
                saveAll();                                                                                           //jesli bede na poczatku
                comeBack();
            }
            return;
        }

    }
    return;
}

void Menu::addMenuButton(string name){                                                                               //metoda dodajaca przycisk menu do wektora przyciskow
    if(findButton(name) != -1 ){
        throw Exist();                                                                                               //rzucenie wyjatku
    }
    buttons.push_back(new MenuButton(name, howDeep, save) );
}

void Menu::addChoiceButton(string name, int x){                                                                     //metoda dodajaca przycisk jednoznacznego wyboru
    if(findButton(name) != -1 ){                                                                                    //do wektora przyciskow
        throw Exist();
    }
    if(x < 0 || x > 10){                                                                                            //rzucenie wyjatkow
        throw NFunc();
    }
    buttons.push_back(new ChoiceButton (name, x));
}

int Menu::findButton(string name) const{                                                                            //metoda zwracajaca indeks buttona, którego szukamy po nazwie
    for(size_t i = 0; i < buttons.size(); ++i){
        if(buttons[i]->getButtonName() == name) {
            return i;
        }
    }
    return -1;
}

/*void Menu::deleteChoiceButton(string name){                                                                         //metoda usuwajaca przycisk Choice (nie pyta czy pelne menu)
    int temp = findButton(name);
    if(temp == -1){
        throw NExist();
    }

    else {
        delete buttons[temp];
        buttons.erase(buttons.begin() + temp);
    }
}*/

void Menu::deleteMenuButton(string name){                                                                             //metoda usuwajaca przycisk Choice/ ale i Menu
    int temp = findButton(name);                                                                                      //nie mozna przy pelnym Menu
    if(temp == -1){
        throw NExist();
    }

    if(buttons[temp]->getIfFree()){
        throw Full();
    }

    else{
        delete buttons[temp];
        buttons.erase(buttons.begin() + temp);
        }
}


void Menu::printMenu(){                                                                             //metoda drukujaca menu
    for(int i = 0; i < howDeep; ++i){
        cout << "*";
    }
    cout<< endl;
    for(auto i = buttons.begin() ; i != buttons.end(); ++i){
        (*i)->printButton();
    }
}


int Menu::getInt(int x1, int x2) const{                                                            //metoda wczytująca liczbę całkowitą z podanego przedziału
    int number;                                                                                     //sprawdza poprawność wprowadzonych danych, prosi o ponowne wpisanie w przypadku bledu
    while (!(cin >> number) || number < x1 || number > x2 || cin.peek() != '\n'){
        cout << "Wpisz liczbę z przedziału "<< x1 <<"-"<< x2 << endl;
        clearBufor();
    }
    return number;
}

void Menu::clearBufor() const{                                                                           //metoda czyszcząca bufor
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
