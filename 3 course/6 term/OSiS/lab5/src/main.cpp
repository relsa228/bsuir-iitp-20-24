#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "headers/controllers.h"
#include "headers/secondaryFunctions.h"

void loop() {
    while(1) {
        sleep(120);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-q") == 0) {        
        termAllProcesses();
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "-q") == 0) {       
        char *endptr; 
        int pidKill = strtol(argv[2], &endptr, 10);
        termProccess(pidKill);
        return 0;
    }

    int pid = fork();
    switch(pid) {
        case 0:
            setsid();
            chdir("/");
            controllerExposer(setConfiguration());
            loop();
            exit(0);
        case -1:
            printf("Fail: unable to fork\n");
            break;
        default:
            printf("OK: demon with pid %d is created\n", pid);
            std::ofstream inptPidList(PID_LIST_FILE, std::ios::app);
            if (inptPidList.is_open())
                inptPidList << std::to_string(pid) + "\n";
            inptPidList.close();
        break;
    }
    return 0;
}