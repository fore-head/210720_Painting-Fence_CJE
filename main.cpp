//
// Created by choij on 2021-07-20.
//

#include <iostream>
#include <stdio.h>
#include <array>
using namespace std;

int getHorizonMax(int planks[], int size, int * start, int * end) {
    int max_length = 1;
    int length_start = 1;
    *start = 0;

    //가로 길이 조사
    for (int i=0; i<size; i++) {
        if (planks[i] == 0) {
            if (max_length < length_start)
                max_length = length_start;
            length_start = 1;
            *end = i;
        }
        else if (i+1 < size && planks[i+1]!=0) {
            length_start++;
        }
        else if (i == size-1) {
            *end = i;
        }
    }

    max_length = length_start;

    return max_length;
}

int getVerticalMax(int planks[], int size, int * index) {
    int max_length = 1;

    //세로 길이 조사 1<=a_i<=10^9
    for (int i=0; i<size; i++) {
        if (planks[i] > max_length) {
            max_length = planks[i];
            *index = i;
        }
    }

    return max_length;
}

int getMaxLength(int planks[], int size) {
    int horizonMax = getHorizonMax(planks, size, 0, 0);
    int verticalMax = getVerticalMax(planks, size, 0);

    return (horizonMax > verticalMax) ? horizonMax : verticalMax;
}

void strokeVertical(int planks[], int index) {
    planks[index] = 0;
}

void strokeHorizontal(int planks[], int start, int end) {
    for (int i=start; i<end; i++)
        planks[i]--;
}

int main() {
    int n;
    int strokes = 0;
    int horizonMax, verticalMax;
    int start, end, index;

    cin >> n;

    int planks[n];

    //cout << "main -> sizeof(planks) / sizeof(planks[0]) : " << sizeof(planks) / sizeof(planks[0]) << endl;

    for (int i=0; i<n; i++) {
        cin >> planks[i];
    }

    int max_length = getMaxLength(planks, sizeof(planks) / sizeof(planks[0]));

    //cout << max_length;

    while (max_length > 1) {
        horizonMax = getHorizonMax(planks, sizeof(planks) / sizeof(planks[0]), &start, &end);
        verticalMax = getVerticalMax(planks, sizeof(planks) / sizeof(planks[0]), &index);

        if (horizonMax > verticalMax) {
            strokeHorizontal(planks, start, end);
        }
        else {
            strokeVertical(planks, index);
        }

        strokes++;
    }

    for (int i=0; i<sizeof(planks) / sizeof(planks[0]); i++) {
        if (planks[i])
            strokes++;
    }

    //1씩 남은 것 처리 필요

    cout << strokes;

    return 0;
}