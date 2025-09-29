#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int fail = 0;
int success = 0;

int numRand(int randNum)
{
	return rand() % randNum;
}

class Driver
{
public:
	virtual void checkInfo() {}
	virtual void checkCargo() {}
	virtual void deportDriver() {}
	virtual void letGo() {}
};

class BoxTruck : public Driver
{
public:
	int numInfo;
	int numCargo;
	BoxTruck()
    {
        numInfo = numRand(3) == 0 ? 1 : 0;
        numCargo = numRand(3) == 0 ? 1 : 0;
    }

	virtual void checkInfo()
	{
		if (numInfo == 0) {
			cout << "Driver::Check() -> Fake info\n";
		}
		else {
			cout << "Driver::Check() -> Real info\n";
			numInfo = 1;
		}
	}
	virtual void checkCargo()
	{
		if (numCargo == 0) {
			cout << "Driver::Check() -> Suspicious cargo\n";
		}
		else {
			cout << "Driver::Check() -> Regular cargo\n";
			numCargo = 1;
		}
	}
	virtual void deportDriver()
	{
		if (numInfo == 0 || numCargo == 0) {
			cout << "Driver::deportDriver() -> Deported\n";
			success++;
		}
		else {
			cout << "Driver::deportDriver() -> Deported\n";
			fail++;
		}
	}
	virtual void letGo()
	{
		if (numInfo != 0 && numCargo != 0) {
			cout << "Driver::LetGo() -> Let the driver pass\n";
			success++;
		}
		else
			cout << "Driver::Letgo() -> Let the driver pass\n";
			fail++;
	}
};


void Menu(BoxTruck &bt) {
	//there will be more car types later
	cout << "Box truck coming thru\n";
	while (true) {
		int choice;
		cout << "1.check info\n";
		cout << "2.check cargo\n";
		cout << "3.deport driver\n";
		cout << "4.let go driver\n\n";
		cin >> choice;
		if (choice == 1) {
			system("cls");
			bt.checkInfo();
		}
		else if (choice == 2) {
			system("cls");
			bt.checkCargo();
		}
		else if (choice == 3) {
			system("cls");
			bt.deportDriver();
			break;
		}
		else if (choice == 4) {
			system("cls");
			bt.letGo();
			break;
		}
		else {
			cout << "wrong";
			Sleep(2);
			system("cls");
		}
	}
}

int main()
{
	srand(time(0));
	BoxTruck bt;
	Menu(bt);
	cout << "fails:\t" << fail << "\n";
	cout << "good doings:\t" << success << "\n";
}