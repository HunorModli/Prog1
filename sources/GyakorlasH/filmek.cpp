#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

int myAtoi(string s) {
    stringstream ss;
    int i;
    ss << s;
    ss >> i;
    return i;
}


/**	Feladat: olvasd be filmek adatait a filmek.csv fájlból megfelelő adatszerkezetbe, majd végezd el a következő feladatokat:
 *		1) Irasd ki a leghosszabb játékidejű filmet.
 *		2) Irasd ki a filmeket Kategória szerint rendeztve, valamint látszódjon az imdb értékelésük is.
 *		3) Ha felhasználó beír egy Kategóriát, akkor adja meg, hogy melyik a legjobb film a kategóriában (imdb alapján).
 * 	A program világosan kommunikáljon a felhasználóval, és a 0 inputra ki lehessen lépni belőle.
 */

struct Film {
    string nev;
    string kategoria;
    int jatekido;
    int ev;
    string szinesz;
    float imdb;
};

bool operator < (Film f1, Film f2) {
    if (f1.jatekido == f2.jatekido) {
        return f1.nev < f2.nev;
    }
    return f1.jatekido > f2.jatekido;
}

ostream &operator << (ostream &of, Film f) {
    cout << "Nev: " << f.nev << ", Kategoria: " << f.kategoria
         << ", Jatekido: " << f.jatekido << ", Ev: " << f.ev
         << ", Szinesz " << f.szinesz << ", Imdb:" << f.imdb;
    return of;
}

bool imdbAlapjan(Film f1, Film f2) { // vector max_element függvényáhez kell hogy mi alapján keressen maxot!
    return f1.imdb < f2.imdb;
}

class Feladat {
    set<Film> filmekSet;
    map<string, vector<Film>> filmekKategoriahoz;

public:
    Feladat() {
        ifstream f("filmek.csv");
        if (!f.good()) {
            cout << "Nem sikerült megnyitni a fájlt!" << endl;
        } else {
//            string s = "12";
//            int a = atoi(s.c_str());
            string tmp;

            getline(f,tmp);

            Film film;
            string kategoria; // MAP-nek a kategória kulcsa stringként

//            cout << film.nev << ", " << film.ev << ", " << film.imdb;
            while(getline(f,film.nev,',')) { // Beolvastuk a sorból a címet az első vesszőig
                getline(f,tmp,',');
                film.kategoria = tmp;
                kategoria = tmp;
                getline(f,tmp,',');
                film.jatekido = atoi(tmp.c_str());
//                film.jatekido = myAtoi(tmp); // alternatíva ha az atoi kudarcot vall
                getline(f,tmp,',');
                film.ev = atoi(tmp.c_str());
                getline(f,film.szinesz,',');
                getline(f,tmp);
                film.imdb = atof(tmp.c_str());

                filmekSet.insert(film);

                if (filmekKategoriahoz.count(kategoria)) { // Ha már létezik ilyen kulcsú elem a map-ben
                    //, azaz van már ilyen kategória a string kulcsok között, akkor csak hozzáadjuk a vektorhoz a filmet.
                    filmekKategoriahoz[kategoria].push_back(film);
                } else { // különben létre kell hozni egy vectort amiben az első film van az adott kategóriához.
                    vector<Film> v;
                    v.push_back(film);
                    filmekKategoriahoz[kategoria] = v;
                }

            }
            f.close();
        }
    }

    void elsoFeladat() {
//        cout << "Elso feladat ide" << endl;
//        cout << "Map mérete: " << filmekKategoriahoz.size() << endl;
//        cout << "Set mérete: " << filmekSet.size() << endl;
//        cout << "Set tartalma: " << endl;
//
//        for (auto i : filmekSet) {
//            cout << i << endl;
//        }
//
//        cout << "Map tartalma" << endl;
//
//        for (auto i : filmekKategoriahoz) {
//            cout << "Kategoria: " << i.first << endl;
//            for (auto j : i.second) {
//                cout << j << endl;
//            }
//        }
        cout << "Leghosszabb játékidejű film: " << endl;
        cout << *filmekSet.begin() << endl;
    }

    void masodikFeladat() {
        cout << "A Filmek Kategóriák szerint: " << endl;

        for (auto i : filmekKategoriahoz) {
            cout << "Kategoria: " << i.first << endl << "------------------" << endl;
            for (auto j : i.second) {
                cout << j.nev << ", " << j.imdb << endl;
            }
            cout << endl << endl;
        }

    }
    void harmadikFeladat() {
        string tmp;
        cout << "Írjon be egy kategóriát!" << endl;
        cin >> tmp;

        if (filmekKategoriahoz.count(tmp)) { // ha létezik ilyen kategória akkor maxkeresés

            vector<Film> v = filmekKategoriahoz.at(tmp);

            // algorithm könyvtár része. működés:
            // param1: iterátor a tömb elejére
            // param2 iterátor a tömb végére.
            // eredmény: iterátor a max elemre. (*-gal dereferálni kell!!!)
            Film max = *max_element(v.begin(), v.end(), imdbAlapjan);
            cout << max << endl;
        } else { // ha nem létezik ilyen akkor kiírjuk
            cout << "Nincs ilyen kategória!";
        }
    }
};

int main() {
    Feladat feladat;
    bool fut = true;
    int bemenet;
    while (fut) {
        cin >> bemenet;
        cin.ignore(); // néha kell, néha nem :D (Code::Blocks egy fos ^__^ )
        switch (bemenet){
            case 0:
                fut = false;
                break;
            case 1:
                feladat.elsoFeladat();
                break;
            case 2:
                feladat.masodikFeladat();
                break;
            case 3:
                feladat.harmadikFeladat();
                break;
            default:
                cout << "Nem megfelelő bemenet. Próbáld újra!" << endl;
                break;
        }
    }
}