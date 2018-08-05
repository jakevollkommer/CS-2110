#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* infile = fopen(argv[1], "r");

    char data_arr[26];
    char new_arr[26];

    fread(data_arr, sizeof(char), 26, infile);
    fclose(infile);

    for (char i = 0; i < 26; i++) {
        new_arr[i] = ~data_arr[i];
    }
    FILE* outfile = fopen("out.txt", "w");
    fwrite(new_arr, sizeof(char), 26, outfile);
}



