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
// Things to do
// The class:
// 1. Contain no. of rows, no. of columns and a pointer to the matrix data (type double)
// 2. Constructor using dynamic memory allocation
// 3. Store data in a one dimensional array. For a matrix by m x n. The location is given by (j-1) + (i-1)*n
// 4. the destructor should delete dynamically allocated memory
// 5. Assignment operator and copy constructor functions would perform deep copies of data
// 6. Recursive calculation of a determinant:
// 7. 

class matrix {
    friend std::ostream& operator<<(std::ostream &os, matrix &numbers);
    friend std::ifstream& operator>>(std::ifstream &os, matrix &numbers);
    
    private:
        int row;
        int col;
        double *data;

        double calc_det(int row, std::vector<double> matrix) {
            if (row == 2) { // col must also be 2 because its a square
                return matrix[0]*matrix[3] - matrix[1]*matrix[2]; // base case
            } else {
                double determinant{0};
                for (int j{1}; j<=row; j++) {
                    determinant += pow(-1, 1+j) * matrix[j-1] * calc_det(row-1, splice_matrix(1,j,matrix));
                }
                return determinant;
            }
        }

        std::vector<double> splice_matrix(int i_pivot, int j_pivot, std::vector<double> matrix) {
            std::vector<double> new_matrix = {};
            int col = pow(matrix.size(), 0.5);
            for (int i{1}; i<=col; i++) {
                for (int j{1}; j<=col; j++) {
                    if ((i != i_pivot) && (j != j_pivot)) {
                        new_matrix.push_back(matrix[(i-1)*col + (j-1)]);
                    }
                }
            }
            return new_matrix;
        }

    public:
        // constructor default
        matrix() {
            this->data = nullptr;
            this->row = 0;
            this->col = 0;
        }
        // parameter constructor
        matrix(int row, int col, double data_in[]): row{row}, col{col} {
            this->data = new double[row*col]; // declares memory space
            for (int i{0}; i<row*col; i++) { // performs deep copy
                this->data[i] = data_in[i];
            }
        }
        // destructor
        ~matrix(){
            this->data = nullptr;
            delete[] this->data;
        }

        matrix(const matrix&); // copy constructor


        int get_row(){return this->row;}
        int get_col(){return this->col;}

        void set_row(int row){this->row=row;}
        void set_col(int col){this->col=col;}
        void set_data(double* data_2, size_t size){
            this->data = new double[size];
            for (size_t i{0}; i< size; i++) {
                this->data[i] = data_2[i];
                std::cout << this->data[i] << std::endl;
                // copies data from one pointer location to the other
            }
            return;        
        }

        matrix operator+(matrix &numbers) const {
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

        matrix operator-(matrix &numbers) const {
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

        matrix operator*(matrix &numbers) {
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

        matrix& operator=(matrix &numbers) { // deep copy
            if (&numbers == this) {return *this;} // avoids self assignment
            
            delete[] data; 
            data = nullptr;
            col = 0;row = 0;
            col = numbers.col;
            row = numbers.row;
            if (row*col>0) {
                data = new double[row*col];
                for (size_t i{}; i<col*row; i++) {
                    data[i]=numbers.data[i];
                }
            }
            return *this;
        }

        std::string show_data() const {
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

        double find_determinant() {
            std::vector<double> temp_vector;
            temp_vector.assign(this->data, this->data+(this->row*this->col));// assigns an array to a vector
            return this->calc_det(this->row, temp_vector); // use private function as a helper
        }
        
        void slice_matrix2(int i_pivot, int j_pivot) {
            std::vector<double> new_data;
            for (size_t i{0}; i<this->row*this->col; i++) {
                new_data.push_back(this->data[i]);
            }
            
            this->row = this->row - 1;
            this->col = this->col - 1;
            delete[] this->data;
            this->data = new double[this->row * this->col];
            // purges and resets the data variables
            new_data = this->splice_matrix(i_pivot, j_pivot, new_data); // uses the helper function to splice the vector
            std::copy(new_data.begin(), new_data.end(), this->data);// copies the data into the pointer location
            // copies the array into a memory location that doesn't disappear when it goes out of scope.            
            matrix temp; // defines object
            double* data_assigned = new double[this->row*this->col];
            std::copy(new_data.begin(), new_data.end(), data_assigned);
            this->set_data(data_assigned, new_data.size());
            delete[] data_assigned;

    }
};



std::ostream& operator<<(std::ostream& os, matrix &numbers) {
    // this function prints matrix in visually representative way
    os << "Printing the matrix:" << std::endl;
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
    delete[] pointer; // frees up assignmed memory in the main

    matrix F; // demonstrates the overloaded functions
    std::cin >> F;
    std::cout << "One" << std::endl;
    std::cout << F;
    std::cout << D;


    D = F;
    std::cout << "Two" << std::endl;
    std::cout << D; 
    D.set_data(pointer, 4);
    std::cout << "Three" << std::endl;
    std::cout << D;


    return 0;
} 
