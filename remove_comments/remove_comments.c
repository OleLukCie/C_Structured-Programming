#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_comments(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    FILE *outfile = fopen(output_file, "w");

    if (!infile) {
        fprintf(stderr, "Error: Could not open input file %s\n", input_file);
        exit(EXIT_FAILURE);
    }
    if (!outfile) {
        fprintf(stderr, "Error: Could not open output file %s\n", output_file);
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    char ch, next_ch;
    int in_single_line_comment = 0;
    int in_multi_line_comment = 0;

    while ((ch = fgetc(infile)) != EOF) {
        if (in_single_line_comment) {
            if (ch == '\n') {
                in_single_line_comment = 0;
                fputc(ch, outfile); // Write the newline character
            }
            continue;
        } else if (in_multi_line_comment) {
            if (ch == '*' && (next_ch = fgetc(infile)) == '/') {
                in_multi_line_comment = 0; // End of multi-line comment
                continue;
            } else {
                // Continue reading until the end of the comment
                continue;
            }
        }

        if (ch == '/') {
            next_ch = fgetc(infile);
            if (next_ch == '/') {
                in_single_line_comment = 1; // Start of single-line comment
                continue;
            } else if (next_ch == '*') {
                in_multi_line_comment = 1; // Start of multi-line comment
                continue;
            } else {
                fputc(ch, outfile); // Just a regular character
                // Don't forget to put back the next character
                ungetc(next_ch, infile);
            }
        }

        // If we are not in a comment, write the character to the output file
        fputc(ch, outfile);
    }

    fclose(infile);
    fclose(outfile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    remove_comments(argv[1], argv[2]);

    printf("Comments removed and saved to %s\n", argv[2]);
    return EXIT_SUCCESS;
}
