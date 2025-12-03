#include "Set.h"


void printMenu() {
    cout << "\nМеню:" << endl;
    cout << "1. Ввести множество из строки" << endl;
    cout << "2. Проверить, пусто ли множество" << endl;
    cout << "3. Добавить элемент" << endl;
    cout << "4. Удалить элемент" << endl;
    cout << "5. Определить мощность множества" << endl;
    cout << "6. Проверка принадлежности элемента (оператор [])" << endl;
    cout << "7. Объединение двух множеств (+)" << endl;
    cout << "8. Объединение с присваиванием (+=)" << endl;
    cout << "9. Пересечение двух множеств (*)" << endl;
    cout << "10. Пересечение с присваиванием (*=)" << endl;
    cout << "11. Разность двух множеств (-)" << endl;
    cout << "12. Разность с присваиванием (-=)" << endl;
    cout << "13. Построить булеан множества" << endl;
    cout << "0. Выход" << endl;
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Set a;
    int choice;

    while (true) {
        printMenu();
        if (!(cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
        case 1: {
            cin >> a;
            cout << "Множество a = " << a << endl;
            break;
        }
        case 2:
            cout << (a.isEmpty() ? "Множество пусто" : "Множество не пусто") << endl;
            break;
        case 3: {
            string elem;
            cout << "Введите элемент: ";
            cin >> elem;
            a.addElement(elem);
            cout << "Теперь a = " << a << endl;
            break;
        }
        case 4: {
            string elem;
            cout << "Введите элемент для удаления: ";
            cin >> elem;
            if (a.removeElement(elem))
                cout << "Удалено. a = " << a << endl;
            else
                cout << "Такого элемента нет." << endl;
            break;
        }
        case 5:
            cout << "Мощность множества: " << a.size() << endl;
            break;
        case 6: {
            string elem;
            cout << "Введите элемент: ";
            cin >> elem;
            cout << (a[elem] ? "Принадлежит" : "Не принадлежит") << endl;
            break;
        }
        case 7: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            Set c = a + b;
            cout << "a + b = " << c << endl;
            break;
        }
        case 8: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            a += b;
            cout << "После a += b, a = " << a << endl;
            break;
        }
        case 9: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            Set c = a * b;
            cout << "a * b = " << c << endl;
            break;
        }
        case 10: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            a *= b;
            cout << "После a *= b, a = " << a << endl;
            break;
        }
        case 11: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            Set c = a - b;
            cout << "a - b = " << c << endl;
            break;
        }
        case 12: {
            Set b;
            cout << "Введите второе множество b:" << endl;
            cin >> b;
            a -= b;
            cout << "После a -= b, a = " << a << endl;
            break;
        }
        case 13: {
            Set p = a.powerSet();
            cout << "Булеан множества a: " << p << endl;
            break;
        }
        default:
            cout << "Нет такого пункта." << endl;
        }
    }

    cout << "Работа завершена!" << endl;
    return 0;
}
