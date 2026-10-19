#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    if (!check_args(argc, 2, "Usage: my_cat.exe <path_to_file>."))
    {
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");

    if (f == NULL)
    {
        perror("Error");
        return 2;
    }

    char buffer[1024];
    size_t bytes_read = 0;

    // Read bytes from file and write them to stdout.

    while ( (bytes_read = fread(buffer, sizeof(char), sizeof(buffer), f)) != 0 )
    {
        if ( (fwrite(buffer, sizeof(char), bytes_read, stdout)) != bytes_read )
        {
            perror("Error");
            fclose(f);
            return 3;
        }
    }

    if (ferror(f))
    {
        perror("Error");
        fclose(f);
        return 4;
    }

    if (fclose(f) != 0)
    {
        perror("Error");
        return 5;
    }

    return 0;
}
