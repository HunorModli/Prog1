#include <iostream>
#include <map>
#include <set>

using namespace std;

struct Koli {

    int emeletekSzama;
    int olcsoAr;
    int dragaAr;
    int feliratkozottakSzama;

    map<int, set<string>> emeletek;

    Koli(int em, int ol, int dr) {
        feliratkozottakSzama = 0;
        emeletekSzama = em;
        olcsoAr = ol;
        dragaAr = dr;
    }

    void jelentkezes(int emelet, string nev) {
        // megnézzük hogy ez az emelet létezik-e?
        if (emeletek.count(emelet)) { // Ha ez az emelet már benne van az adatszerkezetben akkor csak a sethez hozzáadjuk a nevet:
            emeletek[emelet].insert(nev);
        } else { // egyébként létrehozzuk a setet a névvel, és ezt értékül adjuk az emeletnek
            set<string> set1;
            set1.insert(nev);
            emeletek[emelet] = set1;
        }
        feliratkozottakSzama++;
    }

    void visszavon(string nev) {
        // plan: menjünk végig az összes emelenten, és nézzük meg hogy az adott emelethez van-e hozzáadva az adott ember.
        // ha igen, akkor kitöröljük az adott set-ből!

        // ITERÁTOROS BESZÚRÁS
//        for (auto it = emeletek.begin(); it != emeletek.end(); it++) {
//            if (it->second.count(nev)) {
////                cout << it->second.size() << endl;
//                it->second.erase(nev);
////                cout << it->second.size() << endl;
//                return;
//            }
//        }

        // RANGE-BASED FOR LOOP-OS BESZÚRÁS
        for (auto &emelet : emeletek) {
            if (emelet.second.count(nev)) { // Ha ez 1 akkor benne van a set-ben!!
//                cout << emelet.second.size() << endl;
                emelet.second.erase(nev);
//                cout << emelet.second.size() << endl;

                // Ha az utolsó embert is töröltük egy emeletről:
                if (emelet.second.size() == 0) {
                    emeletek.erase(emelet.first);
                }
                feliratkozottakSzama--;
                return;
            }
        }
        cout << "Nincs ilyen nevű (" << nev << ") ember! " << endl;
    }

   /** Így nézzen ki:
    *  3 tétel:
    *   - Kiss Balázs: 46000
    *   - Nagy Juli: 23000
    *   - Fekete Zsolt: 23000
    */
    void dump() {
        if(emeletek.size() != 0) {
            cout << feliratkozottakSzama << " tétel: " << endl;
            for(auto emelet : emeletek){
                int lakokSzama = emelet.second.size();
                int osszesFizetendo = dragaAr-olcsoAr;
                int perFoFizetendo = osszesFizetendo/lakokSzama;
                for (auto ember : emelet.second){
                    cout << " - " << ember << ": " << perFoFizetendo << endl;
                }
            }
        }
    }

    void megrendeles() {
        int hanyEmeletRendelt = emeletek.size();
        int hanyOlcso =  emeletekSzama + 1 - hanyEmeletRendelt;
        cout << "Olcso: " << hanyOlcso << " Draga: " << hanyEmeletRendelt << endl;
    }

    void kiir() {
        for (auto emelet : emeletek) {
            cout << "EMELET: " << emelet.first << endl;
            for (auto ember : emelet.second) {
                cout << " - " << ember << endl;
            }
           cout << "----------" << endl;
        }
    }
};


int main() {

    Koli k(8, 12000, 58000);
    k.dump();
    k.jelentkezes(3, "Kiss Balázs");
    k.jelentkezes(4, "Nagy Juli");
    k.jelentkezes(4, "Fekete Zsolt");
    k.jelentkezes(4, "Tóth Béla");
    k.dump(); // három tétel: Kiss Balázs 46000, Nagy Juli, és Fekete Zsolt fejenként 23000
    k.megrendeles(); // 7 olcsó és 2 drága
    k.visszavon("Kiss Balázs");
    k.megrendeles(); // 8 olcsó és 1 drága
}


