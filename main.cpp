#include <iostream>

using namespace std;

string szyfr_cezara( string tekst, int x );

// ------------------------------------------------------------------------------

int main()
{
    string tekst; //zmienna do przechowywania naszego tekstu

    // UWAGA!!!  tekst wprowadzaæ bez spacji
    int x;       // zmienna przechowujaca wspo lczynnik przesuniecia <0;26>

    cout<<"Podaj tekst do zaszyfrowania" << endl;
    cin >> tekst;                                       // tekst do zaszyfrowania
    cout<<"Podaj wspolczynnik przesuniecia" << endl;
    cin >> x;                                           // o ile miejsc zamieniamy litery

    cout << szyfr_cezara(tekst,x) <<endl;

    return 0;
}

// ------------------------------------------------------------------------------

string szyfr_cezara( string tekst, int x )
{
    for( int i = 0; i <= tekst.length(); i++ )
    {
        if(tekst[i]>=65 && tekst[i]<=90-x)          tekst[i]=int(tekst[i])   +x;  //wielkie liter
        else if(tekst[i]>=91-x && tekst[i]<=90)     tekst[i]=int(tekst[i])-26+x;  // wielkie litery
        else if(tekst[i]>=97 && tekst[i]<=122-x)    tekst[i]=int(tekst[i])   +x;  //ma³e liter
        else if(tekst[i]>=123-x && tekst[i]<=122)   tekst[i]=int(tekst[i])-26+x;  //ma³e litery
    }
    return tekst;
}
