//  Создать классы «Учащийся колледжа», «Школьник», «Студент», «Студент - сотрудник компании» с необходимым
// набором полей и методов. Создать массив объектов базового класса и заполнить этот массив объектами
// базового и производных классов.Вывести информацию о студентах, студентах - сотрудниках, учащихся и
// школьниках на экран и в файл.В отдельный файл и на экран вывести данные о наиболее успевающем студенте,
// учащемся и школьнике.Классы должны содержать методы получения и изменения значений всех полей.Все поля
// классов должны быть объявлены с атрибутами private или protected.

#include "MyIncludes.h"
#include "HeaderLaba3.h"

extern vector<Learner*> learners;

extern void Laba3() {
    int choice;
    string all = "all_learners_data.txt", best = "best_learners_data.txt";

    do {
        cout << "\n========== МЕНЮ ЛАБАРАТОРНОЙ №3 ==========" << endl;
        cout << "1. Внести информацию об учащихся" << endl;
        cout << "2. Вывести всю информацию об учащихся" << endl;
        cout << "3. Показать самого успешного учащегося" << endl;
        cout << "4. Сохранить данные в файлы" << endl;
        cout << "5. Загрузить данные из файлов" << endl;
        cout << "6. Очистить все данные об учащихся" << endl;
        cout << "7. Выход в главное меню" << endl;

        cout << "Выберите опцию: ";
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Выберите из предложеных вариантов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: addLearners(); break;
        case 2: displayAllLearners(); break;
        case 3: displayTopLearners(); break;
        case 4: saveAllToFile(all); break;
        case 5: loadAllFromFile(all); break;
        case 6: clearLearners(); break;
        case 7: cout << "Возврат в главное меню..." << endl; break;
        }
    } while (choice != 7);
}