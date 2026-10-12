//1
/*
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

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health>0;
    }

    void PrintStatus() const {
        std::cout<<name<<": "<<health<<"/"<<maxHealth<<" HP\n";
    }
};

void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

class Game {
private:
    Fighter player;
    Fighter enemy;

public:
    Game(): player("Hero",30,8),enemy("Enemy",12,3) {}

    void Run() {
        while (player.IsAlive()&&enemy.IsAlive()) {
            PrintFighter(player);
            PrintFighter(enemy);
            std::cout<<"1 - Attack\n0 - Exit\n";

            int command;
            if (!(std::cin>>command))
                return;

            if (command==0)
                return;

            if (command!=1) {
                std::cout<<"Invalid command\n";
                continue;
            }

            player.Attack(enemy);
            std::cout<<"Hero attacks Enemy\n";

            if (enemy.IsAlive()) {
                enemy.Attack(player);
                std::cout<<"Enemy attacks Hero\n";
            }
        }

        if (player.IsAlive())
            std::cout<<"Victory!\n";
        else
            std::cout<<"Defeat!\n";
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}*/

//2
/*
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

    void Attack(Fighter& target) const {
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health>0;
    }

    void PrintStatus() const {
        std::cout<<name<<": "<<health<<"/"<<maxHealth<<" HP\n";
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

public:
    Game()
        : player("Hero",30,8),
          enemies{{"Enemy 1",12,3},{"Enemy 2",18,4},{"Enemy 3",24,5}} {}

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

    void Run() {
        while (player.IsAlive()&&!AllEnemiesDefeated()) {
            std::cout<<"\n--- Arena ---\n";
            PrintFighter(player);

            for (int i=0;i<3;i++)
                PrintFighter(enemies[i]);

            std::cout<<"Current target: ";
            if (currentTarget!=nullptr)
                currentTarget->PrintStatus();
            else
                std::cout<<"None\n";

            std::cout<<"1 - Select target\n";
            std::cout<<"2 - Attack\n";
            std::cout<<"0 - Exit\n";

            int command;
            if (!(std::cin>>command))
                return;

            if (command==0)
                return;

            if (command==1) {
                int number;
                std::cout<<"Choose enemy (1-3): ";

                if (!(std::cin>>number))
                    return;

                if (TrySelectTarget(number,currentTarget))
                    std::cout<<"Target selected\n";
                else
                    std::cout<<"Invalid or defeated target\n";

                continue;
            }

            if (command==2) {
                if (currentTarget==nullptr) {
                    std::cout<<"Select a target first\n";
                    continue;
                }

                player.Attack(*currentTarget);
                std::cout<<"Hero attacks!\n";

                if (!currentTarget->IsAlive()) {
                    std::cout<<"Enemy defeated!\n";
                    currentTarget=nullptr;
                } else {
                    currentTarget->Attack(player);
                    std::cout<<"Enemy attacks back!\n";
                }

                if (!player.IsAlive()) {
                    std::cout<<"Defeat!\n";
                    break;
                }

                if (AllEnemiesDefeated()) {
                    std::cout<<"Victory!\n";
                    break;
                }

                continue;
            }

            std::cout<<"Invalid command\n";
        }
    }
};

int main() {
    Game game;
    game.Run();
    return 0;
}
*/