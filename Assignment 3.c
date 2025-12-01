#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_LINE 500

//converts all uppercase letters in a string to lowercase
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
    FILE* fp = NULL; // pointer for reading file
    FILE* outFile = NULL; // pointer for writing file

    int choice = 0; // menu choice
    int keepRunning = 1; // flag for a loop
    int total = 0; // counter for records
    int found = 0; // flag indicating matches during searches

    char line[MAX_LINE]; // buffer for reading each line
    char category[50]; // extracted category from file line
    char searchCategory[50]; // category user searches for
    char filename[60]; // output filename for saving category filters
    char tempLine[MAX_LINE]; // temporary buffer

    //main menu loop
    while (keepRunning == 1) {
        //Display menu
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
        //option 1: display all
        case 1:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("\n--- All Calls to Action ---\n\n");
                //read and print each line until EOF
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    printf("%s", line);
                }

                fclose(fp);
            }
            break;
            
        //option 2: search by category
        case 2:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);
                toLowerCase(searchCategory); // convert keyword to lowercase for comparison

                found = 0;

                while (fgets(line, MAX_LINE, fp) != NULL) {

                    strcpy(tempLine, line); // copy line so strtok doesn't destroy original

                    strtok(tempLine, "|"); // skip first field
                    strcpy(category, strtok(NULL, "|")); // extract category field

                    toLowerCase(category); // normalize case
                    
                    // compare user category with file category
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

        //option 3: count total lines
        case 3:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                total = 0;
                // count lines until EOF
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    total++;
                }

                printf("Total number of Calls to Action: %d\n", total);
                fclose(fp);
            }
            break;

        //option 4: save matches to new file
        case 4:
            fp = fopen("calls_to_action.txt", "r");

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);
                toLowerCase(searchCategory);

                //build output filename using category
                strcpy(filename, searchCategory);   // copy category into filename
                strcat(filename, "_calls.txt");     // append suffix

                outFile = fopen(filename, "w");

                if (outFile == NULL) {
                    printf("Error: Output file could not be created.\n");
                }
                else {
                    found = 0;
                    
                    //search file for matching category
                    while (fgets(line, MAX_LINE, fp) != NULL) {

                        strcpy(tempLine, line);
                        strtok(tempLine, "|"); // skip first field
                        strcpy(category, strtok(NULL, "|")); // extract category

                        toLowerCase(category);

                        if (strcmp(category, searchCategory) == 0) {
                            fprintf(outFile, "%s", line); // write match to new file
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

        //option 5: exit
        case 5:
            printf("Exiting program. Goodbye!\n");
            keepRunning = 0;   
            break;

        //default for any invalid choice
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
