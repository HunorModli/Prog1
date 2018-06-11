/// A feladat letölthető a wikiről, azonban ide is teszek egy rövid összefoglalást:
/// Az alapkoncepció az, hogy egy vannak különböző cégek a világ több pontján, és befektetők, akik érdekeltek egy bizonyos vállalatban.

/// a) feladat: Működtessen a program egy adabázist, amiben benne van az összes ismert cég, az, hogy melyik cégnek hol van székhelye, és hogy kinek van kapcsolata azzal a céggel.
/// Egy cégben többen is lehetnek érdekeltek és egy magányszemélyt több céghez is fűzhetik a kapcsolatai.
/// Az adatbázisból le kell tudnunk kérdezni egy adott országban az összes céghez tartozó magányszemélyt, továbbá az osszes céget és személyt is.

/// b) feladat: Írjuk át a programot úgy, hogy cégek is lehessenek érdekeltek egy cégben. Ez azt jelenti, hogy egy anyavállalattal kapcsolatban áll az összes leányvállalat befektetője is
/// de ez fordítva nem feltétlenül igaz. Ezen felül a régiónális leányvállalatok befektetői egyértelműen akkor is kapcsolatban állnak az anyavállalattal, ha az másik országban működik.

/// c) feladat: Tudjon a fájl .csv formátumba menteni, és abból betölteni.

/// A programnak nem kell feltétlenül interaktívnak lennie, bár nem baj ha az.

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//struct Maganszemely {
//    string nev;
//};

struct Ceg {
    string nev;
    string orszag; // pl "USA", "Japan"
};


class Feladat {

    // Adatszerkezetek.
    map<string,map<string,vector<string>>> orszaghozCegek;
    set<string> szemelyek;
    set<string> cegek;

public:

    Feladat() {

    }

    void new_investor(string orszag, string cegnev, string szemely) {

        if (orszaghozCegek.count(orszag) == 1) { // ha az adott ország már létezik a mapben akkor hozzáadjuk a céghez (ha létezik az ember)

            map<string,vector<string>> orszagCegei = orszaghozCegek.find(orszag)->second; // Ennek a mapnek a kulcsa a cég neve, értéke a befeketetők egy vectorban.

            // Ha ilyen cég már létezik az országban:
            if (orszagCegei.count(cegnev) == 1) {
//                cout << "DEBUG:" << endl;
//                cout << "Jelenlegi szemely:" << szemely << " , jelnenlegi ceg: " << cegnev << endl;
//                vector<string> tmp = orszagCegei[cegnev];
//                for (int i = 0; i < tmp.size(); ++i) {
//                    cout << tmp[i] << endl;
//                }
//                cout << endl << "Vector mérete: " << orszagCegei[cegnev].size();
                // Ha létezik akkor a befeketetőt hozzáadjuk a vectorhoz:
                orszagCegei.at(cegnev)
                orszagCegei[cegnev].push_back(szemely);

//                cout << endl << "Vector mérete: " << orszagCegei[cegnev].size();
//                orszagCegei.find(cegnev)->second.push_back(szemely); //Ez ekvivalens az előzővel.
//                vector<string> tmp2 = orszagCegei[cegnev];
//                for (int i = 0; i < tmp2.size(); ++i) {
//                    cout << tmp2[i] << endl;
//                }
                // valamint ha a setben nincs benne a befektető akkor hozzzáadjuk:
                szemelyek.insert(szemely);

            } else { // ha nem létezik ilyen cég, akkor hozzáadjuk a maphez:
                cout << "debug" << endl << cegnev << endl;
                vector<string> v; // csinálunk egy üres vectort, amit majd értékül adunk a cég kulcsnak.

                v.push_back(szemely); // ebbe belerakjuk az első befeketetőnket a cégnél;
                cout << orszagCegei.size() << endl;
                orszagCegei[cegnev] = v; // majd ezt a vectort értékül adjuk a cégnek;
                cout << orszagCegei.size() << endl;

                cegek.insert(cegnev);
                szemelyek.insert(szemely);
            }
        } else { // Ha nem létezik az ország, létrehozzuk:

            map<string,vector<string>> orszagCegei;
            vector<string> v = {szemely};
            orszagCegei[cegnev] = v;
            orszaghozCegek[orszag] = orszagCegei;

            cegek.insert(cegnev);
            szemelyek.insert(szemely);
        };

    }

    void elsoFeladat() {
        cout << "Első feladat meghívva" << endl;
    }

    void masodikFeladat() {
        cout << "Masodik feladat meghívva" << endl;
    }

    void harmadikFeladat() {
        cout << "Haramdik feladat meghívva" << endl;
    }

    void kiirMap() {
        for (auto i : orszaghozCegek) {
            cout << "ORSZÁG: " << i.first << endl;
            cout << "------------" << endl;
            for (auto j : i.second) {
                cout << "Cegnev: " << j.first << endl;
                cout << " - dolgozok szama: " << j.second.size();
//                for (int l = 0; l < j.second.size(); ++l) {
//                    cout << " - " << j.second[l] << endl;
//                }
            }
            cout << endl;
        }
    }

    void kiirSz() {
        for (auto i : szemelyek) {
            cout << i << endl;
        }
    }

    void kiirC() {
        for (auto i : cegek) {
            cout << i << endl;
        }
    }
};


int main()
{
    Feladat f;

    bool fut = true;
    int bemenet;

    f.new_investor("USA", "General Mills", "Joe");
    f.new_investor("USA", "General Mills", "Steve");
    f.new_investor("USA", "McDonalds", "Bill");
    f.new_investor("USA", "McDonalds", "Dave");
    f.new_investor("England", "KFC", "Gerald");
    f.new_investor("England", "H&M", "Anna");
    f.new_investor("Japan", "Toyota", "Yi");

    while (fut) {
        cin >> bemenet;
        cin.ignore(); // NÉHA KELL :D

        switch (bemenet) {
            case 0:
                fut = false;
                break;
            case 1:
//                f.elsoFeladat();
                f.kiirMap();
                break;
            case 2:
//                f.masodikFeladat();
                f.kiirSz();
                cout << endl;
                break;
            case 3:
//                f.harmadikFeladat();
                f.kiirC();
                cout << endl;
                break;
            default:
                cout << "Rossz input! Válassz 0-4-ig újat!";
                break;
        }
    }




//    earth SR;
//    SR.new_investor("Germany", "Saeder-Krupp", "Lofwyr");
//    SR.new_investor("Germany", "Ares Europe", "Soren Johannsen");
//    SR.new_investor("USA", "Ares Macrotechnology", "Arthur Vogel");
//    SR.new_investor("USA", "Ares Macrotechnology", "Damien Knight");
//    //SR.new_investor("USA", "Ares Macrotechnology", "Guido Cantarelli");
//    //SR.new_investor("USA", "Ares Macrotechnology", "Soren Johannsen");
//    SR.new_investor("USA", "Ares Macrotechnology", "Ares Arms");                        /// Az itt látható program a feladat legtöbb követelményének eleget tesz. Bár vannak olyan részek, amik kimaradtak (Pl az összes magánszemény és cég kiíratása),
//    SR.new_investor("USA", "Ares Arms", "Guido Cantarelli");                            /// ezek vagy kicsit más formátumban (pl. dump) megvannak a programban, vagy nagyon egyszerűen bele lehetne írni őket egy pár perc alatt.
//    SR.new_investor("USA", "Ares Macrotechnology", "Ares Europe");                      /// Ennek a programnak a lényege az volt, hogy a legfontosabb részfeladatokra és a bonyolultabb problémákra egy 3 óra alatt megírható megoldást találjak, és ez a feladatok nagy többségénél sikerült is.
//    SR.new_investor("Japan", "Renraku Computer Systems", "Haruhiko Nakada");            /// Az egyetlen dolog, amit nem tudtam 3 óra alatt megoldani, az a többszörös leányvállalatok kezelése (három- vagy többemeletes cégek), bár mivel a feladat nem említette, hogy erre is szükség lenne, ezért vaószínűleg max. 2-3 pontot vonnának le.
//                                                                                        /// Amennyiben van rá igény, megpróbálhatom megcsinálni a többszörös leányvállalatokat is, bár az már biztosan nem férne bele a három órába.
//    //SR.save();
//    //SR.load();
//
//    SR.retrieve_inv("Arthur Vogel");
//    SR.retrieve_inv("Guido Cantarelli");                                                /// Mindenkinek sikeres készülést!
//    SR.retrieve_inv("Soren Johannsen");
//    SR.retrieve_corp("Saeder-Krupp");
//    SR.retrieve_corp("Ares Macrotechnology");
//
//    SR.retrieve_country("USA");
//    SR.retrieve_country("Germany");
//    SR.retrieve_country("Japan");
//
//    //SR.sub_of_what("Ares Arms");
//    //SR.sub_of_what("Ares Macrotechnology");
//    //SR.sub_of_what("Ares Europe");
//    SR.dump();
    return 0;
}
