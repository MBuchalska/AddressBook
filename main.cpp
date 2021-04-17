#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>

using namespace std;

struct DaneUzytkownika {
    int ID;
    string imie, nazwisko, telefon, mail, adres;
};

DaneUzytkownika KonwertujLinie (string linia);
int DodajOsobe(int liczbaOsob, vector<DaneUzytkownika>& osoby, int ostatnieID);
void WyszukajPoImieniu (const vector<DaneUzytkownika>& osoby, int liczbaOsob);
void WyszukajPoNazwisku (const vector<DaneUzytkownika>& osoby, int liczbaOsob);
void WyswietlWszystko (const vector<DaneUzytkownika>& osoby, int liczbaOsob);
int UsunOsobe (int liczbaOsob, vector<DaneUzytkownika>& osoby);
void EdytujRekordWedlugID (vector<DaneUzytkownika>& osoby, int liczbaOsob);

int main() {
    char znak;
    fstream znajomi;
    int liczbaZnajomych, licznik=0, LastID;
    string linia;
    vector <DaneUzytkownika> adresaci;
    DaneUzytkownika USER;           // tymczasowa zmienna na pojedynczy rekord.


    znajomi.open("znajomi_nowy_format.txt.",ios::in);

    if (znajomi.good()==false) {                    // sprawdzamy czy plik z danymi istnieje
        liczbaZnajomych=0;
        cout <<"Plik z lista adresowa nie istnieje. Dodaj najpierw kilku znajomych";
        system("pause");
    }

    else {
        while (getline(znajomi,linia)) {       // odczytuje kolejne linie dopoki getline nie zwtoci falsz
            USER=KonwertujLinie(linia);
            adresaci.push_back(USER);
            licznik++;
        }
        liczbaZnajomych=licznik;
        LastID=USER.ID;
    }
    znajomi.close();

    cout << "Witaj w swojej ksiazce adresowej" << endl;
    while (true) {
        cout << endl;
        cout << "Wybierz co chcesz zrobic" << endl;
        cout << "Menu glowne:" << endl;
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Koniec pracy" << endl;
        cin >> znak;

        system("cls");
        switch (znak) {
        case '1': {
            liczbaZnajomych=DodajOsobe(liczbaZnajomych, adresaci, LastID);
            LastID++;
        }
        break;
        case '2':
            WyszukajPoImieniu (adresaci,liczbaZnajomych);
            break;
        case '3':
            WyszukajPoNazwisku (adresaci,liczbaZnajomych);
            break;
        case '4':
            WyswietlWszystko (adresaci,liczbaZnajomych);
            break;
        case '5':{
            liczbaZnajomych=UsunOsobe(liczbaZnajomych, adresaci);
            int RozmiarWektora;
            RozmiarWektora=adresaci.size();
            if (adresaci[RozmiarWektora-1].ID<LastID) LastID=adresaci[RozmiarWektora-1].ID;
        }
            break;
        case '6':
            EdytujRekordWedlugID (adresaci,liczbaZnajomych);
            break;
        case '9': {
            cout<<"Koniec pracy. Dziekujemy za skorzystanie z programu"<<endl;
            exit(0);
        }
        break;
        }
    }
    return 0;

}
DaneUzytkownika KonwertujLinie (string linia) {
    DaneUzytkownika USER;
    int pozycja;
    string TempString="";

    pozycja=linia.find("|");
    TempString=linia.substr(0,pozycja);
    USER.ID=atoi(TempString.c_str());
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    USER.imie=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    USER.nazwisko=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    USER.telefon=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    USER.mail=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    USER.adres=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    return USER;
}

int DodajOsobe(int liczbaOsob, vector<DaneUzytkownika>& osoby, int ostatnieID) {
    fstream znajomi;
    DaneUzytkownika User;
    string DaneDoZapisu="";

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj dane osoby" << endl;

    if (liczbaOsob>ostatnieID) User.ID=liczbaOsob+1;
    else User.ID=ostatnieID+1;

    DaneDoZapisu=to_string(User.ID);
    DaneDoZapisu+="|";
    cout << "Imie: ";
    cin >> User.imie;
    DaneDoZapisu+=User.imie+"|";
    cout << "Nazwisko: ";
    cin >> User.nazwisko;
    DaneDoZapisu+=User.nazwisko+"|";
    cout << "Telefon: ";
    cin.sync();
    getline(cin,User.telefon);
    DaneDoZapisu+=User.telefon+"|";
    cout << "Mail: ";
    cin >> User.mail;
    DaneDoZapisu+=User.mail+"|";
    cin.sync();
    cout << "Adres: ";
    getline(cin,User.adres);
    DaneDoZapisu+=User.adres+"|";

    osoby.push_back(User);
    znajomi.open("znajomi_nowy_format.txt.",ios::out|ios::app);      // zapisze dane do pliku w jednej linii
    znajomi<<DaneDoZapisu<<endl;
    znajomi.close();
    cout << "Osoba zostala dodana do bazy" << endl;
    system("pause");
    return liczbaOsob+1;
}

void WyszukajPoImieniu (const vector<DaneUzytkownika>& osoby, int liczbaOsob) {
    system("cls");
    string wyszukajTo;
    cout << "Wyszukiwanie po imieniu" << endl;
    cout << "Podaj imie znajomego" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].imie==wyszukajTo) {
            cout<<"ID: "<< osoby[i].ID<<endl;
            cout<<"Imie: "<< osoby[i].imie<<endl;
            cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
            cout<<"Telefon: "<< osoby[i].telefon<<endl;
            cout<<"Mail: " << osoby[i].mail<<endl;
            cout<<"Adres: " << osoby[i].adres<<endl;
            cout<<endl;
        }
    }
    system("pause");
}
void WyszukajPoNazwisku (const vector<DaneUzytkownika>& osoby, int liczbaOsob) {
    system("cls");
    string wyszukajTo;
    cout << "Wyszukiwanie po nazwisku" << endl;
    cout << "Podaj nazwisko znajomego" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].nazwisko==wyszukajTo) {
            cout<<"ID: "<< osoby[i].ID<<endl;
            cout<<"Imie: "<< osoby[i].imie<<endl;
            cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
            cout<<"Telefon: "<< osoby[i].telefon<<endl;
            cout<<"Mail: " << osoby[i].mail<<endl;
            cout<<"Adres: " << osoby[i].adres<<endl;
            cout<<endl;
        }
    }
    system("pause");
}

void WyswietlWszystko (const vector<DaneUzytkownika>& osoby, int liczbaOsob) {
    system("cls");
    cout << "Wyswietlam dane wszystkich znajomych:" << endl;
    for (int i=0; i<liczbaOsob; i++) {
        cout<<"ID: "<< osoby[i].ID<<endl;
        cout<<"Imie: "<< osoby[i].imie<<endl;
        cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
        cout<<"Telefon: "<< osoby[i].telefon<<endl;
        cout<<"Mail: " << osoby[i].mail<<endl;
        cout<<"Adres: " << osoby[i].adres<<endl;
        cout<<endl;
    }
    system("pause");
}

int UsunOsobe (int liczbaOsob, vector<DaneUzytkownika>& osoby){
    int wyszukajTo, WskaznikRekordu=0;
    char znak;
    fstream znajomi;
    string TempString="";

    system("cls");

    cout << "Usuwanie rekordu" << endl;
    cout << "Podaj ID rekordu, ktory chcesz usunac:" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].ID==wyszukajTo) {
            cout<<"ID: "<< osoby[i].ID<<endl;
            cout<<"Imie: "<< osoby[i].imie<<endl;
            cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
            cout<<"Telefon: "<< osoby[i].telefon<<endl;
            cout<<"Mail: " << osoby[i].mail<<endl;
            cout<<"Adres: " << osoby[i].adres<<endl;
            WskaznikRekordu=i;
            cout<<endl;
        }
    }

    cout<<"Czy napewno chcesz usunac ten rekord? (t/n)" << endl;
    cin>> znak;

    if (znak=='t'){
    osoby.erase(osoby.begin()+WskaznikRekordu);
    liczbaOsob--;

    znajomi.open("znajomi_nowy_format.txt.",ios::out|ios::trunc);
    znajomi.close();

    znajomi.open("znajomi_nowy_format.txt.",ios::out|ios::app);
    for(int i=0; i<liczbaOsob; i++) {
        TempString="";
        TempString=to_string(osoby[i].ID);
        TempString+="|"+osoby[i].imie+"|"+osoby[i].nazwisko+"|";
        TempString+=osoby[i].telefon+"|"+osoby[i].mail+"|"+osoby[i].adres+"|";
        znajomi<<TempString<<endl;
    }
    znajomi.close();

    cout << "Rekord zostal usuniety" << endl;
    system("pause");
    return liczbaOsob;
    }

    else {
        cout << "Rekord nie zostal usuniety" << endl;
        system("pause");
        return liczbaOsob;
    }

}

void EdytujRekordWedlugID (vector<DaneUzytkownika>& osoby, int liczbaOsob) {
    int wyszukajTo, WskaznikRekordu=0;
    char znak;
    string TempString="";
    fstream znajomi;
    system("cls");

    cout << "Edycja rekordu" << endl;
    cout << "Podaj ID rekordu, ktory chcesz edytowac:" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].ID==wyszukajTo) {
            cout<<"ID: "<< osoby[i].ID<<endl;
            cout<<"Imie: "<< osoby[i].imie<<endl;
            cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
            cout<<"Telefon: "<< osoby[i].telefon<<endl;
            cout<<"Mail: " << osoby[i].mail<<endl;
            cout<<"Adres: " << osoby[i].adres<<endl;
            WskaznikRekordu=i;
            cout<<endl;
        }
    }

    cout << "Ktore dane chcesz edytowac:" <<endl;
    cout << "1. Imie" <<endl;
    cout << "2. Nazwisko" <<endl;
    cout << "3. Numer telefonu"<< endl;
    cout << "4. email" << endl;
    cout << "5. Adres"<< endl;
    cout << "6. Powrot do menu" <<endl;
    cout << endl;

    cin>> znak;
    switch(znak) {
    case '1': {
        cout << "Podaj imie: ";
        cin >> TempString;
        osoby[WskaznikRekordu].imie=TempString;
        cout << "Dane zostaly zmienione" << endl;
    }
    break;
    case '2': {
        cout << "Podaj nazwisko: ";
        cin >> TempString;
        osoby[WskaznikRekordu].nazwisko=TempString;
        cout << "Dane zostaly zmienione" << endl;
    }
    break;
    case '3': {
        cout << "Podaj numer telefonu: ";
        cin.sync();
        getline(cin,TempString);
        osoby[WskaznikRekordu].telefon=TempString;
        cout << "Dane zostaly zmienione" << endl;
    }
    break;
    case '4': {
        cout << "Podaj mail: ";
        cin >> TempString;
        osoby[WskaznikRekordu].mail=TempString;
        cout << "Dane zostaly zmienione" << endl;
    }
    break;
    case '5': {
        cout << "Podaj adres: ";
        cin.sync();
        getline(cin,TempString);
        osoby[WskaznikRekordu].adres=TempString;
        cout << "Dane zostaly zmienione" << endl;
    }
    break;
    case '6': {
        system("cls");
        cout << "Powrot do menu glownego" << endl;
    }
    break;
    }
    znajomi.open("znajomi_nowy_format.txt.",ios::out|ios::trunc);
    znajomi.close();

    znajomi.open("znajomi_nowy_format.txt.",ios::out|ios::app);
    for(int i=0; i<liczbaOsob; i++) {
        TempString="";
        TempString=to_string(osoby[i].ID);
        TempString+="|"+osoby[i].imie+"|"+osoby[i].nazwisko+"|";
        TempString+=osoby[i].telefon+"|"+osoby[i].mail+"|"+osoby[i].adres+"|";
        znajomi<<TempString<<endl;
    }
    znajomi.close();

    system("pause");
}
