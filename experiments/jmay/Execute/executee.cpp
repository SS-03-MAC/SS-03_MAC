#include <iostream>

int main(int argc, char* argv[]) {
//    for (int i = 0; i < argc; i++) {
//        std::cout << argv[i] << std::endl;
//    }
    char input[200];
    //gets(input);
    int i = 0;
    do {
        int read;
        read = getchar();
        printf("%d '%c'\n", read, (char) read);
        input[i] = (char) read;
        //fflush(stdout);
    } while (input[i++] != EOF && i < 199);
    input[i - 1] = 0;
    printf("Just in: %s", input);
fflush(stdout);
    return 0;
}