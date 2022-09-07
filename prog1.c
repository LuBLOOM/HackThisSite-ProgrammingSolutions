#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS "wordlist.txt"
#define LINESIZE 1000

static char **real;

static char *sort(char *str)
{
        char a[256] = {0};
        int i, c;
        for (i = 0; (c = str[i]) != '\0' && c != '\n' && c != '\r'; ++i)
                ++a[c];
        for (i = 1; i < 256; ++i)
                a[i] += a[i-1];

        char *buffer = calloc(strlen(str)+1, sizeof *buffer);
        for (i = 0; (c = str[i]) != '\0' && c != '\n' && c != '\r'; ++i)
                buffer[--a[c]] = c;
        buffer[i] = '\0';

        return buffer;
}

static int compare(char *first, char *second)
{
        char *first_s =  sort(first);
        char *second_s = sort(second);

        int c = strcmp(first_s, second_s);

        free(first_s);
        free(second_s);

        return c;
}

static void solve(char **words, size_t words_len)
{
        FILE *fp = fopen(WORDS, "r");

        char *line = NULL;
        size_t line_size = 0;
        ssize_t curr_size = 0;

        while ((curr_size = getline(&line, &line_size, fp)) != -1) {
                for (int i = 0; i < words_len; ++i) {
                        if (compare(words[i], line) == 0) {
                                real[i] = strdup(line);
                        }
                }
        }

        fputc('\n', stdout);

        free(line);

        fclose(fp);
}

int main(int argc, char **argv)
{
        size_t words_len = 10;
        char **words = malloc(words_len * sizeof *words);
        real  = malloc(words_len * sizeof *real);

        char buffer[LINESIZE];
        for (int i = 0; i < words_len; ++i) {
                scanf("%s", buffer);
                words[i] = strdup(buffer);
        }

        solve(words, words_len);

        for (int i = 0; i < words_len; ++i) {
                char *buffer = real[i];
                int j = 0;
                while (buffer[j] != '\r') {
                        fputc(buffer[j], stdout);
                        ++j;
                }
                fputc(',', stdout);
        }

        fputc('\n', stdout);

        return 0;
}
