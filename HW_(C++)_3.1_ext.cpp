//                          Курс.Объектно - ориентированное программирование на C++.
//                                      Домашнее задание к модулю 3
// Создайте класс Array. Класс Array - это класс динамического массива.
// Размер массива может быть передан в качестве параметра или задан с помощью вызова функции - члена.
// Класс должен позволять заполнять массив значениями, отображать содержимое массива, изменять
// размер массива, сортировать массив, определять минимальное и максимальное значение.
// Класс должен содержать набор конструкторов(конструктор копирования обязателен), деструктор.
#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;
template <typename A > class Array
{
private:
	size_t size;
	A *arr, max, min;          // указатель на массив int
public:
	Array()                                  // конструктор по умолчанию
	{
		arr = new A [size];
	}
	Array(size_t Size)                 // конструктор 
	{
		arr = new A [Size];
	}
	Array(size_t Size, A max, A min)                 // конструктор 
	{
		size=Size;
		arr = new A[Size];
		if (typeid(arr[0]) != typeid(int)) {
			for (size_t i = 0; i < size; i++) {
				arr[i] = (A)rand() / RAND_MAX * (max - min) + min;
			}
		}
		else {
			for (size_t i = 0; i < size; i++) {
				arr[i] = rand() % (int)(max - min + 1) + min;
			}
		}
	}
	void init_size() {
		do {
			cout << "Введите размер массива: ";
			cin >> size;
			if (size < 1)
				cout << "\nОшибка! Число меньше 1!\n";
		} while (size < 1);
	}
	void init_arr() {
		for (size_t i = 0; i < size; i++) {
			cout << "arr [" << i + 1 << "] = ";
			cin >> arr[i];
		}
	}
	Array(const Array& ob)                   // конструктор копии
	{
		arr = new A[ob.size];
		for (size_t i = 0; i < ob.size; i++) {
			arr[i] = ob.arr[i];
		}
	}
	~Array()                                 // деструктор
	{
		delete arr;
	}
	void show_Arr(size_t n)                             // отображение содержимого массива
	{
		for (size_t i = 0; i < size; i++) {
			cout << arr[i] << "\t";
			if ((i + 1) % n == 0) cout << endl;
			if(i+1==size) cout << endl;
		}
	}
	void sort() {   // сортировка массива выбором
		for (size_t k = 0; k < size - 1; k++) //k-левая граница сортируемой области
		{   //поиск минимума
			size_t imin = k;
			for (size_t i = k + 1; i<size; i++) //перебираем от k до конца
				if (arr[i] < arr[imin]) {
					imin = i;
				}
			//нашли минимум
			//перестановка k-го и минимального
			A tmp = arr[k];
			arr[k] = arr[imin];
			arr[imin] = tmp;
		}
	}
	A arr_Min() {        // поиск минимального элемента массива
		min  = *arr;
		A *a = arr;
		a++;
		for (size_t i = 1; i < size; i++, a++) {
			if (*a < min+1e-9) {
				min = *a;
			}
		}
		return min;
	}
	A arr_Max() {        // поиск максимального элемента массива
		max = *arr;
		A *a = arr;
		a++;
		for (size_t i = 1; i < size; i++, a++) {
			if (*a > max + 1e-9) {
				max = *a;
			}
		}
		return max;
	}
	void del(size_t pos) {                        // функция удаления записи 
		bool f = false;
		if (pos <= 0 || pos > size)
		{
			cout << "[" << pos << "] элемент отсутствует!\n";
			f = true;
		}
		if (!f) {
			--size;
			A*ptr = new A[size];                               // создание массива указателей на записи
			size_t n = 0;
			for (size_t i = 0; i < pos - 1; i++, n++) {         // переписываем указатели до позиции в новый массив указателей
				ptr[n] = arr[i];
			}
			for (size_t i = pos; i < size + 1; i++, n++) {       // пропускаем удаляемую позицию и переписываем указатели после позиции
				ptr[n] = arr[i];
			}
			delete[] arr;                                       // удаляем старый массив указателей на указатели
			arr = ptr;                                          // переназначаем старый массив указателей на новый
			cout << "Элемент [" << pos << "] удален!\n";
		}
	}
	void add(A value, size_t pos) {                             // функция добавления записи 
		bool f = false;
		if (pos <= 0 || pos > size+1)
		{
			cout << "Ошибка! Неверно выбран номер позиции\n";
			f = true;
		}
		if (!f) {
			++size;
			A*ptr = new A[size];                              // создание массива указателей на записи
			size_t n = 0;
			for (size_t i = 0; i < pos - 1; i++, n++) {            // переписываем указатели до позиции в новый массив указателей
				ptr[n] = arr[i];
			}
			ptr[n] = value;
			n++;
			for (size_t i = pos-1; i < size; i++, n++) {          // пропускаем удаляемую позицию и переписываем указатели после позиции
				ptr[n] = arr[i];
			}
			delete[] arr;                                       // удаляем старый массив указателей на указатели
			arr = ptr;                                          // переназначаем старый массив указателей на новый
			cout << "Новый элемент добавлен в позицию [" << pos << "]!\n";
		}
	}
	void add_var(int kol) {                             // функция добавления записи 
		A*ptr = new A[size+kol];                              // создание массива указателей на записи
		for (size_t i = 0; i < size; i++) {            // переписываем указатели до позиции в новый массив указателей
			ptr[i] = arr[i];
		}
		size += kol;
		size_t n = 0;
		cout << "Введите новые элементы\n";
		for (size_t i = size - kol; i < size; i++, n++) {            // переписываем указатели до позиции в новый массив указателей
			cout << n + 1 << " элемент = ";
			cin >> ptr[i];
		}
		delete[] arr;                                       // удаляем старый массив указателей на указатели
		arr = ptr;                                          // переназначаем старый массив указателей на новый
		cout << "Новые элементы добавлены в массив!\n";
	}

};
void quit() {                          // функция выхода
	cout << "Завершение работы!\n";
	system("pause");
	exit(0);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((size_t)time(0));
	int a = -1, vyb = 0;
	size_t n, pos;
	Array <int> *arr1;
	Array <double> *arr2;
	cout << "Необходимо ввести данные в массив\n";
	while (vyb < 1 || vyb>2) {
		cout << "Выберите способ ввода:\n";
		cout << "1 - ручной ввод;\n";
		cout << "2 - автоматический ввод.\n";
		cout << "Ваш выбор: ";
		cin >> vyb;
		switch (vyb)
		{
			// ручной ввод
		case 1:
			system("cls");
			cout << "Целочисленный тип int\n";
			arr1 = new Array <int>;
			arr1->init_size();
			arr1->init_arr();
			cout << "Данные в массив типа int внесены успешно!\n\n";
			cout << "Вещественный тип double\n";
			arr2 = new Array <double>;
			arr2->init_size();
			arr2->init_arr();
			cout << "Данные в массив типа double внесены успешно!\n\n";
			system("pause");
			break;
			// автоматический ввод
		case 2:
			system("cls");
			arr1 = new Array <int>(20, 50, 0);
			cout << "Данные в массив на 20 элементов типа int внесены успешно!\n";
			arr2 = new Array <double>(20, 50, 0);
			cout << "Данные в массив на 20 элементов типа double внесены успешно!\n\n";
			system("pause");
			break;
		default:
			while (cin.get() != '\n');
			cout << "Неверно! Повторите ввод!\n";
		}
	}
	while (a) {
		int menu = -1;
		system("cls");
		cout << "1 - просмотр содержимого массивов\n";
		cout << "2 - добавление элемента в массив\n";
		cout << "3 - удаление элемента из массива\n";
		cout << "4 - сортировка элементов в массиве\n";
		cout << "5 - поиск минимального значения в массиве\n";
		cout << "6 - поиск максмального значения в массиве\n";
		cout << "7 - копирование массивов\n";
		cout << "8 - добавление элементов в конец массива\n";
		cout << "0 - выход\n";
		cout << "Ваш выбор: ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "\nМассив типа int\n";
			cout << "Введите размерность отображения массива: ";
			cin >> n;
			arr1->show_Arr(n);
			cout << "\n\nМассив типа double\n";
			cout << "Введите размерность отображения массива: ";
			cin >> n;
			arr2->show_Arr(n);
			system("pause");
			break;
		case 2:
			int n; double m;
			cout << "Исходный массив int:\n";
			arr1->show_Arr(10);
			cout << "Введите номер позиции нового элемента: ";
			cin >> pos;
			cout << "Введите значение нового элемента массива типа int: ";
			cin >> n;
			arr1->add(n, pos);
			arr1->show_Arr(10);
			cout << "\n\nИсходный массив double:\n";
			arr2->show_Arr(10);
			cout << "Введите номер позиции нового элемента: ";
			cin >> pos;
			cout << "Введите значение нового элемента массива типа double: ";
			cin >> m;
			arr2->add(m, pos);
			arr2->show_Arr(10);
			system("pause");
			break;
		case 3:
			cout << "Исходный массив int:\n";
			arr1->show_Arr(10);
			cout << "Введите номер позиции удаляемого элемента: ";
			cin >> pos;
			arr1->del(pos);
			cout << "Новый массив int:\n";
			arr1->show_Arr(10);
			cout << "\nИсходный массив double:\n";
			arr2->show_Arr(10);
			cout << "Введите номер позиции удаляемого элемента: ";
			cin >> pos;
			arr2->del(pos);
			cout << "Новый массив int:\n";
			arr2->show_Arr(10);
			system("pause");
			break;
		case 4:
			cout << "\n\nДо сортировки массива int:\n";
			arr1->show_Arr(10);
			arr1->sort();
			cout << "После сортировки массива int:\n";
			arr1->show_Arr(10);
			cout << "\nДо сортировки массива double:\n";
			arr2->show_Arr(10);
			arr2->sort();
			cout << "После сортировки массива double:\n";
			arr2->show_Arr(10);
			system("pause");
			break;
		case 5:
			cout << "Поиск минимального значения в массиве int\n";
			arr1->show_Arr(10);
			cout << "Минимальное значение в массиве int: "<<arr1->arr_Min()<<"\n\n";
			cout << "Поиск минимального значения в массиве double\n";
			arr2->show_Arr(10);
			cout << "Минимальное значение в массиве double: " << arr2->arr_Min() << "\n\n";
			system("pause");
			break;
		case 6:
			cout << "Поиск максимального значения в массиве int\n";
			arr1->show_Arr(10);
			cout << "Максмальное значение в массиве int: " << arr1->arr_Max() << "\n\n";
			cout << "Поиск максмального значения в массиве double\n";
			arr2->show_Arr(10);
			cout << "Максмальное значение в массиве double: " << arr2->arr_Max() << "\n\n";
			system("pause");
			break;
		case 7:
			cout << "Исходный массив int arr1:\n";
			arr1->show_Arr(10);
			Array <int> *arr3;
			arr3 = new Array <int>;
			*arr3 = *arr1;
			cout << "Новый массив int arr3:\n";
			arr3->show_Arr(10);
			system("pause");
			break;
		case 8:
			cout << "Исходный массив int:\n";
			arr1->show_Arr(10);
			cout << "Введите количество новых элементов: ";
			cin >> n;
			arr1->add_var(n);
			arr1->show_Arr(10);
			cout << "\n\nИсходный массив double:\n";
			arr2->show_Arr(10);
			cout << "Введите количество новых элементов: ";
			cin >> n;
			arr2->add_var(n);
			arr2->show_Arr(10);
			system("pause");
			break;
		case 0:
			quit();
			break;
		default:
			while (cin.get() != '\n');
			cout << "Неверно! Повторите ввод!\n";
		}
	}
	system("pause");
	return 0;
}
