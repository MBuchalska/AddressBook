#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

class UserData {
    public:
    int UserID;
    string UserName, UserPassword;

    UserData(int ID=0, string name="name", string password="pass");     //konstruktor
    ~UserData();                                                        //destruktor
    int UserRegister (int liczbaUzytkownikow, vector<UserData>& users);    //rejestracja uzytkownika,
    int LoginUser (int liczbaUzytkownikow, const vector<UserData>& users); // logowanie uzytkownika,
};
