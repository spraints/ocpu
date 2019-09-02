#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef OCASM_ALL
int parse(char *line)
{
    char insts[4];
    int i = 0;
    int t = 0;
    
    int word;
    
    while (t <= 4) {
        
        word = "";
        
        printf("ps wd\n");
        
        while (1) {
            if (i < strlen(line)) {
                if (line[i] != " ") {
                    printf("%s\n",line[i]);
                    strcat(word,line[i]);
                    ++i;
                    printf("inc i\n");
                }
                else {
                    printf("br\n");
                    break;
                }
            }
            else {
                printf("br\n");
                break;
            }
        }
        ++i;
        printf("inc i\n");
        printf("add wd %s\n",word);
        insts[t] = word;
        ++t;
        printf("inc t\n");
    }
    printf("rtn\n");
    return(insts, t);
}


int parseasm(char* line) {
    printf("ps ln %s\n", line);
    char* code = parse(line);
    char ln[4];
    
    int C = code[0];
    
    printf("ps inst %s\n", C);
    if (C == "ld") {
        strcat(ln, "00");
    }
    
    if (C == "ldm") {
        strcat(ln, "01");
    }
    
    if (C == "ldr") {
        strcat(ln, "02");
    }
    
    if (C == "st") {
        strcat(ln, "10");
    }
    
    if (C == "std") {
        strcat(ln, "11");
    }
    
    if (C == "noop") {
        strcat(ln, "FE");
    }
    
    if (C == "halt") {
        strcat(ln, "FF");
    }
    
    printf("asm ln\n");
    strcat(ln, " "); strcat(ln,code[1]); strcat(ln," "); strcat(ln,code[2]);
    strcat(ln," "); strcat(ln,code[3]);
    
    printf("got %s\n", ln);
    
    printf("rtn\n");
    return(ln);
}
#endif

int main(int argc, char **argv) {
    printf("init\n");
    
    if (argc != 2) { /* If there is no [FILE] argument */
        printf("Usage: ocasm [FILE]\n"); /* Print usage */
        exit(0); /* Exit */
    }
    
    printf("open files\n");

#ifdef OCASM_ALL
    int infile = fopen(argv[1],"r"); /* Open the input file */
    int outfile = fopen("out.oca","w"); /* Open the output file */
    
    char lines[65535]; /* File probably won't be this long, but
        a single file should not be longer than 65535 lines. */
    char line[16]; /* Lines should only be about 16 characters max */
    
    int i = 0;
    
    printf("read\n");

    while (fgets(line, sizeof(line), infile)) { /* Magic */
        lines[i] = line;
        printf("get ln %d\n", i);
    }
    
    printf("close\n");

    fclose(infile);
    
    int file_len = i;
    
    printf("parse\n");

    for (int ln=0; ln == i; ++i) {
        fprintf(outfile, parseasm(lines[ln]));
    }
    
    fclose(outfile);
    
    printf("done.\n");
#endif
}
