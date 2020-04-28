#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void typ_prmpt(){
    static int flag=0;
    if(flag==0){                        //for the first time clean the prompt
        const char* clear_promt = "\e[1;1H\e[2J"; //clears the screen(\e:ANSI escape code)
        write(STDOUT_FILENO,clear_promt,12); // here 12 is size of the message of clear_prompt
        flag = 1;
    }
    printf(">>");                       //displaying prompt
}
void rd_cmd(char prm[],char *par[] ){
    char line[1024];
    char *arr[100],*parse;
    int count=0,i=0,j=0;
    // reading the line
    for(;;){
        int a = fgetc(stdin);
        line[count++] = (char) a; 
        if(a=='\n'){
            break;
        }
    }
    if(count==1){
        return;
    }
    parse = strtok(line, " \n");
    //parsing the line into words
    while(parse!=NULL){
        arr[i++] = strdup(parse);
        parse = strtok(NULL," \n");
    }
    strcpy(prm,arr[0]);
    for(j=0;j<i;j++){
        par[j] = arr[j];
        par[i] = NULL;//teminate the list of parameter
    }

}

int main(){
    char cmd[100], command[100], *parameters[20];
    //envir var
    char *env[] = {(char *) "PATH=/bin",0 };
    while(1){                               //infinite loop
        typ_prmpt();                       //displaying prompt on the screen
        rd_cmd(command,parameters);         //
        if(fork()!=0){                      //forking first creats parent with pid for which we do nothing
            continue;
        }
                                            //Child process
        else{
            strcpy(cmd,"/bin/");         
            strcat(cmd,command);          //copying
            execve(cmd,parameters,env);
        }
        if(strcmp(command,"exit")==0){      // for the command exit we are breaking the loop and ending the program
            break;
        }
    }
    return 0;
}