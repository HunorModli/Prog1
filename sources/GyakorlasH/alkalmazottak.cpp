#include <iostream>
#include <fstream>
#include <map>

using namespace std;

/**     Gyakoroljunk még egy kis fájlkezelést! Adott egy "Raw Data.txt" nevű file,
 *      mely egy cég 100 alkalmazottjának adatait tartalmazza a következőképp:
 *
 *      Név,Telefonszám,Email cím,Születési Idő,Azonosítószám
 *  Pl: Michael Cortez,(0141) 554 7341,02/22/1979,placerat@sed.edu,1663061503199
 *      Figyelj rá, hogy a telefonszám többféle formátumban is megadható!
 *      Olvasd be a fileból az adatokat, egy (vagy több) adatszerkezetbe, majd végezd el a feladatokat:
 *
 *      1) Irasd ki a cég dolgozóit abc sorrendben, az elérhetőségükkel együtt (tel, email).
 *      2) Irasd ki a cég dolgozóit születési sorrendben egy fileba.
 *      3) Tudj hozzáadni az adatbázishoz. Ellenőrizd le az 1., és 2. feladatokkal.
 *      4) Keresd meg azt az évet amikor a legtöbb dolgozó született.
 */

struct Ido {                /// Csinálunk egy típust az időnek, a könnyebb kezelés érdekében.
    int honap, nap, ev;
};

struct Dolgozo {            /// Csinálunk egy Dolgozó osztályt.
    string nev,
            telefonszam,
            email;
    Ido    szuletesiDatum;
    string ID;
};

class Ceg {                         /// Létrehozzuk a Cég osztályt
    map<string,Dolgozo> nevKulcs;   /// Kell egy névszerinti rendezés -> a név a kulcs.
    map<Ido,Dolgozo> idoKulcs;      /// Kell egy születési dátum szerinti rendezés -> az idő a kulcs.
public:
    Ceg() {
        ifstream f("alkalmazottak.csv");  /// Megnyitjuk a fájlt, megnézzük hogy jó-e.
        if (!f.good()) {
            cout << "Hiba a fileban" << endl;
        }
        string tmp, mapKulcs;       /// A tmp-be megy az első felesleges sor, a mapKulcs-ba a név.
        getline(f,tmp);             /// Eldobjuk az első sort.
        char kuka;                  /// Ezzel fogjuk eldobni a ','-ket, és a dátumot elválasztó '/'-t.
        Dolgozo dolgTmp;            /// Valamint csinálunk egy Dolgozót, és egy Időt, amikobe olvasunk.
        Ido idoTmp;
        while (getline(f,mapKulcs,',')) {       /// Beolvasunk a két névbe.
            dolgTmp.nev = mapKulcs;
            getline(f,dolgTmp.telefonszam,','); /// Majd a telefonszámba
            getline(f,dolgTmp.email,',');       /// És e-mailbe.

            /**     Itt kicsit megint trükkös, kell olvasni egyszer a hónapba,
                    Majd jön egy '\' karakter, amit berakuknk a kukába.
                    Ez ismételjük a többi adattaggal, majd a végén beolvassuk a ','-t. */
            f >> idoTmp.honap >> kuka >> idoTmp.nap >> kuka >> idoTmp.ev >> kuka;

            dolgTmp.szuletesiDatum = idoTmp;    /// A Dolgozó változónak értékül adjuk a most beolvasott Ido-t.
            getline(f,dolgTmp.ID);              /// Majd végül beolvasunk az ID-be.
            nevKulcs[mapKulcs] = dolgTmp;       /// És hozzáadjuk a két map-hez az elemeket.
            /** FONTOS!
             Ahoz, hogy Ido tíőusú változót kulcsul adjunk egy mapnek definiálnuk kell két
             Ido típusú változó között a '<' operátort. (Implementáció lent) */
            idoKulcs[idoTmp] = dolgTmp;
        }
        f.close();      /// Legvégül bezárjuk a fájlt.
    }

    void elsoFeladat() {            /// Az adatszerkezetünknek hála, mostmár csak végig kell iterálni
        for (auto a : nevKulcs) {   /// A név szerint rendezett map-en, s kiiratni konzolra.
            cout << a.second.nev << " tel.: " << a.second.telefonszam
                 << " e-mail: " << a.second.email << endl;
        }
    }

    void masodikFeladat() {         /// Ugyanolyan könnyű a feladat mint az előbb, csak itt fájlba kell írni.
        ofstream oFile("idoSorrend.txt");   /// Megnyitunk egy fájlt.
        for (auto a:idoKulcs) {             /// Majd végigiterálunk a fájlon, és kiiratjuk az adatokat.
            oFile << a.second.szuletesiDatum.ev << " " << a.second.szuletesiDatum.honap
                  << " " << a.second.szuletesiDatum.nap << " : " << a.second.nev <<  endl;
        }
        oFile.close();      /// Végül bezárjuk a fájlt.
    }

    void harmadikFeladat() {
        Dolgozo d;              /// Csinálunk egy Dolgozót, és egy Időt, mint abeolvasásnál.
        Ido i;
        cout << "Add meg a nevet:" << endl;     /// Majd bekérjük az adatokat.
        getline(cin,d.nev);
        cout << "Add meg a telefonszamot:" << endl;
        getline(cin,d.telefonszam);
        cout << "Add meg az email cimet:" << endl;
        getline(cin,d.email);
        cout << "Add meg a szuletesi datumot:" << endl << "ev: ";
        cin >> i.ev;
        cin.ignore();           /// Az ignore() kell, mivel a cin >> beolvasásnál az enter miatt egy newline
        /// karakter ('\n') ottmarad  az input buffer-ben, ezt így lehet eltüntetni.
        cout << "honap: ";
        cin >> i.honap;
        cin.ignore();
        cout << "nap: ";
        cin >> i.nap;
        cin.ignore();
        d.szuletesiDatum = i;
        cout << "Add meg az azonositot:" << endl;
        getline(cin,d.ID);
        nevKulcs[d.nev] = d;    /// Az adatok bekérése utén hozzáadjuk a map-ekhez.
        idoKulcs[i] = d;
    }

    void negyedikFeladat() {
        /** A feladat könnyű megoldásához csinálunk egy mapet, ahol a
            kulcs az év, az érték pedig, hogy hányszor fordul elő. */
        map<int,int> evekhezElofordulas;
        for (auto a : idoKulcs) {        /// Végimegyünk az idő kulcsú mapen
            if (evekhezElofordulas.count(a.first.ev)) {     /// Ha már hozzá van adva az adott év
                evekhezElofordulas[a.first.ev]++;           /// akkor hozzáadunk az értékhez.
            } else {
                evekhezElofordulas[a.first.ev] = 1;         /// Ha nincs akkor létrhozzuk 1-el.
            }
        }

        /// Ezek után kell egy maximumkeresés az értékek között.
        map<int,int>::iterator it = evekhezElofordulas.begin();
        int ev = it->first;
        int legtobb = it->second;
        for (auto a : evekhezElofordulas) {
            if (a.second > legtobb) {
                ev = a.first;
                legtobb = a.second;
            }
        }
        cout << "Ebben az evben szuletett a legtobb dolgozo: " << ev << " (" << legtobb << ")" << endl;

    }
};
/** A '<' operátort meg kell írni két Ido típusra, hogy mapnek
    kulcsként lehessen adni. */
bool operator < (const Ido &i1,const  Ido &i2) {
    if (i1.ev == i2.ev) {            /// Először megnézzük az év szerinti egyezést
        if (i1.honap == i2.honap) {  /// Majd hónap szerintit is.
            return i1.nap < i2.nap;  /// Ha mindkettő egyezik akkor a nap dönt.
        }
        return i1.honap < i2.honap;  /// Ha csak az év akkor a hónap.
    }
    return i1.ev < i2.ev;            /// Ha nem egyezik az év akkor az év.
}


int main() {
    Ceg ceg;
    bool fut = true;    /// Majd írunk egy kezdetleges user interface-t.
    int userInput;
    while (fut) {
        cin >> userInput;
        cin.ignore();
        switch(userInput) {
            case 1:
                ceg.elsoFeladat();
                break;
            case 2:
                ceg.masodikFeladat();
                break;
            case 3:
                ceg.harmadikFeladat();
                break;
            case 4:
                ceg.negyedikFeladat();
                break;
            case 0:
                fut = false;
                break;
            default:
                cout << "Hibas input, probalj masikat!" << endl;
                break;
        }
    }
}