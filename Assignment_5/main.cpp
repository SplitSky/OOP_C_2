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
            if (this->data != nullptr) {
                delete[] data;
            } // else the data is empty
            this->data = nullptr;
        }

        matrix(matrix&);// copy constructor
        matrix(matrix&&); // move constructor
        void set_row(int row);
        void set_col(int col);
        int get_row() const;
        int get_col() const;
        void set_data(double* data_2, size_t size);
        // overloading operators
        matrix operator+(matrix &numbers);
        matrix operator-(matrix &numbers) const;
        matrix operator*(matrix &numbers) const;
        matrix & operator=(matrix &numbers); // copy operator
        //matrix & operator=(matrix &&numbers); // move operator
        std::string show_data() const;
        double* get_data() const;
        // determinant functions

        double find_determinant() {
            std::vector<double> temp_vector;
            temp_vector.assign(data, data+(row*col));
            return this->calc_det(row, temp_vector);
        }

        double calc_det(int row, std::vector<double> matrix) {
            if (row == 2) {
                return matrix[0]*matrix[3] - matrix[1]*matrix[2];
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

matrix::matrix(matrix &numbers) { // COPY CONSTRUCTOR
    this->set_col(numbers.get_col());
    this->set_row(numbers.get_row());
    this->set_data(numbers.get_data(), numbers.get_col()*numbers.get_row());
}

matrix::matrix(matrix &&numbers) {
    data = numbers.data;
    col = numbers.col;
    row = numbers.row;
    numbers.col = 0;
    numbers.row = 0;
    numbers.data = nullptr;
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
    this->data = new double[size];
    for (size_t i{0}; i< size; i++) {
        this->data[i] = data_2[i];
    }
    return;
}

matrix matrix::operator+(matrix &numbers) {
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

matrix & matrix::operator=(matrix& numbers) { // deep copy
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
    int row{3};
    int col{3};
    double data1[9] = {1,2,3,9,8,7,4,2,6};
    double data2[9] = {5,5,4,1,2,3,6,9,8};
    double data3[6] = {3,4,1,2,5,6};
    matrix A(row, col, data1);
    matrix B(row, col, data2);
    matrix C(2,3,data3);

    std::cout << "Matrix A: " << std::endl;
    std::cout << A << std::endl;
    std::cout << "Matrix B: " << std::endl;
    std::cout << B << std::endl;
    std::cout << "Matrix C: " << std::endl;
    std::cout << C << std::endl;

    matrix result_1{A+B};

    matrix result_2{A-B};
   
    matrix result_3{A*B};

    matrix result_4{C*B};

    // 1. Prints all the matrices
    std::cout << "Printing all matrices" << std::endl;
    std::cout << "matrix A+B: " << result_1 << std::endl;
    std::cout << "matric A-B: " << result_2 << std::endl;
    std::cout << "matrix A*B: " << result_3 << std::endl;

    // 2. Show incorrect dimensions attempt
    std::cout << "Attempting to multiply the matrices with incorrect sizes (B*C)" << std::endl;
    matrix matrix8{B*C};
    //matrix8 = B*C;

    // 3. Calculate determinants
    double det_a{A.find_determinant()};
    double det_b{B.find_determinant()};

    // 3.5 Printing determinants
    std::cout << "Det of A: " << det_a << std::endl;
    std::cout << "Det of B: " << det_b << std::endl; 
    
    // 4. Input testing
    matrix matrix9;
    std::cin >> matrix9; // the input testing
    std::cout << "the input matrix: " << matrix9 << std::endl;

    // 5. Showing that the copy and move constructors work.    
    A = B; // modifies the original matrix
    std::cout << "matrix A after A was overwritten with B: " << A;
    std::cout << "matrix A: " << A << std::endl;
    std::cout << "matrix B: " << B << std::endl;
    std::cout << "Deleting B" << std::endl;
    B.~matrix(); // forces the call of the destructor
    std::cout << "matrix A: " << A << std::endl;

    // 6. Demonstrating the use of the move constructor.
    std::cout << "Calling move constructor" << std::endl;
    matrix result_6{std::move(A)};
    std::cout << "Printing moved matrix:" << std::endl;
    std::cout << result_6 << std::endl;
    std::cout << "Printing original matrix:" << std::endl;
    std::cout << A << std::endl;

    return 0;
}  
