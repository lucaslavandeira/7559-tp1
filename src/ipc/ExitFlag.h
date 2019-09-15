#ifndef TP1_EXITFLAG_H
#define TP1_EXITFLAG_H


#include <sys/ipc.h>

class ExitFlag {
    bool* flag;
    int shared_memory_id;

public:
    ExitFlag();
    ExitFlag(bool readonly);
    ~ExitFlag();

    bool read();
    void exit();
};


#endif //TP1_EXITFLAG_H
