#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class EmptyLibrariesExeption : public std::invalid_argument {
public:
	EmptyLibrariesExeption() : std::invalid_argument("Сначала необходимо создать хотя бы одну библиотеку") {}
};

class EmptyBooksExeption : public std::invalid_argument {
public:
	EmptyBooksExeption() : std::invalid_argument("Сначала необходимо добавить хотя бы одну книгу в эту библиотеку") {}
};

#endif // EXCEPTIONS_H