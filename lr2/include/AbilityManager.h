#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "AbilityInterface.h"
#include <random>
#include <ctime>

class AbilityManager {
private:
    std::queue<std::shared_ptr<AbilityInterface>> abilitiesQueue;  // Очередь способностей

public:
    AbilityManager() = default;

    void addAbility();
//    {
//        abilitiesQueue.push(ability);
//    }

    // Метод для использования следующей способности из очереди
    void useNextAbility();
//    {
//        if (!abilitiesQueue.empty()) {
//            abilitiesQueue.front()->use();  // Используем способность
//            abilitiesQueue.pop();  // Удаляем использованную способность из очереди
//        } else {
//            std::cout << "No abilities in the queue!" << std::endl;
//        }
//    }

    bool isEmpty() const;
//    {
//        return abilitiesQueue.empty();
//    }
};

#endif //ABILITYMANAGER_H
