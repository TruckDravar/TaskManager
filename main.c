#include <stdio.h>
#include <string.h>

#define MAX_TASKS 9
#define MAX_TASK_CHAR 100

// function declarations

int del_specific_task(int TaskNum);
int delallTasks();
int readFile();
int writeFile(char* task_input);
int doubleLineAdder(int lineLength);
int singleLineAdder(int lineLength);

// main function
int main() {
        int choice;
        // loops main menu
        do {

                char tasks[MAX_TASKS][MAX_TASK_CHAR];
                int num_strings = 0; // Initialize num_strings

                printf("\n");
                doubleLineAdder(23);
                printf("\nTO-DO LIST\n``````````\nMain Menu\n``````````\n");
                printf("Add task (1)\n");
                printf("Show Tasks (2)\n");
                printf("Delete task (3)\n");
                printf("Delete all tasks (4)\n");
                printf("Exit (5)\n");
                printf("Action --> ");
                scanf("%d", &choice);
                printf("\n");

                // Clear the newline character from the input
                getchar();

                switch (choice) {
                case 1:
                        for (int INDEX = 0; INDEX < MAX_TASKS; INDEX++) {
                                printf("Enter your task %d --> ", INDEX + 1);
                                fgets(tasks[INDEX], MAX_TASK_CHAR, stdin);

                                if (tasks[INDEX][0] == '\n' ||
                                    tasks[INDEX][0] == ' ' ||
                                    strlen(tasks[INDEX]) <= 1) {
                                        printf("\nTasks saved.\n");
                                        break;
                                }

                                writeFile(tasks[INDEX]);

                                num_strings++; // Increment num_strings for each
                                               // valid input
                        }

                        doubleLineAdder(23);

                        break;

                case 2:
                        printf("Your existing tasks are:\n");
                        int fileDataPresent = readFile();
                        if (fileDataPresent ==
                            1) { // adds a new line if no data present in file
                                printf("\n");
                        }

                        doubleLineAdder(23);
                        break;

                case 3:
                        int delTaskNo;
                        readFile();
                        printf("\nCancel (0)\nTask Number: ");

                        scanf("%d", &delTaskNo);
                        switch (delTaskNo) {
                        case 0:
                                printf("No task deleted.");
                                break;

                        default:
                                del_specific_task(delTaskNo);
                                break;
                        }

                        printf("\n");
                        doubleLineAdder(23);
                        break;
                case 4:
                        delallTasks();
                        printf("All tasks deleted.");
                        printf("\n");
                        doubleLineAdder(23);
                        break;

                case 5:

                        doubleLineAdder(23);
                        break;

                default:
                        printf("Invalid choice!");
                        doubleLineAdder(23);
                        break;
                }
        }
        // exists program
        while (choice != 5);

        return 0;
}

// function definations

// function for deleting specific task
int del_specific_task(int TaskNum) {
        char tempFilename[] = ".//tempfile.txt"; // temporary file
        FILE* tempFile = fopen(tempFilename, "w");
        FILE* storage_file = fopen("storage.txt", "r");

        int i = 0; // task index
        char tasks_entered[255][100];
        int currentTask = 1;

        // transfers data from storage file to temp file
        while (fgets(tasks_entered[i], sizeof(tasks_entered[i]),
                     storage_file) != NULL) {
                if (currentTask != TaskNum) {
                        fputs(tasks_entered[i], tempFile);
                }
                currentTask++;
        }

        fclose(tempFile);
        fclose(storage_file);

        // converts temp file to permanent file
        if (remove("storage.txt") != 0) {
                printf("\nERROR! {storage file no found}"); /*checks if original
                                                            permanent file
                                                            exists*/
        }

        else {
                rename(".//tempfile.txt", ".//storage.txt") == 0;
                printf("\nTask no. %d deleted.", TaskNum);
                return 0;
        }
}

// function for deleting all file data
int delallTasks() {
        FILE* storage_file =
            fopen("./storage.txt", "w"); // deletes all data in txt file.

        fclose(storage_file);

        return 0;
}

// function for reading and printing file data
int readFile() {
        char task_entered[255][100];
        int i = 1;           // gives tasks serial number
        int tasks_found = 0; // checkbox for tasks

        FILE* storage_file = fopen(".//storage.txt", "r");

        if (storage_file == NULL) {
                printf("Error opening file!\n"); /* checks if storage file
                                                    exists */
                return 1;
        }

        // reads tasks and prints it
        singleLineAdder(15);

        while (fgets(task_entered[i - 1], sizeof(task_entered), storage_file) !=
               NULL) {
                if (strcmp(task_entered[0], "") ==
                    0) { // checks if first task is empty
                        tasks_found = 0;

                } else {
                        printf("%d. %s", i, task_entered[i - 1]);
                        i++;
                        tasks_found = 1;
                }
        }

        singleLineAdder(15);

        if (!tasks_found) {
                printf("No tasks found!");
                return 1;
        }

        fclose(storage_file);

        return 0;
}

// function for writing file data
int writeFile(char* task_input) {
        FILE* storage_file = fopen("./storage.txt", "a");

        fprintf(storage_file, "%s", task_input); // writes tasks in txt file

        fclose(storage_file);

        return 0;
}

// makes a  double line of specific length
int doubleLineAdder(int lineLength) {
        char doubleLine = '=';
        char result[lineLength];
        for (int y = 0; y <= lineLength; y++) {
                result[y] = doubleLine;
        }

        result[lineLength] = '\0'; // makes last character end of string
        printf("%s", result);
        return 0;
}

// makes a single line of specific length
int singleLineAdder(int lineLength) {
        char singleLine = '-';
        char result[lineLength];
        for (int y = 0; y <= lineLength; y++) {
                result[y] = singleLine;
        }

        result[lineLength] = '\0'; // makes last character end of string
        printf("%s\n", result);
        return 0;
}
