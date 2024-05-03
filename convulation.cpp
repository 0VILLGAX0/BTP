#include <iostream>
#include <vector>

void applyConvolution(std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& kernel) {
    int rows = image.size();
    int cols = image[0].size();
    int kSize = kernel.size();
    std::vector<std::vector<int>> output(rows, std::vector<int>(cols, 0));

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sum += image[i + ki][j + kj] * kernel[ki + 1][kj + 1];
                }
            }
            output[i][j] = sum;
        }
    }

    // Copy output to original image matrix
    image = output;
}

int main() {
    std::vector<std::vector<int>> image = {
        {10, 10, 10, 10, 10},
        {10, 20, 20, 20, 10},
        {10, 20, 50, 20, 10},
        {10, 20, 20, 20, 10},
        {10, 10, 10, 10, 10}
    };

    std::vector<std::vector<int>> kernel = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };

    applyConvolution(image, kernel);

    for (const auto& row : image) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

