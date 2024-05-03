#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct CacheLine {
    std::vector<int> data;
    bool valid;
    int tag;
};

class Cache {
    std::vector<CacheLine> cache;
    int numLines;
    int blockSize;

public:
    static int totalHits;    // Static member to hold total cache hits
    static int totalMisses;  // Static member to hold total cache misses

    Cache(int numLines, int blockSize) : numLines(numLines), blockSize(blockSize), cache(numLines) {
        for (auto& line : cache) {
            line.data.resize(blockSize);
            line.valid = false;
            line.tag = -1;
        }
    }

    void accessLine(int rowIndex, const std::vector<std::vector<int>>& image) {
        int cacheIndex = rowIndex % numLines;
        if (cache[cacheIndex].valid && cache[cacheIndex].tag == rowIndex) {
            totalHits++;
        } else {
            totalMisses++;
            cache[cacheIndex].data = image[rowIndex];
            cache[cacheIndex].valid = true;
            cache[cacheIndex].tag = rowIndex;
        }
    }

    static void printTotalStats() {
        std::cout << "Total Cache Hits: " << totalHits << ", Total Cache Misses: " << totalMisses << std::endl;
    }
};

int Cache::totalHits = 0;
int Cache::totalMisses = 0;

std::vector<std::vector<int>> loadImage(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error loading image: " << path << std::endl;
        exit(1);
    }
    std::vector<std::vector<int>> image(img.rows, std::vector<int>(img.cols));
    for (int i = 0; i < img.rows; ++i)
        for (int j = 0; j < img.cols; ++j)
            image[i][j] = img.at<uchar>(i, j);
    return image;
}

void processImage(const std::string& imagePath) {
    auto image = loadImage(imagePath);
    Cache cache(3, image[0].size());  // Assuming a simple cache with 3 lines

    for (int i = 1; i < image.size() - 1; ++i) {
        cache.accessLine(i - 1, image);
        cache.accessLine(i, image);
        cache.accessLine(i + 1, image);
    }
}

void processDirectory(const fs::path& directoryPath) {
    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            std::cout << "Processing: " << entry.path() << std::endl;
            processImage(entry.path().string());
        }
    }
    Cache::printTotalStats();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <directory_path>" << std::endl;
        return 1;
    }
    processDirectory(argv[1]);
    return 0;
}
