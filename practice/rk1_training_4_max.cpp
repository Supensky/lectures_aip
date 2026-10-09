#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int n;
    float sr;
    char name[0];
} Student;


Student * newStudent(int n, char name[], float sr) {
    Student * student = (Student *) malloc(sizeof(Student) + strlen(name) + 1);
    student->n = n;
    strcpy(student->name, name);
    student->name[strlen(name)] = '\0';
    student->sr = sr;
    return student;

}
void prStudent(Student **arr, int l) {
    for (int i = 0; i < l; i++) {
        if (arr[i]->n  == 3 && arr[i]->sr >= 4.5f) {
            printf("Student %s: n = %d, sr = %.2f \n", arr[i]->name, arr[i]->n, arr[i]->sr);
        }
    }
}

int main() {
    Student *students[] = {
        newStudent(3, "A", 4.5f),
         newStudent(3, "B", 4.5f),
         newStudent(3, "C", 4.5f),
         newStudent(3, "D", 4.5f),
         newStudent(3, "E", 4.5f),
         newStudent(3, "F", 4.5f),
         newStudent(3, "G", 4.5f),
         newStudent(3, "H", 4.5f),
         newStudent(3, "I", 4.5f),
         newStudent(3, "J", 4.5f),
         newStudent(3, "K", 4.5f),
         newStudent(3, "L", 4.5f),
         newStudent(3, "M", 4.5f),
         newStudent(3, "N", 4.5f),
         newStudent(3, "O", 4.5f),
         newStudent(3, "P", 4.5f),
         newStudent(3, "Q", 4.5f),
         newStudent(3, "R", 4.5f),
         newStudent(3, "S", 4.5f),
         newStudent(3, "T", 4.5f),
         newStudent(3, "U", 4.5f),
         newStudent(3, "V", 4.5f),
         newStudent(3, "W", 4.5f),
         newStudent(3, "X", 4.5f),
         newStudent(3, "Y", 4.5f),
         newStudent(3, "Z", 1.5f),

     };
    prStudent(students, sizeof(students) / sizeof(Student *));
    return 0;
}