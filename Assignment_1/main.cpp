#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

float calculate_Energy(int n_1, int n_2, bool unit, int Z) {
    const double electron_volt{1.6E-19};
    // function which calculates the energy
    float energy;
    energy = 13.6 * std::pow(Z,2) * (1/std::pow(n_1,2) - 1/std::pow(n_2,2));
    if (unit==false) {
        energy = energy * electron_volt; 
    }
    return energy;
}

int main(){
    // delcare variables

    int Z{0};
    int n_1{0};
    int n_2{0};
    double E{0};
    bool interrupt_bool{false};
    char choice{};

    while (interrupt_bool == false) {
        // repeats until the user stops it.
        std::cout << "Enter the atomic number Z:" << std::endl;
        std::cin >> Z;
        while (std::cin.fail()) {
            // loops the command until the user enters the right value
            std::cout << "Wrong input try again.";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> Z;
        }

        std::cout << "Enter first quantum number: " << std::endl;
        std::cin >> n_1;

        while (std::cin.fail() || n_1 <= 0) {
            std::cout << "The number is incorrect. Try again: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> n_1;
        }

        std::cout << "Enter the second quantum number n: " << std::endl;
        std::cin >> n_2;
        while (std::cin.fail() || n_1 < n_2) {
            std::cout << "The number is incorrect. Try again: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> n_2;
        }

        // compute photon energy
        std::cout << "Should it be displayed in eV or Joules? (e/J)" << std::endl;
        std::cin >> choice;
        while (std::cin.fail() || (choice !='e' && choice != 'J')) {
            std::cout << "The choice is incorrect. Try again: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> choice;
        }



        if (choice == 'J') {
            E = calculate_Energy(n_1, n_2, false, Z);
            std::cout << "The energy is: " << std::setprecision(3) << E << " Joules" << std::endl;
        } else {
            E = calculate_Energy(n_1, n_2, true, Z);
            std::cout << "The energy is: " << std::setprecision(3) << E << " eV" << std::endl;
        }

        std::cout << "Should it repeat? (y/n)" << std::endl;
        std::cin >> choice;
        while (std::cin.fail() || (choice != 'y' && choice != 'n')) {
            std::cout << "The choice is incorrect. Try again: ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> choice;
        }
        if (choice=='n') {
            interrupt_bool = true;
        }

    }
    return 0;
}
