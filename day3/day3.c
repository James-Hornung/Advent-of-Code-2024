#include <stdio.h>
#include <stdlib.h>

# define FILENAME "input.txt"
# define BUFFERSIZE 12

int isNum(char c) {
    int is = 1;

    switch (c) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case '0':
            break;
        default:
            is = 0;
    }
    return is;
}

int isValidMul(char *buffer) {
    int valid = 1;
    if (*buffer == 'm' && *(buffer + 1) == 'u' && *(buffer + 2) == 'l' && *(buffer + 3) == '(' && isNum(*(buffer + 4)) == 1) {
        int i = 0;
        do {
            if (isNum(*(buffer + 4 + i)) == 0) {
                valid = 0;
            }
            i++;
            if ((*buffer + i) == '\0') {return 0;}
        } while (*(buffer + 4 + i) != ',' && valid == 1);
        if ( i < 1 || i > 3) {
            valid = 0;
        }

        int j = 1;
        do {
            if (isNum(*(buffer + 4 + i + j)) == 0) {
                valid = 0;
            }
            j++;
            if ((*buffer + 4 + i + j) == '\0') {return 0;}
        } while (*(buffer + 4 + i + j) != ')' && valid == 1);
        if ( j < 1 || j > 4) {
            valid = 0;
        }
    } else {
        valid = 0;
    }

    
    return valid;
}

int isValidDo(char *buffer) {
    int valid;
    if (*(buffer) == 'd' && *(buffer + 1) == 'o' && *(buffer + 2) == '(' && *(buffer + 3) == ')') {
        valid = 1;
    } else {
        valid = 0;
    }

    return valid;
}
int isValidDont(char *buffer) {
    int valid;
    if (*(buffer) == 'd' && *(buffer + 1) == 'o' && *(buffer + 2) == 'n' && *(buffer + 3) == '\'' && *(buffer + 4) == 't' && *(buffer + 5) == '(' && *(buffer + 6) == ')') {
        valid = 1;
    } else {
        valid = 0;
    }

    return valid;
}

int process(char *code) {
    int openIndex, commaIndex, closeIndex = 0;
    
    for (int i = 0; closeIndex == 0; i++) {
        switch (*(code + i)) {
            case '(':
                openIndex = i;
                break;
            case ',':
                commaIndex = i;
                break;
            case ')':
                closeIndex = i;
        }
    }


    int num1Digits = commaIndex - openIndex - 1;
    int num2Digits = closeIndex - commaIndex - 1;

    char *numBuffer = malloc(sizeof(char) * (num1Digits + num2Digits + 2));
    for (int i = 0; i < num1Digits; i++) {
        *(numBuffer + i) = *(code + openIndex + 1 + i);
    }

    *(numBuffer + num1Digits) = ' ';

    for (int i = 1; i < num2Digits + 1; i++) {
        *(numBuffer + num1Digits + i) = *(code + commaIndex + i);
    }

    *(numBuffer + num1Digits + num2Digits + 1) = '\0';

    int num1, num2;
    sscanf(numBuffer, "%i %i", &num1, &num2);

    free(numBuffer);
    return num1 * num2;
}

void initialRead(char *buffer, FILE *f) {
    for (int i = 0; i < BUFFERSIZE; i++) {
        *(buffer + i) = getc(f);
    }
    *(buffer + BUFFERSIZE) = '\0';
}

void readChar(char *buffer, FILE *f) {
    for (int i = 1; i < BUFFERSIZE; i++) {
        *(buffer + i - 1) = *(buffer + i);
    }
    *(buffer + BUFFERSIZE - 1) = getc(f);
}

int main(void) {
    char *buffer = malloc(sizeof(char) * (BUFFERSIZE + 1));
    FILE *f = fopen(FILENAME, "r");
    initialRead(buffer, f);

    int sum = 0, doing = 1;
    do {
        if (isValidDont(buffer)) {
            doing = 0;
        } else if (isValidDo(buffer)) {
            doing = 1;
        }
        if (isValidMul(buffer) && doing) {
            sum += process(buffer);
        }
        readChar(buffer, f);
    } while(*(buffer) != EOF);

    printf("%i", sum);
    free(buffer);
    fclose(f);
    return 0;
}