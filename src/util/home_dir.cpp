#include <unistd.h>
#include <pwd.h>
#include <cstdlib>

const char* home_dir(){
    const char* home = getenv("HOME");
    if (home) {
        return home;
    }
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
}