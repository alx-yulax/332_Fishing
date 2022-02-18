#include <iostream>
#include <ctime>

enum InRiver{
    NONE,
    FISH,
    BOOT

};
class Fish {
public:
    std::string what() {
        return "Congratulations! You have caught a big fish.";
    }
};

class Boot {
public:
    std::string what() {
        return "Sorry! You caught the boot.";
    }
};

class TryAgain {
public:
    std::string what() {
        return "Try again: ";
    }
};

void catchFish(int ind, InRiver river[]) {
    if (ind < 0 || ind > 8) {
        throw std::invalid_argument("ind");
    } else if (river[ind] == FISH) {
        throw Fish();
    } else if (river[ind] == BOOT) {
        throw Boot();
    } else {
        throw TryAgain();
    };
}

int main() {
    std::srand(std::time(nullptr));
    InRiver river[9] = {NONE};

    //fish
    river[std::rand() % 9] = FISH;

    //boots
    for (int i = 0; i < 3; ++i) {
        int ind = std::rand() % 9;
        if (river[ind] == FISH || river[ind] == BOOT) {
            --i;
            continue;
        }
        river[ind] = BOOT;
    }

    std::cout << "river: ";

    for (int i = 0; i < 9; ++i) {
        if (river[i] == FISH){
            std::cout << i << ":FISH ";
        } else if (river[i] == BOOT) {
            std::cout << i << ":BOOT ";
        }
    }

    std::cout << std::endl << "input index (0-8): ";

    //fishing
    int count = 0;
    bool fishing = true;
    while (fishing) {
        ++count;
        int ind;
        std::cin >> ind;
        try {
            catchFish(ind, river);
        } catch (std::invalid_argument &x) {
            std::cout << "Invalid argument: " << x.what() << std::endl;
        } catch (Fish &x) {
            std::cout << x.what() << std::endl;
            std::cout << "count: " << count;
            break;
        } catch (Boot &x) {
            std::cout << x.what() << std::endl;
            return -1;
        } catch (TryAgain &x) {
            std::cout << x.what() << std::endl;
            continue;
        }
        std::cin.clear();
    }

    return 0;
}
