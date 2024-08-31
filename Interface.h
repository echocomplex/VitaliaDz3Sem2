#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

void Interface() {
	std::cout << "Выберите действие: " << std::endl;
	std::cout << "0) Выйти из программы" << std::endl;
	std::cout << "1) Добавить новую библиотеку" << std::endl;
	std::cout << "2) Добавить новую книгу" << std::endl;
	std::cout << "3) Редактировать библиотеку" << std::endl;
	std::cout << "4) Редактировать книгу" << std::endl;
	std::cout << "5) Удалить библиотеку" << std::endl;
	std::cout << "6) Удалить книгу" << std::endl;
	std::cout << "7) Сохранить данные в файл" << std::endl;
	std::cout << "8) Считать данные из файла" << std::endl;
	std::cout << "9) Отсортировать книги во всех библиотеках" << std::endl;
}

#endif // INTERFACE_H