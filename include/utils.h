#ifndef UTILS_H_   /* Include guard */
#define UTILS_H_
#include <stdbool.h>

bool check_args(int argc, int args_to_check, const char* usage_message);
int arefiles_equal(const char* path_source, const char* path_destination);
bool arepaths_equal(const char* path1, const char* path2);
void append_star(char* s, const char* c);

#endif

