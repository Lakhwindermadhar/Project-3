#define _CRT_SECURE_NO_WARNINGS  // Disable warnings for unsafe functions 

#include <stdio.h>   // Standard Input/Output library
#include <string.h>  // String manipulation functions

#define MAX_LINE 500   // Maximum length of a line read from the file

// Function: converts all uppercase letters in a string to lowercase
void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {           // Loop through each character until end of string
        if (str[i] >= 'A' && str[i] <= 'Z') {  // Check if character is uppercase
            str[i] = str[i] + 32;     // Convert uppercase letter to lowercase
        }
        i++;                           // Move to next character
    }
}

int main(void) {
    FILE* fp = NULL;       // File pointer for reading the input file
    FILE* outFile = NULL;  // File pointer for writing filtered output file

    int choice = 0;        // Variable to store menu choice
    int keepRunning = 1;   // Flag to control main menu loop
    int total = 0;         // Counter for total number of Calls to Action
    int found = 0;         // Flag indicating whether a search found matches

    char line[MAX_LINE];       // Buffer to read each line from file
    char category[50];         // Stores extracted category from each line
    char searchCategory[50];   // Stores user input category for searching
    char filename[60];         // Stores filename for saving filtered results
    char tempLine[MAX_LINE];   // Temporary buffer for safe string manipulation

    // Main menu loop
    while (keepRunning == 1) {
        // Display menu options
        printf("\n------ MENU ------\n");
        printf("1. Display all Calls to Action\n");  // Option 1
        printf("2. Search Calls to Action by category\n");  // Option 2
        printf("3. Display total number of Calls to Action\n");  // Option 3
        printf("4. Save Calls to Action by category to a new file\n");  // Option 4
        printf("5. Exit\n");  // Option 5
        printf("Enter your choice: ");
        scanf("%d", &choice);   // Read user's menu choice
        getchar();              // Remove leftover newline from input buffer

        switch (choice) {
            // Option 1: Display all Calls to Action
        case 1:
            fp = fopen("calls_to_action.txt", "r");  // Open file in read mode
            if (fp == NULL) {  // Check if file exists
                printf("Error: File cannot be opened.\n");  // Print error if file not found
            }
            else {
                printf("\n--- All Calls to Action ---\n\n");
                while (fgets(line, MAX_LINE, fp) != NULL) {  // Read each line until EOF
                    printf("%s", line);  // Print line to console
                }
                fclose(fp);  // Close file after reading
            }
            break;

            // Option 2: Search Calls to Action by category
        case 2:
            fp = fopen("calls_to_action.txt", "r");  // Open file in read mode
            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");  // Error if file not found
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);              // Read category input from user
                toLowerCase(searchCategory);       // Convert input to lowercase for case-insensitive search

                found = 0;  // Reset found flag

                while (fgets(line, MAX_LINE, fp) != NULL) {  // Read each line
                    strcpy(tempLine, line);               // Copy line to temp buffer for tokenization
                    strtok(tempLine, "|");                // Skip first field (Call number)
                    strcpy(category, strtok(NULL, "|"));  // Extract category field
                    toLowerCase(category);                // Convert category to lowercase

                    if (strcmp(category, searchCategory) == 0) {  // Compare user input with category
                        printf("%s", line);  // Print matching line
                        found = 1;           // Set found flag
                    }
                }

                if (found == 0) {  // If no matches found
                    printf("No records found.\n");
                }

                fclose(fp);  // Close file after search
            }
            break;

            // Option 3: Count total number of Calls to Action
        case 3:
            fp = fopen("calls_to_action.txt", "r");  // Open file in read mode
            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");  // Error if file not found
            }
            else {
                total = 0;  // Reset total counter
                while (fgets(line, MAX_LINE, fp) != NULL) {  // Count each line
                    total++;
                }
                printf("Total number of Calls to Action: %d\n", total);  // Display total
                fclose(fp);  // Close file after counting
            }
            break;

            // Option 4: Save Calls to Action by category to a new file
        case 4:
            fp = fopen("calls_to_action.txt", "r");  // Open file in read mode
            if (fp == NULL) {
                printf("Error: File cannot be opened.\n");  // Error if file not found
            }
            else {
                printf("Enter category: ");
                gets(searchCategory);             // Read category input from user
                toLowerCase(searchCategory);      // Convert input to lowercase

                strcpy(filename, searchCategory);   // Build output filename
                strcat(filename, "_calls.txt");     // Append suffix

                outFile = fopen(filename, "w");  // Open output file in write mode
                if (outFile == NULL) {
                    printf("Error: Output file could not be created.\n");  // Error if cannot write
                }
                else {
                    found = 0;  // Reset found flag

                    while (fgets(line, MAX_LINE, fp) != NULL) {  // Read input file line by line
                        strcpy(tempLine, line);               // Copy line to temp
                        strtok(tempLine, "|");                // Skip first field (Call number)
                        strcpy(category, strtok(NULL, "|"));  // Extract category field
                        toLowerCase(category);                // Convert category to lowercase

                        if (strcmp(category, searchCategory) == 0) {  // If category matches user input
                            fprintf(outFile, "%s", line);  // Write matching line to output file
                            found = 1;                     // Set found flag
                        }
                    }

                    if (found == 1) {  // If matches were found and saved
                        printf("Matching calls saved to %s\n", filename);
                    }
                    else {  // If no matches found
                        printf("No matching records found.\n");
                    }

                    fclose(outFile);  // Close output file
                }

                fclose(fp);  // Close input file
            }
            break;

            // Option 5: Exit program
        case 5:
            printf("Exiting program. Goodbye!\n");
            keepRunning = 0;  // Stop main menu loop
            break;

            // Default: Invalid menu choice
        default:
            printf("Invalid choice. Try again.\n");  // Print error message
        }
    }

    return 0;  // Program ends
}
