#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cassert>
#include <regex>
#include <conio.h>
#include <windows.h>
using namespace std;

#define MAX_LENGTH 16

extern "C" {
	// external ASM procedures:

	// local C++ functions:
	void writeToFile();
	void readFromFile();
	void displayLogin();
	int read_int();
	void loginChoice(int choice);
	void customerMenu();
	void adminMenu();
	void displayCustMenu();
	void custChoice(int choice);
	void custDisplayLogin();
	void custLoginChoice(int choice);
	void custLogin();
	void custRegister();
	bool checkCustLogin(string username, string pass);
	bool registerCust(string username, string pass);
	bool isDuplicateLogin(string u, string p);
	void changePassword();
	void saveNewPassword(string currPass, string newPass);
}

class Products {
public:
	static int nextid;
	int id;
	string name;
	float price;
	int qty;

	//Default Constructor 
	Products()
	{
		id = nextid;
		nextid++;
	}

	//Parametrized Constructor 
	Products(string n, float p, int q)
	{
		id = nextid;
		++nextid;
		name = n;
		price = p;
		qty = q;
	}

	string toString() {
		string strid = to_string(id);
		string strprice = to_string(price);
		string strqty = to_string(qty);
		return strid + "\t" + name + "\t" + strprice + "\t" + strqty + "\n";
	}

	friend ostream & operator << (ostream &out, const Products &obj)
	{
		out << obj.id << "\n";

		string s = obj.name;
		s = regex_replace(s, regex{ " " }, string{ "_" });

		out << s;
		out << "\n" << obj.price << "\n" << obj.qty << endl;
		return out;
	}

	friend istream & operator >> (istream &in, Products &obj)
	{
		in >> obj.id;
		in >> obj.name;
		in >> obj.price;
		in >> obj.qty;
		return in;
	}
};

class Customer {
public:
	string username;
	string password;

	Customer(){}

	Customer(string u, string p) {
		username = u;
		password = p;
	}

	friend ostream & operator << (ostream &out, const Customer &obj)
	{
		out << obj.username << "\n";
		out << obj.password << endl;
		return out;
	}

	friend istream & operator >> (istream &in, Customer &obj)
	{
		in >> obj.username;
		in >> obj.password;
		return in;
	}
};

int Products::nextid = 1;

vector<Products> arr;
vector<Customer> custArr;
string loginUsername = "";

int main() {
	//writeToFile();
	readFromFile();

	cout << "MacCity" << endl;

	/*
	cout << "  []        []	[][][][][][] [][][][][][]" << endl;
	cout << "  [][]    [][]	[]        [] []          " << endl;
	cout << "  []  [][]  []	[]        [] []          " << endl;
	cout << "  []   []   []	[][][][][][] []          " << endl;
	cout << "  []        []	[]        [] []          " << endl;
	cout << "  []        []	[]        [] []          " << endl;
	cout << "  []        []	[]        [] [][][][][][]" << endl;
	*/

	int choice;
	do {
		displayLogin();
		choice = read_int();
		loginChoice(choice);
	} while (choice != 3);
}

void loginChoice(int choice) {
	cout << endl;

	switch (choice) {
	case 1: 
		custDisplayLogin();
		break;
	
	case 2: 
		adminMenu();
		break;
	}
}

void custDisplayLogin() {
	int choice;
	do {
		cout << "Customer" << endl;
		cout << "1. Login\n2. Register\n3. Back" << endl;

		choice = read_int();
		custLoginChoice(choice);
	} while (choice != 3);
}

void custLoginChoice(int choice) {
	switch (choice) {
	case 1:
		custLogin();
		break;

	case 2:
		custRegister();
		break;
	}
}

void custLogin() {
	char keypressed;
	string username, pass;
	int counter = 0;

	while (counter != 3) {
		cout << "Customer Login" << endl;
		cout << "Enter Username: ";
		cin >> username;

		cout << "Enter Password: ";
		pass = "";

		for (;;) {
			keypressed = NULL;
			keypressed = _getch();

			if (pass.size() < MAX_LENGTH && ((keypressed >= 60 && keypressed <= 90) || (keypressed >= 97 && keypressed <= 122) || (keypressed >= 48 && keypressed <= 57) || keypressed == 32)) {
				pass.push_back(keypressed);
				cout << "*";
			}

			else if (pass.size() > 0 && keypressed == 8) {
				pass.erase(pass.length() - 1);
				cout << "\b \b";
			}

			else if (keypressed == 13) 
				break;
		}
			
		counter++;

			if (checkCustLogin(username, pass)) {
				cout << endl;
				loginUsername = username;
				customerMenu();
				break;
			}
			else {
				cout << endl;
				cout << "\nInvalid username and/or password." << endl;
				cout << "You have " << (3 - counter) << " attempts left" << endl;
				cout << endl;
			}

			if (counter == 3) {
				cout << "You have exceeded number of login attempts. Returning to Customer Menu." << endl;
			}
	}
}

void custRegister() {
	string username, pass;

	cout << "Customer Registration" << endl;
	cout << "Enter -1 to Exit" << endl;
	do {
		cout << "Enter Username: ";
		cin >> username;

		if (username.compare("-1") == 0)
			return;

		if (username.length() < 4)
			cout << "Username must be more than 3 characters. Please re-enter" << endl;

	} while (username.length() < 4);

	do {
		cout << "Enter Password: ";
		cin >> pass;

		if (pass.compare("-1") == 0)
			return;

		if (pass.length() < 4)
			cout << "Password must be more than 3 characters. Please re-enter" << endl;
	} while (pass.length() < 4);

	if (registerCust(username, pass)) {
		cout << "Registration successful" << endl;
		cout << "Would you like to login (Y/N)?: ";
		char c;
		cin >> c;
		if (tolower(c) == 'y') {
			custLogin();
		}else
			return;
	}
	else {
		cout << "Registration unsuccessful" << endl;
		cout << "Customer username already exists :(" << endl;
		return;
	}
}

bool registerCust(string username, string pass) {
	if (isDuplicateLogin(username, pass)) {
		return false;
	}
	
	ofstream out("Customer.txt", ios::app);

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return false;
	}

	Customer c(username, pass);

	out << c;

	out.close();
}

bool isDuplicateLogin(string u, string p) {
	ifstream in("Customer.txt");

	if (!in) {
		cerr << "Error in opening the file" << endl;
		return false;
	}

	Customer c;

	while (in >> c) {
		if (c.username.compare(u) == 0) {
			return true;
		}
	}

	in.close();

	return false;
}

bool checkCustLogin(string username, string pass) {
	ifstream in("Customer.txt");

	if (!in) {
		cerr << "Error in opening the file" << endl;
		return false;
	}

	Customer c;

	while (in >> c) {
		if (c.username.compare(username) == 0 && c.password.compare(pass) == 0) {
			return true;
		}
	}

	in.close();

	return false;
}

void customerMenu() {
	int choice;
	do {
		displayCustMenu();
		choice = read_int();
		custChoice(choice);
	} while (choice != 4);
}

void custChoice(int choice) {
	switch (choice) {
	case 1:
		purchaseItem();
		break;

	case 2:
		//purchaseHistory();
		break;

	case 3:
		changePassword();
		break;

	case 4:
		//Logout
		//Don't forget to set loginUsername to null
		break;
	}
}

void displayCustMenu() {
	cout << "Customer" << endl;
	cout << "1. Purchase Item\n2. Purchase History\n3. Change Password\n4. Logout" << endl;
}

void changePassword() {
	string currPass, pass, pass2;

	if (loginUsername.length() == 0) {
		custDisplayLogin();
	}

	cout << "Change Password for " << loginUsername << endl;
	cout << "Enter current password: ";
	cin >> currPass;

	if (checkCustLogin(loginUsername, currPass)) {
		
		do {

			cout << "Enter new password: ";
			cin >> pass;

			if (pass.length() < 4) {
				cerr << "Password must be more than 3 characters." << endl;
			}

		} while (pass.length() < 4);

		cout << "Re-enter new password: ";
		cin >> pass2;

		if (pass.compare(pass2) == 0) {
			saveNewPassword(currPass, pass);
			cout << "Password has been successfully changed :)" << endl;
		}
		else {
			cerr << "Passwords don't match. Please try again." << endl;
		}
	}
	else {
		cerr << "Incorrect current password." << endl;
	}
}

void saveNewPassword(string currPass, string newPass) {

	ifstream in("Customer.txt");

	if (!in) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	Customer c;

	while (in >> c) {
		if (currPass.compare(c.password) == 0 && loginUsername.compare(c.username) == 0) {
			c.password = newPass;
			custArr.push_back(c);
		}
		else {
			custArr.push_back(c);
		}
	}

	in.close();

	ofstream out("Customer.txt");

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	for (Customer c : custArr) {
		out << c;
	}

	custArr.clear();

	out.close();
}

void adminMenu() {

}

void displayLogin() {
	cout << "Login" << endl;
	cout << "1. Customer\n2. Admin\n3. Exit" << endl;
}

int read_int(){
	int input = -1;
	bool valid = false;

	do
	{
		cout << "Enter your choice: " << flush;
		cin >> input;
		if (cin.good()){
			valid = true;
		}
		else{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Invalid input; please re-enter choice.\n" << endl;
		}
	} while (!valid);

	return (input);
}

void writeToFile() {
	arr.push_back(Products("iPhone 11", 800, 12));
	arr.push_back(Products("iPhone 10", 800, 12));

	ofstream out("Products.txt");

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	for (Products p : arr) {
		out << p;
	}

	out.close();
}

void readFromFile() {
	ifstream in("Products.txt");

	if (!in) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	Products p;

	while (in >> p) {
		p.name = regex_replace(p.name, regex{ "_" }, string{ " " });
		arr.push_back(p);
	}

	in.close();
}
