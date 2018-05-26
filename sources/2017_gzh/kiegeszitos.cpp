//
// Created by hunor on 2018.05.26..
//
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugró érvényes, amely nem tartalmaz semmilyen változtatást a main()-ben,
        ami vagy nem tartalmaz komment blokkot, vagy a komment blokk vége ott marad ahol van és csak az eleje megy lejjebb, és csak ez az egyetlen, összefüggo komment blokk van a main()-ben.
    - az "ellenoriz"-en kívül nem tartalmaz #define sorokat, és azt sem szabad megváltoztatni
*/

// Innentol
    int hatezmi = 0;
    struct A {
        int x;

        A() {
            hatezmi++;
            x = 42;
        }

        A(int _x) {
            x = _x;
        }

        bool operator<(A other) const {
            return x > other.x;
        }

        void setB(int b) {
            x = b;
        }

        int& getB() {
            return x;
        }

        ~A() {
            hatezmi--;
        }


    };
// Idaig

int main()
{
    int pont = 0;

    A a;
    ellenoriz(a.x==42 , pont)

    A b(1337);
    ellenoriz(b.x==1337 , pont)

    set<A> s;
    s.insert(a);
    s.insert(b);
    s.insert(a);
    ellenoriz(s.size()==2, pont)

    a.setB(2);
    b.setB(1);
    ellenoriz(a.getB()==2 && b.getB()==1, pont)

    b.getB()=3;
    ellenoriz(b.getB()==3, pont)
    ellenoriz(b.getB()==3, pont)

    {
        A c;
        hatezmi = 4;
    }
    ellenoriz(hatezmi == 3, pont)
    ellenoriz(hatezmi == 3, pont)
    
    A d;
    ellenoriz(hatezmi == 4, pont)
    ellenoriz(hatezmi == 4, pont)

    cout << pont << " / 10 pont" << endl;
    return 0;
}
