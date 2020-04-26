#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

class Matrix
{
    friend double getTrace(const Matrix& matrix);                                    
    friend double getDeterminant(const Matrix matrix);
    friend Matrix transpose(const Matrix& matrix);                                   
    friend Matrix reverse(const Matrix& matrix);                                     
    friend Matrix exp(const Matrix& matrix, int n);                                  
    friend ostream& operator<<(ostream& out, const Matrix& matrix);                  
    friend istream& operator>>(istream& in, Matrix& matrix);                                  
private:
    double** matrix;
    std::string name;
    int size;
public:
    Matrix(int);//identity matrix                        
    Matrix(string, int, double**);                                   
    Matrix(const Matrix&);//copy constructor
    Matrix(Matrix&&);//move constructor
    Matrix(string, int, double);                                         
    Matrix(string, int, int);//random values

    
    Matrix& operator=(Matrix&&);
    Matrix& operator=(const Matrix&);
    Matrix& operator*=(const Matrix&);     
    Matrix& operator+=(const Matrix&); 
    Matrix& operator-=(const Matrix&); 
    Matrix& operator/=(const int);
    Matrix operator/(const int);
    Matrix operator*(const Matrix&);   
    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    bool operator==(const Matrix&); 
    bool operator!=(const Matrix&);
      
    void print();

    const Matrix reduceColRow(int, int) const;

    ~Matrix();
};