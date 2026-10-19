#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    if (!check_args(argc, 3, "Usage: my_cp.exe <file_to_copy> <new_file>"))
    {
        return 1;
    }

    if (arepaths_equal(argv[1], argv[2]))
    {
        printf("Can't copy the same file.");
        return 2;
    }

    int res = arefiles_equal(argv[1], argv[2]);

    if (res == 1)
    {
        printf("Destination already contains the same data.\n");
        return 3;
    }
    else if (res != 0)
    {
        printf("Error code: %d", res);
        return 4;
    }

    FILE *fsource = fopen(argv[1], "rb");

    if (fsource == NULL)
    {
        perror("Error");
        return 5;
    }

    FILE *fdestination = fopen(argv[2], "wb");

    if (fdestination == NULL)
    {
        fclose(fsource);
        perror("Error");
        return 6;
    }

    char buffer[1024];
    size_t bytes_read = 0;

    // Read files from source and write them to destination file

    while ( (bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fsource)) != 0 )
    {
        if ( (fwrite(buffer, sizeof(char), bytes_read, fdestination)) != bytes_read )
        {
            perror("Error");
            fclose(fsource);
            fclose(fdestination);
            return 7;
        }
    }

    if (ferror(fsource))
    {
        perror("Error");
        fclose(fsource);
        return 8;
    }

    if (fclose(fsource) != 0)
    {
        perror("Error");
        return 9;
    }

    if (fclose(fdestination) != 0)
    {
        perror("Error");
        return 10;
    }

    return 0;
}
