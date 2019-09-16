#include <string>
#include <sys/stat.h>

void create_directory_if_not_exists(const std::string& path) {
    struct stat buffer = {0};
    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        mkdir(path.c_str(), 0700);
    }
}