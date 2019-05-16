/**
*Name : shell.cpp
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#include "shell.h"

#include <iostream>
#include <sstream>

using namespace std;

//words[0] - instrukcja, words[1] - nazwa przycisku, words[2] - numer funkcji

Read::Read(){
}

string Read::returnName(){                                                                                  //meotda zwracajaca wczytana nazwe
    return words[1];
}

int Read::returnNumber(){                                                                                   //metoda zwracajaca wczytana liczbe
    int number = stoi(words[2]);
    return number;
}

void Read::readLine(){

    for (size_t i=0; i<words.size(); ++i){                                                                  //metoda wczytujaca linie
        words.erase(words.begin() + i);                                                                     //czyszczenie wektora
    }
    words.clear();

    string line;
    getline(cin, line);                                                                                     //wczytanie linii

                                                                                                            // Tworzymy strumień z naszą linią
    istringstream readed(line);

                                                                                                            // Pętla powtarza się dopóki w strumieniu są dane
    while(!readed.eof())
    {
        string temp;
        readed >> temp;
        words.push_back(temp);
    }

}

int Read::howManyWords(){                                                                                   //metoda zwraca liczbe wczytanych slow
    int number = 0;
    for(size_t i = 0 ; i < words.size() ; ++i){
        number++;
    }
    //cout << "number"<< number << endl;
    return number;
}

bool Read::ifInstruction(string instruction){                                                               //sprawdza czy instrukcja
    if(instruction == words[0])
        return true;
    else
        return false;
}

bool Read::ifExist(string button){                                                                          //sprawdza czy wczytane takie slowo
    if(button == words[1])
        return true;
    else
        return false;
}

bool Read::ifNumber(){                                                                                      //sprawdza czy liczba
    for(size_t i = 0; i < words[2].length(); i++)
        if(words[2][i]>'9' || words[2][i]<'0')
            return false;

    return true;

}
