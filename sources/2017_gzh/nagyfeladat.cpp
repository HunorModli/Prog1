#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Projekt {

    map<string, set<string>> reszfeladathozEmberek;
    map<string, set<int>> reszfeladathozTalalkozok;
    set<int> meetingesNapok;

    void uj_reszfeladat(string reszfeladatNeve) {
        reszfeladathozEmberek[reszfeladatNeve];
        reszfeladathozTalalkozok[reszfeladatNeve];
    }

    void kulcsember(string reszfeladatNeve, string kulcsemberNeve) {
//        map<string, vector<string>>::iterator it = reszfeladathozEmberek.find(reszfeladatNeve);
        auto it = reszfeladathozEmberek.find(reszfeladatNeve);
        it->second.insert(kulcsemberNeve);
    }

    void uj_talalkozo(string reszfeladatNeve, int idopont) {

        for (auto feladat : reszfeladathozEmberek) { // végigmegyünk az összes feladaton

           for (string ember : feladat.second) { // Végigmegyünk a feladatokhoz hozzáadott embereken

                if (reszfeladathozEmberek[reszfeladatNeve].count(ember)) { // HA az adott ember hozzá van adva a feladathoz
                    if (reszfeladathozTalalkozok[feladat.first].count(idopont)) { // ÉS ez adott napon van meetingje már
                        cout << "Nem lehet hozzáadni, mert ütközik:" << ember << " és " << feladat.first << endl;
                        return;
                    }
                }
            }
        }
        reszfeladathozTalalkozok[reszfeladatNeve].insert(idopont);
        meetingesNapok.insert(idopont);
    }

    void teljes_naptar_kiir() {

//        for (auto i : reszfeladathozEmberek) {
//            cout << "Reszfeladat: " << i.first << endl;
//            cout << "Emberek: " << endl;
//            for (auto j : i.second) {
//                cout << j << endl;
//            }
//        }

        for (auto nap : meetingesNapok) { // végigmegyünk azokon a napokon amikor tudjuk hogy van valamilyen meeting
            cout << "NAP: " << nap << endl;
            // végigmegyünk az összes részfeladaton, és megnézzük hogy nekik aznap van-e meetingjük:
            for (auto talalkozo : reszfeladathozTalalkozok) {
                if (talalkozo.second.count(nap)) {
                    cout << talalkozo.first << endl;
                }
            }
        }
    }
};


int main() {
    Projekt p;
    p.uj_reszfeladat("karbantartas");
    p.uj_reszfeladat("tervezes");
    p.uj_reszfeladat("marketing");
    p.kulcsember("karbantartas","Tibi");
    p.kulcsember("tervezes","Tibi");
    p.kulcsember("tervezes","Zsofi");
    p.kulcsember("marketing","Lajos");
    p.uj_talalkozo("tervezes", 12);
    p.uj_talalkozo("marketing", 12);
    p.uj_talalkozo("tervezes", 13);
    p.uj_talalkozo("karbantartas", 13); //Ne jegyezze fel, írjon ki hibaüzenetet a kulcsember nevével. Maxpontért visszatérési értékben is jelezni kell a sikerességet, de anélkül is érvényes
    p.teljes_naptar_kiir(); //megjelenik valamilyen formaban, hogy melyik nap mi tortenik

}