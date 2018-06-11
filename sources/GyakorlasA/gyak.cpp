#include <iostream>
#include <vector>
//#include <list>
//#include <set>
//#include <algorithm>
#include <map>
//#include <cstdlib>
//#include <sstream>

using namespace std;

struct Ember{

    string nev;
    int eletkor;

    Ember() {
        nev = "Ismeretlen";
        eletkor = 0;
    }

    Ember(string n, int i) {
        nev = n;
        eletkor = i;
    }
};

bool operator < (Ember e1, Ember e2) {

    // Mi van akkor ha két Józsi van?
    if (e1.nev == e2.nev) {
        return e1.eletkor < e2.eletkor;
    } else {
        return e1.nev < e2.nev;
    };
}

ostream &operator << (ostream &out, Ember e) {
    out << e.nev << " -> " << e.eletkor << endl;
}

int main () {
/*
    // -----vector-----

    vector<int> v = {3, 2, 6, 4};

    v.pop_back();
    v.push_back(10);
    for (auto i : v) {
        cout << i << endl;
    }

    // -----list-----

    list<int> l;
    l.push_back(3);
    l.push_front(4);
    for (auto i : l) {
        cout << i << endl;
    }

    // -----set-----

    set<int> s;
    s.insert(4);
    s.insert(3);
    s.insert(2);
    s.insert(4);
    s.insert(10);

    for(auto i : s) {
        cout << i << ",";
    }

    bool is3InSet = s.count(3);
    bool is5InSet = s.count(5);
    cout << endl << "3 benne van? " << is3InSet << endl;
    cout << "5 benne van? " << is5InSet << endl;

 */
    Ember peter("Péter", 20);
//    cout << peter;
    Ember jozsi("Józsi", 40);
    Ember jozsi2("Józsi", 10);
    Ember zsuzsa("Zsuza", 25);
    Ember janka("Janka", 31);
//    Ember* bela = new Ember("Béla", 70);
//    cout << *(bela) << endl;

/*
//    cout << peter.eletkor;
//    peter.nev = "Péter";
//    peter.eletkor = 20;

    // Irassuk ki ABC szerint!!

    //  vectorral: (#include <algorithm>)
//    vector<Ember> emberek = {peter, jozsi, zsuzsa, janka};
//
//    for (auto ember : emberek) {
//        cout << ember.nev << ": " << ember.eletkor << endl;
//    }
//
//    sort(emberek.begin(), emberek.end());
//
//    cout << "------------" << endl;
//    for (auto ember : emberek) {
//        cout << ember.nev << ": " << ember.eletkor << endl;
//    }

    // set-tel:

//    set<Ember> emberek;
//    emberek.insert(peter);
//    emberek.insert(jozsi);
//    emberek.insert(jozsi2);
//    emberek.insert(zsuzsa);
//    emberek.insert(janka);
//
//    for (auto ember : emberek) {
//        cout << ember.nev << ": " << ember.eletkor << endl;
//    }
*/

    // -------MAP-------
    // Feladat: vannak ezek az embereink, vannak kutyáik (névval azonosítva.
    // Tároljuk el a kutyákat az emberekhez! (hint: map!)
    // Adatok:
    //      Péter kutyái: Blöki, Adolf
    //      Józsi(10) kutyái:
    //      Józsi(40) kutyái: Hugó, Jimmy, Gandalf
    //      Zsuzsa kutyái: Bodri
    //      Janka kutyái:

    map<Ember, vector<string>> emberekhezKutya;
    vector<string> peterKutyai = {"Bloki", "Adolf"};
    emberekhezKutya[peter] = peterKutyai;

    vector<string> jozsiKutyai = {"Hugo", "Jimmy", "Gandalf"};
    emberekhezKutya[jozsi] = jozsiKutyai;

    vector<string> ures;
    emberekhezKutya[jozsi2] = ures;

    vector<string> zsuzsaKutyai = {"Bodri"};
    emberekhezKutya[zsuzsa] = zsuzsaKutyai;

    emberekhezKutya[janka] = ures;

//    for (auto emberKutyai : emberekhezKutya) {
//
//        cout << emberKutyai.first.nev << "-nek a kutyái: " << endl;
//        for (auto kutya : emberKutyai.second) {
//            cout << kutya << endl;
//        }
//        cout << "------------" << endl;
//    }

    // Írd ki Józsi kutyáit!
//    map<Ember, vector<string>>::iterator it = emberekhezKutya.find(jozsi); // ez ekvivalens az alatta lévővel csak geci ronda.
    auto it2 = emberekhezKutya.find(jozsi); // it2-ben most a memóriacím van.
    vector<string> kutyak = it2->second; // itt kértük el a memóriacím mögötti kutya vectort!

    for (auto i : kutyak) {
        cout << i << endl;
    }

}