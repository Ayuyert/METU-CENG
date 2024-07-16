#include <stdio.h>
#include "parser.h"


char* satiroku(){
	printf("/> ");
	int i = 0;
	int size = 5;
	char k; 
	char* alan = (char*) malloc(size*sizeof(char));
	while(1){
		k = getchar();
		if(k== '\n' || k == EOF) break;
		alan[i] = k;
		if(i == size -1){
			size *=2;
			alan = (char*) realloc(alan, size*sizeof(char));
		}
		i++;
	}

	alan = (char*) realloc(alan, (i)*sizeof(char));
	alan[i] = '\0';
	return alan;
	
}



void commex(command *com){
	if(!fork()){ //Child
		execvp(com->args[0],com->args);
		exit(0);
	}
	else{
		int status,pid;
		waitpid(0,&status,0);
	
	}
}

void commex2(command *com){
	if(!fork()){ //Child
		execvp(com->args[0],com->args);
		exit(0);
	}

}


void pipex3(pipeline *pipl){
	int fd[MAX_INPUTS][2];
	for(int i=0; i<(pipl->num_commands); i++) pipe(fd[i]);
	for(int i=0; i<(pipl->num_commands); i++){
		
		if(!fork()){
			if(i==0){
				dup2(fd[0][1],1);
				close(fd[i][0]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);
			}
			else if(i>0 && i<(pipl->num_commands)-1){
				dup2(fd[i-1][0],0);
				dup2(fd[i][1],1);
				close(fd[i][0]);
                		close(fd[i-1][1]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);
				
			}
			else{
				dup2(fd[i-1][0],0);
				close(fd[i-1][1]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);	
			}
			exit(0);
		
		}
		
		else{
			
			close(fd[i][1]);
			if (i > 0) close(fd[i - 1][0]);
		
		}
	
	}


}




void pipex2(pipeline *pipl){
	
	int fd[MAX_INPUTS][2];
	for(int i=0; i<(pipl->num_commands); i++) pipe(fd[i]);
	for(int i=0; i<(pipl->num_commands); i++){
		
		if(!fork()){
			if(i==0){
				dup2(fd[0][1],1);
				close(fd[i][0]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);
			}
			else if(i>0 && i<(pipl->num_commands)-1){
				dup2(fd[i-1][0],0);
				dup2(fd[i][1],1);
				close(fd[i][0]);
                		close(fd[i-1][1]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);
				
			}
			else{
				dup2(fd[i-1][0],0);
				close(fd[i-1][1]);
				execvp(pipl->commands[i].args[0],pipl->commands[i].args);	
			}
			exit(0);
		
		}
		
		else{
			for (int i = 0; i < (pipl->num_commands); i++) {
        					wait(NULL);
    					}
			close(fd[i][1]);
			if (i > 0) close(fd[i - 1][0]);
		
		}
	
	}


}



void pipex(parsed_input *inp) {
    int fd[MAX_INPUTS][2];

    for (int i = 0; i < inp->num_inputs; i++) pipe(fd[i]);
    for (int i = 0; i < inp->num_inputs; i++) {
        if (!fork()) {
            if (inp->inputs[i].type == INPUT_TYPE_SUBSHELL) {
                if (i == 0) { // Sadece inputu bağla
                    dup2(fd[0][1], 1);
                    close(fd[i][0]);
                } 
				else if (i > 0 && i < (inp->num_inputs) - 1) {
                    dup2(fd[i - 1][0], 0);
                    dup2(fd[i][1], 1);
                    close(fd[i][0]);
                    close(fd[i - 1][1]);
                } 
				else {
                    dup2(fd[i - 1][0], 0);
                    close(fd[i - 1][1]);
                }

                int child_pid, wpid;
                int status;
                char *subline = inp->inputs[i].data.subshell;
                parsed_input *subinput = malloc(sizeof(parsed_input));
                int hata = parse_line(subline, subinput);
                if (!hata) return;
                int pid[MAX_INPUTS];
                int fd2[MAX_INPUTS][2];

                if (!(wpid = fork())) { // Child
                    switch (subinput->separator) {

                        case SEPARATOR_NONE:
                            seqex(subinput);
                            break;
                        case SEPARATOR_SEQ:
                            seqex(subinput);
                            break;
                        case SEPARATOR_PARA:

                            for (int com = 0; com < subinput->num_inputs; com++) {

                                pipe(fd2[com]);
                                if (!(pid[com] = fork())) {
                                    dup2(fd2[com][0], 0);
                                    close(fd2[com][0]);
                                    close(fd2[com][1]);
                                    if (subinput->inputs[com].type == INPUT_TYPE_COMMAND) execvp(subinput->inputs[com].data.cmd.args[0], subinput->inputs[com].data.cmd.args);
                                    else if (subinput->inputs[com].type == INPUT_TYPE_PIPELINE) pipex2(&subinput->inputs[com].data.pline);
                                    exit(0);
                                } else {
                                    close(fd2[com][0]);
                                }
                            }
                            if (!fork()) {
                                char buffer[INPUT_BUFFER_SIZE];
                                size_t bytes_read;

                                while ((bytes_read = read(0, buffer, INPUT_BUFFER_SIZE)) > 0) {
                                    for (int u = 0; u < subinput->num_inputs; u++) {
                                        write(fd2[u][1], buffer, bytes_read);
                                    }
                                }
                                for (int r = 0; r < subinput->num_inputs; r++) {
                                    close(fd2[r][1]);
                                }
                                exit(0);
                            }
                            for (int r = 0; r < subinput->num_inputs; r++) {
                                close(fd2[r][1]);
                            }
                            break;
                        case SEPARATOR_PIPE:
                            pipex(subinput);
                            break;
                    }
                    exit(0);
                } else {
                    int s2;
                    waitpid(wpid, &s2, 0);
                    for (int i = 0; i < inp->num_inputs; i++) {
                        int status;
                        waitpid(pid[i], &status, 0);
                    }
                }
            }

            if (inp->inputs[i].type == INPUT_TYPE_COMMAND) { // Child
                if (i == 0) { //Sadece inputu bağla
                    dup2(fd[0][1], 1);
                    close(fd[i][0]);
                    execvp(inp->inputs[i].data.cmd.args[0], inp->inputs[i].data.cmd.args);
                } else if (i > 0 && i < (inp->num_inputs) - 1) {
                    dup2(fd[i - 1][0], 0);
                    dup2(fd[i][1], 1);
                    close(fd[i][0]);
                    close(fd[i - 1][1]);
                    execvp(inp->inputs[i].data.cmd.args[0], inp->inputs[i].data.cmd.args);
                } else {
                    dup2(fd[i - 1][0], 0);
                    close(fd[i - 1][1]);
                    execvp(inp->inputs[i].data.cmd.args[0], inp->inputs[i].data.cmd.args);
                }
            }

            exit(0);
        } else {
            for (int i = 0; i < inp->num_inputs; i++) {
                wait(NULL);
            }
            close(fd[i][1]);
            if (i > 0) close(fd[i - 1][0]);
        }
    }
}


void seqex(parsed_input *inp){
	
	for(int i=0; i<(inp->num_inputs); i++){
		if(inp->inputs[i].type == INPUT_TYPE_SUBSHELL){
			int child_pid, wpid;
			int status = 0;
			if(!fork()){ //Child
				char* subline = inp->inputs[i].data.subshell;
				parsed_input* subinput = malloc(sizeof(parsed_input));
				int hata = parse_line(subline, subinput);
				if(!hata) return;
				//pretty_print(subinput);
				
				switch (subinput->separator){
		
					case SEPARATOR_NONE:
						seqex(subinput);
						break;
					case SEPARATOR_SEQ:
						seqex(subinput);
						break;
					case SEPARATOR_PARA:
						parallex(subinput);
						break;
					case SEPARATOR_PIPE:
						pipex(subinput);
						break;
				}
				exit(0);
				
			}
				else{	
					for (int i = 0; i < (inp->num_inputs); i++) {
        					wait(NULL);
    					}
    					
    				}
			
		}
		else if(inp->inputs[i].type == INPUT_TYPE_COMMAND){
			commex(&inp->inputs[i].data.cmd);
			}
		else if(inp->inputs[i].type == INPUT_TYPE_PIPELINE) {pipex2(&inp->inputs[i].data.pline);
			}
	}
}


void parallex(parsed_input *inp){
	for(int i=0; i<(inp->num_inputs); i++){
		if(inp->inputs[i].type == INPUT_TYPE_COMMAND){
			commex2(&inp->inputs[i].data.cmd);
			}
		else if(inp->inputs[i].type == INPUT_TYPE_PIPELINE) {pipex3(&inp->inputs[i].data.pline);
			}
	}
	for (int i = 0; i < (inp->num_inputs); i++) {
        wait(NULL);
    	}
	
	
}
int main(){
	parsed_input* input = malloc(sizeof(parsed_input));
	while(1){
		
		char* line = satiroku();//satırı oku
		if(line[0] =='q' && line[1] =='u' &&line[2] =='i' &&line[3] =='t'  && line[4] == '\0') {
		return 0;
		}
		int a = parse_line(line,input);
		//pretty_print(input);
		if(a == 0) break;
		switch (input->separator){
		
			case SEPARATOR_NONE:
				seqex(input);
				break;
			case SEPARATOR_SEQ:
				seqex(input);
				break;
			case SEPARATOR_PARA:
				parallex(input);
				break;
			case SEPARATOR_PIPE:
				pipex(input);
				break;
		}
		free_parsed_input(input);
		line = NULL;
	}
	
	
	return 0;
}
