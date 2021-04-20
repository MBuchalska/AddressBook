#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>

using namespace std;

struct DaneUzytkownika {
    int UserID;
    string UserName, UserPassword;
};

struct DaneAdresata {
    int IDAdresat;
    string imie, nazwisko, telefon, mail, adres;
};

DaneUzytkownika PrzepiszDoWektora (string linia);
int RejestrujUzytkownika (int liczbaUzytkownikow, vector<DaneUzytkownika>& users);
DaneAdresata KonwertujLinie (string linia);
int DodajOsobe(int liczbaOsob, vector<DaneAdresata>& osoby, int ostatnieIDAdresat);
void WyszukajPoImieniu (const vector<DaneAdresata>& osoby, int liczbaOsob);
void WyszukajPoNazwisku (const vector<DaneAdresata>& osoby, int liczbaOsob);
void WyswietlWszystko (const vector<DaneAdresata>& osoby, int liczbaOsob);
int UsunOsobe (int liczbaOsob, vector<DaneAdresata>& osoby);
void EdytujRekordWedlugID (vector<DaneAdresata>& osoby, int liczbaOsob);

int main() {
    char znak;
    fstream uzytkownicy, znajomi;
    int liczbaUzytkownikow, TempUserID=0;
    int liczbaZnajomych, licznik=0, LastIDAdresat;
    string linia;
    vector <DaneUzytkownika> users;
    vector <DaneAdresata> adresaci;
    DaneUzytkownika USER;           // zmienna na pojedynczego uzytkownika
    DaneAdresata ADRESAT;           // tymczasowa zmienna na pojedynczego adresata

    cout << "Witaj w swojej ksiazce adresowej" << endl;

    while (true) {
        cout<< endl;
        cout << "Co chcesz zrobic:" << endl;
        cout << "1. Rejestracja nowego uzytkownika" << endl;
        cout << "2. Logowanie uzytkownika" << endl;
        cout << "9. Koniec pracy" << endl;
        cin >> znak;

        system("cls");

        uzytkownicy.open("Uzytkownicy.txt.",ios::in);

        if (uzytkownicy.good()==false) {                    // sprawdzamy czy plik z danymi istnieje
            liczbaUzytkownikow=0;
            cout <<"Nie ma jeszcze zadnych zarejestrowanych uzytnowniow. Zarejstruj sie." << endl;
            system("pause");
        }

        else {
            while (getline(uzytkownicy,linia)) {       // odczytuje kolejne linie dopoki getline nie zwtoci falsz
                USER= PrzepiszDoWektora(linia);
                users.push_back(USER);
                licznik++;
            }
            liczbaUzytkownikow=licznik;
        }
        uzytkownicy.close();

        switch (znak) {
        case '1': {
            cout << "1. Rejestracja nowego uzytkownika" << endl;
            liczbaUzytkownikow=RejestrujUzytkownika(liczbaUzytkownikow, users);
        }

        break;
        case '2': {
            cout << "2. Logowanie uzytkownika" << endl;
            TempUserID=1;                                       // tymczasowy symulator zalogowania

            znajomi.open("Adresaci.txt.",ios::in);

            if (znajomi.good()==false) {                    // sprawdzamy czy plik z danymi istnieje
                liczbaZnajomych=0;
                cout <<"Plik z lista adresowa nie istnieje. Dodaj najpierw kilku znajomych";
                system("pause");
            }

            else {
                while (getline(znajomi,linia)) {       // odczytuje kolejne linie dopoki getline nie zwtoci falsz
                    ADRESAT=KonwertujLinie(linia);
                    adresaci.push_back(ADRESAT);
                    licznik++;
                }
                liczbaZnajomych=licznik;
                LastIDAdresat=ADRESAT.IDAdresat;
            }
            znajomi.close();

            while (TempUserID!=0) {
                cout << endl;
                cout << "Wybierz co chcesz zrobic" << endl;
                cout << "1. Dodaj osobe" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmiana hasla" << endl;
                cout << "9. Wyloguj" << endl;
                cin >> znak;

                system("cls");
                switch (znak) {
                case '1': {
                    liczbaZnajomych=DodajOsobe(liczbaZnajomych, adresaci, LastIDAdresat);
                    LastIDAdresat++;
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
                case '5': {
                    liczbaZnajomych=UsunOsobe(liczbaZnajomych, adresaci);
                    int RozmiarWektora;
                    RozmiarWektora=adresaci.size();
                    if (adresaci[RozmiarWektora-1].IDAdresat<LastIDAdresat) LastIDAdresat=adresaci[RozmiarWektora-1].IDAdresat;
                }
                break;
                case '6':
                    EdytujRekordWedlugID (adresaci,liczbaZnajomych);
                    break;
                case '7':
                    cout << "7. Zmiana hasla" << endl;
                    break;
                case '9': {
                    cout<<"Wylogowano"<<endl;
                    TempUserID=0;
                }
                break;
                }
            }
        }
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

DaneUzytkownika PrzepiszDoWektora (string linia) {
    DaneUzytkownika User;
    int pozycja;
    string TempString="";

    pozycja=linia.find("|");
    TempString=linia.substr(0,pozycja);
    User.UserID=atoi(TempString.c_str());
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    User.UserName=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    User.UserPassword=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    return User;
}

int RejestrujUzytkownika (int liczbaUzytkownikow, vector<DaneUzytkownika>& users) {
    fstream uzytkownicy;
    DaneUzytkownika USER;
    string DaneDoZapisu="";

    system("cls");
    cout << "Rejestracja nowego uzytkownika" << endl;
    cout << "Podaj dane" << endl;

    USER.UserID=liczbaUzytkownikow+1;
    DaneDoZapisu=to_string(USER.UserID);
    DaneDoZapisu+="|";

    cout << "Podaj nazwe uzytkownika: ";
    cin >> USER.UserName;
    DaneDoZapisu+=USER.UserName+"|";

    cout << "Podaj haslo do konta: ";
    cin >> USER.UserPassword;
    DaneDoZapisu+=USER.UserPassword+"|";

    users.push_back(USER);

    uzytkownicy.open("Uzytkownicy.txt.",ios::out|ios::app);
    uzytkownicy<<DaneDoZapisu<<endl;
    uzytkownicy.close();

    cout<<endl;
    cout<<"Dane uzytkownika zapisane." << endl;
    system("pause");

    return liczbaUzytkownikow+1;
}

DaneAdresata KonwertujLinie (string linia) {
    DaneAdresata ADRESAT;
    int pozycja;
    string TempString="";

    pozycja=linia.find("|");
    TempString=linia.substr(0,pozycja);
    ADRESAT.IDAdresat=atoi(TempString.c_str());
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    ADRESAT.imie=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    ADRESAT.nazwisko=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    ADRESAT.telefon=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    ADRESAT.mail=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    pozycja=linia.find("|");
    ADRESAT.adres=linia.substr(0,pozycja);
    linia.erase(0,pozycja+1);

    return ADRESAT;
}

int DodajOsobe(int liczbaOsob, vector<DaneAdresata>& osoby, int ostatnieIDAdresat) {
    fstream znajomi;
    DaneAdresata ADRESAT;
    string DaneDoZapisu="";

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj dane osoby" << endl;

    if (liczbaOsob>ostatnieIDAdresat) ADRESAT.IDAdresat=liczbaOsob+1;
    else ADRESAT.IDAdresat=ostatnieIDAdresat+1;

    DaneDoZapisu=to_string(ADRESAT.IDAdresat);
    DaneDoZapisu+="|";
    cout << "Imie: ";
    cin >> ADRESAT.imie;
    DaneDoZapisu+=ADRESAT.imie+"|";
    cout << "Nazwisko: ";
    cin >> ADRESAT.nazwisko;
    DaneDoZapisu+=ADRESAT.nazwisko+"|";
    cout << "Telefon: ";
    cin.sync();
    getline(cin,ADRESAT.telefon);
    DaneDoZapisu+=ADRESAT.telefon+"|";
    cout << "Mail: ";
    cin >> ADRESAT.mail;
    DaneDoZapisu+=ADRESAT.mail+"|";
    cin.sync();
    cout << "Adres: ";
    getline(cin,ADRESAT.adres);
    DaneDoZapisu+=ADRESAT.adres+"|";

    osoby.push_back(ADRESAT);
    znajomi.open("Adresaci.txt.",ios::out|ios::app);      // zapisze dane do pliku w jednej linii
    znajomi<<DaneDoZapisu<<endl;
    znajomi.close();
    cout << "Osoba zostala dodana do bazy" << endl;
    system("pause");
    return liczbaOsob+1;
}

void WyszukajPoImieniu (const vector<DaneAdresata>& osoby, int liczbaOsob) {
    system("cls");
    string wyszukajTo;
    cout << "Wyszukiwanie po imieniu" << endl;
    cout << "Podaj imie znajomego" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].imie==wyszukajTo) {
            cout<<"ID: "<< osoby[i].IDAdresat<<endl;
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
void WyszukajPoNazwisku (const vector<DaneAdresata>& osoby, int liczbaOsob) {
    system("cls");
    string wyszukajTo;
    cout << "Wyszukiwanie po nazwisku" << endl;
    cout << "Podaj nazwisko znajomego" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].nazwisko==wyszukajTo) {
            cout<<"ID: "<< osoby[i].IDAdresat<<endl;
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

void WyswietlWszystko (const vector<DaneAdresata>& osoby, int liczbaOsob) {
    system("cls");
    cout << "Wyswietlam dane wszystkich znajomych:" << endl;
    for (int i=0; i<liczbaOsob; i++) {
        cout<<"ID: "<< osoby[i].IDAdresat<<endl;
        cout<<"Imie: "<< osoby[i].imie<<endl;
        cout<<"Nazwisko: "<< osoby[i].nazwisko<<endl;
        cout<<"Telefon: "<< osoby[i].telefon<<endl;
        cout<<"Mail: " << osoby[i].mail<<endl;
        cout<<"Adres: " << osoby[i].adres<<endl;
        cout<<endl;
    }
    system("pause");
}

int UsunOsobe (int liczbaOsob, vector<DaneAdresata>& osoby) {
    int wyszukajTo, WskaznikRekordu=0;
    char znak;
    fstream znajomi;
    string TempString="";

    system("cls");

    cout << "Usuwanie rekordu" << endl;
    cout << "Podaj ID rekordu, ktory chcesz usunac:" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].IDAdresat==wyszukajTo) {
            cout<<"ID: "<< osoby[i].IDAdresat<<endl;
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

    if (znak=='t') {
        osoby.erase(osoby.begin()+WskaznikRekordu);
        liczbaOsob--;

        znajomi.open("Adresaci.txt.",ios::out|ios::trunc);
        znajomi.close();

        znajomi.open("Adresaci.txt.",ios::out|ios::app);
        for(int i=0; i<liczbaOsob; i++) {
            TempString="";
            TempString=to_string(osoby[i].IDAdresat);
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

void EdytujRekordWedlugID (vector<DaneAdresata>& osoby, int liczbaOsob) {
    int wyszukajTo, WskaznikRekordu=0;
    char znak;
    string TempString="";
    fstream znajomi;
    system("cls");

    cout << "Edycja rekordu" << endl;
    cout << "Podaj ID rekordu, ktory chcesz edytowac:" <<endl;
    cin >> wyszukajTo;
    for(int i=0; i<liczbaOsob; i++) {
        if (osoby[i].IDAdresat==wyszukajTo) {
            cout<<"ID: "<< osoby[i].IDAdresat<<endl;
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
    znajomi.open("Adresaci.txt.",ios::out|ios::trunc);
    znajomi.close();

    znajomi.open("Adresaci.txt.",ios::out|ios::app);
    for(int i=0; i<liczbaOsob; i++) {
        TempString="";
        TempString=to_string(osoby[i].IDAdresat);
        TempString+="|"+osoby[i].imie+"|"+osoby[i].nazwisko+"|";
        TempString+=osoby[i].telefon+"|"+osoby[i].mail+"|"+osoby[i].adres+"|";
        znajomi<<TempString<<endl;
    }
    znajomi.close();

    system("pause");
}
