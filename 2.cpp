/*Вывести литералы всех строк в обратном порядке*/

#include <iostream>
#include <string>
#include <fstream>

class Stack {
private:
    struct Node { //Узел стека
        char text;
        Node* next;
    };
    Node* begin;
    int size;
public:
    Stack() {
        begin = NULL;
        size = 0;
    }
    ~Stack() {
        Node* temp = begin;
        while (size > 0) {
            begin = begin->next;
            delete temp;
            temp = begin;
        }
    }
    bool isEmpty() {//Проверка на пустоту
        if (size == 0) {
            return true;
        }
        return false;
    };
    void pushBegin(char x) { // Добавление элемента
        if (begin == NULL) {
            Node* n = new Node;
            n->text = x;
            begin = n;
        }
        else {// если не пуст
            Node* n = new Node;
            n->text = x;
            n->next = begin;
            begin = n;
        }
        size++;
    }
    void popBegin() {//Удаление элемента
        if (begin) {
            Node* cur = new Node;
            cur = begin;
            begin = cur->next;
            delete(cur);
            size--;
        }
    }
    char  getBegin() {//Получение первого элемента
        if (begin) {
            return begin->text;
        }

    }
    bool isFull() {
        return true;
    }
};

using namespace std;

int main() {

    setlocale(LC_ALL, "ru");

    ifstream inputFile("123.txt");
    if (!inputFile.is_open()) {
        cout << "open file error" << endl;
    }
    string str;
    while (getline(inputFile, str)) {
        Stack  st;
        string::const_iterator firstIterator = str.begin();
        string::const_iterator lastIterator = str.end();
        while (firstIterator != lastIterator) {
            st.pushBegin(*firstIterator);
            ++firstIterator;
        }
        while (!st.isEmpty()) {
            cout << st.getBegin();
            st.popBegin();
        }
        cout << endl;
    }
}
