 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

// o pinakas pou tha apothikeuei ta mitroa kai tous vathmous

struct Student {
    int arithmos_mitroou;
    float students_grade;
};
struct Student grade [200];

// synartisi gia tous mathites poy piran ton idio max_grade

void best_performers (struct Student grade[200], int megethos);

// main

int main(void) {
 
srand(time(NULL));

// gemisma pinaka me mitroa kai tyxaioys vathmous se float

    for (int i = 0; i < 200; i++) {
    grade[i].arithmos_mitroou = 5500 + i;
 
 grade[i].students_grade = ((float)rand() / RAND_MAX) * 10.0;
 grade[i].students_grade = ((int)(grade[i].students_grade * 10 + 0.5)) / 10.0;
    }

    float sum = 0.0;
    float average_grade = 0.0;

// evresh mesou orou 

    for (int j = 0; j < 200; j++) {
         sum += grade[j].students_grade;
    }
    average_grade = sum / 200.0;
    printf("O mesos oros twn vathmon einai: %.2f\n", average_grade);
    best_performers(grade, 200);
}

// ylopoiisi synartisis gia max_grade kai gia tous mathitse me max_grade

void best_performers (struct Student grade[200], int megethos) {
    float max_grade = -1.0;
    int best_grades = 0;

    for (int i = 0; i < megethos; i++) {
        if (grade[i].students_grade > max_grade) {
            max_grade = grade[i].students_grade;
        }
    } 
    for (int j = 0; j < megethos; j++) {
        if (max_grade == grade[j].students_grade) {
            best_grades++;
        }
    }

// ektyposi pinakwn

    printf("O megalyteros vathmos htan: %.2f\n", max_grade);
    printf("Oi foithtes pou elavan ton idio vathmo htan %d.\n", best_grades);
}
