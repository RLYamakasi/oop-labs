# Лабораторная работа №3: "Взрыв"

## 📋 Задание
Добавление системы взрывов в программу "Матрица". Линии теперь могут взрываться с заданной вероятностью, создавая радиальную анимацию расхождения символов.

## 🎯 Цель работы
Освоение продвинутых концепций ООП: композиция объектов, управление сложным состоянием, реализация вероятностных систем, работа с анимацией и временными интервалами.

## 🏗 Архитектура

### Расширенная классовая структура:

```cpp
// 1. Взрыв (новый класс)
class Explosion {
private:
    struct ExplosionParticle {
        COORD position;     // Текущая позиция
        COORD direction;    // Направление движения
        wchar_t symbol;     // Символ
        int color;          // Цвет (случайный)
        int radius;         // Текущий радиус
        int maxRadius;      // Максимальный радиус
        bool active;        // Активна ли частица
    };
    
    std::vector<ExplosionParticle> particles;
    COORD epicenter;        // Центр взрыва
    int currentRadius;      // Текущий радиус взрыва
    int minRadius;          // Минимальный радиус
    int maxRadius;          // Максимальный радиус
    bool isActive;          // Активен ли взрыв
    std::chrono::time_point<std::chrono::steady_clock> lastUpdate;
    
public:
    Explosion(COORD center, int minR, int maxR);
    void update();          // Обновление состояния
    void render() const;    // Отрисовка взрыва
    bool getIsActive() const;
    void generateParticles(); // Генерация частиц для взрыва
};

// 2. Расширенный класс линии
class Line {
private:
    std::vector<Symbol> symbols;
    int length;
    int speed;
    bool isActive;
    bool isExploding;       // Флаг взрыва
    int explosionChance;    // Вероятность взрыва (1 из N)
    int explosionsTriggered; // Количество сработавших взрывов
    std::unique_ptr<Explosion> currentExplosion; // Текущий взрыв
    
    // Метод проверки взрыва
    bool shouldExplode() const;
    
public:
    Line(int length, int speed, int explosionChance);
    void update(float deltaTime);
    void render() const;
    
    // Новые методы
    void triggerExplosion(int minRadius, int maxRadius);
    void shortenLine();     // Укорачивание линии на 1 символ
    bool getIsAlive() const; // Проверка, есть ли еще символы
};

// 3. Расширенный менеджер приложения
class AppManager {
private:
    std::vector<std::unique_ptr<Line>> lines;
    std::vector<std::unique_ptr<Explosion>> explosions;
    int spawnRate;
    int speed;
    int length;
    bool epilepsyMode;
    int explosionChance;    // 1 из N
    int minExplosionRadius;
    int maxExplosionRadius;
    
    // Новые методы
    void updateExplosions(float deltaTime);
    void removeFinishedExplosions();
    void checkLineExplosions();
    
public:
    AppManager(int spawnRate, int speed, int length, 
               bool epilepsyMode, int explosionChance,
               int minRadius, int maxRadius);
    void run();
};
