#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *get_alias_name(const char *s) {
    int start_idx = 6;
    int end_idx;

    for (int i = 0; i < strlen(s); i++) {
        // find index of the first = sign as end index
        if (s[i] == '=') {
            end_idx = i;
            break;
        }
    }

    int len = end_idx - start_idx;
    char *alias_name = malloc(len);
    strncpy(alias_name, s + start_idx, len);
    return alias_name;
}

char *get_alias_cmd(const char *s) {
    char opening_bracket = '\0';
    int start_idx;
    int end_idx;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '"') {
            if (opening_bracket == '\0') {
                opening_bracket = '"';
                start_idx = i + 1;
                continue;
            } else if (opening_bracket == '\'') {
                continue;
            }

            end_idx = i;
        } else if (s[i] == '\'') {
            if (opening_bracket == '\0') {
                opening_bracket = '\'';
                start_idx = i + 1;
                continue;
            } else if (opening_bracket == '"') {
                continue;
            }

            end_idx = i;
        }
    }
    int len = end_idx - start_idx;
    char *alias_cmd = malloc(len);
    strncpy(alias_cmd, s + start_idx, len);
    return alias_cmd;
}


bool starts_with(const char *pre, const char *str) {
    if(strncmp(str, pre, strlen(pre)) == 0) {
        return true;
    }
    return false;
}

void add_alias_to_bash(char *alias_name, char *alias_cmd) {
    printf("adding alias [%s] to command [%s]\n", alias_name, alias_cmd);
    int WRITE_TO_LINE_NO = 5;
    FILE *file;
    char *home = getenv("HOME");
    char file_name[] = "/.zshrc";
    strcat(home, file_name);

    file = fopen(home, "a");
    char line[1000];

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", home);
    }
    fprintf(file, "alias %s=\"%s\"\n", alias_name, alias_cmd);
    fclose(file);
}

void pretty_print(char *s1, char *s2) {
    int MAX_S1_LENGTH = 15;

    printf("%s", s1);
    for(int i = 0; i < MAX_S1_LENGTH - strlen(s1); i++) {
        printf(" ");
    }
    printf(" | %s\n", s2);
}

void print_bash_file() {
    FILE *file;
    char *home = getenv("HOME");
    char file_name[] = "/.zshrc";
    strcat(home, file_name);

    file = fopen(home, "r");
    char line[1000];

    if (file != NULL) {
        while (fgets(line, 1000, file) != NULL) {
            // skip commneted out lines
            if (starts_with("#", line) == 1) {
                continue;
            }
            if (starts_with("alias", line) != 1) {
                continue;
            }

            char *alias_name = get_alias_name(line);
            char *alias_cmd = get_alias_cmd(line);
            pretty_print(alias_name, alias_cmd);
            free(alias_name);
            free(alias_cmd);
        }
    } else {
        printf("Error opening file\n");
    }
    fclose(file);
}

void find_alias(char alias_name[]) {
    printf("finding alias: %s...\n", alias_name);
    FILE *file;
    char *home = getenv("HOME");
    char file_name[] = "/.zshrc";
    strcat(home, file_name);

    file = fopen(home, "r");
    char line[1000];
    if (file != NULL) {
        while (fgets(line, 1000, file) != NULL) {
            if (starts_with("alias", line) != 1) {
                continue;
            }
            char *curr_alias_name = get_alias_name(line);
            if(strcmp(curr_alias_name, alias_name) == 0) {
                char *alias_cmd = get_alias_cmd(line);
                pretty_print(curr_alias_name, alias_cmd);
                free(curr_alias_name);
                free(alias_cmd);
                break;
            }
            free(curr_alias_name);
        }
    } else {
        printf("Error opening file\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int i = 1; // skip the first arg since it's only program name
    while (i < argc) {
        if (strcmp(argv[i], "-h") == 0) {
            printf("Alias Assistant 1.0.0 by danipurwadi\n");
            printf("Usage: main [arguments]\n");
            printf("Arguments:\n");
            printf("  -a <alias_name> <alias_cmd> add new alias in zshrc \n");
            printf("  -l list out all aliases in zshrc\n");
            printf("  -f <alias_name> find and print out alias in zshrc (if exist)\n");
        } else if (strcmp(argv[i], "-l") == 0) {
            print_bash_file();
        } else if (strcmp(argv[i], "-f") == 0) {
            char *name = argv[i + 1];
            find_alias(name);
            i++;
        } else if (strcmp(argv[i], "-a") == 0) {
            char *alias_name = argv[i + 1];
            char *alias_cmd = argv[i + 2];
            add_alias_to_bash(alias_name, alias_cmd);
            i += 2;
        } else {
            printf("Invalid option\n");
        }
        i++;
    }
    return 0;
}