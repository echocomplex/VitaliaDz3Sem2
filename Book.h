#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

#ifndef Book_h
#define Book_h

class IncorrectReleaseYear :public invalid_argument {
public:
	IncorrectReleaseYear():invalid_argument("�������� ��� �������"){}
};
class IncorrectNumberOfPages :public invalid_argument {
public:
	IncorrectNumberOfPages() :invalid_argument("�������� ���������� �������") {}
};
class Book {
	string title;
	string author;
	string genre;
	string publisher;
	int release_year;
	int number_of_pages;
public:
	Book() {
		title = "";
		author = "";
		genre = "";
		publisher = "";
		release_year = 0;
		number_of_pages = 0;
	}
	Book(string t, string a, string g, string p, int r, int n) {
		if (r < 0 || r>2024)throw IncorrectReleaseYear();
		else if (n < 0)throw IncorrectNumberOfPages();
		else {
			title = t;
			author = a;
			genre = g;
			publisher = p;
			release_year = r;
			number_of_pages = n;
		}
	}
	Book(const Book& book) {
		title = book.title;
		author = book.author;
		genre = book.genre;
		publisher = book.publisher;
		release_year = book.release_year;
		number_of_pages = book.number_of_pages;
	}
	void ChangeTitle(string NewTitle) {
		title = NewTitle;
	}
	void ChangeAuthor(string NewAuthor) {
		author = NewAuthor;
	}
	void ChangeGenre(string NewGenre) {
		genre = NewGenre;
	}
	void ChangePublisher(string NewPublisher) {
		publisher = NewPublisher;
	}
	void ChangeReleaseYear(int NewReleaseYear) {
		release_year = NewReleaseYear;
	}
	void ChangeNumberOfPages(int NewNumberOfPages) {
		number_of_pages = NewNumberOfPages;
	}
	string GetTitle() const {
		return title;
	}
	string GetAuthor() const {
		return author;
	}
	string GetGenre() const {
		return genre;
	}
	string GetPublisher() const {
		return publisher;
	}
	int GetReleaseYear() const {
		return release_year;
	}
	int GetNumberOfPages() const {
		return number_of_pages;
	}
	bool IsNewRelease() const {
		int current_year = 2024;
		return current_year - release_year <= 3;
	}
	friend ostream& operator<<(ostream& cout, Book& book) {
		cout << "title: " << book.title << endl;
		cout << "author: " << book.author << endl;
		cout << "genre: " << book.genre << endl;
		cout << "publisher: " << book.publisher << endl;
		cout << "release year: " << book.release_year << endl;
		cout << "number of pages: " << book.number_of_pages << endl;
		return cout;
	}
	~Book() = default;
};
#endif/*Book_h*/