//
// Created by AnimeLord on 07.11.2022.
//

#ifndef LR_3_GAUSS_MODULE_OMP_H
#define LR_3_GAUSS_MODULE_OMP_H

#include "vector"

template <typename T>
int col_max_omp(const std::vector<std::vector<T> > &matrix, int col, int n) {
    T max = std::abs(matrix[col][col]);
    int maxPos = col;
#pragma omp parallel
    {
        T loc_max = max;
        T loc_max_pos = maxPos;
#pragma omp for
        for (int i = col+1; i < n; ++i) {
            T element = std::abs(matrix[i][col]);
            if (element > loc_max) {
                loc_max = element;
                loc_max_pos = i;
            }
        }
#pragma omp critical
        {
            if (max < loc_max) {
                max = loc_max;
                maxPos = loc_max_pos;
            }
        }
    }
    return maxPos;
}

template <typename T>
int triangulation_omp(std::vector<std::vector<T> > &matrix, int n) {
    unsigned int swapCount = 0;

    if (0 == n)
        return swapCount;

    const int num_cols = matrix[0].size();
    for (int i = 0; i < n-1; ++i) {
        unsigned int imax = col_max_omp(matrix, i, n);
        if (i != imax) {
            swap(matrix[i], matrix[imax]);
            ++swapCount;
        }

#pragma omp parallel for
        for (int j = i + 1; j < n; ++j) {
            T mul = -matrix[j][i]/matrix[i][i];

            for (int k = i; k < n; ++k) {
                matrix[j][k] += matrix[i][k]*mul;
            }
        }
    }
    return swapCount;
}

template <typename T>
std::vector<T> gauss_solving_omp(std::vector<std::vector<T> > &matrix,
                             std::vector<T> &free_term_column, int n) {
    std::vector<T> solution(n);

    for (int i = 0; i < n; ++i) {
        matrix[i].push_back(free_term_column[i]);
    }
    triangulation_omp(matrix, n);

    for (int i = n-1; i>=0; --i) {
        solution[i] = matrix[i][n]/matrix[i][i];

        for (int j = 0; j < i; ++j) {
            matrix[j][n] -= matrix[j][i]*solution[i];
        }
    }

    return solution;
}

#endif //LR_3_GAUSS_MODULE_OMP_H
