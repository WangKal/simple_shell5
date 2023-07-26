#ifndef PATH_H
#define PATH_H


int tokenize_path(const char *path_env, char **path_dirs);
void free_path_dirs(char **path_dirs, int num_dirs);

#endif /* PATH_H */

