#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cstdio>
#include "User.h"

using namespace std;


UserData::UserData(int ID, string name, string password){
       UserID = ID;
       UserName = name;
       UserPassword = password;
    }

int UserData::UserRegister (int liczbaUzytkownikow, vector<UserData>& users){
    UserData USER;
    fstream uzytkownicy;
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

    return USER.UserID;
}

int UserData::LoginUser (int liczbaUzytkownikow, const vector<UserData>& users){
    string TempLogin="", TempPassword="";
    UserData USER;

    system("cls");
    cout << "Logowanie" << endl;
    cout << "Podaj nazwe uzytkownika: " ;
    cin >> TempLogin;
    cout <<endl;

    for (int i=0; i<liczbaUzytkownikow; i++) {
        if (users[i].UserName==TempLogin) {
            cout << "Znaleziono login w bazie." << endl;
            for (int j=3; j>0; j--) {
                cout << "Podaj haslo: ";
                cin >> TempPassword;
                cout<<endl;
                if (users[i].UserPassword==TempPassword) {
                    cout << "Logowanie poprawne" <<endl;
                    cout << "Witaj " << users[i].UserName << endl;
                    return users[i].UserID;
                } else {
                    cout << "Haslo niepoprawne. Pozostalo prob: " << j-1 << endl;
                }
            }
            cout << "Logowanie nieudane. Podano 3 razy niepoprawne haslo." << endl;
            return 0;
        }
    }
    cout << "Logowanie nieudane. Nie ma takiego uzytkownika w bazie." << endl;
    return 0;
}
