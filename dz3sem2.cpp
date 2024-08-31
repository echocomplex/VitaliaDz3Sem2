#include "Book.h"
#include "Library.h"
#include "Exceptions.h"
#include "Interface.h"
#include "LibrarySet.cpp"
#include <mutex>
#include <future>
#include <memory>
#include <iostream>
#include <set>


int main() {
	set<unique_ptr<Library>> libraries;

	while (true) {
		cout << endl;
		Interface();
		string buffer; cin >> buffer;
		switch (stoi(buffer)) {
			case 0:
				return 0;
			case 1:
				libraries = CreateLibrary(libraries);
				break;
			case 2:
				libraries = CreateBook(libraries);
				break;
			case 3:
				libraries = EditLibrary(libraries);
				break;
			case 4:
				libraries = EditBook(libraries);
				break;
			case 5:
				libraries = DeleteLibrary(libraries);
				break;
			case 6:
				libraries = DeleteBook(libraries);
				break;
			case 7: 
				future<void> SaveToFileThread = async(SaveToFile, ref(libraries));
				break;
			case 8: 
				future<set<Library>> ReadFromFileThread = async(ReadFromFile, ref(libraries));
				libraries = ReadFromFileThread.get();
				break;
			case 9: 
				ChooseParametrForSorting();
				string buffer; cin >> buffer;
				for (auto& lib : libraries) {
					lock_guard<mutex> lock(mtx);
					switch (stoi(buffer)) {
					case 1:
						lib.books.sort(SortBookListByTitle);
						break;
					case 2:
						lib.books.sort(SortBookListByAuthor);
						break;
					case 3:
						lib.books.sort(SortBookListByGenre);
						break;
					case 4:
						lib.books.sort(SortBookListByPublisher);
						break;
					case 5:
						lib.books.sort(SortBookListByReleaseYear);
						break;
				case 6:
					lib.books.sort(SortBookListByNumberOfPages);
					break;
				}
			}
		}
		}
	}
}

