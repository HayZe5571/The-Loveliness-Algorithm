#include "MyIncludes.h"
#include "HeaderLaba6.h"

void saveInitialData1() {
    // Создаем файл masters.txt
    ofstream mastersFile("masters.txt");
    if (mastersFile.is_open()) {
        mastersFile << "Маляр,25\n";
        mastersFile << "Механик,30\n";
        mastersFile << "Помощник_механика,21\n";
        mastersFile.close();
        cout << "Файл masters.txt создан" << endl;
    }

    // Создаем файл details.txt
    ofstream detailsFile("details.txt");
    if (detailsFile.is_open()) {
        detailsFile << "Двигатель,4.0,200,Механик\n";
        detailsFile << "Свечи_зажигания,1.0,15,Механик\n";
        detailsFile << "Тормозные_колодки,1.5,40,Механик\n";
        detailsFile << "Аккумулятор,0.5,80,Механик\n";
        detailsFile << "Ремень_ГРМ,2.0,25,Механик\n";
        detailsFile << "Масло_двигатель,0.5,20,Механик\n";
        detailsFile << "Фильтр_воздушный,0.3,10,Механик\n";
        detailsFile << "Фильтр_масляный,0.4,12,Механик\n";
        detailsFile << "Тормозная_жидкость,0.5,18,Механик\n";
        detailsFile << "Охлаждающая_жидкость,0.5,22,Механик\n";
        detailsFile << "Подвеска_передняя,3.0,150,Механик\n";
        detailsFile << "Подвеска_задняя,2.5,120,Механик\n";
        detailsFile << "Рулевая_рейка,3.5,180,Механик\n";
        detailsFile << "Сцепление,4.0,200,Механик\n";
        detailsFile << "Коробка_передач,5.0,300,Механик\n";
        detailsFile << "Шины,1.0,80,Механик\n";
        detailsFile << "Диски,1.5,120,Механик\n";
        detailsFile << "Генератор,2.0,100,Механик\n";
        detailsFile << "Стартер,1.5,90,Механик\n";
        detailsFile << "Топливный_насос,2.0,110,Механик\n";
        detailsFile << "Фары_передние,1.0,60,Механик\n";
        detailsFile << "Фары_задние,0.8,50,Механик\n";
        detailsFile << "Поворотники,0.5,15,Механик\n";
        detailsFile << "Стекло_лобовое,2.0,150,Механик\n";
        detailsFile << "Стекло_заднее,1.5,120,Механик\n";
        detailsFile << "Боковые_стекла,1.0,80,Механик\n";
        detailsFile << "Зеркала_боковые,0.8,40,Механик\n";
        detailsFile << "Бампер_передний,2.5,100,Механик\n";
        detailsFile << "Бампер_задний,2.0,90,Механик\n";
        detailsFile << "Двери,3.0,180,Механик\n";
        detailsFile << "Капот,2.0,120,Механик\n";
        detailsFile << "Крышка_багажника,1.5,100,Механик\n";
        detailsFile << "Краска_кузова,3.0,80,Маляр\n";
        detailsFile << "Лак,2.0,60,Маляр\n";
        detailsFile << "Полировка,1.5,40,Маляр\n";
        detailsFile << "Шпаклевка,2.5,50,Маляр\n";
        detailsFile << "Защитная_пленка,4.0,120,Маляр\n";
        detailsFile << "Тонировка,2.0,70,Маляр\n";
        detailsFile << "Сигнализация,2.0,100,Механик\n";
        detailsFile << "Музыкальная_система,3.0,150,Механик\n";
        detailsFile << "Колонки,1.5,60,Механик\n";
        detailsFile << "Усилитель,1.0,80,Механик\n";
        detailsFile << "Кондиционер,4.0,200,Механик\n";
        detailsFile << "Печка,3.0,120,Механик\n";
        detailsFile << "Руль,1.5,70,Механик\n";
        detailsFile << "Кресла,2.0,100,Механик\n";
        detailsFile << "Ремни_безопасности,1.0,30,Механик\n";
        detailsFile << "Щетки_стеклоочистителя,0.3,15,Механик\n";
        detailsFile << "Жидкость_стеклоомывателя,0.2,8,Механик\n";
        detailsFile.close();
        cout << "Файл details.txt создан" << endl;
    }

    cout << "Начальные данные сохранены в файлы!" << endl;
}