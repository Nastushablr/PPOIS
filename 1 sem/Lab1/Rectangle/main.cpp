#include <iostream>
#include "Rectangle.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Rectangle r(0, 0, 0, 0);
    int choice;

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Ввести прямоугольник" << endl;
        cout << "2. Получить координаты вершин" << endl;
        cout << "3. Переместить прямоугольник" << endl;
        cout << "4. Изменить размер" << endl;
        cout << "5. Увеличить размер на единицу (++пре/пост)" << endl;
        cout << "6. Уменьшить размер на единицу (--пре/пост)" << endl;
        cout << "7. Построить прямоугольник, содержащий два (оператор +)" << endl;
        cout << "8. Построить с += (присваивание объединения)" << endl;
        cout << "9. Построить пересечение двух (оператор -)" << endl;
        cout << "10. Построить с -= (присваивание пересечения)" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта:" << endl;
        cin >> choice;

        if (choice == 0) break;
        switch (choice) {
        case 1:
            cin >> r;
            break;
        case 2:
            r.printCoords();
            break;
        case 3: {
            int dx, dy;
            cout << "dx, dy: ";
            cin >> dx >> dy;
            r.move(dx, dy);
            break;
        }
        case 4: {
            int dw, dh;
            cout << "dWidth, dHeight: ";
            cin >> dw >> dh;
            r.resize(dw, dh);
            break;
        }
        case 5: {
            ++r;
            cout << "Размер увеличен: " << r << endl;
            break;
        }
        case 6: {
            --r;
            cout << "Размер уменьшен: " << r << endl;
            break;
        }
        case 7: {
            Rectangle r2(0, 0, 0, 0);
            cout << "Ввод второго прямоугольника: ";
            cin >> r2;
            Rectangle united = r + r2;
            cout << "Результат объединения: " << united << endl;
            break;
        }
        case 8: {
            Rectangle r2(0, 0, 0, 0);
            cout << "Ввод второго прямоугольника: ";
            cin >> r2;
            r += r2;
            cout << "Результат присваивания объединения: " << r << endl;
            break;
        }
        case 9: {
            Rectangle r2(0, 0, 0, 0);
            cout << "Ввод второго прямоугольника: ";
            cin >> r2;
            Rectangle inter = r - r2;
            cout << "Результат пересечения: " << inter << endl;
            break;
        }
        case 10: {
            Rectangle r2(0, 0, 0, 0);
            cout << "Ввод второго прямоугольника: ";
            cin >> r2;
            r -= r2;
            cout << "Результат присваивания пересечения: " << r << endl;
            break;
        }
        default:
            cout << "Нет такого пункта!" << endl;
        }
    }
    cout << "Работа завершена!" << endl;
    return 0;
}