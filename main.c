#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "vec.h"

#define CHAR_DEFAULT_LENGTH 50

struct record {
    char id[CHAR_DEFAULT_LENGTH];
    char firstName[CHAR_DEFAULT_LENGTH];
    char lastName[CHAR_DEFAULT_LENGTH];
    char email[CHAR_DEFAULT_LENGTH];
    char gender[CHAR_DEFAULT_LENGTH];
    char ipAddress[CHAR_DEFAULT_LENGTH];
};

typedef vec_t(struct record*) vec_record_t;

void readFile(char *filePath, vec_record_t *v,struct record *rec);
void buildRecord(char *line, vec_record_t *v, struct record *rec);
void printRecords(vec_record_t v);

int main() {
    char filePath[] = "C:/Users/Jason/Downloads/MOCK_DATA.csv";
    struct record *rec;

    vec_record_t v;
    vec_init(&v);

    readFile(filePath, &v, rec);

    printRecords(v);

    vec_deinit(&v);

    return 0;
}

void readFile(char *filePath, vec_record_t *v, struct record *rec) {
    FILE *fp;
    char tempRecord[1024];

    fp = fopen(filePath, "r");

    //getting rid of the headers
    fgets(tempRecord, LONG_MAX, fp);

    while (fgets(tempRecord, LONG_MAX, fp) != NULL) {
        buildRecord(tempRecord, v, rec);
    }

    fclose(fp);
}

void buildRecord(char *line, vec_record_t *v, struct record *rec) {
    char *token;

    rec = (struct record*) malloc(sizeof(struct record));

    /* get the first token */
    token = strtok(line, ",");

    if (token != NULL) {
        strcpy(rec->id, token);
        token = strtok(NULL, ",");

        strcpy(rec->firstName, token);
        token = strtok(NULL, ",");

        strcpy(rec->lastName, token);
        token = strtok(NULL, ",");

        strcpy(rec->email, token);
        token = strtok(NULL, ",");

        strcpy(rec->gender, token);
        token = strtok(NULL, ",");

        strcpy(rec->ipAddress, token);
    }

    vec_push(v, rec);
}

void printRecords(vec_record_t v) {
    int i; struct record **rec;
    vec_foreach_ptr(&v, rec, i) {
        printf("first name: %s\n", (*rec)->firstName);
        printf("last name: %s\n", (*rec)->lastName);
        printf("gender: %s\n", (*rec)->gender);
        printf("email: %s\n", (*rec)->email);
        printf("ip address: %s\n", (*rec)->ipAddress);
    }
}