// PHYS 30762 Programming in C++
// Assignment 5
// Tomasz Neska - ID: 10294857
// Matrix Determinants and inverses

#include <fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<array>
#include<iterator>
#include<cstring>

class matrix {
    friend std::ostream& operator<<(std::ostream &os, matrix &numbers);
    friend std::ifstream& operator>>(std::ifstream &os, matrix &numbers);
    
    private:
        int row;
        int col;
        double *data;
    public:
        matrix();
        matrix(int row, int col, double data_in[]);
        ~matrix(){
            std::cout << "calling destructor" << std::endl;
            this->data = nullptr;
            delete[] this->data;
        }

        matrix(matrix&);// copy constructor
        void set_row(int row);
        void set_col(int col);
        int get_row() const;
        int get_col() const;
        void set_data(double* data_2, size_t size);
        // overloading operators
        matrix operator+(matrix &numbers) const;
        matrix operator-(matrix &numbers) const;
        matrix operator*(matrix &numbers) const;
        matrix& operator=(matrix &numbers);
        std::string show_data() const;
        double* get_data() const;

};
matrix::matrix() {
    this->data = nullptr;
    this->row = 0;
    this->col = 0;
}

matrix::matrix(int row, int col, double data_in[]): row{row}, col{col} {
    this->data = new double[row*col]; // declares memory space
    for (int i{0}; i<row*col; i++) { // performs deep copy
          this->data[i] = data_in[i];
    }
}

matrix::matrix(matrix& numbers) { // COPY CONSTRUCTOR
    std::cout << "Copy constructor called" << std::endl;
    this->set_col(numbers.get_col());
    this->set_row(numbers.get_row());
    this->set_data(numbers.get_data(), numbers.get_col()*numbers.get_row());
}

double* matrix::get_data() const {
    return this->data;
}

int matrix::get_row() const{
    return this->row;
}
int matrix::get_col() const{
    return this->col;
}
void matrix::set_row(int row){
    this->row=row;
}
void matrix::set_col(int col){
    this->col=col;
}
void matrix::set_data(double* data_2, size_t size){
    // this function perfroms a deep copy of the data taking care of memory leaks
    //if (this->data != nullptr) {
    //    delete[] this->data;
    //}
    this->data = new double[size];
    for (size_t i{0}; i< size; i++) {
        this->data[i] = data_2[i];
    }
    return;
}

matrix matrix::operator+(matrix &numbers) const {
    if ((this->row == numbers.row) && (this->col == numbers.col)) {
        matrix temp; // defines object
            std::vector<double> data_added;
            for (int i{0}; i<this->row*this->col ;i++) {
                data_added.push_back(this->data[i] + numbers.data[i]);
            }   
            double* data_assigned = new double[this->row*this->col];
            std::copy(data_added.begin(), data_added.end(), data_assigned);
            temp.set_col(numbers.get_col());
            temp.set_row(numbers.get_row());
            temp.set_data(data_assigned, data_added.size());
            delete[] data_assigned;
            return temp;
    } else {
            matrix temp;
            std::cout << "The dimensions don't match" << std::endl;
            return temp;
    }
}

matrix matrix::operator-(matrix &numbers) const {
    if ((this->row == numbers.row) && (this->col ==numbers.col)) {
           matrix temp; 
           std::vector<double> data_added;
           for (int i{0}; i<this->row*this->col ;i++) {
                data_added.push_back(this->data[i] - numbers.data[i]);
           }           
           double* data_assigned = new double[this->row*this->col];
           std::copy(data_added.begin(), data_added.end(), data_assigned);
           temp.set_col(numbers.get_col());
           temp.set_row(numbers.get_row());
           temp.set_data(data_assigned, data_added.size());
           delete[] data_assigned;
           return temp;
    } else {
        matrix temp;
        std::cout << "The dimensions don't match" << std::endl;
        return temp;
    }
}

matrix matrix::operator*(matrix &numbers) const {
    if (this->row == numbers.col) {
        double sum{0};
        std::vector<double> data_multiplied;
        for (int j{1}; j<=numbers.col;j++) {
            for (int i{1}; i <= this->row; i++) {
                sum = 0;
                    for (int k{1};k <= this->col; k++) {
                        sum += this->data[(k-1)+(i-1)*this->col] * numbers.data[(j-1)+(k-1)*numbers.col];
                    }
                data_multiplied.push_back(sum); // adds the entry to the result array
            }
        }
        matrix temp;
        double* data_assigned = new double[this->row*this->col];
        std::copy(data_multiplied.begin(), data_multiplied.end(), data_assigned);
        temp.set_col(numbers.get_col());
        temp.set_row(this->get_row());
        temp.set_data(data_assigned, data_multiplied.size());
        delete[] data_assigned;
        return temp;
    } else {
        matrix temp;
        std::cout << "The dimensions don't match" << std::endl;
        return temp;
    }
}

matrix & matrix::operator=(matrix &numbers) { // deep copy
    std::cout << "Calling assignment operator" << std::endl;
    if (&numbers == this) {return *this;} // avoids self assignment    
    delete[] this->data;
    
    this->data = nullptr;
    this->col = numbers.col;
    this->row = numbers.row;
    
    if (col*row != 0) {
        this->set_data(numbers.get_data(), this->col*this->row);
    }        
    return *this;
}

std::string matrix::show_data() const {
    std::string temp[this->row];
    std::string temp_string;
    for (int i{1}; i <= this->row; i++) {
        temp_string += "[";
                for (int j{1}; j <= this->col; j++) {
                    temp_string += " ";
                    temp_string += std::to_string(this->data[(j-1)+this->col*(i-1)]) + ", ";
                }
                temp_string = temp_string.substr(0,temp_string.size()-2);
                temp_string += "], ";
            }
            temp_string = temp_string.substr(0,temp_string.size()-2);
        return temp_string;
}

std::ostream& operator<<(std::ostream& os, matrix &numbers) {
    // this function prints matrix in visually representative way
    os << "Printing the matrix:" << std::endl;
    std::cout << numbers.get_row() << " , " << numbers.get_col() << " and stuff" << std::endl;
    std::cout << numbers.get_data()[0] << numbers.get_data()[1] << std::endl;

    std::string temp[numbers.get_row()];
    std::string temp_string;
    for (int i{1}; i <= numbers.get_row(); i++) {
        temp_string += "[";
        for (int j{1}; j <= numbers.get_col(); j++) {
            temp_string += " ";
            temp_string += std::to_string(numbers.data[(j-1)+numbers.get_col()*(i-1)]) + ", ";
        }
        temp_string = temp_string.substr(0,temp_string.size()-2);
        temp_string += "]";
        os << temp_string << std::endl;
        temp_string = "";
    }
    return os;
}

std::istream& operator>>(std::istream& os, matrix &numbers) {
    // this function allows for input of a matrix
    std::cout << "Enter the number of rows: " << std::endl;
    std::string input;
    os >> input; // gets the input
    numbers.set_row(std::stoi(input));
    
    input = "";
    std::cout << "Enter the number of columns: " << std::endl;
    os >> input;
    numbers.set_col(std::stoi(input));
    
    std::cout << "Enter the matrix in form: {a,b...}: " << std::endl;
    input = "";
    os >> input;
    std::vector<double> data;
    double temp_number;
    std::string temp_string;
    int i{1};
    std::cout << "the input: " << input << std::endl; 

    bool number_start;
    while (i != input.length()) {
        number_start = true;
        temp_string = "";
        while (number_start) {
            if (input[i]==',') {
                temp_number = std::stod(temp_string);
                data.push_back(temp_number);
                i++;
                break;
            } else if (input[i] =='}') {
                number_start=false;
                temp_number = stold(temp_string);
                data.push_back(temp_number);
            } else {
                temp_string += input[i];
            }
            i++;
        }
    }
    
    double* new_data = new double[data.size()];
    std::copy(data.begin(), data.end(), new_data); 
    // copies the array into a memory location that doesn't disappear when it goes out of scope.
    
    // convert a vector into double array
    numbers.set_data(&new_data[0],data.size()); // assigns the data onto the matrix
    return os;
}


int main() {

    double* pointer;
    pointer = new double[4];
    pointer[0] = 5;
    pointer[1] = 5;
    pointer[2] = 5;
    pointer[3] = 5;
    matrix D(2,2,pointer);
    std::cout << D;

    matrix G;
    matrix F = D; // copy constructor
    G = D; // assignment operator
    std::cout << F;
    std::cout << G;

    delete[] pointer;
    return 0;
}  
