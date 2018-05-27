//
// Created by hunor on 2018.05.26..
//
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

struct Ember {
    int kor;
    string nev;
    int kutyakSzama;
//        Ember() {
//            kor = 0;
//            nev = "Ismeretlen";
//        }

    Ember(int k, string n) {
        kor = k;
        nev = n;
        kutyakSzama = 0;
    }

    Ember(int k, string n, int ku) {
        kor = k;
        nev = n;
        kutyakSzama = ku;
    }
};

struct Kutya {
    string nev;
    int kor;

    Kutya() {
        nev = "iseretlen";
        kor = -1;
    }

    Kutya(string n, int k) {
        nev = n;
        kor = k;
    }
};


struct Tulajdonsagok {
    int kor;
    int kutyakSzama;
    string lakcim;
    Tulajdonsagok() {
        kor = 0;
        kutyakSzama = 0;
        lakcim = "nem ismert";
    }
    Tulajdonsagok(int k, int ku,  string l) {
        kor = k;
        kutyakSzama = ku;
        lakcim = l;
    }
};

bool operator < (Ember e1, Ember e2) {
    if (e1.kutyakSzama == e2.kutyakSzama) {
        return e1.kor < e2.kor;
    }
    return e1.kutyakSzama < e2.kutyakSzama;
}

int main(){

    vector<int> v;
    list<int> l;

//    --------------VECTOR--------------
//    v.push_back(1);
//    v.push_back(2);
//    v.push_back(3);
//    v.push_back(4);
//    v.pop_back();
//
//    for (int i = 0; i < v.size(); ++i) {
//        cout << v[i] << endl;
//    }
//
//    for (auto j : v) {
//        cout << j << endl;
//    }

//    --------------LIST--------------

//    if (l.empty()) {
//        cout << "ÜRES" << endl;
//    } else {
//        cout << "NEM ÜRES" << endl;
//    }

//    l.push_back(5);
//    l.push_back(6);
//    l.push_back(7);
//    l.push_back(7);
//    l.push_back(7);
//    l.push_back(7);
//    l.push_back(8);
//    cout << "Back: " << l.back() << endl;
//    l.pop_front();
//    cout << "Front: " << l.front() << endl;
//    l.push_front(10);
//    l.remove(7);
//
//    for (list<int>::iterator iterator1 = l.begin(); iterator1 != l.end(); iterator1++) {
//        cout << *iterator1 << endl;
//    }
//
//    if (l.empty()) {
//        cout << "ÜRES" << endl;
//    } else {
//        cout << "NEM ÜRES" << endl;
//    }

//    for (auto i : l) {
//        cout << i << endl;
//    }

//    --------------SET--------------

//    set<int> s = {5,4,2,3,1};
//
//    s.insert(8);
//
//    for(auto i : s) {
//        cout << i << ";";
//    }
//    cout << endl;
//
//    auto it = s.find(5);
//    s.erase(it);
//
//    for(auto i : s) {
//        cout << i << ";";
//    }
//    cout << endl;
//
//    cout << "3:" << s.count(3) << endl;
//    cout << "7:" << s.count(7) << endl;

    // Saját struct set-be:



//    Ember e;
//    cout << e.nev << " , " << e.kor << endl;
//    Ember e1(65, "Feri");
//    cout << "Név: " << e1.nev << " , " << e1.kor << " Kutyak: " << e1.kutyakSzama << endl;

//    Ember e2(25, "Béla", 2);
//    cout << "Név: " << e2.nev << " , " << e2.kor << " Kutyak: " << e2.kutyakSzama << endl;

//    Ember e3(30, "Anna", 2);
//    cout << "Név: " << e2.nev << " , " << e2.kor << " Kutyak: " << e2.kutyakSzama << endl;

//    set<Ember> emberek;
//    cout << "size: " << emberek.size() << endl;
//    emberek.insert(e1);
//    cout << "size: " << emberek.size() << endl;
//    emberek.insert(e2);
//    cout << "size: " << emberek.size() << endl;
//    emberek.insert(e3);
//    cout << "size: " << emberek.size() << endl;
//
//    for (auto i : emberek) {
//        cout << i.nev << "," << i.kor << "," << i.kutyakSzama << endl;
//    }

//    --------------MAP--------------
//    map<int,string> m;
//
//    m[3] = "harom";
//    m[0] = "nulla";
//    m[2] = "ketto";
//
//    for (auto i : m) {
//        cout << i.first << " : " << i.second << endl;
//    }

    Ember e1(65, "Feri");
    Ember e2(25, "Béla", 2);
    Ember e3(30, "Anna", 2);

//    map<string, Tulajdonsagok> emberek;
//    emberek["Béla"] = Tulajdonsagok(25,2,"Diófa utca 3.");
//    emberek["Feri"] = Tulajdonsagok(65,0,"Móra Ferenc utca 5.");
//    emberek["Anna"] = Tulajdonsagok(30,3,"Akácfa utca 100.");
//    for (auto i : emberek) {
//        cout << i.first << " --> " << i.second.kor << "," << i.second.kutyakSzama << "," << i.second.lakcim << endl;
//    }
    map<Ember,vector<Kutya>> emberekKutyai;

    Kutya bloki("Blöki", 4);
    Kutya szuszi("Szuszi", 6);
    vector<Kutya> belaKutyai = {bloki,szuszi};

    Kutya aprod("Apród", 3);
    Kutya leci("Léci", 10);
    vector<Kutya> annaKutyai = {aprod,leci};
    vector<Kutya> feriKutyai;

    emberekKutyai[e1] = feriKutyai;
    emberekKutyai[e2] = belaKutyai;
    emberekKutyai[e3] = annaKutyai;

    for (auto jelenlegiGazda : emberekKutyai) {
        cout << "Név:"
             << jelenlegiGazda.first.nev
             << " --> ";
        for (auto jelenlegiKutya : jelenlegiGazda.second) {
            cout << jelenlegiKutya.nev << "," << jelenlegiKutya.kor << endl;
        }
        cout << endl;
    }
}
