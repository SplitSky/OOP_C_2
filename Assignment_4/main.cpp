// PHYS 30762 Programming in C++
// Assignment 4
// Tomasz Neska - ID: 10294857
// Class for complex numbers

#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>

class complex
{
    friend std::ostream& operator<<(std::ostream &os, const complex &z);
    friend std::istream& operator>>(std::ostream &os, const complex &z);
    private:
        double re,im;
    public:
        // Constructors & destructor
        complex(){re=im=0;}
        complex(double real_part, double im_part){re=real_part; im=im_part;}
        ~complex(){}
        // Return real component
        double real() {return this->re;}
        // Return imaginary component
        double imaginary() {return this->im;}

        // Return modulus
        double modulus() {return pow(this->re*this->re + this->im*this->im,0.5);}
        // Return argument
        double argument() {
            if (this->re == 0) {
                return M_PI;
            } else {
                return std::atan(this->im / this->re);
            }        
        }
        // Return complex conjugate
        complex conjugate() {
            complex conjugate{this->re, -1*this->im};
            return conjugate;
        }
        // Overload + operator for addition 
        complex operator+(const complex &number) const {
            complex temp{number.re + this->re, number.im + this->im};
            return temp;
        }
        // Overload - operator for subtraction
        complex operator-(const complex &number) const {
            complex temp{number.re - this->re, number.im - this->im};
            return temp;
        }
        // Overload * operator for multiplication, z1*z2
        complex operator*(const complex &number) const {
            complex temp{number.re*this->re - number.im*this->im, number.im*this->re + this->im*number.re}; 
            return temp;
        }
        // Overload / operator for division, z1/z2
        complex operator/(const complex &number) const {
            complex temp{(this->re * number.re + this->im * number.im)/(number.re*number.re +  number.im*number.im) ,(number.re*this->im - number.im*this->re)/(number.re*number.re +  number.im*number.im)}; 
            return temp;
        }
};

// Function to overload << operator for complex numbers
std::ostream& operator<<(std::ostream& os, const complex &number) {
    std::string temp;
    if (number.im >= 0) {
        temp = std::to_string(number.re) + "+" +std::to_string(number.im) + "i";
    } else {
        temp = std::to_string(number.re) + std::to_string(number.im) + "i";
    }    
    os << temp;
    return os; 
    }
// Function to overload >> operator for complex number
std::istream& operator>>(std::istream& os, complex &number) {
    std::string input;
    os >> input;
    std::string real;
    std::string imag;
    int pivot;
    for (int i{1};i<input.size();i++) {
        if ((input[i] == '+') || (input[i] == '-')) {
            pivot = i;
            break;
        }
    }

    real = input.substr(0,pivot);
    imag = input.substr(pivot,input.size()-1); 
    complex temp{std::stod(real), std::stod(imag)};
    number = temp;
    return os;
}


int main()
{  
    std::cout.precision(3);

    // Create two complex numbers
    complex a{3,4};
    complex b{1,-2};

    // Get real and imaginary components, modulus and argument
    std::cout << "Real and imaginary parts" << std::endl;
    std::cout << "Real: " << a.real() << " Imaginary: " << a.imaginary() << std::endl;
    std::cout << "Real: " << b.real() << " Imaginary: " << b.imaginary() << std::endl;
    std::cout << "Modulus and argument" << std::endl;
    std::cout << "Argument: " << a.argument() << " Modulus:" << a.modulus() << std::endl;
    std::cout << "Argument: " << b.argument() << " Modulus:" << b.modulus() << std::endl;
    // Get conjugates
    std::cout << "Conjugates" << std::endl;
    std::cout << a.conjugate() << std::endl;
    std::cout << b.conjugate() << std::endl;
    // Get sum, difference, product and quotient of a and b
    std::cout << "Sum: "<< a+b << std::endl;
    std::cout << "Diffeence: " << a-b << std::endl;
    std::cout << "Product: " << a*b << std::endl;
    std::cout << "Quotient: " << a/b << std::endl;
    // Print out results, also demonstrating use of overloaded operator<<
    std::cout << "Complex number a: " << a << std::endl;
    std::cout << "Complex number b: " << b << std::endl;
    
    // Showing the extraction from an input stream
    complex c;
    std::cout << "Enter a complex number in the form a+bi: ";
    std::cin >> c;
    std::cout << "Complex number c: "<< c << std::endl;

    std::cout << "the sum of a and c: " << a+c << std::endl;
    return 0;
}
