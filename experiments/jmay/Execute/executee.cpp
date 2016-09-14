#include <iostream>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    long addr;
    sscanf(argv[1], "%ld", &addr);
    printf("%s", (char *) addr);
    return 0;
}