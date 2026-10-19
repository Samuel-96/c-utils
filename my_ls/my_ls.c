#include "../include/utils.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>


void print_header(char* path);

int main(int argc, char* argv[])
{
   HANDLE hFind = INVALID_HANDLE_VALUE;
   WIN32_FIND_DATA ffd;
   DWORD dwError=0;
   char path[MAX_PATH];

   if (!check_args(argc, 2, "Usage: my_ls.exe <directory>"))
   {
      return 1;
   }

   append_star(argv[1], "\\*");

   hFind = FindFirstFile(argv[1], &ffd);

   if (hFind == INVALID_HANDLE_VALUE)
   {
      printf("Couldn't find directory.");
      return 2;
   }

   // Obtain the absolute path we want to list
   if (GetFullPathName(argv[1], MAX_PATH, path, NULL) == 0)
   {
      return 3;
   }

   print_header(path);

   // List the files in directory
   do
   {
      // Ignore current and parent directory entries
      if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
      {
         continue;
      }

      // Combine the high and low parts of the 64-bit file size
      unsigned long long file_size = ((unsigned long long)ffd.nFileSizeHigh << 32) |ffd.nFileSizeLow;

      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         printf("\t%-40s <DIR>\n", ffd.cFileName);
      }
      else
      {
         printf("\t%-40s %llu bytes\n", ffd.cFileName, file_size);
      }

   } while (FindNextFile(hFind, &ffd) != 0);
   printf("\n");

   dwError = GetLastError();

   FindClose(hFind);

   if (dwError != ERROR_NO_MORE_FILES)
   {
      fprintf(stderr, "Error during enumeration: %lu\n", (unsigned long)dwError);
      FindClose(hFind);
      return 4;
   }

   return 0;
}

void print_header(char* path)
{
   path[strlen(path)-2] = '\0';

   printf("\n");
   printf("Listing directory <%s>\n", path);
   printf("\n");
   printf("\t%-40s %s\n", "NAME", "SIZE");
   printf("\n");
}
