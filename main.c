#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_alias_to_bash(char *args) {
    printf("Enter the arguments: ");
    scanf("%s", args);
}

void read_bash_file() {
    FILE *file;
    char *home = getenv("HOME");
    char file_name[] = "/.zshrc";

    
    strcat(home, file_name);
    file = fopen(home, "r");
    char myFile[1000];

    if (file != NULL) {
        while (fgets(myFile, 1000, file) != NULL) {
            printf("%s", myFile);
        }
    } else {
        printf("Error opening file\n");
    }

    fclose(file);
}


int main(int argc, char *argv[]) {
    printf("no of arguments: %d\n", argc);
    int i = 1; // skip the first arg since it's only program name
    while (i < argc) {
        if (strcmp(argv[i], "-h") == 0) {
            printf("Help option\n");
        } else if (strcmp(argv[i], "-l") == 0) {
            printf("Reading from bash file\n");
            read_bash_file();
        } else if (strcmp(argv[i], "-a") == 0) {
            char arg[100];
            add_alias_to_bash(arg);
        } else {
            printf("Invalid option\n");
        }
        i++;
    }
    printf("Finished executing program...\n");
    return 0;
}