#include "../include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

bool check_args(int argc, int args_to_check, const char* usage_message)
{
    if (argc != args_to_check)
    {
        fprintf(stderr, "%s\n", usage_message);
        return false;
    }

    return true;
}

bool arepaths_equal(const char* path1, const char* path2)
{
    return strcmp(path1, path2) == 0;
}

int arefiles_equal(const char* path_source, const char* path_destination)
{
    // Open both source and destination files

    FILE* fsource = fopen(path_source, "rb");
    FILE* fdestination = fopen(path_destination, "rb");

    if (fsource == NULL)
    {
        perror("Error\n");
        return 2;
    }

    if (fdestination == NULL)
    {
        int err = errno;
        fclose(fsource);

        if (err == ENOENT)
        {
            return 0;
        }

        errno = err;
        perror("Error");
        return 3;
    }

    char buffer_source[BUFFER_SIZE];
    char buffer_destination[BUFFER_SIZE];
    size_t byte_source, byte_destination;

    // Read up to 2048 bytes from each file

    while ( (byte_source = fread(buffer_source, 1, sizeof(buffer_source), fsource)) != 0)
    {
        byte_destination = fread(buffer_destination, 1, sizeof(buffer_destination), fdestination);

        // // Check whether the number of bytes read differs between both files, if so that means the files are different

        if (byte_destination != byte_source)
        {
            fclose(fsource);
            fclose(fdestination);
            return 0;
        }

        // Number of bytes read are the same, compare the contents of both buffers for the number of bytes read

        if (memcmp(buffer_destination, buffer_source, byte_source) != 0)
        {
            fclose(fsource);
            fclose(fdestination);
            return 0;
        }
    }

    // If destination has additional data to read they're different files

    if (fread(buffer_destination, 1, sizeof(buffer_destination), fdestination) != 0)
    {
        fclose(fsource);
        fclose(fdestination);
        return 0;
    }

    if (ferror(fsource))
    {
        perror("Error\n");
        fclose(fsource);
        return 4;
    }

    if (ferror(fdestination))
    {
        perror("Error\n");
        fclose(fsource);
        return 5;
    }

    if (fclose(fsource) != 0)
    {
        perror("Error\n");
        return 6;
    }

    if (fclose(fdestination) != 0)
    {
        perror("Error\n");
        return 7;
    }

    return 1;
}

void append_star(char* s, const char* c)
{
    size_t tam = strlen(s);
    s[tam] = c[0];
    s[tam + 1] = c[1];
    s[tam + 2] = '\0';
}
