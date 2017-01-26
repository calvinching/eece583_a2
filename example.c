#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graphics.h"

#define DEBUG
#define SUCCESS 0
#define ERROR -1

void delay();
void button_press(float x, float y);
void drawscreen();
int parse_file(char *file);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Need input file\n");
        exit(1);
    }

    char *file = argv[1];
    printf("Input file: %s\n", file);

    // initialize display
    init_graphics("Some Example Graphics");
    init_world(0.,0.,1000.,1000.);

    parse_file(file);

    drawscreen();
    event_loop(button_press, drawscreen);
    return 0;
}

int parse_file(char *file) {
    FILE *fp;
    int ret = SUCCESS;

    if (file != NULL) {
        fp = fopen(file, "r");
        if (fp == NULL) {
            printf("Failed to open file: %s\n", file);
            ret = ERROR;
        } else {
            char *line;
            size_t len = 0;
            ssize_t read;

            int line_num = 0;
            while ((read = getline(&line, &len, fp)) != -1) {
#ifdef DEBUG
                printf("parse_file[%d]: %s", line_num, line);
#endif
                line_num++;
            }
        }
    } else {
        printf("Invalid file!\n");
    }

    return ret;
}

void drawscreen() {
    setlinestyle (SOLID);
    drawtext(60.,500.,"Cost",800.);
    drawtext(500.,940.,"Number of Iterations",800.);
    setlinewidth (3);
    drawline(100.,920.,900.,920.);
    drawline(100.,920.,100.,100.);
}

void delay() {
    int i, j, k, sum;

    sum = 0;
    for (i = 0; i < 1000; i++)
        for (j = 0; j < i; j++)
            for (k = 0; k < 30; k++)
                sum = sum + i + j - k;
}

void button_press(float x, float y) {
    printf("User clicked a button at coordinates (%f, %f)\n", x, y);
}
