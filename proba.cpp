#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    // Tworzymy 3 wektory: 1 na wyrazy, 2 na liczby całkowite
    vector<string> vecOfStr;
    // Pobieramy całą linię do zmiennej linia
    string linia;
    getline(cin, linia);

    // Tworzymy strumień z naszą linią
    istringstream iss(linia);

    // Pętla powtarza się dopóki w strumieniu są dane
    while(!iss.eof())
    {
        // Z każdym obrotem pętli wczytujemy napis, 2 liczby
        // i zapisujemy je do 3 różnych pojemników na dane

        string s;
        iss >> s;
        vecOfStr.push_back(s);
    }

    // Wyświetlamy zawartość 3 wektorów

    cout << "\nZawartosc vecOfStr:";
    for(int i=0; i<vecOfStr.size(); ++i)
        cout << " " << vecOfStr[i];


    return 0;
}
