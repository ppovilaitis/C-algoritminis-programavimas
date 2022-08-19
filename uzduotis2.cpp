#include <iostream>
#include <string>

using namespace std;


class C_Sergantysis {
public:
    string pavarde;
    C_Sergantysis* pKitas;

    C_Sergantysis(string pavarde) : pavarde(pavarde) {}
};

class Ligos_info {
public:
    string ligos_pav;
    int gyd_trukme;
    Ligos_info* pKitas;
    int kiek_serganciu = 0;

    C_Sergantysis* pFirst; //hadleris

    Ligos_info(string ligos_pav, int gyd_trukme) : ligos_pav(ligos_pav), gyd_trukme(gyd_trukme) {}

    void iterpti_serganti(string pavarde) {
        C_Sergantysis* nauja_liga = new C_Sergantysis(pavarde);
        if (pFirst == NULL) {
            pFirst = nauja_liga;
        }
        else {
            C_Sergantysis* dabartinis = pFirst;
            if (nauja_liga->pavarde < dabartinis->pavarde) {
                pFirst = nauja_liga;
                pFirst->pKitas = dabartinis;
            }
            else {
                while (dabartinis->pKitas != NULL) {
                    if (nauja_liga->pavarde > dabartinis->pavarde && nauja_liga->pavarde < dabartinis->pKitas->pavarde) {
                        C_Sergantysis* temp = dabartinis->pKitas; //kad neprarasciau objekto ejusio dabartinis->pkitas
                        dabartinis->pKitas = nauja_liga;
                        nauja_liga->pKitas = temp;
                        break;
                    }           
                        dabartinis = dabartinis->pKitas;
                }
                dabartinis->pKitas = nauja_liga; //jei dabartinis-> pkitas butu Null, kad priskirtu i gala saraso
            }
        }
        kiek_serganciu++;
    }

    ~Ligos_info() {
        C_Sergantysis* dabartinis = pFirst;
        if (dabartinis == NULL) return; //jei pirmojo zmogaus net nera
        while (dabartinis->pKitas != NULL) {
            C_Sergantysis* bomba = dabartinis;
            dabartinis = dabartinis->pKitas;
            delete bomba;
        }
        delete dabartinis;
    }

    C_Sergantysis* rastiSergatiPraeit(string pavard) { 
        C_Sergantysis* dabartinis = pFirst;
        while (dabartinis->pKitas != NULL) {  
            if (dabartinis->pKitas->pavarde == pavard) {
                return dabartinis;
            }
            dabartinis = dabartinis->pKitas;
        }
        return NULL;
    }

    void serganciojo_salinimas(string pavard) {
        if (pFirst->pavarde==pavard) {
            C_Sergantysis* trinamasis = pFirst;
            pFirst = pFirst->pKitas;
            delete trinamasis;
            kiek_serganciu--;
            return;
        }
        C_Sergantysis* rastas_serg_Praeit = rastiSergatiPraeit(pavard);
        if (rastas_serg_Praeit == NULL) {
            cout << "Nera tokio serganciojo" << endl;
            return;
        }
        C_Sergantysis* trinamasis = rastas_serg_Praeit->pKitas;
        rastas_serg_Praeit->pKitas = rastas_serg_Praeit->pKitas->pKitas;
        delete trinamasis;
        kiek_serganciu--;
    }
};

class Ligu_sar {
public:
    Ligos_info* pFirst;//handleris
    int ligu_kiekis = 0;
    
    Ligos_info* prideti_liga(string pav, int trukme) {
        Ligos_info* nauja_liga = new Ligos_info(pav, trukme);
        if (pFirst == NULL) {
            pFirst = nauja_liga;
        }
        else {
            Ligos_info* dabartinis = pFirst;
            while (dabartinis->pKitas != NULL) {
                dabartinis = dabartinis->pKitas;
            }
            dabartinis->pKitas = nauja_liga;
        }
        ligu_kiekis++;
        return nauja_liga;
    }

    Ligos_info* rastiLiga(string liga) { //ligu paieska
        Ligos_info* dabartinis = pFirst;
        while (dabartinis != NULL) { // iesko ar tokia liga jau buvo sarase
            if (dabartinis->ligos_pav == liga) {
                return dabartinis;
            }
            dabartinis = dabartinis->pKitas;
        }
        return NULL; //jeigu nerado ligos
    }

    Ligos_info* rastiLigaPraeit(string liga) { //ligu paieska
        Ligos_info* dabartinis = pFirst;
        while (dabartinis->pKitas != NULL) { // iesko ar tokia liga jau buvo sarase
            if (dabartinis->pKitas->ligos_pav == liga) {
                return dabartinis;
            }
            dabartinis = dabartinis->pKitas;
        }
        return NULL; //jeigu nerado ligos
    }

    void pridetiLigoni(string pavard, string liga) {
        Ligos_info* pLiga = rastiLiga(liga);
        int trukme;
        if (pLiga == NULL) {
            
            cout << "Irasykite ligos trukme:" << endl;
            cin >> trukme;
            pLiga = prideti_liga(liga, trukme);
        }
        pLiga->iterpti_serganti(pavard);
    }
    
    void isvestiSar(int trukme) {
        Ligos_info* dabartinis = pFirst;
        while (dabartinis != NULL) {
            if (dabartinis->gyd_trukme >= trukme) {
                cout << dabartinis->ligos_pav << endl;
            }
            dabartinis = dabartinis->pKitas;
        }
    }

    void ligoniu_isv(string liga) {
        Ligos_info* rastas = rastiLiga(liga);
        if (rastas == NULL) {
            cout << "Tokios ligos nera" << endl;
        }
        else {
            C_Sergantysis* dabartinis = rastas->pFirst;
            while (dabartinis != NULL) {
                cout << dabartinis->pavarde << endl;
                dabartinis = dabartinis->pKitas;
            }
        }
    }

    void isvesti_Sk(int sk) { //4 dalis
        Ligos_info* dabartinis = pFirst;
        while (dabartinis != NULL) {
            if (sk == dabartinis->kiek_serganciu) {
                cout << dabartinis->ligos_pav << endl;
            }
            dabartinis = dabartinis->pKitas;
        }
    }

    void ligos_salinimas(string liga, string pavard) {
        Ligos_info* rasta_liga = rastiLiga(liga);//Bandoma rasti liga

        if (rasta_liga == NULL) {
            cout << "Nera tokios ligos" << endl;
            return;
        }// Ar ji buvo rasta?

        if (rasta_liga->pFirst != NULL) {// Jei rastos ligos pirmasis sergantysis buvo rastas, salinamas nurodytas per parametrus sergantysis
            rasta_liga->serganciojo_salinimas(pavard);
        }
        if (rasta_liga->kiek_serganciu == 0) {// Jei serganciuju kiekis yra 0, tai istrinamas objektas(liga)
            if (pFirst->ligos_pav == liga) {// Kai nurodyta liga yra pFirst(pati pirmoji)
                Ligos_info* trinamasis = pFirst;
                pFirst = pFirst->pKitas;
                delete trinamasis;
                ligu_kiekis--;
                return;
            }
            Ligos_info* rastas_serg_Praeit = rastiLigaPraeit(liga);
            Ligos_info* trinamasis = rastas_serg_Praeit->pKitas;
            rastas_serg_Praeit->pKitas = rastas_serg_Praeit->pKitas->pKitas;
            delete trinamasis;
            ligu_kiekis--;
        }
    }

    ~Ligu_sar() {
        Ligos_info* dabartinis = pFirst;
        if (dabartinis == NULL) return; //jei pirmojo zmogaus net nera
        while (dabartinis->pKitas != NULL) {
            Ligos_info* bomba = dabartinis;
            dabartinis = dabartinis->pKitas;
            delete bomba;
        }
        delete dabartinis;
    }
        
};

int meniu() {
    cout << "[1] Ivesti ligoni ir liga" << endl;
    cout << "[2] Isvesti visu ligu sarasa" << endl;
    cout << "[3] Isvesti visu ligu sarasa pagal nurodyta trukme" << endl;
    cout << "[4] Ivesti visu ligoniu sarasa, pagal abecele" << endl;
    cout << "[5] Isvesti ligu sarasa, kuriomis serga nurodytas skaicius ligoniu" << endl;
    cout << "[6] Pasalinti nurodyta ligoni ir liga is saraso" << endl;
    string pasirinkimas;
    cin >> pasirinkimas;
    if (pasirinkimas =="") { //jei ivestas pasirinkimas yra tuscias
        return NULL;
    }
    return stoi(pasirinkimas); //pakeiciu string i integeri
}

int main()
{
    Ligu_sar* ligu_sar = new Ligu_sar();
    string pavarde, ligos_pav;
    string trukme, kiekis_Serganciu;
    while (1) {

        switch (meniu())
        {
        case 1:
            cout << "Iveskite ligonio pavarde:" << endl;
            cin >> pavarde;
            cout << "Iveskite ligos pavadinima:" << endl;
            cin>>ligos_pav;

            ligu_sar->pridetiLigoni(pavarde, ligos_pav);
            break;
        case 2:
            ligu_sar->isvestiSar(0);
            break;
        case 3:

            cout << "Iveskite ligos trukme:" << endl;
            cin >> trukme;
            if (stoi(trukme) != NULL) {
                ligu_sar->isvestiSar(stoi(trukme));
            }

            break;
        case 4:
            cout << "Iveskite ligos pavadinima:" << endl;
            cin >> ligos_pav;
            ligu_sar->ligoniu_isv(ligos_pav);
            break;
        case 5:
            cout << "Iveskite ligoniu skaiciu" << endl;
            cin >> kiekis_Serganciu;
            if (stoi(kiekis_Serganciu) != NULL) {
                ligu_sar->isvesti_Sk(stoi(kiekis_Serganciu));
            }
            break;
        case 6:
            cout << "Nurodykite ligos pavadinima: " << endl;
            cin >> ligos_pav;
            cout << "Nurodykite ligonio pavarde" << endl;
            cin >> pavarde;
            ligu_sar->ligos_salinimas(ligos_pav, pavarde);
            break;
        case 7:
            delete ligu_sar;
            break;
        }
    }
    
}

