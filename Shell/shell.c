 /*
  * Program by: Gus Temple 
  * CMS 470
  */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

 /*
  * Main loop for shell simulation program
  * Shell is a parent process that has 3 specific command functions, pwd, cd, and exit
  * Every other process is handled by a child process made with fork and executes with execvp
  * 
  * Areas for improvement with more time and resources (mostly time):
  * Break the main function into smaller pieces of about 4 or 5 methods
  * Each method has a specific purpose such as getting input, executing parent functions, forking, etc
  */
int main(void) {

  char input[100];                 // input is limited to 100 chars
  char* buffer;                    // pointer to help tokenize the input
  char* tokens[11];                // string array, stores the tokenized input
  char* command;                   // first token of input, typically is the main command
  char* fileName = "output.txt";   // default file for child processes
  int redirect = 0;                // boolean to handle redirection

  while (1) {
    printf("best shell ever$ ");   // distinct shell name from actual shell

    buffer = fgets(input, sizeof(input), stdin);    // get input from stdin

    //tokenize input to array of pointers to strings
    int i = 0;                         // loop variable
    buffer = strtok(input, " \t\n");   // begin tokenizing input
    while(buffer && i < 10) {    
      
        tokens[i] = buffer; // store each token in the string array that keeps tokens
      
        // special case for redirecting output
        if (strcmp(buffer, ">") == 0) {
          buffer = strtok(NULL, " \t\n");
          fileName = buffer;      // update output file name
          tokens[i] = buffer;     // terminate the tokens array with NULL
          redirect = 1;           // boolean to setup redirection
          break;
        }
      
        i++;                              // increment loop variable
        buffer = strtok(NULL, " \t\n");   // move to the next token
    }
    
    tokens[i] = NULL;    // the last element needs to be NULL

    command = tokens[0]; // assign the first token as the main command

    // exit keyword functionality
    if (strcmp(command, "exit") == 0) {
      break;
    }

    // pwd command functionality
     else if (strcmp(command, "pwd") == 0) {
      buffer = getcwd(input, 100);      // reusing the input variable for pwd
      printf("%s\n", buffer);
    }
  
    // cd command functionality
    else if (strcmp(command, "cd") == 0) {
      if (chdir(tokens[1]) != 0) {
        printf("error changing directory\n");
      }
    }
      
    // fork command functionality
    else {
      int rc = fork();     // split processes
      if (rc == 0) {       // child process goes here

        // change output if the user wants to redirect
        if (redirect) {
          close(1);
          open(fileName , O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        }
        
        // execute whatever command is typed after fork with its list of args, if any
        execvp(tokens[0], tokens);

        // if there is an issue, this executes
        perror("execvp");
        return -1;
        
      } else if (rc > 0) {
        // parent process goes here to wait for the child to be done
        rc = wait(NULL);
      }
    }
    redirect = 0; // reset redirection output boolean to 0
  }
  return 0;
}
