//                          ����.�������� - ��������������� ���������������� �� C++.
//                                      �������� ������� � ������ 3
// �������� ����� Array. ����� Array - ��� ����� ������������� �������.
// ������ ������� ����� ���� ������� � �������� ��������� ��� ����� � ������� ������ ������� - �����.
// ����� ������ ��������� ��������� ������ ����������, ���������� ���������� �������, ��������
// ������ �������, ����������� ������, ���������� ����������� � ������������ ��������.
// ����� ������ ��������� ����� �������������(����������� ����������� ����������), ����������.
#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;
template <typename A > class Array
{
private:
	size_t size;
	A *arr, max, min;          // ��������� �� ������ int
public:
	Array()                                  // ����������� �� ���������
	{
		arr = new A [size];
	}
	Array(size_t Size)                 // ����������� 
	{
		arr = new A [Size];
	}
	Array(size_t Size, A max, A min)                 // ����������� 
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
			cout << "������� ������ �������: ";
			cin >> size;
			if (size < 1)
				cout << "\n������! ����� ������ 1!\n";
		} while (size < 1);
	}
	void init_arr() {
		for (size_t i = 0; i < size; i++) {
			cout << "arr [" << i + 1 << "] = ";
			cin >> arr[i];
		}
	}
	Array(const Array& ob)                   // ����������� �����
	{
		arr = new A[ob.size];
		for (size_t i = 0; i < ob.size; i++) {
			arr[i] = ob.arr[i];
		}
	}
	~Array()                                 // ����������
	{
		delete arr;
	}
	void show_Arr(size_t n)                             // ����������� ����������� �������
	{
		for (size_t i = 0; i < size; i++) {
			cout << arr[i] << "\t";
			if ((i + 1) % n == 0) cout << endl;
			if(i+1==size) cout << endl;
		}
	}
	void sort() {   // ���������� ������� �������
		for (size_t k = 0; k < size - 1; k++) //k-����� ������� ����������� �������
		{   //����� ��������
			size_t imin = k;
			for (size_t i = k + 1; i<size; i++) //���������� �� k �� �����
				if (arr[i] < arr[imin]) {
					imin = i;
				}
			//����� �������
			//������������ k-�� � ������������
			A tmp = arr[k];
			arr[k] = arr[imin];
			arr[imin] = tmp;
		}
	}
	A arr_Min() {        // ����� ������������ �������� �������
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
	A arr_Max() {        // ����� ������������� �������� �������
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
	void del(size_t pos) {                        // ������� �������� ������ 
		bool f = false;
		if (pos <= 0 || pos > size)
		{
			cout << "[" << pos << "] ������� �����������!\n";
			f = true;
		}
		if (!f) {
			--size;
			A*ptr = new A[size];                               // �������� ������� ���������� �� ������
			size_t n = 0;
			for (size_t i = 0; i < pos - 1; i++, n++) {         // ������������ ��������� �� ������� � ����� ������ ����������
				ptr[n] = arr[i];
			}
			for (size_t i = pos; i < size + 1; i++, n++) {       // ���������� ��������� ������� � ������������ ��������� ����� �������
				ptr[n] = arr[i];
			}
			delete[] arr;                                       // ������� ������ ������ ���������� �� ���������
			arr = ptr;                                          // ������������� ������ ������ ���������� �� �����
			cout << "������� [" << pos << "] ������!\n";
		}
	}
	void add(A value, size_t pos) {                             // ������� ���������� ������ 
		bool f = false;
		if (pos <= 0 || pos > size+1)
		{
			cout << "������! ������� ������ ����� �������\n";
			f = true;
		}
		if (!f) {
			++size;
			A*ptr = new A[size];                              // �������� ������� ���������� �� ������
			size_t n = 0;
			for (size_t i = 0; i < pos - 1; i++, n++) {            // ������������ ��������� �� ������� � ����� ������ ����������
				ptr[n] = arr[i];
			}
			ptr[n] = value;
			n++;
			for (size_t i = pos-1; i < size; i++, n++) {          // ���������� ��������� ������� � ������������ ��������� ����� �������
				ptr[n] = arr[i];
			}
			delete[] arr;                                       // ������� ������ ������ ���������� �� ���������
			arr = ptr;                                          // ������������� ������ ������ ���������� �� �����
			cout << "����� ������� �������� � ������� [" << pos << "]!\n";
		}
	}
	void add_var(int kol) {                             // ������� ���������� ������ 
		A*ptr = new A[size+kol];                              // �������� ������� ���������� �� ������
		for (size_t i = 0; i < size; i++) {            // ������������ ��������� �� ������� � ����� ������ ����������
			ptr[i] = arr[i];
		}
		size += kol;
		size_t n = 0;
		cout << "������� ����� ��������\n";
		for (size_t i = size - kol; i < size; i++, n++) {            // ������������ ��������� �� ������� � ����� ������ ����������
			cout << n + 1 << " ������� = ";
			cin >> ptr[i];
		}
		delete[] arr;                                       // ������� ������ ������ ���������� �� ���������
		arr = ptr;                                          // ������������� ������ ������ ���������� �� �����
		cout << "����� �������� ��������� � ������!\n";
	}

};
void quit() {                          // ������� ������
	cout << "���������� ������!\n";
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
	cout << "���������� ������ ������ � ������\n";
	while (vyb < 1 || vyb>2) {
		cout << "�������� ������ �����:\n";
		cout << "1 - ������ ����;\n";
		cout << "2 - �������������� ����.\n";
		cout << "��� �����: ";
		cin >> vyb;
		switch (vyb)
		{
			// ������ ����
		case 1:
			system("cls");
			cout << "������������� ��� int\n";
			arr1 = new Array <int>;
			arr1->init_size();
			arr1->init_arr();
			cout << "������ � ������ ���� int ������� �������!\n\n";
			cout << "������������ ��� double\n";
			arr2 = new Array <double>;
			arr2->init_size();
			arr2->init_arr();
			cout << "������ � ������ ���� double ������� �������!\n\n";
			system("pause");
			break;
			// �������������� ����
		case 2:
			system("cls");
			arr1 = new Array <int>(20, 50, 0);
			cout << "������ � ������ �� 20 ��������� ���� int ������� �������!\n";
			arr2 = new Array <double>(20, 50, 0);
			cout << "������ � ������ �� 20 ��������� ���� double ������� �������!\n\n";
			system("pause");
			break;
		default:
			while (cin.get() != '\n');
			cout << "�������! ��������� ����!\n";
		}
	}
	while (a) {
		int menu = -1;
		system("cls");
		cout << "1 - �������� ����������� ��������\n";
		cout << "2 - ���������� �������� � ������\n";
		cout << "3 - �������� �������� �� �������\n";
		cout << "4 - ���������� ��������� � �������\n";
		cout << "5 - ����� ������������ �������� � �������\n";
		cout << "6 - ����� ������������ �������� � �������\n";
		cout << "7 - ����������� ��������\n";
		cout << "8 - ���������� ��������� � ����� �������\n";
		cout << "0 - �����\n";
		cout << "��� �����: ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "\n������ ���� int\n";
			cout << "������� ����������� ����������� �������: ";
			cin >> n;
			arr1->show_Arr(n);
			cout << "\n\n������ ���� double\n";
			cout << "������� ����������� ����������� �������: ";
			cin >> n;
			arr2->show_Arr(n);
			system("pause");
			break;
		case 2:
			int n; double m;
			cout << "�������� ������ int:\n";
			arr1->show_Arr(10);
			cout << "������� ����� ������� ������ ��������: ";
			cin >> pos;
			cout << "������� �������� ������ �������� ������� ���� int: ";
			cin >> n;
			arr1->add(n, pos);
			arr1->show_Arr(10);
			cout << "\n\n�������� ������ double:\n";
			arr2->show_Arr(10);
			cout << "������� ����� ������� ������ ��������: ";
			cin >> pos;
			cout << "������� �������� ������ �������� ������� ���� double: ";
			cin >> m;
			arr2->add(m, pos);
			arr2->show_Arr(10);
			system("pause");
			break;
		case 3:
			cout << "�������� ������ int:\n";
			arr1->show_Arr(10);
			cout << "������� ����� ������� ���������� ��������: ";
			cin >> pos;
			arr1->del(pos);
			cout << "����� ������ int:\n";
			arr1->show_Arr(10);
			cout << "\n�������� ������ double:\n";
			arr2->show_Arr(10);
			cout << "������� ����� ������� ���������� ��������: ";
			cin >> pos;
			arr2->del(pos);
			cout << "����� ������ int:\n";
			arr2->show_Arr(10);
			system("pause");
			break;
		case 4:
			cout << "\n\n�� ���������� ������� int:\n";
			arr1->show_Arr(10);
			arr1->sort();
			cout << "����� ���������� ������� int:\n";
			arr1->show_Arr(10);
			cout << "\n�� ���������� ������� double:\n";
			arr2->show_Arr(10);
			arr2->sort();
			cout << "����� ���������� ������� double:\n";
			arr2->show_Arr(10);
			system("pause");
			break;
		case 5:
			cout << "����� ������������ �������� � ������� int\n";
			arr1->show_Arr(10);
			cout << "����������� �������� � ������� int: "<<arr1->arr_Min()<<"\n\n";
			cout << "����� ������������ �������� � ������� double\n";
			arr2->show_Arr(10);
			cout << "����������� �������� � ������� double: " << arr2->arr_Min() << "\n\n";
			system("pause");
			break;
		case 6:
			cout << "����� ������������� �������� � ������� int\n";
			arr1->show_Arr(10);
			cout << "����������� �������� � ������� int: " << arr1->arr_Max() << "\n\n";
			cout << "����� ������������ �������� � ������� double\n";
			arr2->show_Arr(10);
			cout << "����������� �������� � ������� double: " << arr2->arr_Max() << "\n\n";
			system("pause");
			break;
		case 7:
			cout << "�������� ������ int arr1:\n";
			arr1->show_Arr(10);
			Array <int> *arr3;
			arr3 = new Array <int>;
			*arr3 = *arr1;
			cout << "����� ������ int arr3:\n";
			arr3->show_Arr(10);
			system("pause");
			break;
		case 8:
			cout << "�������� ������ int:\n";
			arr1->show_Arr(10);
			cout << "������� ���������� ����� ���������: ";
			cin >> n;
			arr1->add_var(n);
			arr1->show_Arr(10);
			cout << "\n\n�������� ������ double:\n";
			arr2->show_Arr(10);
			cout << "������� ���������� ����� ���������: ";
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
			cout << "�������! ��������� ����!\n";
		}
	}
	system("pause");
	return 0;
}
