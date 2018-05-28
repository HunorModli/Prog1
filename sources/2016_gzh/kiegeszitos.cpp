#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugró érvényes, amely nem tartalmaz semmilyen változtatást a main()-ben,
        és már nincs benne kommentezve semmi
    - az "ellenoriz"-en kívül nem tartalmaz #define sorokat, és azt sem szabad megváltoztatni
*/

// Innentol

struct A {
    int x;
    A() {
        x = 42;
    }
    A(int _x) {
        x = _x;
    }
};

struct B {
    string mezo1;
    string mezo2;

    B(string s1, string s2) {
        mezo1 = s1;
        mezo2 = s2;
    }
};

bool operator == (B b1, B b2) {
    return (b1.mezo1 == b2.mezo1 && b1.mezo2 == b2.mezo2);
}

bool operator != (B b1, B b2) {
    return (b1.mezo1 != b2.mezo1 || b1.mezo2 != b2.mezo2);
}

bool operator < (B b1, B b2) {
    if (b1.mezo1 == b2.mezo1) {
        return b1.mezo2 < b2.mezo2;
    }
    return b1.mezo1 < b2.mezo1;
}

//struct Ember {
//    string nev;
//    int kor;
//};

bool operator < (A a1, A a2) {
    return  a1.x < a2.x;
}

ostream &operator << (ostream &o, A a) {
    o << a.x;
    return o;
}

//ostream &operator << (ostream &o, Ember e) {
//    o << "Nev: " << e.nev << " -> " << e.kor << endl;
//    return o;
//}
// Idaig


int main()
{
    int pont = 0;

//    Ember e;
//    e.nev = "Bela";
//    e.kor = 40;
//    cout  << e;

    A a;
    ellenoriz(a.x==42 , pont)

    A b(1337);
    ellenoriz(b.x==1337 , pont)

    vector<A> v;
    v.push_back(A(3));
    v.push_back(A(2));
    v.push_back(A(1));
    sort(v.begin(), v.end());
    ellenoriz(v[0].x==1 && v[1].x==2 && v[2].x==3, pont)

    stringstream ss;
    ss << a;
    ellenoriz(ss.str()=="42", pont)

    stringstream ss2;
    ss2 << a << "!";
    ellenoriz(ss2.str()=="42!", pont)

    B b1("ab","cd");
    B b1m("ab","cd");
    B b2("abc","d");
    ellenoriz(b1m==b1 && !(b1==b2), pont)
    ellenoriz(b1!=b2, pont)

    map<B, int> m;
    m[b1]=1;
    m[b2]=2;
    m[b1m]=3;

    ellenoriz(m.at(b2)==2, pont)
    ellenoriz(m.size()==2, pont)
    ellenoriz(m.at(b1)==3, pont)

    cout << pont << " / 10 pont" << endl;
    return 0;
}
