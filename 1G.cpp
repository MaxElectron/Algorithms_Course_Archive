/*Герой по имени Магина сражается с группой из n монстров с помощью легендарного топора,
известного как Ярость Битвы.
Каждый из монстров имеет ai очков здоровья.
Каждым ударом топора Магина уменьшает здоровье того, кого он ударил, на p очков,
при этом уменьшая здоровье всех остальных монстров на q очков.
Монстр умирает, когда у него остается 0 или менее очков здоровья.
Магина хочет при каждом ударе выбирать цель таким образом,
чтобы убить всех монстров за минимальное количество ударов.
Требуется определить это количество.

Входные данные
В первой строке содержатся три целых числа через пробел:
n, p и q (1⩽n⩽200000, 1⩽q⩽p⩽109)
— количество монстров, урон по цели и урон по всем остальным соответственно.

Во второй строке содержатся n целых чисел через пробел:
ai (1⩽ai⩽109) — количество очков здоровья у каждого из монстров.

Выходные данные
Выведите единственное целое число — минимальное количество ударов,
за которое Магина сможет убить всех монстров.*/


#include <iostream>
#include <vector>
#include <algorithm>


long long roundUpDiv(long long a, long long b) {
    if (a % b == 0) {
        return a/b;
    } else {
        return  a/b + 1;
    }
}


long long targetHitsRequired(long long hp, long long targetDamage, long long aoeDamage, long long ans) {
    long long damageDifference = targetDamage - aoeDamage;
    hp -= aoeDamage * ans;
    if (hp <= 0) {
        return 0;
    } else {
        if (damageDifference == 0) {
            return 1000000001;
        }
        return roundUpDiv(hp, damageDifference);
    }
}


bool canKill(int* monsters, int amountOfMonsters, int targetDamage, int aoeDamage, int ans) {
    long long targets = 0;
    int* runningPointer = monsters;
    while (runningPointer != monsters + amountOfMonsters) {
        targets += targetHitsRequired(*runningPointer, targetDamage, aoeDamage, ans);
        if (targets > ans) {
            return false;
        }
        runningPointer++;
    }
    return true;
}


int howManyHits(int* monsters, int amountOfMonsters, int targetDamage, int aoeDamage) {
    int minAns = 0;
    int maxAns = 1000000000;
    int ans;

    while (minAns < maxAns - 1) {
        ans = (minAns + maxAns) / 2;
        if(canKill(monsters, amountOfMonsters, targetDamage, aoeDamage, ans)) {
            maxAns = ans;
        } else {
            minAns = ans;
        }
    }

    if (canKill(monsters, amountOfMonsters, targetDamage, aoeDamage, minAns)) {
        return minAns;
    } else {
        return maxAns;
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int amountOfMonsters = 0;
    int targetDamage = 0;
    int aoeDamage = 0;

    std::cin >> amountOfMonsters;
    std::cin >> targetDamage;
    std::cin >> aoeDamage;

    std::vector<int> monsters(amountOfMonsters);

    for (int i = 0; i < amountOfMonsters; ++i) {
        std::cin >> monsters[i];
    }

    std::cout << howManyHits(&monsters[0], amountOfMonsters, targetDamage, aoeDamage);

    return 0;
}
