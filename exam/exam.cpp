#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class Driver
{
public:
    virtual void carType() = 0;
    virtual void checkInfo() = 0;
    virtual void checkStuff() = 0;
    virtual void deportDriver(int& success, int& fail) = 0;
    virtual void letGo(int& success, int& fail) = 0;
    virtual string getType() = 0;
    static Driver* rngType();
};

class cargoDriver : public Driver
{
private:
    int numInfo;
    int numType;
    int numCargo;
    string typeStorage;
    static int numRand(int randNum) {
        return rand() % randNum;
    }
public:
    cargoDriver()
    {
        numType = numRand(4);
        numInfo = numRand(3) == 0 ? 1 : 0;
    }
    string getType() override {
        return typeStorage;
    }
    void carType() {
        if (numType == 0) {
            typeStorage = "Liquid Tank Truck.\n";
            numCargo = numRand(5) == 1 ? 0 : 1;
        }
        else if (numType == 1) {
            typeStorage = "Animal Truck.\n";
            numCargo = numRand(6) == 1 ? 0 : 1;
        }
        else if (numType == 2) {
            typeStorage = "Wood Truck.\n";
            numCargo = numRand(4) == 1 ? 0 : 1;
        }
        else if (numType == 3) {
            typeStorage = "Box Truck\n";
            numCargo = numRand(3) == 1 ? 0 : 1;
        }
    }
    void checkInfo() override
    {
        if (numInfo == 0) {
            cout << "Driver::Check() -> Fake info\n";
        }
        else {
            cout << "Driver::Check() -> Real info\n";
            numInfo = 1;
        }
    }
    void checkStuff() override
    {
        if (numCargo == 0) {
            cout << "Driver::Check() -> Suspicious cargo\n";
        }
        else {
            cout << "Driver::Check() -> Regular cargo\n";
            numCargo = 1;
        }
    }
    void deportDriver(int& success, int& fail) override
    {
        if (numInfo == 0 || numCargo == 0) {
            success++;
        }
        else {
            fail++;
        }
        cout << "Driver::deportDriver() -> Deported\n";
    }
    void letGo(int& success, int& fail) override
    {
        if (numInfo != 0 && numCargo != 0) {
            success++;
        }
        else {
            fail++;
        }
        cout << "Driver::LetGo() -> Let the driver go\n";
    }
};

class passengerDriver : public Driver
{
private:
    int numInfo;
    int numType;
    int numPassengers;
    string typeStorage;
    static int numRand(int randNum) {
        return rand() % randNum;
    }
public:
    passengerDriver()
    {
        numInfo = numRand(3) == 0 ? 1 : 0;
        numType = numRand(6);
    }
    string getType() override {
        return typeStorage;
    }
    void carType() override {
        if (numType == 0) {
            typeStorage = "Bus.\n";
            numPassengers = numRand(5) == 1 ? 0 : 1;
        }
        else if (numType == 1) {
            typeStorage = "Biker.\n";
            numPassengers = numRand(6) == 1 ? 0 : 1;
        }
        else if (numType == 2) {
            typeStorage = "Micro car.\n";
            numPassengers = numRand(6) == 1 ? 0 : 1;
        }
        else if (numType == 3) {
            typeStorage = "Minibus.\n";
            numPassengers = numRand(4) == 1 ? 0 : 1;
        }
        else if (numType == 4) {
            typeStorage = "Van.\n";
            numPassengers = numRand(3) == 1 ? 0 : 1;
        }
        else if (numType == 5) {
            typeStorage = "Coupe car.\n";
            numPassengers = numRand(5) == 1 ? 0 : 1;
        }
    }
    void checkInfo() override
    {
        if (numInfo == 0) {
            cout << "Driver::Check() -> Driver info fake\n";
        }
        else {
            cout << "Driver::Check() -> Driver info good\n";
            numInfo = 1;
        }
    }
    void checkStuff() override
    {
        if (numPassengers == 0) {
            cout << "Driver::Check() -> Passenger's info fake\n";
        }
        else {
            cout << "Driver::Check() -> Passenger's info good\n";
            numPassengers = 1;
        }
    }
    void deportDriver(int& success, int& fail) override
    {
        if (numInfo == 0 || numPassengers == 0) {
            success++;
        }
        else {
            fail++;
        }
        cout << "Driver::deportDriver() -> Deported\n";
    }
    void letGo(int& success, int& fail) override
    {
        if (numInfo != 0 && numPassengers != 0) {
            success++;
        }
        else {
            fail++;
        }
        cout << "Driver::LetGo() -> Let the driver go\n";
    }
};

Driver* Driver::rngType()
{
    int r = rand() % 2;
    if (r == 0) {
        return new cargoDriver();
    }
    else {
        return new passengerDriver();
    }
}

class saveScore {
private:
    string filename;

public:
    saveScore(const string& file = "C:\\Users\\Admin\\Desktop\\gameHS.txt") : filename(file) {}

    void save(int fails, int successes) {
        ofstream out(filename, ios::out | ios::trunc);
        if (!out.is_open()) {
            cout << "eror\n";
            return;
        }
        out << "Current Highscore\n";
        out << "fails: " << fails << "\n";
        out << "good doings: " << successes << "\n";
        out.close();
        cout << "highscore saved\n";
    }
};

class Game
{
private:
    int fail = 0;
    int success = 0;
    void Menu(Driver& d)
    {
        while (true) {
            int choice;
            cout << d.getType();
            cout << "1. check info\n";
            cout << "2. check cargo\n";
            cout << "3. deport driver\n";
            cout << "4. let go driver\n\n";
            cin >> choice;

            if (choice == 1) {
                system("cls");
                d.checkInfo();
            }
            else if (choice == 2) {
                system("cls");
                d.checkStuff();
            }
            else if (choice == 3) {
                system("cls");
                d.deportDriver(success, fail);
                break;
            }
            else if (choice == 4) {
                system("cls");
                d.letGo(success, fail);
                break;
            }
            else {
                cout << "wrong";
                Sleep(2);
                system("cls");
            }
        }
    }
public:
    void run()
    {
        srand(time(0));
        for (int i = 1; i <= 2; i++) {
            if (i < 5) {
                cout << "Starting new round\n";
                Sleep(1000);
                system("cls");
            }
            
            cout << "round: " << i << "\n";
            Driver* d = Driver::rngType();
            d->carType();
            Menu(*d);
            delete d;
        }
        cout << "fails:\t" << fail << "\n";
        cout << "good doings:\t" << success << "\n";
        saveScore saving;
        saving.save(fail, success);
    }
};

int main()
{
    Game g;
    g.run();
}
