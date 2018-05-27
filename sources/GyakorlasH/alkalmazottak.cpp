#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

/**     Gyakoroljunk még egy kis fájlkezelést! Adott egy "alkalmazottak.csv" nevű file,
 *      mely egy cég 100 alkalmazottjának adatait tartalmazza a következőképp:
 *
 *      Név,Telefonszám,Email cím,Születési Idő,Azonosítószám
 *  Pl: Michael Cortez,(0141) 554 7341,02/22/1979,placerat@sed.edu,1663061503199
 *      Figyelj rá, hogy a telefonszám többféle formátumban is megadható!
 *      Olvasd be a fileból az adatokat, egy (vagy több) adatszerkezetbe, majd végezd el a feladatokat:
 *
 *      1) Irasd ki a cég dolgozóit születési sorrendben.
 *      2) Tudj hozzáadni az adatbázishoz. Ellenőrizd le az 1., és 2. feladatokkal.
 *      3) Keresd meg azt az évet amikor a legtöbb dolgozó született.
 */

struct Ido {
    int ev;
    int ho;
    int nap;
};

struct Dolgozo {
    string nev,
           telefonszam,
           email;
    Ido    szuletesiDatum;
    string ID;
};

bool operator < (Dolgozo d1, Dolgozo d2) {
    if (d1.szuletesiDatum.ev == d2.szuletesiDatum.ev) {
        if (d1.szuletesiDatum.ho == d2.szuletesiDatum.ho) {
            if (d1.szuletesiDatum.nap == d2.szuletesiDatum.nap) {
                return d1.nev < d2.nev;
            } else {
                return d1.szuletesiDatum.nap < d2.szuletesiDatum.nap;
            }
        }
        return d1.szuletesiDatum.ho < d2.szuletesiDatum.ho;
    }
    return d1.szuletesiDatum.ev < d2.szuletesiDatum.ev;
}

class Ceg {
    set<Dolgozo> idoAlapjan;
    map<int,int> evAlapjan;
public:
    Ceg() {
        ifstream f ("alkalmazottak.csv");
        if (!f.good()) {
            cout << "hiba a fileban" << endl;
        } else {
            string tmp;
            getline(f,tmp); // eldobjuk az 1. sort.

            Dolgozo dolgozo;

            while (getline(f,dolgozo.nev,',')) {
                getline(f,dolgozo.telefonszam,',');
                getline(f,dolgozo.email,',');
                Ido datum;
                getline(f,tmp,'/');
                datum.ho = atoi(tmp.c_str());
                getline(f,tmp,'/');
                datum.nap = atoi(tmp.c_str());
                getline(f,tmp,',');
                datum.ev = atoi(tmp.c_str());
                dolgozo.szuletesiDatum = datum;

                getline(f,dolgozo.ID);

                idoAlapjan.insert(dolgozo);

                if (evAlapjan.count(dolgozo.szuletesiDatum.ev)) { // Ha van már ilyen év a mapben:
                    evAlapjan[dolgozo.szuletesiDatum.ev]++;
                } else {
                    evAlapjan[dolgozo.szuletesiDatum.ev] = 1; // Ha nincs ilyen, akkor létrehozzuk a kulcsot, 1 értékkel.
                }
            }
            f.close();
        }
    }

    void elsoFeladat() {
        for (auto i : idoAlapjan) {
            cout << i.nev << " --> " << i.szuletesiDatum.ev << "-"
                 << i.szuletesiDatum.ho << "-" << i.szuletesiDatum.nap << endl;
        }
    }
    void masodikFeladat() {
        // TODO : befejezni!! :D

    }
    void harmadikFeladat() {
        // maxkeresés:
        // TODO : befejezni!! :D

        int maxEv = evAlapjan.begin()->first;
        int max = evAlapjan.begin()->second;

        for (auto i : evAlapjan) {
            if (max < i.second) {
                maxEv = i.first;
                max = i.second;
            }
        }
    }

};

int main() {
    Ceg ceg;
    bool fut = true;
    int bemenet;

    while (fut) {
        cin >> bemenet;
        cin.ignore();
        switch (bemenet) {
            case 0:
                fut = false;
                break;
            case 1:
                ceg.elsoFeladat();
                break;
            case 2:
                ceg.masodikFeladat();
                break;
            case 3:
                ceg.harmadikFeladat();
                break;
            default:
                cout << "Rossz bemeent, próbáld újra!" << endl;
                break;
        }
    }
}