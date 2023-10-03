#include "options.h"

void match(char* keys, FILE* myfile){
    char buffer[200];
    int num=1;
    int num_n=1;
    int lin_num=1;
    int num_s=0;
    int len = strlen(keys);
    int lines = line_count(myfile);

    if (strlen(keys)==0){
        while (fgets(buffer, sizeof(buffer), myfile) != NULL){
            printf("%s", buffer);
        }
    } else {
        while (fgets(buffer, sizeof(buffer), myfile) != NULL){
            for (int i=0; keys[i]!='\0'; i++){
                if (keys[i]=='b'){
                    num = func_b(buffer, num, num_s);
                } else if (keys[i]=='e'){
                    func_e(buffer, lin_num, lines, num_s);
                    lin_num++;
                } else if (keys[i]=='n'){
                    num_n = func_n(buffer, num_n, num_s);
                } else if (keys[i]=='s'){
                    num_s = func_s(buffer, num_s);
                } else if (keys[i]=='t'){
                    func_t(buffer);
                }
            }
            printf("%s", buffer);
        }
    }
}

int line_count(FILE* myfile){
    int line_count = 0;
    char ch;
    char prev_ch = '\n'; // Предыдущий символ - символ новой строки

    while ((ch = fgetc(myfile)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
        prev_ch = ch;
    }

    // Если файл не заканчивается символом новой строки, учтем последнюю строку
    if (prev_ch != '\n') {
        line_count++;
    }
    fseek(myfile, 0, SEEK_SET);
    return line_count;
}

int func_b(char* buffer, int num, int num_s){
    char new_str[300];
    if ((buffer[0] == '\n' || buffer[0] == '$') && num_s<2) {
        if (buffer[0] == '$'){
            snprintf(new_str, sizeof(new_str), "       %s", buffer);
        } else {
            snprintf(new_str, sizeof(new_str), "     %s", buffer);
        }  
    } else if (num_s<2){
        snprintf(new_str, sizeof(new_str), "     %d  %s", num, buffer);
        num++;
    } else if (num_s>1){
        snprintf(new_str, sizeof(new_str), "%s", buffer);
    }
    if (strlen(new_str) < sizeof(new_str)) {
        strcpy(buffer, new_str);
    } else {
        printf("ERROR\n");
    }
    return num;
}

void func_e(char* buffer, int lin_num, int lines, int num_s){
    char new_str[300];
    buffer[strcspn(buffer, "\n")]='\0';
    if (buffer[0] == '\n' && num_s<2) {
        snprintf(new_str, sizeof(new_str), "%s$\n", buffer);
    } else if (num_s<2) {
        if (lin_num==lines){snprintf(new_str, sizeof(new_str), "%s", buffer);} 
        else{snprintf(new_str, sizeof(new_str), "%s$\n", buffer);}
    } else {
        snprintf(new_str, sizeof(new_str), "%s", buffer);
    }
    if (strlen(new_str) < sizeof(new_str)) {
        strcpy(buffer, new_str);
    } else {
        printf("ERROR\n");
    }
}

int func_n(char* buffer, int num, int num_s){
    char new_str[300];
    if (num_s<2){
        snprintf(new_str, sizeof(new_str), "     %d  %s", num, buffer);
        num++;
    } else {
        snprintf(new_str, sizeof(new_str), "%s", buffer);
    }
    
    if (strlen(new_str) < sizeof(new_str)) {
        strcpy(buffer, new_str);
    } else {
        printf("ERROR\n");
    }
    return num;
}

int func_s(char* buffer, int tmp){
    if (buffer[0] == '\n') {
        if (tmp==0 || tmp==1){
            if (tmp==1){
                buffer[strcspn(buffer, "\n")]='\0';
            }
            tmp++;
        } else {
            buffer[strcspn(buffer, "\n")]='\0';
        }
    } else {
        tmp=0;
    }
    return tmp;
}

void func_t(char* str){
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] < 32 || str[i] > 126) {
            // Если символ непечатаемый, заменяем его на специальный эквивалент.
            switch (str[i]) {
                case '\n':
                    str[i] = '$'; // заменяем перевод строки на '$'.
                    break;
                case '\r':
                    strcpy(&str[i], "^M");
                    // str[i] = '^M'; // заменяем возврат каретки на '^M'.
                    break;
                case '\t':
                    strcpy(&str[i], "^I");
                    // str[i] = '^I'; // заменяем табуляцию
                    break;
                case '\v':
                    strcpy(&str[i], "^K");
                    // str[i] = '^K'; // заменяем вертикальный таб
                    break;
                case '\f':
                    strcpy(&str[i], "^L");
                    // str[i] = '^L'; // заменяем подачу страницы
                    break;
                case '\a':
                    strcpy(&str[i], "^G");
                    // str[i] = '^G'; // заменяем Управляющий символ BELL
                    break;
                case '\e':
                    strcpy(&str[i], "^[");
                    // str[i] = '^['; // заменяем Управляющий символ ESC
                    break;
                case '\0':
                    strcpy(&str[i], "^@");
                    // str[i] = '^@'; // заменяем Управляющий символ NUL
                    break;
                default:
                    break;
            }
        }
    }
}


