#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// Класс для персонажей
class Character {
protected:
    std::string name;
    int health;
    int attackPower;
    int defense;
    
public:
    Character(std::string characterName, int characterHealth, int characterAttackPower, int characterDefense)
        : name(characterName), health(characterHealth), attackPower(characterAttackPower), defense(characterDefense) {}

    virtual void attack(Character& target) {
        int damage = attackPower - target.defense;
        if (damage < 0) damage = 0; // Урон не может быть меньше 0
        target.takeDamage(damage);
        std::cout << name << " атакует " << target.getName() << " на " << damage << " урона!" << std::endl;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }

    std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    virtual void printStatus() const {
        std::cout << name << " - Здоровье: " << health << ", Сила атаки: " << attackPower << ", Защита: " << defense << std::endl;
    }

    void heal(int amount) {
        health += amount;
        std::cout << name << " лечится на " << amount << " здоровья!" << std::endl;
    }
};

// Класс для героя
class Hero : public Character {
public:
    Hero(std::string name, int health, int attackPower, int defense)
        : Character(name, health, attackPower, defense) {}

    void attack(Character& target) override {
        int damage = rand() % attackPower + 1; // Случайный урон от 1 до attackPower
        target.takeDamage(damage);
        std::cout << name << " атакует " << target.getName() << " на " << damage << " урона!" << std::endl;
    }

    void castSpell(Character& target) {
        int spellDamage = rand() % 30 + 1; // Случайный урон от заклинания
        target.takeDamage(spellDamage);
        std::cout << name << " использует заклинание, наносящее " << spellDamage << " урона!" << std::endl;
    }
};

// Класс для монстра
class Monster : public Character {
public:
    Monster(std::string name, int health, int attackPower, int defense)
        : Character(name, health, attackPower, defense) {}

    void attack(Character& target) override {
        int damage = rand() % attackPower + 1; // Случайный урон от 1 до attackPower
        target.takeDamage(damage);
        std::cout << name << " атакует " << target.getName() << " на " << damage << " урона!" << std::endl;
    }
};

// Функция для вывода меню действий героя
void showHeroActions() {
    std::cout << "Выберите действие:\n";
    std::cout << "1. Атака\n";
    std::cout << "2. Заклинание\n";
    std::cout << "3. Пропустить ход\n";
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    // Создаем героя и монстра
    Hero hero("Герой", 100, 20, 5);
    Monster monster("Монстр", 80, 15, 3);

    char playAgain;
    
    do {
        // Игровой цикл
        while (hero.isAlive() && monster.isAlive()) {
            // Печатаем статусы
            hero.printStatus();
            monster.printStatus();

            // Игровой выбор героя
            int action = 0;
            while (true) {
                showHeroActions();
                std::cin >> action;
                if (std::cin.fail() || action < 1 || action > 3) {
                    std::cin.clear(); // Очистка флага ошибки
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование неверного ввода
                    std::cout << "Неверный ввод, попробуйте снова.\n";
                } else {
                    break;
                }
            }

            // Действия героя
            switch (action) {
                case 1:
                    hero.attack(monster);
                    break;
                case 2:
                    hero.castSpell(monster);
                    break;
                case 3:
                    std::cout << "Вы пропустили ход.\n";
                    break;
            }

            if (!monster.isAlive()) {
                break; // Если монстр мертв, заканчиваем игру
            }

            // Ответ монстра
            monster.attack(hero);

            std::cout << std::endl;
        }

        // Завершение игры
        if (hero.isAlive()) {
            std::cout << "Поздравляем, вы победили монстра!\n";
        } else {
            std::cout << "Вы проиграли, монстр победил.\n";
        }

        // Повтор игры
        std::cout << "Хотите сыграть снова? (y/n): ";
        std::cin >> playAgain;
        std::cin.ignore(); // Очистить буфер ввода
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Спасибо за игру!\n";

    return 0;
}
