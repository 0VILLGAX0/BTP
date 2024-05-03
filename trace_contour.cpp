#include <iostream>
#include <vector>

void traceContour(std::vector<std::vector<int>>& image, std::vector<std::vector<int>>& output, int startX, int startY) {
    int rows = image.size();
    int cols = image[0].size();
    int direction[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    int x = startX, y = startY;
    int dir = 0; // Start looking to the east

    do {
        output[x][y] = 255; // Mark the contour
        int found = 0;
        for (int i = 0; i < 8; ++i) {
            int idx = (dir + i) % 8;
            int nx = x + direction[idx][0], ny = y + direction[idx][1];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && image[nx][ny] == 1) {
                x = nx;
                y = ny;
                dir = (idx + 5) % 8; // Adjust the next direction to search
                found = 1;
                break;
            }
        }
        if (!found) break; // No more contours
    } while (x != startX || y != startY);

    for (const auto& row : output) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> image = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    std::vector<std::vector<int>> output(5, std::vector<int>(5, 0));
    traceContour(image, output, 1, 1);

    return 0;
}

