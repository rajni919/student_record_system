#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[50];
    char course[50];
};

int checkDuplicate(int id) {
    struct student s;
    FILE *fp = fopen("record.txt", "r");

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d %s %s", &s.id, s.name, s.course) != EOF) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent() {
    struct student s;
    FILE *fp = fopen("record.txt", "a");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &s.id);

    if (checkDuplicate(s.id)) {
        printf("Duplicate ID! Student already exists.\n\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Course: ");
    scanf("%s", s.course);

    fprintf(fp, "%d %s %s\n", s.id, s.name, s.course);
    fclose(fp);

    printf("Student Added Successfully!\n\n");
}

void viewStudents() {
    struct student s;
    FILE *fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("No records found.\n\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fscanf(fp, "%d %s %s", &s.id, s.name, s.course) != EOF) {
        printf("ID: %d | Name: %s | Course: %s\n", s.id, s.name, s.course);
    }

    fclose(fp);
    printf("\n");
}

void searchStudent() {
    struct student s;
    int searchId, found = 0;
    FILE *fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("No records found.\n\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    while (fscanf(fp, "%d %s %s", &s.id, s.name, s.course) != EOF) {
        if (s.id == searchId) {
            printf("Student Found!\n");
            printf("ID: %d | Name: %s | Course: %s\n", s.id, s.name, s.course);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
    printf("\n");
}

void updateStudent() {
    struct student s;
    int updateId, found = 0;

    FILE *fp = fopen("record.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("No records found.\n\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &updateId);

    while (fscanf(fp, "%d %s %s", &s.id, s.name, s.course) != EOF) {
        if (s.id == updateId) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Course: ");
            scanf("%s", s.course);
        }
        fprintf(temp, "%d %s %s\n", s.id, s.name, s.course);
    }

    fclose(fp);
    fclose(temp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    if (found)
        printf("Student Updated Successfully!\n\n");
    else
        printf("Student Not Found!\n\n");
}

void deleteStudent() {
    struct student s;
    int deleteId, found = 0;

    FILE *fp = fopen("record.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("No records found.\n\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &deleteId);

    while (fscanf(fp, "%d %s %s", &s.id, s.name, s.course) != EOF) {
        if (s.id == deleteId) {
            found = 1;
        } else {
            fprintf(temp, "%d %s %s\n", s.id, s.name, s.course);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    if (found)
        printf("Student Deleted Successfully!\n\n");
    else
        printf("Student Not Found!\n\n");
}

int main() {
    int choice;

    while (1) {
        printf("===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice!\n\n");
        }
    }

    return 0;
}




