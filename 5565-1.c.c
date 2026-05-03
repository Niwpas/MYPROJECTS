#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // evala kai tin ora tis stigmis gia na arxikopoihthoun oi tyxaioi arithmoi
struct Fraction {
        int arithmitis;
        int paronomastis;
    };
   
int MKD(int a, int b);        // evala tin arxikopoiisi twn metavlitwn edo gia na tis vlepei to programma prin tin main
int EKP(int a, int b);
struct Fraction pollaplasiasmos(struct  Fraction a, struct Fraction b);
struct Fraction prosthese (struct Fraction a, struct Fraction b);

int main(void) {
   struct Fraction A[3][3];
   struct Fraction B[3][3];
   struct Fraction SUM[3][3];    
   struct Fraction AB[3][3];
   struct Fraction BA[3][3];
   srand(time(NULL));  //evala ena Fraciton SUM gia na apothikeuoume to athroisma kapou
  
  // gemizei tous pinakes me tyxaious arithmous
  
   for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        A[i][j].arithmitis =  2 + 2 * (rand() % 5);
        A[i][j].paronomastis = 11 + 2 * (rand() % 5);    // allaja tis times gia na bgainoun sosta oi artioi kai oi perittoi
        B[i][j].arithmitis = 2 + 2 * (rand() % 5);
        B[i][j].paronomastis = 11 + 2 * (rand() % 5);
    }
   }

   // evgala apo edo mia sinartisi poy evriske ton MKDa kai MKDb giati to ypologizoume etsi kai allios pio kato kateueian
    // kanei tin prosthesi

   for (int i = 0; i < 3; i++) {
    for (int j= 0; j < 3; j++) {
        int koinos_diairetis = EKP(A[i][j].paronomastis, B[i][j].paronomastis);          
        int new_num = A[i][j].arithmitis * (koinos_diairetis / A[i][j].paronomastis) +        // evala edo mia akomi grammi gia na briskei ton arithmiti
        B[i][j].arithmitis * (koinos_diairetis / B[i][j].paronomastis);
        int mkd = MKD(new_num, koinos_diairetis);                        // evala tin synartisi MKD se mia metavliti mkd gia na mporoume na kanoume prajeis sthn kato seira
        SUM[i][j].arithmitis = new_num / mkd;                     // me to SUM pou evala sto Fraction pio pano ypologizetai to klasma meta tin prosthesi
        SUM[i][j].paronomastis = koinos_diairetis / mkd;
    }
}

       // emfanizei ton pinaka me tis prostheseis 

printf("A + B: \n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d/%d\t", SUM[i][j].arithmitis, SUM[i][j].paronomastis);
            }
            printf("\n");                   // gia na phgainei mia grammmi kato meta apo kathe seira
        }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    struct Fraction sum = {0, 1};
                    for (int k = 0; k < 3; k++) {
                        struct Fraction temp = pollaplasiasmos(A[i][k], B[k][j]);
                        sum = prosthese(sum, temp);
                    }
                    AB[i][j] = sum;
                }
            }
    printf("\nA * B: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d/%d\t", AB[i][j].arithmitis, AB[i][j].paronomastis);
        }
        printf("\n");
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            struct Fraction sum = {0, 1};
            for (int k = 0; k < 3; k++) {
                struct Fraction temp = pollaplasiasmos(B[i][k], A[k][j]);
                sum =  prosthese(sum, temp);
            }
           BA[i][j] = sum;
        }
    }
    printf("\nB * A: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d/%d\t", BA[i][j].arithmitis, BA[i][j].paronomastis);
        }
        printf("\n");
    }
}



    // ypologizei ton MKD

int MKD(int a, int b) {
    if (b == 0) { 
        return a;
    } else {                         // evala ena else mesa se aggiles gia na leitourgei sosta i sinartisi
        return MKD(b, a % b);         // kai allaja to gcb se MKD gia na douleuei sto programa mas 
    }
}
     // ypologizei to EKP

int EKP (int a, int b) {
    return (a * b) / MKD(a, b);
}

// ypologizei ton pollaplasiasmo apo kathe grammi se kathe stoixeio kathe stilis

struct Fraction pollaplasiasmos(struct Fraction a, struct Fraction b) {
struct Fraction result;
result.arithmitis = a.arithmitis * b.arithmitis;
result.paronomastis = a.paronomastis * b.paronomastis;
int mkd = MKD(result.arithmitis, result.paronomastis);
result.arithmitis = result.arithmitis / mkd;
result.paronomastis = result.paronomastis / mkd;
return result;
}
 
// prosthetei ta klasmata gia na emfanistoun

struct Fraction prosthese (struct Fraction a, struct Fraction b) {
struct Fraction result;
int ekp_2 = EKP(a.paronomastis, b.paronomastis);
result.arithmitis = a.arithmitis * (ekp_2 / a.paronomastis) + b.arithmitis * (ekp_2 / b.paronomastis);
result.paronomastis = ekp_2;
int mkd_2 = MKD(result.arithmitis, result.paronomastis);
result.arithmitis = result.arithmitis / mkd_2;
result.paronomastis = result.paronomastis / mkd_2;
return result;
}