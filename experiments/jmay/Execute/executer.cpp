#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* test;
    malloc(10000);
    test = (char*) malloc(20);
    sprintf(test, "This is only a test");
    char testAddr[20];
    sprintf(testAddr, "%ld", (long) test);
    char* const newargv[] = {(char *) "executee.exe", (char *const) testAddr, NULL};
    execv("./executee.exe", newargv);
    return 0;
}