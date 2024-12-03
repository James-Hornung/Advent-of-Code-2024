#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int lines = 1000;

int calculateTotalDistance(int list1[], int list2[]) {
    int index1;
    int index2;
    int num1, num2, dist, total = 0;
    for (int i = 0; i < lines; i++) {
        num1 = 999999;
        num2 = 999999;
        index1 = -1;
        index2 = -1;
        for (int j = 0; j < lines; j++) {
            if (list1[j] < num1 && list1[j] != -1) {
                num1 = list1[j];
                index1 = j;
            }
            if (list2[j] < num2 && list2[j] != -1) {
                num2 = list2[j];
                index2 = j;
            }
        }

        list1[index1] = -1;
        list2[index2] = -1;

        dist = num1 - num2;
        if (dist < 0) {
            dist *= -1;
        }

        total += dist;
    }

    return total;
}

int calculateSimilarityScore(int list1[], int list2[]) {
    int num, count;
    int score = 0;
    for (int i = 0; i < lines; i++) {
        num = list1[i];
        count = 0;
        for (int j = 0; j < lines; j++) {
            if (list2[j] == num) {
                count++;
            }
        }
        score += num * count;
    }

    return score;
}

int main(void) {
    FILE *f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("Could not open file");
        return 1;
    }

    char buffer[15];
    int num1, num2, total, score;
    int list1[lines];
    int list2[lines];
    for (int i = 0; i < lines; i++) {
        fgets(buffer, sizeof(buffer), f);

        sscanf(buffer, "%d   %d", &num1, &num2);

        list1[i] = num1;
        list2[i] = num2;
    }

    score = calculateSimilarityScore(list1, list2);

    total = calculateTotalDistance(list1, list2);
    
    printf("%i\n", total);
    printf("%i", score);
    fclose(f);
    return 0;
}