#include"../banking_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 256
#define FILE_PATH_LENGTH 150

void update_customer_info(const char *account_number) {
    char filename[FILE_PATH_LENGTH];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    // Check if the file exists
    if (access(filename, F_OK) != 0) {
        printf("Error: Account file '%s' not found.\n", filename);
        return;
    }

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to read the file '%s'.\n", filename);
        return;
    }

    // Load all lines into memory
    char lines[15][MAX_LINE_LENGTH] = {0}; // Assuming max 15 lines
    int total_lines = 0;

    while (fgets(lines[total_lines], MAX_LINE_LENGTH, file) != NULL) {
        total_lines++;
    }
    fclose(file);

    // Display update options
    printf("What would you like to update?\n");
    printf("1. Full Name\n");
    printf("2. Date of Birth\n");
    printf("3. Mobile Number\n");
    printf("4. Email\n");
    printf("5. NID\n");
    printf("6. User Name\n");
    printf("7. Password\n");
    printf("8. Account PIN\n");
    printf("9. Nominee Name\n");
    printf("10. Nominee NID\n");
    printf("11. Address\n");
    printf("Enter your choice (1-11): ");

    int choice;
    scanf("%d", &choice);
    getchar(); // Clear newline character from buffer

    if (choice < 1 || choice > 11) {
        printf("Error: Invalid choice.\n");
        return;
    }

    // Ask for the new value
    char new_value[MAX_LINE_LENGTH];
    printf("Enter the new value: ");
    fgets(new_value, sizeof(new_value), stdin);
    new_value[strcspn(new_value, "\n")] = '\0'; // Remove trailing newline

    // Update the selected line
    const char *field_names[] = {
        "Full Name", "Date of Birth", "Mobile Number", "Email", "NID",
        "User Name", "Password","Account Pin", "Nominee Name", "Noninee NID", "Address"
    };

    int field_index = choice - 1;
    char updated_line[MAX_LINE_LENGTH];
    snprintf(updated_line, sizeof(updated_line), "%-15s: %s\n", field_names[field_index], new_value);

    // Replace the line in memory
    int line_found = 0;
    for (int i = 0; i < total_lines; i++) {
        if (strstr(lines[i], field_names[field_index]) != NULL) {
            strcpy(lines[i], updated_line);
            line_found = 1;
            break;
        }
    }

    if (!line_found) {
        printf("Error: Field '%s' not found in the file.\n", field_names[field_index]);
        return;
    }

    // Write the updated lines back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to write to the file '%s'.\n", filename);
        return;
    }

    for (int i = 0; i < total_lines; i++) {
        fputs(lines[i], file);
    }
    fclose(file);

    printf("Update successful: '%s'.\n", field_names[field_index]);
}