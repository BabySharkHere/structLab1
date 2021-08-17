#include <iostream>
#include <locale>
#include <cstdio>
#include <Windows.h>
#include <cstring>
#pragma warning(disable:4996)

using namespace std;

struct hotelInfo //информация о данных узла
{
	char country[30];
	char town[30];
	char name[30];
	int class_hotel;
	double price_day;
	double price_road;


};
typedef struct hotelInfo DataType; //Информация о данных узла
struct node //Узел списка
{
	DataType data;
	struct node* next;
};
typedef struct node* list; //Переопределение имени узла
DataType inputHoteLInformation(void); //Ввод информации об отелях
list readFile(char* filename); //Чтение файла
list newNode(list, DataType); //Новый узел
list addToEnd(list, DataType); //Добавление узла в конец
int writeFile(char* filename, list); //Сохранение файла
void deleteList(list); //Удаление списка
void edit(list); //Изменение узла
void show(list); //Показать список
void search(list begin); //Поиск узла
list deleteNode(list); //Удаление узла
list deleteLast(list); //Удаление последнего узла
void showExact(list); //Вывод узла
void showMiddlePrice(list); //Вывод узла
list editNote(list, char*); //Изменить запись
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file[50];
	int menu;
	list hotel = NULL;
	if (argc > 1) {
		hotel = readFile(argv[1]);
	}
	else {
		cout << "Введите название файла: ";
		while (!(cin >> file) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			system("cls");
			cout << "Ошибка ввода! Попробуйте снова" << endl;
		}
	}
	hotel = readFile(file);
	do
	{
		cout << " 1. Добавить новый отель в конце списка" << endl;
		cout << " 2. Показать список" << endl;
		cout << " 3. Показать отель определенного класса, где цена проживания минимальна" << endl;
		cout << " 4. Удалить последний отель" << endl;
		cout << " 5. Показать среднюю стоимость тура на неделю в отелях определенного класса" << endl;
		cout << " 6. Изменить данные об отеле" << endl;
		cout << " 0. Выход" << endl;
		while (!(cin >> menu) || (cin.peek() != '\n')) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка ввода! Попробуйте снова" << endl;
		}
		switch (menu)
		{
		case 1: {
			hotel = addToEnd(hotel, inputHoteLInformation());
			break;
		}
		case 2: {
			show(hotel);
			system("Pause");
			system("CLS");
			break;
		}
		case 3: {
			show(hotel);
			showExact(hotel);
			system("Pause");
			system("CLS");
			break;
		}
		case 4: {
			hotel = deleteLast(hotel);
			cout << "Удаление прошло успешно!" << endl;
			system("Pause");
			system("CLS");
			break;
		}
		case 5: {
			show(hotel);
			showMiddlePrice(hotel);
			system("Pause");
			system("CLS");
			break;
		}
		case 6: {
			show(hotel);
			char name[30];
			cout << "Введите название отеля:" << endl;
			cin >> name;
			hotel = editNote(hotel, name);
			break;
		}
		}

	} while (menu != 0);

	if (writeFile(file, hotel))
		cout << "Файл сохранён" << endl;
	else
		cout << "Файл не сохранён" << endl;

	deleteList(hotel);

	return 0;
}
DataType inputHoteLInformation(void)
{
	DataType hotel;
	cout << "Введите страну:" << endl;
	while (!(cin >> hotel.country) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	cout << "Введите город:" << endl;
	while (!(cin >> hotel.town) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	cout << "Введите название отеля:" << endl;
	while (!(cin >> hotel.name) || (cin.peek() != '\n') ||
		(hotel.name <= 0)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	cout << "Введите класс отеля(1-5):" << endl;
	while (!(cin >> hotel.class_hotel) || (cin.peek() != '\n') ||
		(hotel.class_hotel < 1 || hotel.class_hotel > 5)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	cout << "Введите стоимость за день(1-50.000):" << endl;
	while (!(cin >> hotel.price_day) || (cin.peek() != '\n') ||
		(hotel.price_day <= 0 || hotel.price_day > 50000)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	cout << "Введите стоимость дороги в оба конца(1-10.000):" << endl;
	while (!(cin >> hotel.price_road) || (cin.peek() != '\n') ||
		(hotel.price_road <= 0 || hotel.price_road > 10000)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}
	system("Pause");
	system("CLS");
	return hotel;
}
list editNote(list begin, char* name) {
	list cur = begin;
	while (cur) {
		if (strcmp(cur->data.name, name) == 0) {

			cout << "Введите страну:" << endl;
			while (!(cin >> cur->data.country) || (cin.peek() != '\n')) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;
			}

			cout << "Введите город:" << endl;
			while (!(cin >> cur->data.town) || (cin.peek() != '\n')) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;
			}

			cout << "Введите класс(1-5):" << endl;
			while (!(cin >> cur->data.class_hotel) || (cin.peek() != '\n') ||
				(cur->data.class_hotel < 1 || cur->data.class_hotel > 5)) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;
			}

			cout << "Введите цену проживания(1-50.000):" << endl;
			while (!(cin >> cur->data.price_day) || (cin.peek() != '\n') ||
				(cur->data.price_day <= 0 || cur->data.price_day > 50000)) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;
			}

			cout << "Введите цену проезда в оба конца(1-10.000):" << endl;
			while (!(cin >> cur->data.price_road) || (cin.peek() != '\n') ||
				(cur->data.price_road <= 0 || cur->data.price_road > 10000)) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;
			}
			system("Pause");
			system("CLS");
			/*while (!(cin >> cur->data.price) || (cin.peek() != '\n')
				|| (cur->data.price <= 0)) {
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Попробуйте снова" << endl;*/
			return begin;
		}
		else {
			cur = cur->next;
			cout << "Записи с таким именем нет" << endl;
			getchar();
			return begin;
		}
	}
}
list newNode(list begin, DataType hotel)
{
	list temp = (list)malloc(sizeof(struct node));
	temp->data = hotel;
	temp->next = begin;
	return temp;
}
list findLast(list cur) {
	if (!cur) {
		return NULL;
	}
	while (cur->next) {
		cur = cur->next;
	}
	return cur;
}
list addToEnd(list begin, DataType hotel) {
	list cur;
	if (begin == NULL) {
		return newNode(NULL, hotel);
	}
	cur = findLast(begin);
	cur->next = newNode(NULL, hotel);
	return begin;
}
list readFile(char* filename)
{
	FILE* f;
	DataType hotel;
	list begin = NULL, cur;
	if ((f = fopen(filename, "rb")) == NULL)
	{
		perror("Ошибка открытия файла");
		getchar();
		return begin;
	}
	if (fread(&hotel, sizeof(hotel), 1, f))
		begin = newNode(NULL, hotel);
	else
		return NULL;
	cur = begin;
	while (fread(&hotel, sizeof(hotel), 1, f))
	{
		cur->next = newNode(NULL, hotel);
		cur = cur->next;
	}
	fclose(f);
	return begin;
}
list deleteNode(list begin) {
	list tmp = begin;
	if (begin) {
		begin = begin->next;
		free(tmp);
	}
	return begin;
}
list deleteLast(list begin) {
	list cur = begin;
	if (cur == NULL) {
		return NULL;
	}
	if (cur->next == NULL) {
		free(cur);
		begin = NULL;
		return begin;
	}
	while (cur->next->next) {
		cur = cur->next;
	}
	cur->next = deleteNode(cur->next);
	return begin;
}
void showExact(list begin) {
	int k = 0, a = 0;

	double min_price = 50001;
	if (!begin) {
		cout << "Список пуст" << endl;
		getchar();
		return;
	}
	cout << "Выберите класс отеля:" << endl;
	while (!(cin >> a) || (cin.peek() != '\n') ||
		(a < 1 || a > 5)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}


	list cur = begin;
	while (cur) {
		if (cur->data.price_day < min_price && cur->data.class_hotel == a)
			min_price = cur->data.price_day;
		cur = cur->next;
	}
	cur = begin;
	while (cur) {
		if (cur->data.class_hotel == a) {

			if (cur->data.price_day == min_price) {
				printf(" Страна: %-17s \n Город: %-17s \n Отель: %-17s\n Класс: %d\n Цена за неделю: %.3lf\n Цена за дорогу: %.3lf \n", cur->data.country,
					cur->data.town, cur->data.name, cur->data.class_hotel, cur->data.price_day * 7, cur->data.price_road);
				k++;
				break;
			}



		}
		cur = cur->next;
	}

	if (k == 0)
		cout << "Невозможно" << endl;

}

void showMiddlePrice(list begin) {
	int  a;
	int k = 0;

	double mid_price = 0;
	if (!begin) {
		cout << "Список пуст" << endl;
		getchar();
		return;
	}
	cout << "Выберите класс отеля" << endl;
	while (!(cin >> a) || (cin.peek() != '\n') ||
		(a < 1 || a > 5)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Попробуйте снова" << endl;
	}

	list cur = begin;


	while (cur) {
		if (cur->data.class_hotel == a) {
			mid_price = mid_price + (cur->data.price_road + cur->data.price_day * 7);
			k++;
		}
		cur = cur->next;

	}
	if (k == 0) {
		cout << " Отель этого класса не найден " << endl;
	}
	else {
		mid_price = mid_price / k;
		cout << " Средняя стоимость: " << mid_price << endl;
	}
}


void deleteList(list begin)
{
	list temp = begin;
	while (temp)
	{
		begin = temp->next;
		free(temp);
		temp = begin;
	}
}
int writeFile(char* filename, list begin)
{
	FILE* f;
	if ((f = fopen(filename, "wb")) == NULL)
	{
		perror("Ошибка создания файла");
		getchar();
		return 0;
	}
	while (begin)
	{
		if (fwrite(&begin->data, sizeof(DataType), 1, f))
			begin = begin->next;
		else
			return 0;
	}
	return 1;
}
void print_data(DataType hotel)
{
	printf("       Страна : %s| Город : %s| Название отеля : %s| Класс отеля : %d| Стоимость проживания: %lf | Стоимость проезда: %lf",
		hotel.country, hotel.town, hotel.name, hotel.class_hotel, hotel.price_day, hotel.price_road);
}
void show(list cur)
{
	int k = 0;
	system("CLS");
	if (cur == NULL)
	{
		cout << "Список пуст" << endl;
		getchar();
		return;
	}
	cout << "| N  |      Страна       |      Город       |  Название отеля  | Класс | Стоимость за сутки| Стоимость проезда |" << endl;
	while (cur)
	{
		printf("|%3d | %-17s |%-17s |%-17s |%6d |%18.2lf |%18.2lf |\n", ++k, cur->data.country,
			cur->data.town, cur->data.name, cur->data.class_hotel, cur->data.price_day, cur->data.price_road);
		cur = cur->next;
	}
}