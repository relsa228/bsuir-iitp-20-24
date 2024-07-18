//
// Created by AnimeLord on 07.11.2022.
//

#ifndef LR_3_GAUSS_MODULE_H
#define LR_3_GAUSS_MODULE_H

#include "vector"

template <typename T>
int col_max(const std::vector<std::vector<T> > &matrix, int col, int n) {
    T max = std::abs(matrix[col][col]);
    int maxPos = col;
    for (int i = col+1; i < n; ++i) {
        T element = std::abs(matrix[i][col]);
        if (element > max) {
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

template <typename T>
int triangulation(std::vector<std::vector<T> > &matrix, int n) {
    unsigned int swapCount = 0;

    if (0 == n)
        return swapCount;

    const int num_cols = matrix[0].size();
    for (int i = 0; i < n-1; ++i) {
        unsigned int imax = col_max(matrix, i, n);
        if (i != imax) {
            swap(matrix[i], matrix[imax]);
            ++swapCount;
        }

        for (int j = i + 1; j < n; ++j) {
            T mul = -matrix[j][i]/matrix[i][i];
            for (int k = i; k < num_cols; ++k) {
                matrix[j][k] += matrix[i][k]*mul;
            }
        }
    }
    return swapCount;
}

template <typename T>
std::vector<T> gauss_solving(std::vector<std::vector<T> > &matrix,
                             std::vector<T> &free_term_column, int n) {
    std::vector<T> solution(n);

    for (int i = 0; i < n; ++i) {
        matrix[i].push_back(free_term_column[i]);
    }
    triangulation(matrix, n);

    for (int i = n-1; i>=0; --i) {
        solution[i] = matrix[i][n]/matrix[i][i];

        for (int j = 0; j < i; ++j) {
            matrix[j][n] -= matrix[j][i]*solution[i];
        }
    }

    return solution;
}


#endif //LR_3_GAUSS_MODULE_H
