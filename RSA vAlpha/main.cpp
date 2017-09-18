#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//#include <cstdio> // printf
#include <fstream>  // pliki
#include <conio.h>  // geth
#include <memory>   // unique_ptr
#include <vector>

using namespace std;



long p=0, q=0, n=0, t=0, flag=0, e[100]={0}, d[100]={0}, temp[100]={0}, j=0, m[100]={0}, en[100]={0}, i={0};
//char buff;
//char msg[100];
string msg = "";
void setup( );
int is_prime(long);
void ce();
long cd(long);
void encrypt();
void decrypt();
void wczytajPlik( string nazwaPliku, string &zmienna );
void zapiszPlik( string nazwaPliku, string &zmienna );
void load_file( string nazwaPliku, string &zmienna );
void make_choice( char & value );
void set_is_primes();

unsigned long liczba_pierwsza_max79( int n = 50 )
{
    return n*n - 79*n + 1601;
}

int main( int argc, char * argv[] )
{
    char choice = '1';
//setlocale( LC_ALL, "C.UTF-8" ); // linux
//setlocale(LC_ALL, "pl_PL.UTF-8");

    if ( 1 < argc )
    {
//        wczytajPlik( argv[1], msg );
        load_file( argv[1], msg );
        make_choice( choice );
    }
    else
    {
        cout << "\nWprowadz dane:\n";
        cin.clear();
        getline( cin, msg );
    }
// msg = "ZAQ";

//p = 0; q=0;

    system("cls");

        switch ( choice )
        {
            case '0': break;
            case '1':
            case 13:                                                        // enter
                cout << "Szyfrowanie\n";
                    setup();

                encrypt(); zapiszPlik( "encrypted.txt", msg );
                break;
            case '2':
                cout << "Deszyfrowanie\nPodaj klucz publiczny: ";
                cin >> d[0];
                cout << "Podaj n: ";
                cin >> n;
                for (i = 0; msg[i] != NULL; i++)
                    m[i] = msg[i];

                decrypt(); zapiszPlik( "decrypted.txt", msg );
                break;

              default:
                  cout << "Jesteœ pewien ze wcisnales dobry klawisz? Wprowadzono: int(" << (int)choice <<") char(" << choice << ")" << endl;
        }

    if ( p != 0 && q != 0)
    {
        cout << "\nMozliwe wartosci 'e' i 'd'\n";
        j = sqrt(p);
        for (i = 0; i < j - 1; i++)
        cout << e[i] << "\t" << d[i] << endl; //"\t(d*e) mod t = " << (d[i]*e[i]) % t << "\n";      // powinno rowanc sie 1
    }

    system("pause");
    return 0;
}

// -----------------------------------------------------------------------------------

void setup( )
{
    set_is_primes();

    for (i = 0; msg[i] != NULL; i++)
        m[i] = msg[i];

    n = p * q;
    t = (p - 1) * (q - 1);

    ce();
}

int is_prime(long pr)      // sprawdzamy czy parametr jest liczb¹ pierwsz¹
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

// -----------------------------------------------------------------------------------

void set_is_primes()
{
    cout << "Losowe: \t" << liczba_pierwsza_max79( rand() %80  ) <<  "\t" << liczba_pierwsza_max79( rand() %80 ) << endl;
    long buff[2] = {0};
    for ( int i = 0; i < 2; i++ )
    {
        do {
            if ( i == 0 ) cout << "\nPodaj liczbe pierwsza: ";
            else          cout << "\nPodaj inna liczbe pierwsza: ";

            cin >> buff[i];

            flag = is_prime( buff[i] );
            if ( flag == 0 ) cout << "\nBlad, " << buff[i] << " to nie jest liczba pierwsza. np. 7, 11, 13, 17, 19 \nSproboj jeszcze raz.";
            else if ( buff[i] < 7 ) { cout << "\nZbyt mala liczba pierwsza. ( p >= 7 )"; flag = 0; }
            else if ( i == 1 && p == buff[i] ) flag = 0;

            if ( i == 0 ) p = buff[i];
            else          q = buff[i];
        }
        while ( flag == 0 );
    }
}

// -----------------------------------------------------------------------------------

void ce()
{
    int k = 0;

    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = is_prime(i);
        if (flag == 1 && i != p && i != q)  // rozne od podanych
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

// -----------------------------------------------------------------------------------

long cd(long x)
{
    long k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

// -----------------------------------------------------------------------------------

void encrypt()
{
    long pt, ct, key = e[0], k, len;
    i = 0;
//    len = strlen(msg);
    len = msg.length();
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    cout << "\nZaszyfrowana zawartosc:\n";
    msg = "";
//    char buffer [128];
    unique_ptr <char[]> buffer ( new char[sizeof( en )] );
    for (i = 0; en[i] != -1; i++)
    {
        printf ("%c", en[i] );
        snprintf (buffer.get(), sizeof(buffer),"%c", en[i] );
        msg += buffer.get();
    }
    cout << "\nKlucz prywatny ( e, n ): \t" << e[0] << "\t" << n;
    cout << "\nKlucz publiczny( d, n ): \t" << d[0] << "\t" << t << endl;

    cout << msg;
}

// -----------------------------------------------------------------------------------

void decrypt()
{
    long int pt, ct, key = e[0], k;
    i = 0;
    long len = msg.length();
//key = 145;
//    // wyznaczanie tablicy tmp
//    while (i != len)
//    {
//        pt = m[i];
//        pt = pt - 96;
//        k = 1;
//        for (j = 0; j < key; j++)
//        {
//            k = k * pt;
//            k = k % n;
//        }
//        temp[i] = k;
//        ct = k + 96;
//        en[i] = ct;
//        i++;
//        cout << "\ntmp: " << k <<"\t"<< ct ;
//    }
key = d[0];

    while (i != len)
    {
        ct = m[i];
        ct = ct - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "\nRozszyfrowana zawrartosc:\n";
    msg = "";
    unique_ptr <char[]> buffer ( new char[sizeof(m)] );
    for (i = 0; m[i] != -1; i++)
    {
        printf("%c", m[i]);
        snprintf (buffer.get(), sizeof(buffer),"%c", m[i] );
        msg += buffer.get();
    }

//    cout << "\nKlucz publiczny: "  << d[0] << n << msg<<endl;

}
// -----------------------------------------------------------------------------------

void wczytajPlik( string nazwaPliku, string &dest )
{
    std::ifstream plik;
    plik.open( nazwaPliku.c_str() );
    if( !plik.good() )
    {
        cout << "\nB³¹d otwarcia pliku: " << nazwaPliku << endl;
        system("pause");
        exit(1);
    }

    while( !plik.eof() )
        {
            getline( plik, dest );
            cout << dest << endl;
        }
}

// -----------------------------------------------------------------------------------

void zapiszPlik( string nazwaPliku, string &src )
{
     ofstream out(nazwaPliku, ios::out | ios::binary);

    if(!out) {
        cout << "Nie mogê otworzyæ pliku do zapisu.\n";
        system("pause");
        exit(2);
    }
//    std::copy(
//        std::istreambuf_iterator<char>(src),
//        std::istreambuf_iterator<char>( ),
//        std::ostreambuf_iterator<char>(out));
//streamsize = strlen()
    out.write(src.c_str(),(streamsize) strlen(src.c_str()));
//    out << src;
    cout << "\nZapisano do: " << nazwaPliku << endl;
    out.close();
}

// -----------------------------------------------------------------------------------

void load_file( string file_name, string &src )
{
//    std::ifstream input( file_name, std::ios::binary );
//
//     std::vector<char> buffer((
//            std::istreambuf_iterator<char>(input)),
//            (std::istreambuf_iterator<char>()));
//
//     std::copy(
//        std::istreambuf_iterator<char>(input),
//        std::istreambuf_iterator<char>( ),
//        std::ostreambuf_iterator<char>(src));

    std::ifstream ifs( file_name, std::ios::binary );
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    src = content;
}

// -----------------------------------------------------------------------------------

void make_choice( char & value )
{
        cout << msg
             << "\n\nCo zrobic:\n"
             << "1. Zaszyfruj (Enter)\n"
             << "2. Rozszyfruj\n";

        value = getch();
}

// -----------------------------------------------------------------------------------
