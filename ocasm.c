#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOL int

BOOL ocblank(char c) {
    return c == ' ' || c == '\r' || c == '\n' || c == '\0';
}

char *next_token(char *s) {
    if (ocblank(*s)) {
        return NULL;
    }

    while(!ocblank(*s)) {
        s++;
    }

    while(ocblank(*s)) {
        if (*s == '\0') {
            break;
        }
        *s = '\0';
        s++;
    }

    return s;
}

void process(char *line, FILE *output) {
    char *token = line;
    char *rest = next_token(token);
    if (rest == NULL)
        return;

    if (strcmp(token, "ld") == 0) {
        fputs("00", output);
    }
    
    if (strcmp(token, "ldm") == 0) {
        fputs("01", output);
    }
    
    if (strcmp(token, "ldr") == 0) {
        fputs("02", output);
    }
    
    if (strcmp(token, "st") == 0) {
        fputs("10", output);
    }
    
    if (strcmp(token, "std") == 0) {
        fputs("11", output);
    }
    
    if (strcmp(token, "noop") == 0) {
        fputs("FE", output);
    }
    
    if (strcmp(token, "halt") == 0) {
        fputs("FF", output);
    }

    for(rest = next_token(token = rest); rest != NULL; rest = next_token(token = rest)) {
        fprintf(output, " %s", token);
    }

    fputs("\n", output);
}

int main(int argc, char **argv) {
    if (argc != 2) { /* If there is no [FILE] argument */
        printf("Usage: ocasm [FILE]\n"); /* Print usage */
        exit(0); /* Exit */
    }

    FILE *infile = fopen(argv[1],"r"); /* Open the input file */
    FILE *outfile = fopen("out.oca","w"); /* Open the output file */

    char line[1000];
    while (fgets(line, sizeof(line), infile)) {
        process(line, outfile);
    }

    fclose(infile);
    fclose(outfile);
}
