#include <iostream>
#include <fstream>
#include <string>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Compositeshape.h"
#include "cstring"

void shapeSort(Shape** figures, size_t size); // сортировка фигур по 

CompositeShape returnValue(CompositeShape& value)
{
    std::cout << "FOO " << std::endl;
    return value;
}

void printFigs(Shape** shapes, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << *shapes[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "ТЕСТ НА РАБОТУ С ФАЙЛОМ" << std::endl
        << "_______________________________________________" << std::endl;

    std::ifstream in("B:\\de\\Res\\DotNet\\лаба классы 2\\лаба классы 2\\in.txt");

    if (in.fail())
    {
        std::cerr << "Невозможно открыть файл!\n";
        return -1;
    }

    int count = 0; // ----------------------------------- считывание с файла -----------------------------------

    char* str = new char[1024];
    while (!in.eof()) {
        in.getline(str, 1024, '\n');
        if (!std::string(str).empty()) { // подсчет непустых строк/фигур
            count++;
        }
    }
    delete[] str;

    in.clear();
    in.seekg(0, std::ios::beg); //возврат в начало файла

    Shape** figures = new Shape * [count];

    std::string word;
    bool firstComm = true;
    int realCount = 0;
    while (!in.eof()) {
        in >> word;
        if (word == "RECTANGLE") {
            double  x1 = 0, 
                    y1 = 0, 
                    x2 = 0, 
                    y2 = 0;
            in >> x1 >> y1 >> x2 >> y2;
            
            try
            {
                Rectangle rect({ x1, y1 }, { x2, y2 });
                figures[realCount] = rect.clone();
                realCount++;
            }
            catch (std::invalid_argument& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        else if (word == "CIRCLE") {
            double  x1 = 0, 
                    y1 = 0, 
                    radius = 0;
            in >> x1 >> y1 >> radius;
            
            try
            {
                Circle circle({ x1, y1 }, radius);
                figures[realCount] = circle.clone();
                realCount++;
            }
            catch (std::invalid_argument& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (word == "COMPLEX") {
            int maxSize = 0, 
                realSize = 0;
            in >> maxSize;
            realSize = 0;
            CompositeShape compositeShape(maxSize);
            while (word != "COMPLEXEND")
            {
                in >> word;
                if (word == "RECTANGLE") {
                    double x1, y1, x2, y2;
                    in >> x1 >> y1 >> x2 >> y2;
                    
                    try
                    {
                        Rectangle rect({ x1, y1 }, { x2, y2 });
                        compositeShape.add(rect.clone());
                        realSize++;
                    }
                    catch (std::invalid_argument& e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                    catch (std::out_of_range& e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
                else if (word == "CIRCLE") {
                    double x1, y1, radius;
                    in >> x1;
                    in >> y1;
                    in >> radius;
                    try
                    {
                        Circle circle({ x1, y1 }, radius);
                        compositeShape.add(circle.clone());
                        realSize++;
                    }
                    catch (std::invalid_argument& e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                    catch (std::out_of_range& e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
            figures[realCount] = compositeShape.clone();
            realCount++;
        }
        else if (word == "MOVE") {
            if (firstComm) {
                shapeSort(figures, realCount);
                std::cout << "Отсортированный список фигур до применения команд:" << std::endl;
                printFigs(figures, realCount);
                firstComm = false;
            }
            double x, y;
            in >> x;
            in >> y;
            for (int i = 0; i < realCount; i++) {
                figures[i]->move(x, y);
            }
        }
        else if (word == "SCALE") {
            if (firstComm) {
                shapeSort(figures, realCount);
                std::cout << "Отсортированный список фигур после команд:\n" << std::endl;
                printFigs(figures, realCount);
                firstComm = false;
            }
            double x, y, k;
            in >> x;
            in >> y;
            in >> k;
            for (int i = 0; i < realCount; i++) {
                figures[i]->scale(x, y, k);
            }
        }
    }
    in.close();

    std::cout << "_______________________________________________" << std::endl
        << "Отсортированные фигуры после комманд:\n" << std::endl;
    shapeSort(figures, realCount);
    printFigs(figures, realCount);
    for (int i = 0; i < realCount; i++)
    {
        delete figures[i];
    }
    delete[] figures;

    std::cout << "_______________________________________________" << std::endl
        << "ТЕСТ НА КОПИРОВАНИЕ И ПЕРЕМЕЩЕНИЕ СОСТАВНЫХ ФИГУР\n" << std::endl;

    std::cout << "Создаем составные фигуры: " << std::endl;
    CompositeShape comp1(5);
    CompositeShape comp2(4);

    Circle circle1({ 2.0, 2.0 }, 4);
    Circle circle2({ 1.0, 3.0 }, 6);
    Rectangle rectangle1({ 0.0, 1.0 }, { 3.0, 6.0 });
    Rectangle rectangle2({ 1.0, -2.0 }, { 10.0, 7.0 });

    comp1.add(rectangle1.clone());
    comp1.add(circle1.clone());

    CompositeShape comp3 = comp2 = comp1;
    std::cout << "Срабатывает двойное присваивание" << std::endl;

    CompositeShape comp4(comp1);

    std::cout << "Срабатывает конструктор копирования" << std::endl;

    std::cout << comp1 << comp2 << comp3 << comp4;


    comp2 = std::move(comp1);

    CompositeShape comp5(CompositeShape(5));

    std::cout << "Срабатывает конструктор перемещения" << std::endl << std::endl;

    try
    {
        std::cout << comp1;
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << " - ";
    }

    std::cout << "1. При попытке вывода comp1 выбрасывается исключение" << std::endl;

    comp5 = comp1 = comp2;

    std::cout << "2. Для comp1 нормально работает оператор присваивания" << std::endl << std::endl;

    std::cout << std::endl << comp1 << comp2 << comp3 << comp4 << comp5 << std::endl;

    CompositeShape comp6 = returnValue(comp1);
    std::cout << comp6;

    std::cout << "3. Срабатывает вызов и возврат из функции" << std::endl;
    CompositeShape comp7(CompositeShape(5));

    return 0;
}

