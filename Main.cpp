#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cassert>
#include <regex>
using namespace std;

extern "C" {
	// external ASM procedures:

	// local C++ functions:
}

class Products
{
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

int Products::nextid = 1;

std::vector<Products> arr;

void writeToFile() {
	arr.push_back(Products("iPhone 11", 800, 12));
	arr.push_back(Products("iPhone 10", 800, 12));

	ofstream out("Products.txt");

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

int main() {
	//writeToFile();
	readFromFile();

	for (Products p : arr) {
		cout << p.toString();
	}
}