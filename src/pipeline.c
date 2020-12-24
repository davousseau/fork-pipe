/**
 * @file pipeline.c
 * @brief Interpret a character stream with a pipe.
 * @author David Brousseau
 * @version 0.1
 * @date December 2020
 */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LENGTH 255 /**< Buffer maximum length */

// These function declarations are required to use alphabetical order
void groupFrequencies(int *pipe);
void printLetters(int *frequencies);
void summateDigits(int *pipe);

/**
 * @brief Create all process childs
 * @param pipe1 Pipe between child 1 and his parent
 * @param pipe2 Pipe between child 2 and his parent
 */
void createChilds(int *pipe1, int *pipe2)
{
    int child1 = fork();
    int status;
    if (child1 == 0)
    {
        summateDigits(pipe1);
    }
    else
    {
        waitpid(child1, &status, WNOHANG | WUNTRACED);
        int child2 = fork();
        if (child2 == 0)
        {
            groupFrequencies(pipe2);
        }
    }
}

/**
 * @brief Create a new pipe.
 * @return File descriptor
 */
int *createPipe()
{
    int *fd = calloc(2, sizeof(int));
    if (pipe(fd) != 0)
    {
        fprintf(stderr, "pipeline: fd: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return fd;
}

/**
 * @brief Group letter frequencies within the second child.
 * @param pipe Pipe between child and his parent
 */
void groupFrequencies(int *pipe)
{
    close(pipe[1]);
    char letters[MAX_LENGTH] = "";
    read(pipe[0], letters, MAX_LENGTH);
    int frequencies[52] = {0};
    int l = 0, x = 0;
    while (letters[l] != '\0')
    {
        if (letters[l] >= 'a' && letters[l] <= 'z') // Lower case
        {
            x = letters[l] - 'a';
            frequencies[x]++;
        }
        if (letters[l] >= 'A' && letters[l] <= 'Z') // Upper case
        {
            x = letters[l] - 'A';
            frequencies[x + 26]++;
        }
        l++;
    }
    printLetters(frequencies);
    exit(EXIT_SUCCESS);
}

/**
 * @brief Print the letters to stdout stream.
 * @param frequencies Letter frequencies
 */
void printLetters(int *frequencies)
{
    for (int i = 0; i < 26; i++) // Lower case
    {
        if (frequencies[i] > 0)
        {
            printf("La lettre %c apparaît %d fois.\n", i + 'a', frequencies[i]);
        }
    }
    for (int i = 0; i < 26; i++) // Upper case
    {
        if (frequencies[i + 26] > 0)
        {
            printf("La lettre %c apparaît %d fois.\n", i + 'A', frequencies[i + 26]);
        }
    }
}

/**
 * @brief Load the contents of the file into the buffer.
 * @param filename File to read
 * @return Content buffer
 */
char *readFile(const char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "pipeline: %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    char *buffer = calloc(MAX_LENGTH, sizeof(char));
    fread(buffer, MAX_LENGTH, 1, file);
    fclose(file);
    return buffer;
}

/**
 * @brief Summate all digits within the first child.
 * @param pipe Pipe between child and his parent
 */
void summateDigits(int *pipe)
{
    close(pipe[1]);
    char digit[MAX_LENGTH] = "";
    read(pipe[0], digit, MAX_LENGTH);
    int sum = 0;
    for (unsigned long i = 0; i < (strlen(digit)); i++)
    {
        sum = sum + (digit[i] - 48);
    }
    if(sum > 0) {
        fprintf(stdout, "La somme des chiffres est %d.\n", sum);
    }
    exit(EXIT_SUCCESS);
}

/**
 * @brief Launch the software.
 * @param argc Number of parameters
 * @param argv File to interpret
 * @return Exit status
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: bin/pipeline <filename>\n");
        exit(EXIT_FAILURE);
    }
    char *buffer = readFile(argv[1]);
    int *pipe1 = createPipe();
    int *pipe2 = createPipe();
    for (unsigned long i = 0; i < strlen(buffer); i++)
    {
        if (isdigit(buffer[i]))
        {
            write(pipe1[1], &buffer[i], 1);
        }
        else if (isalpha(buffer[i]) != 0)
        {
            write(pipe2[1], &buffer[i], 1);
        }
    }
    createChilds(pipe1, pipe2);
    close(pipe1[0]);
    close(pipe2[0]);
    wait(0);
    free(buffer);
    free(pipe1);
    free(pipe2);
    return EXIT_SUCCESS;
}