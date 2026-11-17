/* PROGRAM CreateStudentArchive
   create student archives, data are read from the keyboard */

#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} Student;

// Procedure to display all student data
void DisplayAllStudent() {
    Student aStudent;
    FILE *studentFile;

    studentFile = fopen("StudentFile.dat", "rb");

    if (studentFile == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\n=== ALL STUDENT DATA ===\n");

    while (fread(&aStudent, sizeof(aStudent), 1, studentFile) == 1) {
        printf("\nStudent ID : %d", aStudent.id);
        printf("\nName       : %s", aStudent.name);
        printf("\nGrade      : %.2f\n", aStudent.grade);
    }

    fclose(studentFile);
}

// Procedure to calculate average grade
void CalculateAverageGrade() {
    Student aStudent;
    FILE *studentFile;
    float totalGrade = 0;
    int totalStudent = 0;

    studentFile = fopen("StudentFile.dat", "rb");

    if (studentFile == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    while (fread(&aStudent, sizeof(aStudent), 1, studentFile) == 1) {
        totalGrade = totalGrade + aStudent.grade;
        totalStudent = totalStudent + 1;
    }

    if (totalStudent > 0) {
        printf("\nAverage Grade = %.2f\n", totalGrade / totalStudent);
    } else {
        printf("\nNo student data available!\n");
    }

    fclose(studentFile);
}

int main() {
    // DECLARATION
    Student aStudent;
    FILE *studentFile;

    // ALGORITHM
    studentFile = fopen("StudentFile.dat", "wb");

    if (studentFile == NULL) {
        printf("File cannot be opened!\n");
        return 1;
    }

    printf("input Student ID = ");
    scanf("%d", &aStudent.id);

    while (aStudent.id != 9999) {
        printf("Name : ");
        scanf("%24s", aStudent.name);

        printf("Grade : ");
        scanf("%f", &aStudent.grade);

        fwrite(&aStudent, sizeof(aStudent), 1, studentFile);

        printf("input Student ID = ");
        scanf("%d", &aStudent.id);
    }

    fclose(studentFile);

    // Call procedures
    DisplayAllStudent();
    CalculateAverageGrade();

    return 0;
}
