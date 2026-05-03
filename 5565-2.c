#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// define ypallhlou

#define YPALLHLOS_PIN 5565

// pinakas gia ta accounts 

struct account {
unsigned short int arithmos_account;
unsigned short int PIN;
char eponymo[28];
char onoma[28];
float poso;
};

//pinakas gia tis synallages 

struct synallagi {
float poso;
char perigrafi[10];
unsigned short int arithmos_account;
unsigned short int day;
unsigned short int month;
unsigned short int year;
};

// synartisi xronou

void set_date(struct synallagi *s) {
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
     
    s->day = now->tm_mday;
    s->month = now->tm_mon + 1;
    s->year = now->tm_year % 100;
}

// ta xartonomismata

int atm20 = 400;
int atm10 = 800;
int atm5 = 800;


// arxikopoihsh synartisis katathesis

int katathesi (FILE *account_dedomena, struct account *user_account, FILE *synallagi_dedomena, long account_thesi);

// arxikopoihsh synartisis analipsis

int analipsi (FILE *account_dedomena, struct account *user_account, FILE *synallagi_dedomena, long account_thesi);

// arxikopoihsh synartisis login

int login(FILE *account_dedomena, struct account *user_account, long *account_thesi);

// arxi synartisis main

int main(void) {

// anoigma arxeiou account

FILE *account_dedomena = fopen("accounts", "rb+");
if (account_dedomena == NULL) {
    account_dedomena = fopen("accounts", "wb+");
    if (account_dedomena == NULL) {
        printf("Error: Cannot create file\n");
        exit(1);
    }
}

// anoigma arxeiou synallagwn

FILE *synallagi_dedomena = fopen("transactions", "ab+");
if (synallagi_dedomena == NULL) {
    printf("Error: Cannot open synallagi file\n");
    exit(1);
}

// menu epilogwn xristi h ypallhlou

int epilogi_ypallhlou_h_xristi;
printf("Epilexte 1 | 2\n");
printf("\n1.Eimai pelatis\n");
printf("2.Eimai ypallhlos\n");
scanf("%d", &epilogi_ypallhlou_h_xristi);

if (epilogi_ypallhlou_h_xristi == 1) {
struct account eggegrammenos_xristis;
long account_thesi = -1;
int epilogi;
do {
printf("\n====== Epiloges ATM ======\n\n");
printf("1.Enhmerwsi\n");
printf("2.Metafora\n");
printf("3.Analipsi\n");
printf("4.Katathesi\n");
printf("5.Plhrwmes\n");
printf("6.Allagh PIN\n");
printf("0.Exodos\n");
printf("\nParakalo Epilexte oti thelete\n\n"); 
scanf("%d", &epilogi);
switch(epilogi) {
  
  // 1h epilogi enhmerwshs

    case 1: {
       
        if(!login(account_dedomena, &eggegrammenos_xristis, &account_thesi)) {
            break;
        }
        printf("Ti akrivos enhmerwsh thelete na kanete?\n");
        printf("========================================\n");
        printf("1.Ypoloipo LOgariasmou\t");
        printf("2.Teleytaies Kiniseis\t");
        printf("3.Leptomeroies logariasmou\n");
        
        int enhmerwsh_epilogi;

        printf("Parakalo epilexte (1-3)\n");
        scanf("%d", &enhmerwsh_epilogi);
       
    


       
            if (enhmerwsh_epilogi == 1) {
                printf("To ypoloipo tou logariasmou sas einai: %.2f\n", eggegrammenos_xristis.poso);
            } else if (enhmerwsh_epilogi == 2) {
                struct synallagi s;
                struct synallagi teleytaies4[4];
              
                int count = 0;

                rewind(synallagi_dedomena);
                while(fread(&s, sizeof(struct synallagi), 1, synallagi_dedomena) == 1) {
                    if (s.arithmos_account == eggegrammenos_xristis.arithmos_account) {
                        teleytaies4[count % 4] = s;
                        count ++;
                    }
                }
            
                int start = count >= 4 ? (count % 4) : 0;
                int total = count >= 4 ? 4 : count;

                for (int i = 0; i < total; i++) {
                    struct synallagi temp = teleytaies4[(start + i) % 4];
                    printf("%hu%hu%hu %s %.1f\n", temp.day, temp.month, temp.year, temp.perigrafi, temp.poso);
                }
            } else if(enhmerwsh_epilogi == 3) {
                printf("Epwnymo: %s\n", eggegrammenos_xristis.eponymo);
                printf("Onoma: %s\n", eggegrammenos_xristis.onoma);
                printf("Ypoloipo Logariasmou: %.2f\n", eggegrammenos_xristis.poso);
            } else {
                printf("Lanthasmenh Epilogi!\n");
            }
        

        break;
    }

// 2h epilogi metafora

    case 2: {
        
        if(!login(account_dedomena, &eggegrammenos_xristis, &account_thesi)) {
            break;
        }
        printf("Eisagete ton arithmo logariasmou pou thelete na kanete metafora: \n");
        unsigned short int account_metaforas;
        scanf("%hu", &account_metaforas);
        rewind(account_dedomena);
        int found = 0;
        long liptis_pos;
        struct account liptis_account;

        while(fread(&liptis_account, sizeof(struct account), 1, account_dedomena) == 1) {
            if(liptis_account.arithmos_account == account_metaforas) {
                found = 1;
                liptis_pos = ftell(account_dedomena) - sizeof(struct account);
                break;
            }
        }
        if (!found) {
            printf("O logariasmos pou epileksate den einai egkyros!\n");
            break;
        }
        float poso_metaforas;
        printf("Ti poso tha thelate na metaferete?\n");
        scanf("%f", &poso_metaforas);
        if (poso_metaforas <= 0) {
            printf("To poso einai mhdeniko h arnhtiko!\n");
            break;
        } else if(poso_metaforas > eggegrammenos_xristis.poso) {
            printf("Aneparkes ypoloipo tou logariasmou sas!\n");
            break;
        } 
        eggegrammenos_xristis.poso -= poso_metaforas;
        liptis_account.poso += poso_metaforas;
        fseek(account_dedomena, liptis_pos, SEEK_SET);
        fwrite(&liptis_account, sizeof(struct account), 1, account_dedomena);
        fflush(account_dedomena);
        fseek(account_dedomena, account_thesi, SEEK_SET);
        fwrite(&eggegrammenos_xristis, sizeof(struct account), 1, account_dedomena);
        fflush(account_dedomena);

        struct synallagi kinisi;
        kinisi.poso = -poso_metaforas;
        strcpy(kinisi.perigrafi, "TRN");
        kinisi.arithmos_account = eggegrammenos_xristis.arithmos_account;
        set_date(&kinisi);
        fwrite(&kinisi, sizeof(struct synallagi), 1, synallagi_dedomena);
        fflush(synallagi_dedomena);

        kinisi.poso = poso_metaforas;
        kinisi.arithmos_account = liptis_account.arithmos_account;
        strcpy(kinisi.perigrafi, "TRN");
        set_date(&kinisi);
        fwrite(&kinisi, sizeof(struct synallagi), 1, synallagi_dedomena);
        fflush(synallagi_dedomena);
        printf("Epitixys Metafora!\n");
        break;
    }

// 3h epilogi analipsis

    case 3: {
        
        if(!login(account_dedomena, &eggegrammenos_xristis, &account_thesi)) {
            break;
        }
        analipsi(account_dedomena, &eggegrammenos_xristis, synallagi_dedomena, account_thesi);
        break;
    }

// 4h epilogi katathesis

    case 4: {
       if(account_thesi == -1) {
        printf("Prepei na kanete Login prwta!\n");
        break;
       }
        katathesi(account_dedomena, &eggegrammenos_xristis, synallagi_dedomena, account_thesi);
        break;
    }

// 5h epilogi plhrwmes

    case 5: {
        if(account_thesi == -1) {
            printf("Prepei na kanete Login prwta!\n");
            break;
        }
       
        printf("Parakalo epilexte thn plhrwmh: \n");
        printf("==============================\n");
        printf("1.Enoikio\t");
        printf("2.Dapanes logariasmwn (px. DEH, Ydreush, Thlefonia)\n");
        printf("Parakalo epilexte (1-2)\n");
        unsigned short int plhrwmes_epilogi;
        scanf("%hu", &plhrwmes_epilogi);
        float poso_plhrwmis;
        printf("Eisagete to poso pou thelete na plhrwsete: \n");
        scanf("%f", &poso_plhrwmis);
        if (poso_plhrwmis <= 0) {
            printf("To poso einai mhdeniko h arnhtiko!\n");
            break;
        } else if (poso_plhrwmis > eggegrammenos_xristis.poso) {
            printf("Aneparkes ypoloipo tou logariasmou sas!\n");
            break;
        }
        unsigned short int elegxos_PIN;
        printf("Eisagete to PIN sas gia epivevaiwsh ths plhrwmhs: \n");
        scanf("%hu", &elegxos_PIN);
        if (elegxos_PIN != eggegrammenos_xristis.PIN) {
            printf("Lanthasmeno PIN! Den mporeite na proxwrhsete me thn plhrwmh\n");
            break;
        }
        struct synallagi kinisi;
        if(plhrwmes_epilogi == 1) {
            strcpy(kinisi.perigrafi, "RNT");
        } else {
            strcpy(kinisi.perigrafi, "EXP");
        }
        eggegrammenos_xristis.poso -= poso_plhrwmis;
        fseek(account_dedomena, account_thesi, SEEK_SET);
        fwrite(&eggegrammenos_xristis, sizeof(struct account), 1, account_dedomena);
        fflush(account_dedomena);
        kinisi.poso = -poso_plhrwmis;
        kinisi.arithmos_account = eggegrammenos_xristis.arithmos_account;
        set_date(&kinisi);
        fwrite(&kinisi, sizeof(struct synallagi), 1, synallagi_dedomena);
        fflush(synallagi_dedomena);
        printf("Epitixys Plhrwmi! Neo ypoloipo: %.2f\n", eggegrammenos_xristis.poso);

       
        break;
    }

// 6h epilogi allagh PIN

    case 6: {
       
        if(!login(account_dedomena, &eggegrammenos_xristis, &account_thesi)) {
            break;
        }
        unsigned short int old_PIN;
        printf("Eisagete to palio PIN sas: \n");
        scanf("%hu", &old_PIN);
        if (old_PIN != eggegrammenos_xristis.PIN) {
            printf("Lanthasmeno PIN! Den mporeite na allaxete to PIN sas\n");
            break;
        } 
        unsigned short int neo_PIN, epivevaiwsi_PIN;
        printf("Eisagete to neo sas PIN: (4 psifia)\n");
        scanf("%hu", &neo_PIN);

        if (neo_PIN < 1000 || neo_PIN > 9999) {
            printf("To PIN prepei na exei akrivws 4 psifia!\n");
            break;
        }

        printf("Eisagete to neo sas PIN xana gia epivevaiwsh: \n");
        scanf("%hu", &epivevaiwsi_PIN);
        if(neo_PIN != epivevaiwsi_PIN) {
            printf("To PIN den tairiazei me thn epivevaiwsh!\n");
            break;
        } 
        eggegrammenos_xristis.PIN = neo_PIN;
        fseek(account_dedomena, account_thesi, SEEK_SET);
        fwrite(&eggegrammenos_xristis, sizeof(struct account), 1, account_dedomena);
        fflush(account_dedomena);
        printf("To PIN sas allakse epitixws!\n");
        break;
    }

// default epilogi 

    default: {
        if(epilogi != 0) {
        printf("Lathos Epilogi!\n");
        break;
        }
    }
    
}

} while(epilogi != 0);

} else if (epilogi_ypallhlou_h_xristi == 2) {

}

// MENU YPALLHLOU

unsigned short int pin_ypallhlou;
printf("Eisagete to PIN ypallhlou: \n");
scanf("%hu", &pin_ypallhlou);

if (pin_ypallhlou != YPALLHLOS_PIN) {
    printf("Lanthasmeno PIN ypallhlou! Episrtofh sthn arxiki othoni\n");
    exit(0);
} else {
    int epilogh_ypallhlou;
     do {printf("======== Epiloges Ypallhlou ========\n\n");
        printf("101.Emfanisi xrimatwn ATM\n");
        printf("102.Trophodosia xartonomismatwn ATM\n");
        printf("103.Exodos apo leitourgia ypallhlou\n");
        printf("Parakalo epilexte: \n");
        scanf("%d", &epilogh_ypallhlou);

        switch (epilogh_ypallhlou) {

//  check ATM

            case 101: {
                printf("Xartonomismata ATM\n");
                printf("20 x %d euro", atm20);
                printf("10 x %d euro", atm10);
                printf("5 x %d euro", atm5);
                break;
            }

// Trophodosia ATM

            case 102: {
                int trexon_poso = 
                atm20 * 20 +
                atm10 * 10 +
                atm5 * 5;
                
                int poso_trophodosias = 
                100 * 20 +
                250 * 10 +
                500 * 5;

                if (trexon_poso + poso_trophodosias <= 8000) {
                    
                    atm20 += 100;
                    atm10 += 250;
                    atm5 += 500;

                    printf("To ATM efodiasthke epitixws!\n");
                    break;
                } else {
                    printf("Den yparxei arketh xwritikothta sto ATM\n");
                }
                break;
            }
        }



    } while (epilogh_ypallhlou != 103);
}



// kleisimo twn arxeiwn 

fclose(account_dedomena);
fclose(synallagi_dedomena);
}

// synartisi Login

int login(FILE *account_dedomena, struct account *user_account, long *account_thesi) {
    for (int i = 0; i < 3; i++) {
    unsigned short int xristis_account, xristis_PIN;
    printf("Eisagete ton arithmo logariasmou sas: \n");  
    scanf("%hu", &xristis_account);
    printf("Eisagete to PIN sas: \n");
    scanf("%hu", &xristis_PIN);

    struct account a;

    rewind(account_dedomena);

    int found = 0;
        while(fread(&a, sizeof(struct account), 1, account_dedomena) == 1) {
            if(a.arithmos_account == xristis_account && a.PIN == xristis_PIN ) {
                 found = 1;
                 *user_account = a;
                 *account_thesi = ftell(account_dedomena) - sizeof(struct account);
                 break;
           }
        }
        if (found) {
            printf("Epityxes Login!\n");
            *account_thesi = ftell(account_dedomena) - sizeof(struct account);
            return 1;
        } else {

            // check gia epityxes / anepityxes Login

if (3 - (i + 1) != 0) {
        printf("Anepityxes Login! | Sas apomenoun %d prospathies\n", 3 - (i + 1)); 
} else {
    printf("Anepityxes Login! | Eksantlisate tis prospathies sas\n");
}
    }  
}   
return 0;
}

// synartisi tis analipsis 

int analipsi (FILE *account_dedomena, struct account *user_account, FILE *synallagi_dedomena, long account_thesi) {
    float poso_analipsis;
    printf("Posa xrimata thelete na analipsete; \n");
    
    // elegxos gia eisodo posou

    if (scanf("%f", &poso_analipsis) != 1) {
        printf("Lathos Eisodos!\n");
        return 0;
    } 

    int poso = (int) poso_analipsis;
    if(poso != poso_analipsis) {
printf("Den epitrepontai dekadika sthn analipsi!\n");
return 0;  
  }

  if(poso % 5 != 0) {
printf("To poso prepei na einai pollaplasio tou 5!\n");
return 0;
  } 

    if (poso > user_account->poso) {
        printf("Aneparkes ypoloipo ston logariasmo sas!\n");
        return 0;
    }

    // elegxos gia poly megalo / poly mikro poso

    if(poso <= 0) {
        printf("To poso prepei na einai thetiko!\n");
        return 0;
    }
    if (poso > 1000000) {
        printf("To poso einai poly megalo!\n");
        return 0;
    }


int d20 = 0, d10 = 0, d5 = 0;
int ypoloipo = poso;
d20 = ypoloipo / 20;
if (d20 > atm20) {
    d20 = atm20;
}
ypoloipo -= d20 * 20;
d10 = ypoloipo / 10;
if (d10 > atm10) {
    d10 = atm10;
}
ypoloipo -= d10 * 10;
d5 = ypoloipo / 5;
if (d5 > atm5) {
    d5 = atm5;
}
ypoloipo -= d5 * 5;

if (ypoloipo != 0) {
    printf("To ATM den mporei na dwsei to poso me ta diathesima xartonomismata.\n");
    return 0;
}

atm20 -= d20;
atm10 -= d10;
atm5 -= d5;

// mhnyma enhmerwshs pelath

printf("To ATM sas edwse: \n");
printf("%d x 20\n", d20);
printf("%d x 10\n", d10);
printf("%d x 5\n", d5);

struct synallagi s;
int synolo_hmeras = 0;

struct synallagi temp_date;
set_date(&temp_date);

rewind(synallagi_dedomena);
while(fread(&s, sizeof(struct synallagi), 1, synallagi_dedomena) == 1) {
    if(s.arithmos_account == user_account->arithmos_account && strcmp(s.perigrafi, "WDR") == 0 
    && s.day == temp_date.day 
    && s.month == temp_date.month 
    && s.year == temp_date.year) {
        synolo_hmeras += -s.poso;
    }
}
if (synolo_hmeras + poso > 600) {
    printf("Ypervash hmerisiou orio twn 600 euro!\n");
    printf("Exete hdh kanei analipsis twn %d euro gia shmera!\n", synolo_hmeras);
    return 0;
}

user_account->poso -= poso;
printf("Epityxis analipsi! Neo ypoloipo: %.2f\n", user_account->poso);

struct synallagi kinisi;
kinisi.poso = -poso;
strcpy(kinisi.perigrafi, "WDR");
kinisi.arithmos_account = user_account->arithmos_account;

set_date(&kinisi);
fwrite(&kinisi, sizeof(struct synallagi), 1, synallagi_dedomena);
fflush(synallagi_dedomena);

    fseek(account_dedomena, account_thesi, SEEK_SET);
    fwrite(user_account, sizeof(struct account), 1, account_dedomena);
    fflush(account_dedomena);
    return 1;
}

// synartisi katathesis 

int katathesi (FILE *account_dedomena, struct account *user_account, FILE *synallagi_dedomena, long account_thesi) {
int d20, d10, d5;

printf("Xasrtonomismata twn 20 euro: \n");
scanf("%d", &d20);
printf("Xartonomismata twn 10 euro: \n");\
scanf("%d", &d10);
printf("Xartonomismata twn 5 euro: \n");
scanf("%d", &d5);

if (d20 < 0 || d10 < 0 || d5 < 0) {
    printf("Den epitrepontai arnhtika xartonomismata!\n");
    return 0;
}

int poso_katathesis = d20 * 20 + d10 * 10 + d5 * 5;

if (poso_katathesis == 0) {
    printf("To poso einai mhdeniko!\n");
    return 0;
}

if (poso_katathesis > 1000000) {
    printf("To poso einai poly megalo!\n");
    return 0;
}

atm20 += d20;
atm10 += d10;
atm5 += d5;

user_account->poso += poso_katathesis;

printf("Epitixys katathesi! Neo ypoloipo: %.2f\n", user_account->poso);

struct synallagi kinisi;
kinisi.poso = poso_katathesis;
strcpy(kinisi.perigrafi, "DEP");
kinisi.arithmos_account = user_account->arithmos_account;
set_date(&kinisi);
fwrite(&kinisi, sizeof(struct synallagi), 1, synallagi_dedomena);
fflush(synallagi_dedomena);
fseek(account_dedomena, account_thesi, SEEK_SET);
fwrite(user_account, sizeof(struct account), 1, account_dedomena);
fflush(account_dedomena);
return 1;
}


