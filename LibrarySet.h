#ifndef LIBRARYSET_H
#define LIBRARYSET_H

#include "Book.h"
#include "Library.h"
#include "Exceptions.h"
#include "Interface.h"
#include <mutex>
#include <future>
#include <memory>
#include <iostream>
#include <set>
#include <thread>

using namespace std;
mutex mtx;


bool SortBookListByTitle(Book b1, Book b2) {
	return b1.GetTitle() < b2.GetTitle();
}
bool SortBookListByAuthor(Book b1, Book b2) {
	return b1.GetAuthor() < b2.GetAuthor();
}
bool SortBookListByGenre(Book b1, Book b2) {
	return b1.GetGenre() < b2.GetGenre();
}
bool SortBookListByPublisher(Book b1, Book b2) {
	return b1.GetPublisher() < b2.GetPublisher();
}
bool SortBookListByReleaseYear(Book b1, Book b2) {
	return b1.GetReleaseYear() < b2.GetReleaseYear();
}
bool SortBookListByNumberOfPages(Book b1, Book b2) {
	return b1.GetNumberOfPages() < b2.GetNumberOfPages();
}

set<unique_ptr<Library>> CreateLibrary(set<unique_ptr<Library>> libs) {
	try {
		string n, a;
		int r;
		bool i;
		cout << "Введите название библиотеки: "; cin >> n;
		cout << "Введите адрес библиотеки: "; cin >> a;
		cout << "Введите количество уникальных читателей библиотеки: "; cin >> r;
		cout << "Открыта ли библиотека? (1, если открыта, иначе - 0): "; cin >> i;
		unique_ptr<Library> lib(new Library(n, a, {}, r, i));
		libs.insert(lib);
	}
	catch (IncorrectReadersCount& exeption) {
		cout << exeption.what() << endl;
	}
	catch (IncorrectIsOpen& exeption) {
		cout << exeption.what() << endl;
	}
	return libs;
}
void GetSetOfLibraries(set<unique_ptr<Library>> libs, string message) {
	if (libs.empty()) throw EmptyLibrariesExeption();
	else {
		cout << message << endl;
		int i = 1;
		for (auto& lib : libs) {
			cout << i << ") " << lib.GetName() << endl;
			i++;
		}
	}
}
void GetListOfBooks(Library lib, string message) {
	if (lib.books.empty()) throw EmptyBooksExeption();
	else {
		cout << message << endl;
		int i = 1;
		for (auto& book : lib.books) {
			cout << i << ") " << book.GetTitle() << ", " << book.GetNumberOfPages() << "с" <<
				endl;
			i++;
		}
	}
}
void GetListOfLibraryParametrsToEdit() {
	cout << "1) Изменить название библиотеки" << endl;
	cout << "2) Изменить адресс библиотеки" << endl;
	cout << "3) Изменить количество уникальных читателей" << endl;
	cout << "4) Открыть библиотеку" << endl;
	cout << "5) Закрыть библиотеку" << endl;
}
void GetListOfBookParametrsToEdit() {
	cout << "1) Изменить название книги" << endl;
	cout << "2) Изменить автора книги" << endl;
	cout << "3) Изменить жанр книги" << endl;
	cout << "4) Изменить издание книги" << endl;
	cout << "5) Изменить год выпуска книги" << endl;
	cout << "6) Изменить количество страниц книги" << endl;
}
set<unique_ptr<Library>> AddBookToLibrary(int n, set<unique_ptr<Library>> libs, Book book) {
	int i = 1;
	for (auto& lib : libs) {
		if (i == n) {
			*lib += book;
		}
		i++;
	}
	return libs;
}
set<unique_ptr<Library>> CreateBook(set<unique_ptr<Library>> libs) {
	try {
		GetSetOfLibraries(libs, "Выберите библиотеку, в которую вы хотите добавить созданную книгу : ");
			string buffer2; cin >> buffer2;

		string t, a, g, p;
		int r, n;
		cout << "Введите название книги: "; cin >> t;
		cout << "Введите автора книги: "; cin >> a;
		cout << "Введите жанр книги: "; cin >> g;
		cout << "Введите издание книги: "; cin >> p;
		cout << "Введите год выпуска книги: "; cin >> r;
		cout << "Введите количество страниц: "; cin >> n;
		lock_guard<mutex> lock(mtx);
		{
			Book book(t, a, g, p, r, n);
			libs = AddBookToLibrary(stoi(buffer2), libs, book);
		}
	}
	catch (EmptyLibrariesExeption& exeption) {
		cout << exeption.what() << endl;
	}
	catch (IncorrectReleaseYear& exeption) {
		cout << exeption.what() << endl;
	}
	catch (IncorrectNumberOfPages& exeption) {
		cout << exeption.what() << endl;
	}
	return libs;
}
set<unique_ptr<Library>> EditLibrary(set<unique_ptr<Library>> libs) {
	try {
		GetSetOfLibraries(libs, "Выберите библиотеку, которую вы хотите отредактировать: ");
			string buffer3; cin >> buffer3;
		GetListOfLibraryParametrsToEdit();
		string buffer4; cin >> buffer4;

		int i = 1;
		for (auto& lib : libs) {
			if (i == stoi(buffer3)) {
				lock_guard<mutex> lock(mtx);
				switch (stoi(buffer4)) {
				case 1: {
					string NewName;
					cout << "Введите новое название библиотеки: "; cin >> NewName;
					lib.ChangeName(NewName);
					break;
				}
				case 2: {
					string NewAddress;
					cout << "Введите новый адрес библиотеки: "; cin >> NewAddress;
					lib.ChangeAddress(NewAddress);
					break;
				}
				case 3: {
					int NewReadersCount;
					cout << "Введите новое количество уникальных читателей: "; cin >>
						NewReadersCount;
					lib.ChangeReadersCount(NewReadersCount);
					break;
				}
				case 4:
					lib.OpenLibrary();
					break;
				case 5:
					lib.CloseLibrary();
					break;
				}
			}
			i++;
		}
	}
	catch (EmptyLibrariesExeption& exeption) {
		cout << exeption.what() << endl;
	}
	return libs;
}
set<unique_ptr<Library>> EditBook(set<unique_ptr<Library>> libs) {
	GetSetOfLibraries(libs, "Выберите библиотеку, книгу в которой вы хотите отредактировать: ");
		string buffer; cin >> buffer;

	int i = 1;
	for (auto& lib : libs) {
		if (i == stoi(buffer)) {
			GetListOfBooks(lib, "Выберите книгу, которую хотите отредактировать: ");
			string buffer3; cin >> buffer3;
			GetListOfBookParametrsToEdit();
			string buffer2; cin >> buffer2;

			int j = 1;
			for (auto& book : lib.books) {
				if (j == stoi(buffer3)) {
					lock_guard<mutex> lock(mtx);
					switch (stoi(buffer2)) {
					case 1: {
						string NewTitle;
						cout << "Введите новое название книги: "; cin >> NewTitle;
						book.ChangeTitle(NewTitle);
						break;
					}
					case 2: {
						string NewAuthor;
						cout << "Введите нового автора: "; cin >> NewAuthor;
						book.ChangeAuthor(NewAuthor);
						break;
					}
					case 3: {
						string NewGenre;
						cout << "Введите новый жанр: "; cin >> NewGenre;
						book.ChangeGenre(NewGenre);
						break;
					}
					case 4: {
						string NewPublisher;
						cout << "Введите новое издательство: "; cin >> NewPublisher;
						book.ChangePublisher(NewPublisher);
						break;
					}
					case 5: {
						int NewReleaseYear;
						cout << "Введите новый год выпуска книги: "; cin >> NewReleaseYear;
						book.ChangeReleaseYear(NewReleaseYear);
						break;
					}
					case 6: {
						int NewNumberOfPages;
						cout << "Введите новое количество страниц в книге: "; cin >>
							NewNumberOfPages;
						book.ChangeNumberOfPages(NewNumberOfPages);
						break;
					}
					}
				}
				j++;
			}
		}
		i++;
	}
	return libs;
}
set<unique_ptr<Library>> DeleteLibrary(set<unique_ptr<Library>> libs) {
	try {
		GetSetOfLibraries(libs, "Выберите библиотеку, которую вы хотите удалить: ");
		string buffer; cin >> buffer;
		auto iter = libs.begin();
		int i = 1;
		while (i != stoi(buffer)) {
			i++;
			++iter;
		}
		lock_guard<mutex> lock(mtx);
		libs.erase(iter);
	}
	catch (EmptyLibrariesExeption& exeption) {
		cout << exeption.what() << endl;
	}
	return libs;
}
set<unique_ptr<Library>> DeleteBook(set<unique_ptr<Library>> libs) {
	try {
		GetSetOfLibraries(libs, "Выберите библиотеку, книгу в которой вы хотите удалить: ");
		string buffer; cin >> buffer;
		int i = 1;
		for (auto& lib : libs) {
			if (i == stoi(buffer)) {
				GetListOfBooks(lib, "Выберите книгу, котрую вы хотите удалить: ");
				string buffer2; cin >> buffer2;
				auto iter = lib.books.begin();
				int j = 1;
				while (j != stoi(buffer2)) {
					j++;
					++iter;
				}
				lock_guard<mutex> lock(mtx);
				lib.books.erase(iter);
			}
			i++;
		}
	}
	catch (EmptyLibrariesExeption& exeption) {
		cout << exeption.what() << endl;
	}
	catch (EmptyBooksExeption& exeption) {
		cout << exeption.what() << endl;
	}
	return libs;
}
void ChooseParametrForSorting() {
	cout << "1) Отсортировать книги по названию" << endl;
	cout << "2) Отсортировать книги по автору" << endl;
	cout << "3) Отсортировать книги по жанру" << endl;
	cout << "4) Отсортировать книги по изданию" << endl;
	cout << "5) Отсортировать книги по году выпуска" << endl;
	cout << "6) Отсортировать книги по количеству страниц" << endl;
}
void SaveToFile(set<unique_ptr<Library>> libraries) {
	ofstream fout("/Users/macbook/Desktop/dz3/dz3/output.txt");
	int i = 1;
	for (auto& lib : libraries) {
		fout << "\t\t\t\t\t\tLibrary №" << i << endl;
		fout << lib;
		i++;
	}
}
set<unique_ptr<Library>> ReadFromFile(set<unique_ptr<Library>> libraries) {
	ifstream fin("/Users/macbook/Desktop/dz3/dz3/input.txt");
	int LibrariesCount; fin >> LibrariesCount;
	for (int i = 0; i < LibrariesCount; i++) {
		set<Book> books;
		string name, address;
		int readers_count, BooksCount;
		bool is_open;
		fin >> name >> address >> BooksCount;
		for (int j = 0; j < BooksCount; j++) {
			string title, author, genre, publisher;
			int release_year, number_of_pages;
			fin >> title >> author >> genre >> publisher >> release_year >> number_of_pages;
			try {
				Book book(title, author, genre, publisher, release_year, number_of_pages);
				books.insert(book);
			}
			catch (IncorrectReleaseYear& exeption) {
				cout << exeption.what() << endl;
			}
			catch (IncorrectNumberOfPages& exeption) {
				cout << exeption.what() << endl;
			}
		}
		fin >> readers_count >> is_open;
		try {
			Library lib(name, address, books, readers_count, is_open);
			libraries.insert(lib);
		}
		catch (IncorrectReadersCount& exeption) {
			cout << exeption.what() << endl;
		}
	}
	return libraries;
}

#endif // LIBRARYSET_H