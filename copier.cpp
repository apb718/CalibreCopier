#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> supportedExtensions = { ".epub", ".mobi", ".pdf" }; // Add more extensions as needed

bool isSupportedExtension(const std::string& fileName) {
    for (const auto& ext : supportedExtensions) {
        if (fileName.size() >= ext.size() && fileName.compare(fileName.size() - ext.size(), ext.size(), ext) == 0) {
            return true;
        }
    }
    return false;
}

void copySupportedFiles(const fs::path& sourceDir, const fs::path& destinationDir) {
    try {
        if (!fs::exists(destinationDir))
            fs::create_directory(destinationDir);

        for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
            if (fs::is_regular_file(entry.path()) && isSupportedExtension(entry.path().extension().string())) {
                fs::copy(entry, destinationDir / entry.path().filename(), fs::copy_options::overwrite_existing);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
}

int main() {
    std::string sourceDirPath, destinationDirPath;

    std::cout << "Enter source directory path: ";
    // std::cin >> sourceDirPath;
    sourceDirPath= "/home/alecbyrd/temp";

    std::cout << "Enter destination directory path: ";
    // std::cin >> destinationDirPath;
    destinationDirPath= "/home/alecbyrd/out";

    fs::path sourceDir(sourceDirPath);
    fs::path destinationDir(destinationDirPath);

    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) {
        std::cerr << "Source directory does not exist or is not a directory." << std::endl;
        return 1;
    }

    copySupportedFiles(sourceDir, destinationDir);

    std::cout << "Files copied successfully." << std::endl;

    return 0;
}
