#include <stdio.h>

typedef struct {
    char name[100];
    int n;
    float sr;
} Student;

void prStudent(const Student *arr, int l) {
    for (int i = 0; i < l; i++) {
        if ((arr + i)->n == 3 && (arr + i)->sr > 4.5f) {
            printf("Student %s: n = %d, sr = %.2f \n", (arr+i)->name, (arr+i)->n, (arr+i)->sr);
        }
    }
}

int main() {
    Student students[8] = {
        {"Ivan Ivanov", 2, 4.5f},
        {"Peter Petrov", 1, 3.0f},
        {"Kuzma Kuznetsov", 3, 4.7f},
        {"Andrey Andreev", 3, 3.0f},
        {"Alexander Alexandrov", 3, 4.0f},
        {"Daniil Danilov", 3, 3.0f},
        {"Egor Egorov", 3, 5.0f},
        {"Lev Lvov", 3, 4.6f}
    };
    prStudent(students, 8);
    return 0;
}