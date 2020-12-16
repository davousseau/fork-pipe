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
        fprintf(stderr, "Use: bin/pipeline <filename>\n");
        exit(EXIT_FAILURE);
    }
    // TODO:
    return EXIT_SUCCESS;
}