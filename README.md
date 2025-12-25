# Лабораторная работа №2: "Матрица: продолжение"

## 📋 Задание
Расширение программы "Матрица" из первой лабораторной работы. Добавление управления частотой генерации линий и улучшенной системы временного планирования.

## 🎯 Цель работы
Освоение принципов ООП на практике: инкапсуляция временной логики, управление коллекциями объектов, работа с системным временем в Windows.

## 🏗 Архитектура

### Классовая структура:

```cpp
// 1. Класс символа (Character/Symbol)
class Symbol {
private:
    wchar_t value;      // Символ (например, L'0'-L'9', L'А'-L'Я')
    COORD position;     // Позиция в консоли
    int color;          // Цвет символа
public:
    void draw() const;  // Отрисовка символа
    void update();      // Обновление состояния
};

// 2. Класс линии (Line) - расширенный
class Line {
private:
    std::vector<Symbol> symbols;  // Коллекция символов
    int length;                   // Длина линии
    int speed;                    // Скорость движения (символов/сек)
    int startDelay;               // Задержка перед стартом (мс)
    bool isActive;                // Активна ли линия
    COORD startPosition;          // Начальная позиция
    
    // Методы для внутренней логики
    void generateSymbols();       // Генерация символов линии
    void move();                  // Движение всей линии
    bool isFinished() const;      // Проверка завершения
    
public:
    Line(int length, int speed, int startDelay);
    void update(float deltaTime); // Обновление за время deltaTime
    void render() const;          // Отрисовка всей линии
    bool getIsActive() const;
};

// 3. Класс менеджера приложения (AppManager)
class AppManager {
private:
    std::vector<Line> lines;      // Активные линии
    std::vector<int> startTimes;  // Времена старта для запланированных линий
    int spawnRate;                // Частота генерации (линий/сек)
    int speed;                    // Скорость линий
    int length;                   // Длина линий
    bool epilepsyMode;            // Режим эпилепсии
    
    // Вспомогательные методы
    void generateStartTimes();    // Генерация времен старта
    void spawnLines();            // Создание новых линий
    void removeFinishedLines();   // Удаление завершенных линий
    
public:
    AppManager(int spawnRate, int speed, int length, bool epilepsyMode);
    void run();                   // Главный цикл приложения
    void handleInput();           // Обработка ввода
};

// 4. Служебный класс (ConsoleUtils)
class ConsoleUtils {
public:
    static void clearScreen();
    static void setCursorPosition(int x, int y);
    static void hideCursor();
    static void setColor(int color);
    static int getRandom(int min, int max);
    static wchar_t getRandomSymbol();
};
