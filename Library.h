#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <stdexcept>
#include "Book.h"

using namespace std;

#ifndef Library_h
#define Library_h

class IncorrectReadersCount : public invalid_argument {
public:
	IncorrectReadersCount():invalid_argument("�������� ���������� ���������"){}
};
class IncorrectIsOpen : public invalid_argument {
public:
	IncorrectIsOpen() :invalid_argument("�������� �������� ����������-���������� ����������") {}
};

class Library {
public:
	string name;
	string adress;
	set<Book>books;
	int readers_count;
	bool is_open;
	Library() {
		name = "";
		adress = "";
		books = {};
		readers_count = 0;
		is_open = 0;
	}
	Library(string n, string a, set<Book>b, int r, bool i) {
		if (r < 0)throw IncorrectReadersCount();
		else if (i != 0 && i != 1) throw IncorrectIsOpen();
		else {
			name = n;
			adress = a;
			books = b;
			readers_count = r;
			is_open = i;
		}
	}

	void ChangeName(string NewName) {
		name = NewName;
	}

	void ChangeAddress(string NewAdress) {
		adress = NewAdress;

	}
	void ChangeReadersCount(int NewReadersCount) {
		readers_count = NewReadersCount;
	}

	void OpenLibrary() { // �������� ����������
		is_open = 1;
	}

	void CloseLibrary() { // �������� ����������
		is_open = 0;
	}

	bool IsLibraryOpen() const { // ��������, ������� �� ����������
		return is_open;
	}

	string GetName() const { // ��������� �������� ����������
		return name;
	}
	string GetAddress() const { // ��������� ������ ����������
		return adress;
	}
	int GetReadersCount() const { // ��������� ���������� ��������� � ����������
		return readers_count;
	}

	friend Library& operator += (Library& lib, Book& book) { // ���������� ����� � ����������
			lib.books.insert(book);
		return lib;
	}
	friend ostream& operator << (ostream& outt, Library& lib) { // ������������� �������� ������� � ����� ������
			outt << "Name: " << lib.name << endl;
		outt << "Adress: " << lib.adress << endl;
		int i = 1;
		for (auto& book : lib.books) {
			outt << "\tBook �" << i << endl;
			outt << book << endl;
			i++;
		}
		outt << "Count of readers: " << lib.readers_count << endl;
		outt << "Is library open?: " << lib.is_open << endl;
		return outt;
	}

	~Library() = default;
};


#endif/*Library_h*/