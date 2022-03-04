// PHYS 30762 Programming in C++
// Assignment 2 - part 1
// Tomasz Neska 17/02/2022

// Program to compute mean, standard deviation and standard
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>

// Functions
int calculate_file_length(std::string file_name) {
    std::fstream file(file_name);
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

double splicing(std::string long_string, int first_index, int last_index) {
    std::string word{};
    char temp_arrayc[20];
    for (int i=first_index; i <= last_index; i++) {
        word = word + long_string[i];
    }
    double number = std::stod(word);
    return number;
}

double calculate_mean(float *scores, int N) {
    double sum{0};
    for (size_t i{0}; i<N; i++) {
        sum += scores[i];
    }
    return sum/static_cast<double>(N);
}

double calculate_std(float *scores, int mean, int N) {
    double sum{0};
    for (size_t i{0}; i<N; i++) {
        sum = sum + pow(scores[i] - mean,2);
    }
    return pow(1/(static_cast<double>(N)-1) * sum, 0.5);
}

// Main function

int main() {
    // declare variables
    std::string file_name = "courselist.dat";
    int N = calculate_file_length(file_name);
    std::ifstream my_file2("courselist.dat");
    std::string *data_array{new std::string[N]};
    double standard_deviation{};
    double mean{};
    double standard_deviation_error{};
    double sum{0};
    float *scores{new float[N]}; // used for scores
    std::string file_line;
    for(int i{0}; i < N; i++) {
        getline(my_file2, file_line);
        data_array[i] = file_line;
        scores[i] = splicing(file_line,0,3);
    }
    mean = calculate_mean(scores, N);
    standard_deviation = calculate_std(scores,mean,N);
    standard_deviation_error = standard_deviation/pow(N,0.5);
    delete[] data_array; // freeing memor // freeing memoryy
    std::cout << "The mean is: " << mean << std::endl;
    std::cout << "The standard deviation: " << standard_deviation << std::endl;
    std::cout << "The standard deviation error: " << standard_deviation_error << std::endl;
    return 0; 
}
