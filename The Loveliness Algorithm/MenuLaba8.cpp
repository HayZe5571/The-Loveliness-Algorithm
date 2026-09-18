// Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной
// области «Выставка».Функционал программы должен позволить собрать данные об экспозиции.Сгенерировать минимум пять типов
// исключительных ситуаций.Реализовать перенаправление исключительных ситуаций.  Сгенерировать минимум одну исключительную
// ситуацию с оператором new. Создать исключительную ситуацию в конструкторе и продемонстрировать вызов конструкторов и
// деструкторов.Задать собственную функцию завершения.Создать собственный(пользовательский) класс исключения, сгенерировать
// исключение этого типа и обработать его.

#include "MyIncludes.h"
#include "HeaderLaba8.h"

void myTerminateHandler() {
    cout << "\n!!! СРАБОТАЛА СОБСТВЕННАЯ ФУНКЦИЯ ЗАВЕРШЕНИЯ !!!" << endl;
    cout << "Программа будет завершена из-за неперехваченного исключения." << endl;
    clearAllData8();
    exit(1);
}

//void loadSampleData() {
//    exhibits.clear();
//    Painting* p1 = new Painting("Мона Лиза", "Леонардо да Винчи", 1503, 850000, "Ренессанс", "Масло", 77, 53);
//    exhibits.push_back(p1);
//    Painting* p2 = new Painting("Звездная ночь", "Винсент ван Гог", 1889, 120000, "Постимпрессионизм", "Масло", 73.7, 92.1);
//    exhibits.push_back(p2);
//    Painting* p3 = new Painting("Крик", "Эдвард Мунк", 1893, 110000, "Экспрессионизм", "Масло", 91, 73.5);
//    exhibits.push_back(p3);
//    Painting* p4 = new Painting("Герника", "Пабло Пикассо", 1937, 200000, "Кубизм", "Масло", 349.3, 776.6);
//    exhibits.push_back(p4);
//    Painting* p5 = new Painting("Постоянство памяти", "Сальвадор Дали", 1931, 150000, "Сюрреализм", "Масло", 24.1, 33);
//    exhibits.push_back(p5);
//    Sculpture* s1 = new Sculpture("Давид", "Микеланджело", 1504, 500000, "Мрамор", 5570, false);
//    exhibits.push_back(s1);
//    Sculpture* s2 = new Sculpture("Мыслитель", "Огюст Роден", 1904, 350000, "Бронза", 700, false);
//    exhibits.push_back(s2);
//    Sculpture* s3 = new Sculpture("Венера Милосская", "Александрос Антиохийский", -130, 400000, "Мрамор", 900, false);
//    exhibits.push_back(s3);
//
//    halls.clear();
//    ExhibitionHall* h1 = new ExhibitionHall("Зал Ренессанса", 50, 200);
//    h1->addExhibit(p1);
//    h1->addExhibit(s1);
//    halls.push_back(h1);
//    ExhibitionHall* h2 = new ExhibitionHall("Зал Современного Искусства", 40, 180);
//    h2->addExhibit(p2);
//    h2->addExhibit(p3);
//    h2->addExhibit(p4);
//    h2->addExhibit(p5);
//    halls.push_back(h2);
//    ExhibitionHall* h3 = new ExhibitionHall("Зал Классики", 35, 150);
//    h3->addExhibit(s2);
//    h3->addExhibit(s3);
//    halls.push_back(h3);
//}

void Laba8() {
    set_terminate(myTerminateHandler);

    //loadSampleData();

    int choice;
    do {
        cout << "\n========== ВЫСТАВКА ПРОИЗВЕДЕНИЙ ИСКУССТВА (ЛАБА 8) ==========" << endl;
        cout << "1. Добавить экспонат (с обработкой исключений)" << endl;
        cout << "2. Добавить выставочный зал" << endl;
        cout << "3. Показать все экспонаты" << endl;
        cout << "4. Сохранить данные в файл" << endl;
        cout << "5. Загрузить данные из файла" << endl;
        cout << "6. Очистить все данные" << endl;
        cout << "7. Выход в главное меню" << endl;

        choice = chek<int>("Выберите пункт", "Неверный выбор", [](int x) { return x >= 1 && x <= 7; });

        try {
            switch (choice) {
            case 1: addExhibitWithExceptions(); break;
            case 2: addExhibitionHall(); break;
            case 3: displayAllExhibits(); break;
            case 4: saveToFile("exhibition_data.txt"); break;
            case 5: loadFromFile("exhibition_data.txt"); break;
            case 6: clearAllData8(); break;
            case 7: cout << "Возврат в главное меню..." << endl; break;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка в меню: " << e.what() << endl;
        }
        catch (...) {
            cout << "Неизвестная ошибка в меню" << endl;
        }

    } while (choice != 7);
}