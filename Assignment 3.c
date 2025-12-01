#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_LINE 500


void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main(void) {
    FILE* fp = NULL;
    FILE* outFile = NULL;

    int choice = 0;
    int keepRunning = 1;
    int total = 0;
    int found = 0;

    char line[MAX_LINE];
    char category[50];
    char searchCategory[50];
    char filename[60];
    char tempLine[MAX_LINE];

    while (keepRunning == 1) {

        printf("\n------ MENU ------\n");
        printf("1. Display all Calls to Action\n");
        printf("2. Search Calls to Action by category\n");
        printf("3. Display total number of Calls to Action\n");
        printf("4. Save Calls to Action by category to a new file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();   // clear newline

        switch (choice) {

        case 1:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("\n--- All Calls to Action ---\n\n");

                while (fgets(line, MAX_LINE, fp) != NULL) {
                    printf("%s", line);
                }

                fclose(fp);
            }
            break;

        case 2:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);
                toLowerCase(searchCategory);

                found = 0;

                while (fgets(line, MAX_LINE, fp) != NULL) {

                    strcpy(tempLine, line);

                    strtok(tempLine, "|");
                    strcpy(category, strtok(NULL, "|"));

                    toLowerCase(category);

                    if (strcmp(category, searchCategory) == 0) {
                        printf("%s", line);
                        found = 1;
                    }
                }

                if (found == 0) {
                    printf("No records found.\n");
                }

                fclose(fp);
            }
            break;

        case 3:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                total = 0;

                while (fgets(line, MAX_LINE, fp) != NULL) {
                    total++;
                }

                printf("Total number of Calls to Action: %d\n", total);
                fclose(fp);
            }
            break;

        case 4:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);
                toLowerCase(searchCategory);

                strcpy(filename, searchCategory);   // copy category into filename
                strcat(filename, "_calls.txt");     // append suffix

                outFile = fopen(filename, "w");

                if (outFile == NULL) {
                    printf("Error: Output file could not be created.\n");
                }
                else {
                    found = 0;

                    while (fgets(line, MAX_LINE, fp) != NULL) {

                        strcpy(tempLine, line);
                        strtok(tempLine, "|");
                        strcpy(category, strtok(NULL, "|"));

                        toLowerCase(category);

                        if (strcmp(category, searchCategory) == 0) {
                            fprintf(outFile, "%s", line);
                            found = 1;
                        }
                    }

                    if (found == 1) {
                        printf("Matching calls saved to %s\n", filename);
                    }
                    else {
                        printf("No matching records found.\n");
                    }

                    fclose(outFile);
                }

                fclose(fp);
            }
            break;

        case 5:
            printf("Exiting program. Goodbye!\n");
            keepRunning = 0;   // ✅ CONTROL FLAG EXIT
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
