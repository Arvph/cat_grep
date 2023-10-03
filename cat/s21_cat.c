#include <stdio.h>
#include <string.h>
#include "options.h"


// флаги: определение и изменение вывода
// файл открытие и вывод на принт
int validation (int argc, char* argv[], char buffer[]);
int is_letter(char ch);
void file_operations (int argc, char* argv[], char keys[]);
int GNU_check (char* argv);
void compare(int GNU, char* buff);
void priority (char keys[]);
int check_files(int argc, char* argv[]);
int file_quantity(int argc, char* argv[]);



int main(int argc, char* argv[]){
    
    char buffer[20];

    if(validation(argc, argv, buffer)){
        file_operations(argc, argv, buffer);
    } else {
        printf("5n/a\n");
    }
    
    return 0;
}


void compare(int GNU, char* buff) {
    switch (GNU) {
        case 1: strcat(buff, "-b"); break;
        case 3: strcat(buff, "-n"); break;
        case 4: strcat(buff, "-s"); break;
    }
}

int GNU_check (char* argv) {
    int flag = 0;

    if (strcmp(argv, "--number-nonblank")==0){
        flag=1;
    } else if (strcmp(argv, "--number")==0){
        flag=3;
    } else if (strcmp(argv, "--squeeze-blank")==0){
        flag=4;
    }
    return flag;
}

int file_quantity(int argc, char* argv[]){
    int count_files=0;
    for (int i = 1; i < argc; i++){
        if (argv[i][0]!='-'){
            count_files++;
        }
    }
    return count_files;
}

int validation (int argc, char* argv[], char buffer[]){
    int flag = 0;
    int minus = 0;
    int GNU = 0;
    int tmp = 0;
    int k = 0;
    char extra_buf[3] = "";
    int count_files=file_quantity(argc, argv);

    for (int i = 1; i < argc - count_files; i++) {
        char* current_arg = argv[i];
        int len = strlen(current_arg);

        if (len < 2) {
            flag = 0;
            continue; // Пропустить текущий аргумент и перейти к следующему.
        }

        if ((GNU = GNU_check(current_arg)) > 0) {
            compare(GNU, extra_buf);
            tmp = i;
        } else if (i != tmp) {
            for (int j = 0; current_arg[j] != '\0'; j++) {
                buffer[k] = current_arg[j];
                k++;
                char ch = current_arg[j];
                if (is_letter(ch)) {
                    flag++;
                } else if (ch == '-') {
                    minus++;
                } else if (ch == '-' && is_letter(current_arg[j + 1])) {
                    flag++;
                } else {
                    flag = 0;
                    break;
                }
            }
        }
        if (strlen(extra_buf) > 1) {
            for (int p=0; extra_buf[p]!='\0'; p++){
                buffer[k] = extra_buf[p];
                k++;
                if (extra_buf[p]=='-'){
                    minus++;
                }
            }
            extra_buf[0] = '\0'; 
        }
    }
    buffer[k]='\0';
    if (minus != argc - count_files - 1) {
        flag = 0;
    }

    // printf("buffer %s\n", buffer);
    // printf("minus %d\n", minus);
    // printf("count_files %d\n", count_files);
    // printf("argc %d\n", argc);

    if (argc==2 || ((argc-count_files-1)==0)){
        flag = 1;
    }

    if (check_files(argc,argv)==0){
        flag = 0;
    }
    
    // printf("flag: %d\n", flag);

    return flag;
}

int is_letter(char ch){
    int flag = 0;
    if (ch =='b' || ch =='e' || ch =='n' || ch =='s' || ch =='t'){
        flag++;
    }
    return flag;
}

void file_operations (int argc, char* argv[], char keys[]){
    char filename[50];
    int address=0;

    for (int i = 1; i < argc; i++){
        if (argv[i][0]!= '-'){
            address = i;
            break;
        }
    }

    for (int i = address; i < argc; i++){
        sprintf(filename, "%s", argv[i]); 
        
        FILE* myfile;
        myfile = fopen(filename, "r");
        if(myfile==NULL){
            printf("2n/a\n");
        } else {
            // здесь должна быть часть где вызываются нужные функции
            priority(keys);
            match(keys, myfile);
        }
        if (myfile!=NULL){fclose(myfile);}
    }
}

void priority (char keys[]){
    for (int i=0; keys[i]!='\0'; i++){
        if (keys[i]=='b'){ // убираем повторы
            for (int j=0; keys[j]!='\0'; j++){
                if (keys[j]=='b' || keys[j]=='n'){
                    keys[j]='-';
                }
            }
            keys[i]='b';
        } else if (keys[i]=='e'){
            for (int j=0; keys[j]!='\0'; j++){
                if (keys[j]=='e'){
                    keys[j]='-';
                }
            }
            keys[i]='e';
        } else if (keys[i]=='n'){
            for (int j=0; keys[j]!='\0'; j++){
                if (keys[j]=='n'){
                    keys[j]='-';
                }
            }
            keys[i]='n';
        } else if (keys[i]=='s'){
            for (int j=0; keys[j]!='\0'; j++){
                if (keys[j]=='s'){
                    keys[j]='-';
                }
            }
            keys[0]='s';
        } else if (keys[i]=='t'){
            for (int j=0; keys[j]!='\0'; j++){
                if (keys[j]=='t'){
                    keys[j]='-';
                }
            }
            keys[i]='t';
        }
    }
}

int check_files(int argc, char* argv[]){
    int flag = 1;
    int address=0;

    for (int i = 1; i < argc; i++){
        if (argv[i][0]!= '-'){
            address = i;
            break;
        }
    }

    for (int i = address; i < argc; i++){
        
        FILE* myfile;
        myfile = fopen(argv[i], "r");
        if(myfile==NULL){
            flag=0;
            break;
        }
        if (myfile!=NULL){fclose(myfile);}
    }
    return flag;
}



