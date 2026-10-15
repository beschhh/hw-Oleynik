#include <iostream>

class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* name,int health,int damage)
        : name(name),health(health),maxHealth(health),damage(damage) {}

    void TakeDamage(int amount) {
        health-=amount;
        if (health<0)
            health=0;
    }

    void Heal(int amount) {
        health+=amount;
        if (health>maxHealth)
            health=maxHealth;
    }

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health>0;
    }

    void PrintStatus() const {
        std::cout<<name<<": "<<health<<"/"<<maxHealth<<" HP, урон "<<damage<<"\n";
    }
};

void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

class Game {
private:
    Fighter player;
    Fighter enemies[3];
    Fighter* currentTarget=nullptr;
    int medkits=1;

    bool TrySelectTarget(int number,Fighter*& outTarget) {
        outTarget=nullptr;

        if (number<1||number>3)
            return false;

        if (!enemies[number-1].IsAlive())
            return false;

        outTarget=&enemies[number-1];
        return true;
    }

    bool AllEnemiesDefeated() const {
        for (int i=0;i<3;i++) {
            if (enemies[i].IsAlive())
                return false;
        }
        return true;
    }

    void PrintState() const {
        std::cout<<"\n--- Арена ---\n";
        std::cout<<"Игрок: ";
        PrintFighter(player);

        for (int i=0;i<3;i++) {
            std::cout<<i+1<<") ";
            PrintFighter(enemies[i]);
        }

        std::cout<<"Аптечек: "<<medkits<<"\n";

        std::cout<<"Текущая цель: ";
        if (currentTarget!=nullptr)
            currentTarget->PrintStatus();
        else
            std::cout<<"нет\n";
    }
    void PrintMenu() const {
        std::cout<<"1 -выбрать цель\n";
        std::cout<<"2-атаковать\n";
        std::cout<<"3-использовать аптечку\n";
        std::cout<<"0 - выйти\n";
        std::cout<<"> ";
    }

public:
    Game()
        : player("Герой",20,8),
          enemies{{"Противник 1",12,3},
                  {"Противник 2",18,4},
                  {"Противник 3",24,5}} {}

    void Run() {
        while (true) {
            PrintState();
            PrintMenu();

            int command;
            if (!(std::cin>>command))
                return;

            if (command==0) {
                std::cout<<"Выход из игры\n";
                return;
            }

            if (command==1) {
                int number;
                std::cout<<"Выберите противника (1-3): ";

                if (!(std::cin>>number))
                    return;

                if (TrySelectTarget(number,currentTarget))
                    std::cout<<"Выбрана цель: противник "<<number<<"\n";
                else
                    std::cout<<"Ошибка: неверный номер или противник уже повержен\n";

                continue;
            }

            if (command==2) {
                if (currentTarget==nullptr) {
                    std::cout<<"Ошибка: сначала выберите цель\n";
                    continue;
                }

                player.Attack(*currentTarget);
                std::cout<<"Герой атакует цель!\n";

                if (!currentTarget->IsAlive()) {
                    std::cout<<"Противник повержен!\n";
                    currentTarget=nullptr;

                    if (AllEnemiesDefeated()) {
                        PrintState();
                        std::cout<<"Победа! Все противники повержены.\n";
                        return;
                    }
                } else {
                    currentTarget->Attack(player);
                    std::cout<<"Противник атакует в ответ!\n";

                    if (!player.IsAlive()) {
                        PrintState();
                        std::cout<<"Поражение! Герой погиб.\n";
                        return;
                    }
                }

                continue;
            }
             if (command==3) {
                if (currentTarget==nullptr||!currentTarget->IsAlive()) {
                    std::cout<<"Ошибка: сначала выберите цель\n";
                    continue;
                }

                if (medkits==0) {
                    std::cout<<"Ошибка: аптечек не осталось\n";
                    continue;
                }

                player.Heal(8);
                medkits--;
                std::cout<<"Герой использует аптечку!\n";

                currentTarget->Attack(player);
                std::cout<<"Противник атакует в ответ!\n";

                if (!player.IsAlive()) {
                    PrintState();
                    std::cout<<"Поражение! Герой погиб.\n";
                    return;
                }

                continue;
            }

            std::cout<<"Ошибка: неизвестная команда\n";
        }
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}

