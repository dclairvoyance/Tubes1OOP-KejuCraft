#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <array>
#include <iostream>

template<class T, int row, int col>
class Matrix
{
    array<T, row * col> datas;
public:
    T& operator()(int y, int x){
        return datas[y * col + x];
    }

    // more methods go here
};

#endif