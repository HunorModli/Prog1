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


int main()
{
    earth SR;
    SR.new_investor("Germany", "Saeder-Krupp", "Lofwyr");
    SR.new_investor("Germany", "Ares Europe", "Soren Johannsen");
    SR.new_investor("USA", "Ares Macrotechnology", "Arthur Vogel");
    SR.new_investor("USA", "Ares Macrotechnology", "Damien Knight");
    //SR.new_investor("USA", "Ares Macrotechnology", "Guido Cantarelli");
    //SR.new_investor("USA", "Ares Macrotechnology", "Soren Johannsen");
    SR.new_investor("USA", "Ares Macrotechnology", "Ares Arms");                        /// Az itt látható program a feladat legtöbb követelményének eleget tesz. Bár vannak olyan részek, amik kimaradtak (Pl az összes magánszemény és cég kiíratása),
    SR.new_investor("USA", "Ares Arms", "Guido Cantarelli");                            /// ezek vagy kicsit más formátumban (pl. dump) megvannak a programban, vagy nagyon egyszerűen bele lehetne írni őket egy pár perc alatt.
    SR.new_investor("USA", "Ares Macrotechnology", "Ares Europe");                      /// Ennek a programnak a lényege az volt, hogy a legfontosabb részfeladatokra és a bonyolultabb problémákra egy 3 óra alatt megírható megoldást találjak, és ez a feladatok nagy többségénél sikerült is.
    SR.new_investor("Japan", "Renraku Computer Systems", "Haruhiko Nakada");            /// Az egyetlen dolog, amit nem tudtam 3 óra alatt megoldani, az a többszörös leányvállalatok kezelése (három- vagy többemeletes cégek), bár mivel a feladat nem említette, hogy erre is szükség lenne, ezért vaószínűleg max. 2-3 pontot vonnának le.
                                                                                        /// Amennyiben van rá igény, megpróbálhatom megcsinálni a többszörös leányvállalatokat is, bár az már biztosan nem férne bele a három órába.
    //SR.save();
    //SR.load();

    SR.retrieve_inv("Arthur Vogel");
    SR.retrieve_inv("Guido Cantarelli");                                                /// Mindenkinek sikeres készülést!
    SR.retrieve_inv("Soren Johannsen");
    SR.retrieve_corp("Saeder-Krupp");
    SR.retrieve_corp("Ares Macrotechnology");

    SR.retrieve_country("USA");
    SR.retrieve_country("Germany");
    SR.retrieve_country("Japan");

    //SR.sub_of_what("Ares Arms");
    //SR.sub_of_what("Ares Macrotechnology");
    //SR.sub_of_what("Ares Europe");
    SR.dump();
    return 0;
}
