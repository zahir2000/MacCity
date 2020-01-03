#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cassert>
#include <regex>
#include <conio.h>
#include <windows.h>
#include <array>
#include <chrono>
#include <time.h>
using namespace std;

#define MAX_LENGTH 16

extern "C" {
	// external ASM procedures:
	void CalculateItemTotal(double price, double qty);
	void GetNewItemPrice(double p1, double p2);
	int GetNewItemQty(int q1, int q2);
	void CalculateSubTotal(int len, array<double, 100> total);
	void DisplayPaymentCart(double sst, double sch, double total);
	void CalculateTotal(double totalAllItems);

	// local C++ functions:
	void writeToFile();
	void readFromFile();
	void displayLogin();
	int read_int();
	int read_info(string outputText);
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
	void purchaseItem();
	void displayProducts(int &i);
	int getProductQty(int choice);
	void displayCart();
	void addToCart(int uid, string name, int qty, double price, double totalPrice);
	void setItemTotal(double price);
	int getCartQty(int index);
	void SetSubTotal(double total);
	void findSubTotal();
	void displayPaymentOptions();
	int read_int_no_cout();
	void displayReceipt(string paymentOpt);
	void displayEqualLine();
	void printDashLine();
	void ClearScreen();
	void writePurchaseHistory(string paymentOpt, string orderDate);
	void updateQty(int mId, int mQty);
	void updateProductQty();
	void writeNewQty();
	void purchaseHistory();
	string getProductName(int id);
}

class Products {
public:
	static int nextid;
	int id;
	string name;
	double price;
	int qty;

	//Default Constructor 
	Products()
	{
		id = ++nextid;
	}

	//Parametrized Constructor 
	Products(string n, double p, int q)
	{
		id = ++nextid;
		name = n;
		price = p;
		qty = q;
	}

	Products(int i, string n, double p, int q)
	{
		id = i;
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

	string display() {
		string strprice = to_string(price);
		string strqty = to_string(qty);
		return name + "\t" + strprice + "\t" + strqty + "\n";
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

class Cart {
public:
	int id;
	string name;
	int qty;
	double unitPrice;
	double totalPrice;

	Cart(int mId, string mName, int mQty, double mUnitPrice, double mTotalPrice)
	{
		id = mId;
		name = mName;
		qty = mQty;
		unitPrice = mUnitPrice;
		totalPrice = mTotalPrice;
	}
};

class PurchaseHistory {
public:
	string username;
	int id;
	int qty;
	double totalPayment;
	string paymentOption;
	string paymentDate;

	PurchaseHistory(){}

	PurchaseHistory(string s, int i, int q, double t, string pO, string pD) {
		username = s;
		id = i;
		qty = q;
		totalPayment = t;
		paymentOption = pO;
		paymentDate = pD;
	}

	friend ostream & operator << (ostream &out, const PurchaseHistory &obj)
	{
		out << obj.username << "\n";
		out << obj.id << "\n";
		out << obj.qty << "\n";
		out << obj.totalPayment << "\n";

		string s = obj.paymentOption;
		s = regex_replace(s, regex{ " " }, string{ "_" });

		out << s;
		out << "\n" << obj.paymentDate << endl;
		return out;
	}

	friend istream & operator >> (istream &in, PurchaseHistory &obj)
	{
		in >> obj.username;
		in >> obj.id;
		in >> obj.qty;
		in >> obj.totalPayment;
		in >> obj.paymentOption;
		in >> obj.paymentDate;
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

vector<Products> arrProd;
vector<Customer> custArr;

//Customer cart
vector<Cart> arrCart;
//vector<Products> cart;

//Customer Username
string loginUsername = "";

double newItemPrice = 0.0;
double totalAllItems = 0;

//Cart Variables
double cartSST, cartSCH, cartTotal;

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
				//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				//int k = 12;
				//SetConsoleTextAttribute(hConsole, k);

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
	
	return true;
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
		cout.setf(ios::fixed, ios::floatfield);
		cout << setprecision(2);
		purchaseItem();
		break;

	case 2:
		purchaseHistory();
		break;

	case 3:
		changePassword();
		break;

	case 4:
		loginUsername = "";
		cout << "\nYou have been successfuly logged out.\n" << endl;
		system("pause");
		ClearScreen();
		break;
	}
}

void purchaseItem() {
	//1. Display item
	//2. Select product
	//3. Select qty
	//4. Check if storedQty > qty
	//5. Calculate subtotal and ask if have more item to purchase
	//6. If no, go to payment (display total with all tax and shit)
	//7. Display receipt when payment is >= total else display msg need more
	//8. Store to purchase history

	//todo: -1 to proceed with payment

	int choice, qty, storedQty, index;
	char c;
	string productChoice = "Enter product to buy >> ";
	string productQty = "Enter quantity to purchase >> ";

	do {
		int i = 0;
		
		ClearScreen();
		displayCart();
		printf("\n\n");
		displayProducts(i);

		do {
			choice = read_info(productChoice);

			if (choice > i || choice < 1) {
				cout << "Please enter product within range [0 - " << i << "]" << endl;
			}
			else {
				index = choice - 1;
				storedQty = getProductQty(index);
				storedQty -= getCartQty(index);

				if (storedQty < 1) {
					cout << "Sorry this item has no more stock. Please try again later." << endl;
					purchaseItem();
					break;
				}
			}
		} while (choice > i || choice < 1);

		do {
			if (storedQty < 1) {
				purchaseItem();
				break;
			}

			qty = read_info(productQty);

			if (qty > storedQty) {
				cout << "Please enter quantity that is available (Stock count: " << storedQty << ")" << endl;
			}
			else if (qty < 1) {
				cout << "Please enter quantity more than 0." << endl;
			}
		} while (qty < 1 || qty > storedQty);

		CalculateItemTotal(arrProd.at(index).price, (double)qty);
		double itemTotal = newItemPrice;

		//cout << "Total: ";
		//cout << itemTotal << endl;

		addToCart(arrProd.at(index).id, arrProd.at(index).name, qty, arrProd.at(index).price, itemTotal);
			
		cout << "\nDo you want to purchase more item(s)? [Y/N] >> ";
		cin >> c;
			
		if (c != 'y') {
			findSubTotal();
			cout << setprecision(3);
			CalculateTotal(totalAllItems);
		}

	} while (tolower(c) == 'y');
}

void purchaseHistory() {
	//READ PurchaseHistory.txt
	//Check which entries match loginUsername
	//Display those..

	vector<PurchaseHistory> arrPh;
	int counter = 0;

	ifstream in("PurchaseHistory.txt");

	if (!in) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	PurchaseHistory p;

	while (in >> p) {
		p.paymentOption = regex_replace(p.paymentOption, regex{ "_" }, string{ " " });
		arrPh.push_back(p);
	}

	in.close();

	for (PurchaseHistory ph : arrPh) {
		if (ph.username.compare(loginUsername) == 0) {
			counter++;

			if (counter == 1) {
				ClearScreen();
				displayEqualLine();
				printf("\n%35s %-25s\n", "PURCHASE HISTORY", "");
				displayEqualLine();
				cout << endl;
				printf("%-18s %-5s %-18s %-18s\n", "Name", "Qty", "Unit Price (RM)", "Total Price (RM)");
				printDashLine();
				cout << endl;
			}

			cout << setw(20) << left << getProductName(ph.id) << setw(9) << left << ph.qty
				<< left << setw(22) << ph.totalPayment << setw(20) << left << ph.paymentDate << ph.paymentOption << endl;
		}
	}

	cout << endl;
	printDashLine();
	cout << endl;

	if (counter == 0) {
		//no orders for this guy
	}
}

string getProductName(int id) {
	for (Products p : arrProd) {
		if (id == p.id) {
			return p.name;
		}
	}

	return "";
}

void displayCartWithTotal(double sst, double sch, double total) {
	ClearScreen();

	displayEqualLine();
	printf("\n%35s %-25s\n", "USER CART", "");
	displayEqualLine();
	cout << endl;

	printf("%-18s %-5s %-18s %-18s\n", "Name", "Qty", "Unit Price (RM)", "Total Price (RM)");
	printDashLine();
	cout << endl;

	if (arrCart.size() == 0) {
		cout << "Cart is empty." << endl;
	}
	else {
		findSubTotal();

		cout << endl;

		for (Cart p : arrCart) {
			cout << setw(20) << left << p.name << setw(9) << left << p.qty
				<< left << setw(22) << p.unitPrice << setw(20) << left << p.totalPrice << endl;
		}

		cout << endl;

		printDashLine();

		cout << endl;

		cout << setw(51) << right << "SUBTOTAL: " << totalAllItems << endl;
	}

	displayEqualLine();
	cout << endl;

	cout << setw(52) << right << "SST (6%): " << sst << endl;
	cout << setw(52) << right << "SC (10%): " << sch << endl;

	for (int z = 0; z < 60; z++) {
		printf("-");
	}
	cout << endl;

	cout << setw(51) << right << "TOTAL: " << total << endl;

	displayEqualLine();

	cout << endl;
}

void setSST(double sst) {
	cartSST = sst;
}

void setSCH(double sch) {
	cartSCH = sch;
}

void setCartTotal(double total) {
	cartTotal = total;
}

//Starts from Assembly
void DisplayPaymentCart(double sst, double sch, double total) {
	displayCartWithTotal(sst, sch, total);

	setSST(sst);
	setSCH(sch);
	setCartTotal(total);

	//Maybe Shipping Fee & Discount

	char c;

	do {
		cout << "\nProceed with payment? [Y/N] >> ";
		cin >> c;
		if (tolower(c) != 'y' && tolower(c) != 'n') {
			cout << "Please enter either [Y (Yes) / N (No)]" << endl;
		}
	} while (tolower(c) != 'y' && tolower(c) != 'n');

	if (c == 'y') {
		displayPaymentOptions();
	}
	else {
		cout << "Purchase cancelled :(" << endl;
		arrCart.clear();
		customerMenu();
	}
}

void displayPaymentOptions() {
	ClearScreen();
	
	displayEqualLine();
	printf("\n%38s %-22s\n", "PAYMENT OPTIONS", "");
	displayEqualLine();
	cout << endl;

	cout << "1. Cash on Delivery" << endl;
	cout << "2. Credit Card" << endl;
	displayEqualLine();
	cout << endl;

	int option;
	string paymentOpt;

	do {
		cout << "Enter your payment option >> ";
		option = read_int_no_cout();

		if (option != 1 && option != 2) {
			cerr << "Please input between option [1 - 2]\n\n";
		}
	} while (option != 1 && option != 2);

	switch (option) {
	case 1: 
		paymentOpt = "Cash on Delivery";
		break;

	case 2:
		paymentOpt = "Credit Card";
		break;
	}

	displayReceipt(paymentOpt);
	//DisplayReceipt
	//Store everything to PurchaseHistory
	//Store PurchaseHistory to FILE
}

void displayReceipt(string paymentOpt) {
	string orderDate;

	ClearScreen();

	displayEqualLine();
	printf("\n%30s %-30s\n", "RECEIPT", "");
	displayEqualLine();
	cout << endl;

	//user detail here

	auto end = chrono::system_clock::now();
	time_t end_time = chrono::system_clock::to_time_t(end);
	char buffer[80];
	struct tm timeinfo;
	time(&end_time);
	localtime_s(&timeinfo, &end_time);

	cout << "\nPayment by: " << loginUsername << endl;
	cout << "Order date: ";
	strftime(buffer, 80, "%d/%m/%Y", &timeinfo);
	puts(buffer);
	orderDate = buffer;

	cout << "Payment option: " << paymentOpt << endl;
	
	cout << endl;

	printf("%35s %-25s\n", "ORDER DETAILS", "");

	printDashLine();
	cout << endl;

	printf("%-18s %-5s %-18s %-18s\n", "Name", "Qty", "Unit Price (RM)", "Total Price (RM)");

	printDashLine();

	cout << endl;

	findSubTotal();

	cout << endl;

	for (Cart p : arrCart) {
		cout << setw(20) << left << p.name << setw(9) << left << p.qty
			<< left << setw(22) << p.unitPrice << setw(20) << left << p.totalPrice << endl;
	}

	cout << endl;

	printDashLine();

	cout << endl;

	cout << setw(51) << right << "SUBTOTAL: " << totalAllItems << endl;

	printDashLine();
	cout << endl;

	cout << setw(52) << right << "SST (6%): " << cartSST << endl;
	cout << setw(52) << right << "SC (10%): " << cartSCH << endl;

	for (int z = 0; z < 60; z++) {
		printf("-");
	}

	cout << endl;
	cout << setw(51) << right << "TOTAL: " << cartTotal << endl;
	displayEqualLine();
	cout << endl;

	writePurchaseHistory(paymentOpt, orderDate);
}

void writePurchaseHistory(string paymentOpt, string orderDate) {
	vector<PurchaseHistory> arrPH;

	for (Cart c : arrCart) {
		arrPH.push_back(PurchaseHistory(loginUsername, c.id, c.qty, c.totalPrice, paymentOpt, orderDate));
	}

	ofstream out("PurchaseHistory.txt", ios::app);

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	for (PurchaseHistory p : arrPH) {
		out << p;
	}

	out.close();

	updateProductQty();
}

void updateProductQty() {
	for (Cart c : arrCart) {
		updateQty(c.id, c.qty);
	}
	
	arrCart.clear();

	cout << "\n" << endl;
	system("pause");

	ClearScreen();
	customerMenu();
}

void updateQty(int mId, int mQty) {
	int i = -1;

	for (Products p : arrProd) {
		++i;
		if (mId == p.id) {
			//DO IT IN ASSEMBLY
			p.qty = p.qty - mQty;
			arrProd.at(i).qty = p.qty;
		}
	}

	writeNewQty();
}

void writeNewQty() {
	ofstream out("Products.txt");

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	for (Products p : arrProd) {
		out << p;
	}

	out.close();
}

int getCartQty(int index) {
	for (Cart p : arrCart) {
		if (p.id == arrProd.at(index).id) {
			return p.qty;
		}
	}

	return 0;
}

void setItemTotal(double price) {
	newItemPrice = price;
}

void addToCart(int uid, string name, int qty, double price, double totalPrice) {
	int i = 0;
	bool added = false;

	if (arrCart.size() == 0) {
		//cart.push_back(Products(uid, name, price, qty));
		arrCart.push_back(Cart(uid, name, qty, price, totalPrice));
		return;
	}
	else {
		for (Cart p : arrCart) {
			if (p.id == uid) {
				GetNewItemPrice(p.totalPrice, totalPrice);
				int newQty = GetNewItemQty(p.qty, qty);

				arrCart.erase(arrCart.begin() + i);
				arrCart.push_back(Cart(uid, name, newQty, price, newItemPrice));
				//cart.erase(cart.begin() + i);
				//cart.push_back(Products(uid, name, newItemPrice, newQty));

				return;
			}
			i++;
		}

		if (!added) {
			arrCart.push_back(Cart(uid, name, qty, price, totalPrice));
			//cart.push_back(Products(uid, name, price, qty));
		}
	}
}

void displayCart() {
	displayEqualLine();

	printf("\n%35s %-25s\n", "USER CART", "");

	displayEqualLine();

	cout << endl;
	printf("%-18s %-5s %-18s %-18s\n", "Name", "Qty", "Unit Price (RM)", "Total Price (RM)");

	printDashLine();

	cout << endl;

	if (arrCart.size() == 0) {
		cout << "Cart is empty." << endl;
	}
	else {
		findSubTotal();

		for (Cart p : arrCart) {
			cout << setw(20) << left << p.name << setw(9) << left << p.qty
				<< left << setw(22) << p.unitPrice << setw(20) << left << p.totalPrice << endl;
		}

		cout << endl;

		printDashLine();

		cout << endl;

		cout << setw(51) << right << "SUBTOTAL: " << totalAllItems << endl;
	}

	displayEqualLine();
	cout << endl;
}

void printDashLine() {
	for (int z = 0; z < 60; z++) {
		printf("-");
	}
}

void findSubTotal() {
	int i = -1;
	array<double, 100> total;

	for (Cart p : arrCart) {
		i++;
		total[i] = p.totalPrice;
	}

	CalculateSubTotal(++i, total);
}

void displayEqualLine() {
	for (int z = 0; z < 60; z++) {
		printf("=");
	}
}

void SetSubTotal(double total) {
	totalAllItems = total;
}

int getProductQty(int choice) {
	return arrProd.at(choice).qty;
}

void displayProducts(int &i) {
	displayEqualLine();
	printf("\n%35s %-25s\n", "PRODUCTS", "");
	displayEqualLine();
	cout << endl;
	printf("%-2s %-28s %-16s %-16s\n", "", "Name", "Price", "Stock Count");
	printDashLine();
	cout << endl;

	for (Products p : arrProd) {
		i++;
		cout << i << ". ";
		cout << setw(25) << left << p.name << setw(10) << right << p.price
			<< right << setw(18) << p.qty << endl;
	}

	displayEqualLine();	cout << endl;
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
			//Tell them to enter integer only
		}
	} while (!valid);

	return (input);
}

int read_int_no_cout() {
	int input = -1;
	bool valid = false;

	do
	{
		cin >> input;
		if (cin.good()) {
			valid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Please input integer only.\n" << endl;
			cout << "Enter your payment option >> ";
		}
	} while (!valid);

	return (input);
}

int read_info(string outputText) {
	int input = -1;
	bool valid = false;

	do
	{
		cout << outputText << flush;
		cin >> input;
		if (cin.good()) {
			valid = true;
		}
		else {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Invalid input; please re-enter choice.\n" << endl;
		}
	} while (!valid);

	return (input);
}

void writeToFile() {
	arrProd.push_back(Products("iPhone 11", 800, 12));
	arrProd.push_back(Products("iPhone 10", 800, 12));

	ofstream out("Products.txt");

	if (!out) {
		cerr << "Error in opening the file" << endl;
		return;
	}

	for (Products p : arrProd) {
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
		arrProd.push_back(p);
	}

	in.close();
}

void ClearScreen(){
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
