#include <iostream>
#include <ctime>

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

void catchFish(int ind, char river[]) {
    if (ind < 0 || ind > 8) {
        throw std::invalid_argument("ind");
    } else if (river[ind] == 'f') {
        throw Fish();
    } else if (river[ind] == 'b') {
        throw Boot();
    } else {
        throw TryAgain();
    };
}

int main() {
    std::srand(std::time(nullptr));
    char river[9] = {};

    //fish
    river[std::rand() % 9] = 'f';

    //boots
    for (int i = 0; i < 3; ++i) {
        int ind = std::rand() % 9;
        if (river[ind] == 'f' || river[ind] == 'b') {
            --i;
            continue;
        }
        river[ind] = 'b';
    }
std::cout << "river: ";
    for (int i = 0; i < 9; ++i) {
        if (river[i] != 'b' && river[i] != 'f') continue;
        std::cout << i << ":" << river[i] << " ";
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
