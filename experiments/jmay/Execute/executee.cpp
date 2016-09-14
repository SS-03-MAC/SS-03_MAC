#include <iostream>

int main(int argc, char* argv[]) {
//    for (int i = 0; i < argc; i++) {
//        std::cout << argv[i] << std::endl;
//    }
    char input[200];
    gets(input);
    printf("Just in: %s", input);

    return 0;
}