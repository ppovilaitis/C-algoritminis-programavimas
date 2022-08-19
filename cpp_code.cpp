#include <iostream>
#include <string>
using namespace std;

class Interviu_Info { //deklaruojama interviu informacijos klase
public:
	
	int trukme=0;
	string data="";
	string miestopav="";
	string tema="";
	Interviu_Info* pNext; //nuoroda i sekanti interviu kintamaji
	Interviu_Info* pBack; //nuoroda i pries tai buvusi interviu kintamaji

	Interviu_Info(int trukme,string data, string miestopav, string tema) {
		this->data = data;
		this->trukme = trukme;
		this->miestopav = miestopav;
		this->tema = tema;
	}
	Interviu_Info() {}
};

class Inter_Info_list {
private:
	Interviu_Info* pFirst;
	Interviu_Info* pLast;
	string miestai[50]; //max miestu masyvas ivesciai
	int miestu_skaicius[50] = {0}; //masyvas ivestu miestu skaiciaus apskaiciavimui
	int miestu_kiekis = 0;
	bool arBuvoMiestas = false;
public:
	void interviu_reg(int trukme, string data, string miestopav, string tema) { // naujo interviu registravimas
		Interviu_Info* naujasInterviu = new Interviu_Info(trukme, data, miestopav, tema);

		if (pFirst == NULL) {                         // tikrina ar jau buvo ivestas bent vienas interviu, jei ne - prilygina ji pirmajam nariui
			pFirst = naujasInterviu;
		}
		else {                                        // jei buvo, tai prilygina ji paskutiniajam nariui
			pLast->pNext = naujasInterviu;
			naujasInterviu->pBack = pLast;
		}
		pLast = naujasInterviu;

		for (int i = 0; i < miestu_kiekis; i++) {      // tikrina ar yra daugiau nei 4 to paties miesto pavadinimai, jei taip - perduoda funkcija, skirta miesto rikiavimam is eiles (surikiuoti_miesta)
			if (miestai[i] == miestopav) {
				arBuvoMiestas = true;
				miestu_skaicius[i] = miestu_skaicius[i] + 1;
				if (miestu_skaicius[i] > 4) {
					surikiuoti_miesta(miestopav);
				}
				break;
			}
		}
		if (!arBuvoMiestas) {
			miestai[miestu_kiekis] = miestopav;
			miestu_skaicius[miestu_kiekis]++;
			miestu_kiekis++;
		}
	}
	void surikiuoti_miesta(string miestopav) { //Jeigu tame pačiame mieste atlikti 4 interviu, automatiskai perkeltia visus interviu greta vienas kito sarase is eiles po pirmojo tame mieste atlikto interviu
		Interviu_Info* temp=pFirst, *mainpoz, *dabartinis;
		while (1) {
			if (temp->miestopav == miestopav) {
				mainpoz = temp;
				break;
			}
		}
		temp = mainpoz;
		temp = temp->pNext;
		while (temp != NULL) {
			if (temp->miestopav == miestopav) {
				dabartinis = temp;
				if (dabartinis->pNext == NULL) {
					dabartinis->pBack->pNext = NULL;
					mainpoz->pNext->pBack = dabartinis;
					dabartinis->pNext = mainpoz->pNext;
					mainpoz->pNext = dabartinis;
					dabartinis->pBack = mainpoz;
					mainpoz = dabartinis;
				}
				else {
					dabartinis = temp;
					dabartinis->pNext->pBack = dabartinis->pBack;
					dabartinis->pBack->pNext = dabartinis->pNext;
					mainpoz->pNext->pBack = dabartinis;
					dabartinis->pNext = mainpoz->pNext;
					mainpoz->pNext = dabartinis;
					dabartinis->pBack = mainpoz;
					mainpoz = dabartinis;
				}
			}
			temp = temp->pNext;
		}
	}
	void interviu_isved() { //isveda visa interviu informacija
		Interviu_Info* temp = pFirst;
		while (temp != NULL) {
			cout << "Data: " << temp->data << " Miestas: " << temp->miestopav << " Tema: " << temp->tema << " Trukme:" << temp->trukme << endl;
			temp = temp->pNext;
		}
	}
	void trys_interviu() { // triju ilgiausiu interviu isvedimas
		Interviu_Info pirm, antr, trec;
		Interviu_Info* temp = pFirst;

		pirm = *temp; //prilyginam pirma nari
		temp = temp->pNext;

		while (temp != NULL) {
			if (pirm.trukme < temp->trukme) {
				trec = antr; //atiduodam nuo trecio, kai ateinantis "temp" objekto trukme didesne, tai viskas "paslenka" ir treciasis narys igauna antrojo reiksme, antrasis- pirmojo, o pirmasis narys gauna temp reiksme, taip issaugome praeitas trukmes 
				antr = pirm;
				pirm = *temp;
			}
			else if (antr.trukme < temp->trukme) {
				trec = antr;
				antr = *temp;
			}
			else if (trec.trukme < temp->trukme) {
				trec = *temp;
			}
			temp = temp->pNext;
		}
		cout << "Pirmasis ilgiausias interviu: " << "Data: " << pirm.data << " Miestas: " << pirm.miestopav << " Tema: " << pirm.tema << " Trukme:" << pirm.trukme << endl;
		cout << "Antrasis ilgiausias interviu: " << "Data: " << antr.data << " Miestas: " << antr.miestopav << " Tema: " << antr.tema << " Trukme:" << antr.trukme << endl;
		cout << "Treciasis ilgiausias interviu: " << "Data: " << trec.data << " Miestas: " << trec.miestopav << " Tema: " << trec.tema << " Trukme:" << trec.trukme << endl;
	}
	void interviu_tema() { // pagal zmogaus ivesta temos pavadinima, isveda visu interviu informacija, kurie turejo sia tema
		Interviu_Info* temp = pFirst;
		string temos_pav;
		cout << "Iveskite tema straipsnio sudarymui" << endl;
		cin >> temos_pav;
		while (temp != NULL) {
			if (temos_pav == temp->tema) {
				cout << "Data: " << temp->data << " Miestas: " << temp->miestopav << " Tema: " << temp->tema << " Trukme:" << temp->trukme << endl;
			}
			temp = temp->pNext;
		}
	}
	void istr_minut(int minut) { // istrina visus interviu is saraso, pagal mazesni nei ivesta laika minutemis
		Interviu_Info* temp = pFirst;
		Interviu_Info* naikinti;
		while (temp != NULL) {
			if (temp->trukme < minut) {
				naikinti = temp;
				if (temp->pBack != NULL) {// kai temp= pfirst
					temp->pBack->pNext = temp->pNext;
				}
				else {
					pFirst = temp->pNext;
				}
				if (temp->pNext != NULL) {// kai temp= plast
					temp->pNext->pBack = temp->pBack;
				}
				else {
					pLast = temp->pBack;
				}
				temp = temp->pNext;

				delete naikinti;
				continue;
			}
			temp = temp->pNext;
		}
	}	
};

int meniu() {
	int pasirinkimas;
	cout << "Pasirinkite meniu punkta ivesdami skaiciu:" << endl;
	cout << "1. Naujo interviu registravimas" << endl;
	cout << "2. Viso interviu saraso ivedimas" << endl;
	cout << "3. Triju ilgiausiai trukusiu interviu isvedimas" << endl;
	cout << "4. Straipsnio sudarymas pagal tema" << endl;
	cout << "5. Interviu pasalinimas is saraso pagal nurodyta trukme minutemis" << endl;
	cin.clear();
	cin >> pasirinkimas;
	return pasirinkimas;

}

int main()
{
	int trukmee;
	string miestopavv, temaa, dataa;
	Inter_Info_list* interviu_list = new Inter_Info_list();
	while (1) {
		switch (meniu())
		{
		case 1:
			cout << "Iveskite data:" << endl;
			cin >> dataa;
			cout << "Iveskite trukme:" << endl;
			cin >> trukmee;
			cout << "Iveskite miesto pavadinima:" << endl;
			cin >> miestopavv;
			cout << "Iveskite tema:" << endl;
			cin >> temaa;
			interviu_list->interviu_reg(trukmee, dataa, miestopavv, temaa);
			break;
		case 2:
			interviu_list->interviu_isved();
			break;
		case 3:
			interviu_list->trys_interviu();
			break;
		case 4:
			interviu_list->interviu_tema();
			break;
		case 5:
			cout << "Iveskite interviu trukme, uz kuria mazesnes trukmes bus istrinamos: " << endl;
			cin >> trukmee;
			interviu_list->istr_minut(trukmee);
			break;
		}
	}

}