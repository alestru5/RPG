#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

template <typename T>
class Matrix {
    private:
        T **matrix;
        int m;
        int n;
    public:
        Matrix(): n(0), m(0), matrix(nullptr){}
        Matrix(int height, int width){
            if (height <0){
                throw std::invalid_argument("height less than zero");
            }
            if (width < 0){
                throw std::invalid_argument("width less than zero");
            }
            m = height;
            n = width;
            matrix = (T**) new T*[m];
            for (int i = 0; i < m; i++){
                matrix[i] = (T*) new T[n];
            }
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    matrix[i][j] = 0;
                }
            }
        }

        Matrix(const Matrix& M){
            m = M.getM();
            n = M.getN();
            matrix = (T**) new T*[m];
            for (int i = 0; i < m; i++){
                matrix[i] = (T*) new T[n];
            }
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    matrix[i][j] = M.getMatrix()[i][j];
                }
            }
        }

        Matrix(std::vector<std::vector<T>> &data){
            if (data.size() == 0){
                m = 0;
                n = 0;
            } else{
                m = data.size();
                n = data[0].size();
            }
            matrix = (T**) new T*[m];
            for (int i = 0; i < m; i++){
                matrix[i] = (T*) new T[n];
            }
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    matrix[i][j] = data[i][j];
                }
            }
        }


        ~Matrix(){
            if (n > 0)
            {
                for (int i = 0; i < m; i++)
                    delete[] matrix[i];
            }

            if (m > 0)
                delete[] matrix;
        }

        int getM() const { return m; }
        int getN() const { return n;}
        T** getMatrix() const { return matrix; }
        T* operator [](const int i) const{
            if (i > m || i < 0){
                throw std::invalid_argument("ivalid index");
            }
            return matrix[i];
        }
        Matrix& swap(int i1, int j1, int i2, int j2){
            if (i1 >= m || j1 >=n || i2 >= m || j2 >= n || i1 < 0 || j1 < 0 || i2 < 0 || j2 < 0){
                throw std::invalid_argument("index out of range");
            }
            T tmp= matrix[i1][j1];
            matrix[i1][j1] = matrix[i2][j2];
            matrix[i2][j2] = tmp;
        }

        void setValue(int i, int j, T &value)
        {
            if ((i < 0) || (i >= m))
                return;
            if ((j < 0) || (j >= n))
                return;
            matrix[i][j] = value;
        }

        Matrix operator=(const Matrix& M)
        {
            if (n > 0)
            {
                for (int i = 0; i < m; i++)
                    delete[] matrix[i];
            }

            if (m > 0)
            {
                delete[] matrix;
            }

            m = M.m;
            n = M.n;

            matrix = (T**) new T*[m];
            for (int i = 0; i < m; i++)
                matrix[i] = (T*) new T[n];

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    matrix[i][j] = M.matrix[i][j];
            return *this;
        }
    };

#endif // MATRIX_H
