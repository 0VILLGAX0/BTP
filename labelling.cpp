#include <iostream>
#include <vector>
#include <queue>

void labeling(std::vector<std::vector<int>>& image) {
    int rows = image.size();
    int cols = image[0].size();
    int label = 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (image[i][j] == 1) { // If cell is unvisited and marked
                std::queue<std::pair<int, int>> q;
                q.push({i, j});
                image[i][j] = ++label; // Assign a new label

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (int dx = -1; dx <= 1; ++dx) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            int nx = x + dx, ny = y + dy;
                            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && image[nx][ny] == 1) {
                                image[nx][ny] = label;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
    }

    for (const auto& row : image) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> image = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    labeling(image);

    return 0;
}

