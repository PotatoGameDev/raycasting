#include "util.h"

namespace potato_raycasting {

std::vector<std::vector<int>>
transpose(const std::vector<std::vector<int>> &matrix) {
    int rows = matrix.size();
    if (rows == 0) {
        return {};
    }
    int cols = matrix[0].size();

    std::vector<std::vector<int>> transposed(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

} // namespace potato_raycasting
