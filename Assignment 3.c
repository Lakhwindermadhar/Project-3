#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_LINE 500   // maximum length of a line from the file

// converts all uppercase letters in a string to lowercase
void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {   // loop through each character
        if (str[i] >= 'A' && str[i] <= 'Z') {  // if uppercase
            str[i] = str[i] + 32;             // convert to lowercase
        }
        i++;
    }
}

// remove newline character from fgets input
void trimNewline(char str[]) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {   // check if last character is newline
        str[len - 1] = '\0';                 // remove newline
    }
}

int main(void) {
    FILE* fp = NULL;       // pointer for reading file
    FILE* outFile = NULL;  // pointer for writing file

    int choice = 0;        // variable to store menu choice
    int keepRunning = 1;   // loop control flag
    int total = 0;         // counter for total number of Calls to Action
    int found = 0;         // flag to indicate if a match is found

    char line[MAX_LINE];       // buffer for reading each line from file
    char category[50];         // extracted category from each line
    char searchCategory[50];   // category input by user
    char filename[60];         // output filename for saving filtered category
    char tempLine[MAX_LINE];   // temporary buffer to safely manipulate strings

    // main menu loop
    while (keepRunning == 1) {
        // display menu
        printf("\n------ MENU ------\n");
        printf("1. Display all Calls to Action\n");
        printf("2. Search Calls to Action by category\n");
        printf("3. Display total number of Calls to Action\n");
        printf("4. Save Calls to Action by category to a new file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);   // read user choice
        getchar();              // clear leftover newline from buffer

        switch (choice) {
        // option 1: display all Calls to Action
        case 1:
            fp = fopen("calls_to_action.txt", "r");  // open file for reading

            if (fp == NULL) {  // check if file opened successfully
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("\n--- All Calls to Action ---\n\n");
                // read and print each line until the end of the file
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    printf("%s", line);
                }
                fclose(fp);  // close file after reading
            }
            break;

        // option 2: search Calls to Action by category
        case 2:
            fp = fopen("calls_to_action.txt", "r");  // open file for reading

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                fgets(searchCategory, 50, stdin);   // read input safely
                trimNewline(searchCategory);        // remove newline from input
                toLowerCase(searchCategory);        // convert input to lowercase

                found = 0;  // reset found flag

                // read file line by line
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    strcpy(tempLine, line);              // copy line to preserve original
                    strtok(tempLine, "|");               // skip first field (number)
                    strcpy(category, strtok(NULL, "|")); // extract category field
                    toLowerCase(category);               // convert to lowercase

                    // compare user input with category in file
                    if (strcmp(category, searchCategory) == 0) {
                        printf("%s", line);  // print matching line
                        found = 1;           // set found flag
                    }
                }

                // if no matches found
                if (found == 0) {
                    printf("No records found.\n");
                }

                fclose(fp);  // close file after search
            }
            break;

        // option 3: count total number of Calls to Action
        case 3:
            fp = fopen("calls_to_action.txt", "r");  // open file for reading

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                total = 0;  // reset total counter
                // loop through file counting lines
                while (fgets(line, MAX_LINE, fp) != NULL) {
                    total++;
                }

                printf("Total number of Calls to Action: %d\n", total);  // display total
                fclose(fp);  // close file
            }
            break;

        // option 4: save Calls to Action by category to a new file
        case 4:
            fp = fopen("calls_to_action.txt", "r");  // open file for reading

            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");
            }
            else {
                printf("Enter category: ");
                fgets(searchCategory, 50, stdin);   // read category safely
                trimNewline(searchCategory);        // remove trailing newline
                toLowerCase(searchCategory);        // normalize to lowercase

                // create output filename using category
                strcpy(filename, searchCategory);
                strcat(filename, "_calls.txt");     // append suffix to filename

                outFile = fopen(filename, "w");     // open output file for writing

                if (outFile == NULL) {
                    printf("Error: Output file could not be created.\n");
                }
                else {
                    found = 0;  // reset found flag

                    // read input file line by line
                    while (fgets(line, MAX_LINE, fp) != NULL) {
                        strcpy(tempLine, line);              // copy line for safe tokenization
                        strtok(tempLine, "|");               // skip first field (number)
                        strcpy(category, strtok(NULL, "|")); // extract category
                        toLowerCase(category);               // convert to lowercase

                        // if category matches user input, write line to new file
                        if (strcmp(category, searchCategory) == 0) {
                            fprintf(outFile, "%s", line);  // write matching line
                            found = 1;                      // set found flag
                        }
                    }

                    // inform user about result
                    if (found == 1) {
                        printf("Matching calls saved to %s\n", filename);
                    }
                    else {
                        printf("No matching records found.\n");
                    }

                    fclose(outFile);  // close output file
                }

                fclose(fp);  // close input file
            }
            break;

        // option 5: exit program
        case 5:
            printf("Exiting program. Goodbye!\n");
            keepRunning = 0;   // stop main menu loop
            break;

        // default case for invalid menu choice
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;  // program ends
}
