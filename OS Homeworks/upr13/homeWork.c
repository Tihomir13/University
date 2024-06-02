#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_STUDENTS 25

struct Student {
    char name[50];
    int year;
    int facultyNumber;
};

struct Student students[MAX_STUDENTS];
int count = 0;

void addStudent() {
    if (count < MAX_STUDENTS) {
        struct Student newStudent;

        printf("Enter student name: ");
        scanf("%s", newStudent.name);

        printf("Enter year of admission: ");
        scanf("%d", &newStudent.year);

        printf("Enter faculty number: ");
        scanf("%d", &newStudent.facultyNumber);

        int fd = open("students.dat", O_WRONLY | O_CREAT | O_APPEND, 0640);
        if (fd == -1) {
            perror("open");
            return;
        }

        write(fd, &newStudent, sizeof(struct Student));
        close(fd);

        printf("Student successfully added.\n");
    } else {
        printf("The student registry is full. You cannot add more students.\n");
    }
}

void searchByName(char *name) {
    int found = 0;
    struct Student tempStudent;

    int fd = open("students.dat", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    while (read(fd, &tempStudent, sizeof(struct Student)) > 0) {
        if (strcmp(tempStudent.name, name) == 0) {
            printf("Name: %s, Year of admission: %d, Faculty number: %d\n", tempStudent.name, tempStudent.year,
tempStudent.facultyNumber);
            found = 1;
            break;
        }
    }

    close(fd);

    if (!found) {
        printf("Student with this name was not found.\n");
    }
}

void searchByFacultyNumber(int facultyNumber) {
    int found = 0;
    struct Student tempStudent;

    int fd = open("students.dat", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    while (read(fd, &tempStudent, sizeof(struct Student)) > 0) {
        if (tempStudent.facultyNumber == facultyNumber) {
            printf("Name: %s, Year of admission: %d, Faculty number: %d\n", tempStudent.name, tempStudent.year,
tempStudent.facultyNumber);
            found = 1;
            break;
        }
    }

    close(fd);

    if (!found) {
        printf("Student with this faculty number was not found.\n");
    }
}

int main() {
    int choice;
    char name[50];
    int facultyNumber;

    do {
         clearScreen();
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Search student by name\n");
        printf("3. Search student by faculty number\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                printf("Enter student name: ");
                scanf("%s", name);
                searchByName(name);
                break;
            case 3:
                printf("Enter faculty number: ");
                scanf("%d", &facultyNumber);
                searchByFacultyNumber(facultyNumber);
                break;
            case 4:
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}