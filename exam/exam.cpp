#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <list>
#include <algorithm>
using namespace std;

class Driver
{
public:
    virtual void carType() = 0; //randomization of the car type (as in what kind of cargo or how many people they can hold)
    virtual void checkInfo() = 0; //check driver's information to see if they are elligible for entry or have a real driver's license
    virtual void checkStuff() = 0; //check the inside of the car. For cargo trucks its the inside material, for passager cars its people inside for their entry
    virtual void deportDriver(int& success, int& fail) = 0; //deport the driver back into the country away from the border
    virtual void letGo(int& success, int& fail) = 0; //let the driver pass the border
    virtual string getType() = 0; //the buffer for the carType.
    static Driver* rngType(); //the buffer for if the car is cargo or passenger
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
        carType();
    }
    string getType() override {
        return typeStorage;
    }
    void carType() {
        if (numType == 0) {
            typeStorage = "Liquid Tank Truck.\n";
            numCargo = numRand(5) == 0 ? 1 : 0;
        }
        else if (numType == 1) {
            typeStorage = "Animal Truck.\n";
            numCargo = numRand(6) == 0 ? 1 : 0;
        }
        else if (numType == 2) {
            typeStorage = "Wood Truck.\n";
            numCargo = numRand(4) == 0 ? 1 : 0;
        }
        else if (numType == 3) {
            typeStorage = "Box Truck\n";
            numCargo = numRand(3) == 0 ? 1 : 0;
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
        carType();
    }
    string getType() override {
        return typeStorage;
    }
    void carType() override {
        if (numType == 0) {
            typeStorage = "Bus.\n";
            numPassengers = numRand(5) == 0 ? 1 : 0;
        }
        else if (numType == 1) {
            typeStorage = "Biker.\n";
            numPassengers = numRand(6) == 0 ? 1 : 0;
        }
        else if (numType == 2) {
            typeStorage = "Micro car.\n";
            numPassengers = numRand(6) == 0 ? 1 : 0;
        }
        else if (numType == 3) {
            typeStorage = "Minibus.\n";
            numPassengers = numRand(4) == 0 ? 1 : 0;
        }
        else if (numType == 4) {
            typeStorage = "Van.\n";
            numPassengers = numRand(3) == 0 ? 1 : 0;
        }
        else if (numType == 5) {
            typeStorage = "Coupe car.\n";
            numPassengers = numRand(5) == 0 ? 1 : 0;
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

Driver* Driver::rngType() //randomization of the type of car passing through
{
    int r = rand() % 2;
    if (r == 0) {
        return new cargoDriver();
    }
    else {
        return new passengerDriver();
    }
}

class saveScore { //the current and highscore saver
private:
    string filename;

public:
    saveScore(const string& file = "BC-Score.txt") : filename(file) {}

    void save(int fails, int success, int hs) {
        ofstream out(filename, ios::out | ios::trunc);
        if (!out.is_open()) {
            cout << "error saving file\n";
            return;
        }
        out << "highscore: " << hs << "\n";
        out << "last_game:\n";
        out << "fails: " << fails << "\n";
        out << "good doings: " << success << "\n";
        out.close();
    }
    int highScore() {
        ifstream in(filename);
        if (!in.is_open()) {
            return 0;
        }

        string line;
        int hs = 0;
        while (getline(in, line)) {
            size_t pos = line.find("highscore:");
            if (pos < line.size()) {
                pos += 10;
                while (pos < line.size() && isspace(line[pos])) {
                    pos++;
                }
                hs = 0;
                while (pos < line.size() && isdigit(line[pos])) {
                    hs = hs * 10 + (line[pos] - '0');
                    pos++;
                }
                break;
            }
        }

        in.close();
        return hs;
    }
};

class Game //game menu
{
private:
    int fail = 0;
    int success = 0;
    list<Driver*> drivers;
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
                Sleep(750);
                system("cls");
            }
        }
    }
public:
    void run()
    {
        srand(time(0));

        for (int i = 1; i <= 4; i++) {
            drivers.push_back(Driver::rngType());
        }
        int round = 1;
        for (auto it = drivers.begin(); it != drivers.end(); ++it, ++round) {
            cout << "round: " << round << "\n";
            Menu(**it);
        }

        cout << "fails:\t" << fail << "\n";
        cout << "good doings:\t" << success << "\n";

        saveScore saving;
        int hs = saving.highScore();

        if (success > hs)
            hs = success;

        char choice;
        cout << "save (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            saving.save(fail, success, hs);
        }
        else {
            cout << "Score not saved.\n";
        }

        for_each(drivers.begin(), drivers.end(), [](Driver* d) {
            delete d;
            });
        drivers.clear();
    }
};

int main()
{
    Game g;
    g.run();
}