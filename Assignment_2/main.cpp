// PHYS 30762 Programming in C++
// Assignment 2
// Tomasz Neska 17/02/2022

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>

// Functions
int caclculate_file_length(std::fstream file) {
    std::string file_line;
    int N{0};
    if (!file.good()) {
        std::cout << "The file couldn't be loaded";
        return -1;
    } else {
        while (!file.eof()) {
            getline(file,file_line); // function loading line into string
            if (file_line.length()!=0) {
                N++;
            }
        }
    }
    file.close();
    return N;
}

// Main function

int main() {
    // declare variables
    std::fstream file("courselist.dat");
    int N = calculate_file_length(file);

    std::ifstream my_file2("courselist.dat");
    std::string *data_array{new std::string[N]};
    double standard_deviation{};
    double mean{};
    double std_error{};
    double sum{0};
    float *scores{new float[N]}; // used for scores

    for(int i{0}; i < N; i++) {
        getline(my_file2, file_line);
        data_array[i] = file_line;
        scores[i] = splicing(file_line,0,3);
        sum = sum + scores[i];
    }
    // casting an int into a double for increased precision
    double N_2 = static_cast<double>(N);
    mean = 1/N_2 * sum;
    sum = 0;

    

    for(int i{0}; i < N; i++) {
        sum = sum + pow(scores[i] - mean,2);

    }
    standard_deviation = pow(1/(N_2) * sum ,0.5);
    std_error = standard_deviation/pow(N_2,0.5);
    delete[] data_array;
    

    std::cout << "The mean is: " << mean << std::endl;
    std::cout << "The standard deviation: " << standard_deviation << std::endl;
    std::cout << "The standard deviation error: " << std_error << std::endl;

    return 0;    
}
