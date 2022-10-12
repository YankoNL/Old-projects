#include <iostream>
#include <string>
#include <fstream>

int const size = 30;

using namespace std;
struct TelephoneAbonat			// Phone Structure
{
	string Name, TelephoneNumber;			// Name, Number 
	char Surname[20];			// Last name
	double MoneyForPay;				// Monthly

};


int Input(TelephoneAbonat Abonat[], int NumberOfAbonat)
{
	ofstream File("Abonat.txt");			// Open file (read only)

	for (int i = 0; i < NumberOfAbonat; i++)
	{
		// Input + read from file
		cout << "\nВъведете данни за абонат номер: " << i + 1 << " :\n";
		cout << "\nИме на абоната: ";
		cin.ignore();
		getline(cin, Abonat[i].Name);
		File << "Име: " << Abonat[i].Name;

		cout << "Въведете фамилия: ";
		cin.getline(Abonat[i].Surname, 20);
		File << "\nФамилия: " << Abonat[i].Surname;

		cout << "Въведете тел. номер: ";
		cin >> Abonat[i].TelephoneNumber;
		File << "\nТел. номер: " << Abonat[i].TelephoneNumber;

		cout << "Въведете месечна такса: ";
		cin >> Abonat[i].MoneyForPay;			// put in massive 
		File << "\nСума: " << Abonat[i].MoneyForPay << "\n" << endl;
	}
	File.close();

	return 0;
}

int PrintAllAbonat(TelephoneAbonat Abonat[], int NumberOfAbonat)	// Output
{
	for (int i = 0; i < NumberOfAbonat; i++)
	{
		cout << "\nИме: " << Abonat[i].Name;
		cout << "\nФамилия: " << Abonat[i].Surname;
		cout << "\nТел. номер: " << Abonat[i].TelephoneNumber;
		cout << "\nТакса: " << Abonat[i].MoneyForPay << endl;
	}
	return 0;
}

int PrintFromFile()			// Get from file
{
	string data;
	ifstream File("Abonat.txt");


	while (File)
	{
		getline(File, data);
		cout << data << endl;
	}
	File.close();

	return 0;
}

double SearchForPay(TelephoneAbonat Abonat[], int NumberOfAbonat)	// Search by payment
{
	double money;
	cout << "\nВъведете сумата която търсите: ";
	cin >> money;
	for (int i = 0; i < NumberOfAbonat; i++)
	{

		if (Abonat[i].MoneyForPay == money)
		{
			cout << "\nИме: " << Abonat[i].Name;
			cout << "\nФамилия: " << Abonat[i].Surname;
			cout << "\nТел. номер: " << Abonat[i].TelephoneNumber;
			cout << "\nТакса: " << Abonat[i].MoneyForPay << endl;

		}
	}
	return 0;
}

int SearchForName(TelephoneAbonat Abonat[], int NumberOfAbonat)		// Search by name
{
	char SearchName[20];
	cout << "\nВъведете фамиля която търсите: ";
	cin.ignore();
	cin.getline(SearchName, 20);

	for (int i = 0; i < NumberOfAbonat; i++)
	{
		if (!strcmp(SearchName, Abonat[i].Surname))
		{
			cout << "\nИме: " << Abonat[i].Name;
			cout << "\nФамилия: " << Abonat[i].Surname;
			cout << "\nТел. номер: " << Abonat[i].TelephoneNumber;
			cout << "\nТакса: " << Abonat[i].MoneyForPay << endl;
		}

	}
	return 0;
}

int Sort(TelephoneAbonat Abonat[], int NumberOfAbonat)		// Sort function
{


	cout << "Сортиране по месечна такса ";

	TelephoneAbonat swap;
	for (int c = 0; c < (NumberOfAbonat - 1); c++)
	{
		for (int d = 0; d < NumberOfAbonat - c - 1; d++)
		{
			if (Abonat[d].MoneyForPay > Abonat[d + 1].MoneyForPay)
			{

				swap = Abonat[d];
				Abonat[d] = Abonat[d + 1];
				Abonat[d + 1] = swap;
			}
		}
	}

	cout << "\nУспешно сортиране!\n" << endl;

	return 0;
}

// Return function after confirmation
int menu()
{
	int n;

	do
	{
		cout << "\n1. Въвеждане"
			<< "\n2. Извеждане на всички"
			<< "\n3. Справка по фамилия"
			<< "\n4. Справка по такса"
			<< "\n5. Сортиране\n"
			<< "\nВашият избор е: ";
		cin >> n;
	}
	while (!(n > 0 && n <= 5));			// Confirm user input

	// Return user choice
	return n;
}

int main()
{
	/*setlocale(LC_ALL, "Bulgarian");	// Read cyrilic symbols BUG!*/
	system("chcp 1251");					// Read cyrilic symbols FIX!
	TelephoneAbonat *Abonat = NULL;			// Declare massive
	int NumberOfAbonat = 0					// Records in massive
		, val;								// Repeat

	do
	{
		switch (menu())			//CASE, Gets return value from func
		{

		case 1:
			if (!NumberOfAbonat)
			{			// Use inpur if no existing record
				do
				{
					cout << "\nКолко записа искате да въведете? ";
					cin >> NumberOfAbonat;			// Number of records, user input
				}
				while (NumberOfAbonat > 0 & NumberOfAbonat >= 31);

				// Seperate massive size from structure
				Abonat = new TelephoneAbonat[NumberOfAbonat];

				// and than send massive for input
				Input(Abonat, NumberOfAbonat);
			}
			else			// For existing record
				cout << "\nДанните вече са въведени! Ако искате да въведете още, моля рестартирайте програмата!\n";

			break;
		case 2:
			if (NumberOfAbonat)
				PrintAllAbonat(Abonat, NumberOfAbonat);
			else
				cout << "\nНяма данни!\n";
			break;
		case 3:
			if (NumberOfAbonat)
			{
				int n;
				do
				{
					SearchForName(Abonat, NumberOfAbonat);
					do
					{
						cout << "\nЖелаете ли да направите още една справка? (1 - да, 2 - не) ";
						cin >> n;
					} while (!(n > 0 && n < 3));
				} while (n == 1);
			}
			else
				cout << "\nНяма данни!\n";
			break;
		case 4:
			if (NumberOfAbonat)
			{
				int n;
				do
				{
					SearchForPay(Abonat, NumberOfAbonat);
					do
					{
						cout << "\nЖелаете ли да направите още една справка? (1 - да, 2 - не) ";
						cin >> n;
					} while (!(n > 0 && n < 3));
				} while (n == 1);
			}
			else
				cout << "\nНяма данни!\n";
			break;
		case 5:
			if (NumberOfAbonat)
				Sort(Abonat, NumberOfAbonat);
			else
				cout << "\nНяма данни!\n";
			break;
		}

		do
		{
			cout << "\nЖелаете ли да направите още една операция? (1 - да, 2 - не) ";
			cin >> val;
		}
		while (!(val > 0 && val < 3));			// Ask user to continue
	}
	while (val == 1);

	delete[] Abonat;
}