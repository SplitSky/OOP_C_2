// PHYS 30762 Programming in C++
// Assignment 2 - part 2
// Tomasz Neska 17/02/2022

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>

// Structures
struct list_node {
    double mark;
    int unit_code;
    std::string title;
};

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

double calculate_mean(std::vector<list_node> data_array) {
    int N = data_array.size();
    double sum{0};
    for (int i{0}; i<N; i++) {
        sum += data_array[i].mark;
    }
    return sum/static_cast<double>(N);
}

double calculate_standard_deviation(std::vector<list_node> data_array, double mean) {
    int N = data_array.size();
    double sum{0};
    for (int i{0}; i<N; i++) {
        sum = sum + pow(data_array[i].mark-mean, 2);
    }
    return pow(1/static_cast<double>(N) * sum, 0.5);
}


void bubble_sort(std::vector<list_node>& array, int type) {
    // sorting function
    int size = array.size();
    bool swap{true};
    list_node holder;
    if (type==1) {
        while (swap == true) {
            swap = false;
            for (int i{1}; i<size; i++) {
                if (array[i-1].title > array[i].title) {
                    holder.mark = array[i-1].mark;
                    holder.unit_code = array[i-1].unit_code;
                    holder.title = array[i-1].title;
                    array[i-1].mark = array[i].mark;
                    array[i-1].unit_code = array[i].unit_code;
                    array[i-1].title = array[i].title;
                    array[i].mark = holder.mark;
                    array[i].unit_code = holder.unit_code;
                    array[i].title = holder.title;
                    swap = true;
                }
            }
        }
    } else {
        while (swap==true) {
            swap = false;
            for (int i{1}; i<size; ) {
                if (array[i-1].unit_code > array[i].unit_code) {
                    holder.mark = array[i-1].mark;
                    holder.unit_code = array[i-1].unit_code;
                    holder.title = array[i-1].title;
                    array[i-1].mark = array[i].mark;
                    array[i-1].unit_code = array[i].unit_code;
                    array[i-1].title = array[i].title;
                    array[i].mark = holder.mark;
                    array[i].unit_code = holder.unit_code;
                    array[i].title = holder.title;
                }
            }
        }
    }
    return;
}

// Main function

int main() {
    // function constructors
    double calculate_standard_deviation(std::vector<list_node> data_array, double mean);
    double calculate_mean(std::vector<list_node> data_array);
    void bubble_sort(std::vector<list_node>& array, int type);
    int calculate_file_length(std::string file_name);
    // declare variables
    int number_courses{0};
    std::string file_name = "courselist.dat";
    int N{0};
    double standard_deviation{};
    double mean{};
    double std_error{};
    double sum{0};
    std::string file_line;
    list_node temporary_node;
    std::vector<list_node> sliced_data;
    std::vector<std::string> full_data;
    std::vector<list_node> chosen_data;
    // 2. open and load file
    // 3. determine the number of file entries
    std::ifstream my_file(file_name);
    if (!my_file.good()) {std::cout << "The file couldn't be loaded. Try again." << std::endl; return -1;}

    while (!my_file.eof()) {
        getline(my_file, file_line);
        if (file_line.length() != 0) {
            temporary_node.mark = std::stod(file_line.substr(0,4));
            temporary_node.unit_code = std::stoi(file_line.substr(5,9));
            temporary_node.title = file_line.substr(13, file_line.length());
            sliced_data.push_back(temporary_node);
            full_data.push_back(file_line.substr(5,file_line.length()));
            N ++;
        }
    }
    my_file.close();
    // 6. print out information for each course using an iterator
    std::cout << "The full data set from the file: " << std::endl;
    std::vector<std::string>::iterator vector_begin{full_data.begin()};
    std::vector<std::string>::iterator vector_end{full_data.end()};
    std::vector<std::string>::iterator vector_iterator;
    for (vector_iterator=vector_begin; vector_iterator<vector_end; ++vector_iterator) {
        std::cout << "PHYS " << *vector_iterator << std::endl;
    }

    // 4. calculate mean, std of the full set
    mean = calculate_mean(sliced_data);
    standard_deviation = calculate_standard_deviation(sliced_data, mean);
    std_error = standard_deviation/(pow(static_cast<double>(number_courses),0.5)); 
    std::cout << "The mean for the file is: " << mean << std::endl;
    std::cout << "The standard deviation is: " << standard_deviation << "+/- " << std_error << std::endl;

    // 5. use string stream to combine bits
    // 7. print out a list of course for a particular year identified by first digit
    // 8. print out mean and std for each course selection
    // 9. sort the list of courses by title or course code 
    // - using bubble sort or quick sort if you can be bothered
    std::cout << "Enter the year you want to display: ";
    int year{0};
    std::cin >> year;
    while (std::cin.fail()) {
        std::cout << "The year is incorrect. Try again: ";
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cin >> year;
    }
    int choice{0};
    std::cout << "Sort by (1) Title or by (2) Unit Code: ";
    std::cin >> choice;
    std::string temp;
    std::cout << "The data for the selected range:" << std::endl;;
    for (int i{0}; i<sliced_data.size(); i++) {
        if (sliced_data[i].unit_code/ 10000 == year) {
            chosen_data.push_back(sliced_data[i]);        
        }
    }
    mean = calculate_mean(chosen_data);
    standard_deviation = calculate_standard_deviation(chosen_data, mean);
    std_error = standard_deviation/(pow(static_cast<double>(number_courses),0.5));

    bubble_sort(chosen_data, choice); // passed by reference
    
    std::ostringstream output_stream;
    for (size_t i{0}; i<chosen_data.size(); i ++) {
        output_stream << "PHYS" << chosen_data[i].unit_code << " " << chosen_data[i].title;
        std::string output{output_stream.str()};
        std::cout << output << std::endl;
        output_stream.str("");
    }

    std::cout << "The mean for the data set is: " << mean << std::endl;
    std::cout << "The standard deviation is: " << standard_deviation << " +/- " << std_error <<std::endl;

    return 0;    
}
