#include "../include/my_hash_table.h"
#include<dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_export(char **args);
int ls(char **args);
int lsh_env(char **args);
int lsh_echo(char **args);

hashtable_t *ht;
/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "ls",
  "echo",
  "export",
  "env",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &ls,
  &lsh_echo,
  &lsh_export,
  &lsh_env,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
/*
  Builtin function implementations.
*/
int lsh_echo(char **args)
{
  int i;
  char *word;

  word = malloc(12*sizeof(char));
  i = 1;
  while(args[i] != NULL){
    if( i > 1)
      printf(" ");
    if(args[i][0] == '$'){
      printf("%s", hash_get(ht, args[i]+1));
      i++;
      continue;
    }
    printf("%s", args[i]);
    i++;
  }
  free(word);
  printf("\n");

  return 1;
}

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Type program names and arguments, and hit enter.\n");
  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  return 1;
}

int ls(char **args){
 struct dirent *pDirent;
   DIR *pDir;

   if (args[1])
   {
     pDir = opendir(args[1]);
     if (pDir == NULL)
     {
       printf ("Cannot open directory '%s'\n", args[1]);
       return 1;
     }
   }
   else
     pDir = opendir(".");
   while ((pDirent = readdir(pDir)) != NULL)
     printf ("[%s] ", pDirent->d_name);
   closedir (pDir);
   printf("\n");
   return 1;
 }

int lsh_export(char **args)
{
  char *key, *data, *p, *word;
  char *delimiter = "=";
  if(args[1] == NULL)
    return 1;
  word = args[1];
  p = strtok(word, delimiter);
  key = malloc((strlen(p)+1)*sizeof(char ));
  strcpy(key, p);
  printf("\n");
  while(p != NULL){
    data = malloc((strlen(p)+1)*sizeof(char *));
    strcpy(data, p);
    p = strtok(NULL, delimiter);
  }
  if(key == data)
    return 1;
  hash_set(ht, key, (void*)data);
  return 1;
}

int lsh_env(char **args)
{
  print_table(ht);
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}

