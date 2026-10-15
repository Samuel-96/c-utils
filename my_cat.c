#include <stdio.h>
#include <stdbool.h>

bool check_args(int argc, char* argv[]);

int main(int argc, char* argv[])
{

    if (!check_args(argc, argv))
    {
        return 1;
    }

    char* file_path = argv[1];

    printf("%s\n", file_path);

    FILE *f = fopen(file_path, "rb");

    if (f == NULL)
    {
        printf("Error reading file");
        return 2;
    }

    char buffer[1024];
    size_t bytes_read = 0;

    while ( (bytes_read = fread(buffer, sizeof(char), 1024, f)) != 0 )
    {
        fwrite(buffer,sizeof(char),bytes_read,stdout);
    }

    fclose(f);

    return 0;
}

bool check_args(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Wrong number of arguments. Use: ls.exe <path to file>");
        return false;
    }

    return true;
}

bool isfile_valid(char* file)
{

}
