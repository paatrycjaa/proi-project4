/**
*Name : saveXML.cpp
*Purpose : PROI Projekt_4 - menu okienkowe
*@author Patrycja Cieplicka
*@version 1.0 28/04/2019
*/

#include "saveXML.h"

using namespace std;


SaveXML::~SaveXML(){                                                                                            //konstruktor
    if(fileXML.good())                                                                                          //zamkniecie pliku
        fileXML.close();
}


bool SaveXML::checkIfOpened(){                                                                                  //sprawdzenie czy plik otworzony poprawnie
    fileXML.open("menu_okienkowe.xml", ios::out);
    if(fileXML.good()){
        fileXML << "<?xml version=""1.0"" encoding=""iso-8859-2"" ?>\n" << endl << endl;
        return true;
    }
    else{
        cout << "Blad otwarcia pliku" << endl;
        return false;
    }
}

void SaveXML::saveMarker(string object){                                                                        //zapisanie w postaci <object>
    fileXML << "<" << object << ">" ;
}

void SaveXML::saveEnter(){                                                                                      //zapisanie \n
    fileXML << endl;
}

void SaveXML::saveEndMarker(string object){                                                                     //zapisanie w postaci <object/>
    fileXML << "<" << object << "/>" << endl;
}

void SaveXML::saveNameMarker(string object, string name){                                                       //zapisanie w postaci <object name="objectname">
    fileXML << "<" << object << " name=\"" << name << "\">" << endl;
}

void SaveXML::saveTabulates (int number){                                                                       //zapisanie \t
    for(int i=0; i<number; i++){
        fileXML << "\t";
    }
}

void operator<< (SaveXML &s, const string name) {                                                               //przeciazenie operatora, zapisanie do pliku stringa
   s.fileXML << name;
 }
