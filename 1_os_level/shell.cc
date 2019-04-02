#include "shell.hh"
using namespace std;

int main(){
	string input;
	char pc[512];
	int filedes;
	if((filedes = syscall(SYS_open, "conf.txt", O_RDONLY)) == -1){
		cout << "Cant open config file.\n";
		return 1;
	}
	string readprompt="";
	while(syscall(SYS_read, filedes, pc, 1) > 0){
		readprompt += pc;
	}
	readprompt.pop_back();
	string prompt = readprompt;
  while(true){
	cout << prompt;              // Print het prompt
    	getline(cin, input);         // Lees een regel
    	if (input == "new_file") new_file();   // Kies de functie
    	else if (input == "ls") list();        //   op basis van
    	else if (input == "src") src();        //   de invoer
    	else if (input == "find") find();
    	else if (input == "python") python();
    	else if (input == "exit") return 0;
    	else if (input == "quit" || "q") return 0;
    	else if (input == "error") return 1;

    	if(cin.eof()){
		return 0; 
  } 
}      // EOF is een exit
}
void new_file(){
	string str_fname;
       	string str_text;
	string answer;
	while(str_fname.empty()){
			cout << "File name:  ";
			getline(cin, str_fname);
	}
	const char * fname = str_fname.c_str();
	if(syscall(SYS_open, fname, O_RDONLY) > 0){
		cout << "File already exists, Do you want to continue?";
		cout << "(y,N): ";
		getline(cin, answer);
		cout << "\n";
	}else{
		answer = "y";
	}
	if(answer == "y"){
		int fd = syscall(SYS_open, fname, O_WRONLY | O_CREAT, mode_t S_IRWXU);
		cout << "Write here your text: \n";
		getline(cin,str_text);
		str_text.append("<EOF>");
		const void * text = str_text.c_str();
		syscall(SYS_write, fd, text, str_text.size());	
	}
}

void list(){ 
	pid_t pid = fork();
	int status;
	if(pid == 0){
		execlp("ls", "ls", "-la", NULL);
	}else{
		wait(NULL);
	}	
}

void find(){ 
	int pid;
	int pip[2];
	int status;
	string str_search;

	cout << "Search: ";
	getline(cin, str_search);
	const char * search = str_search.c_str();

	pipe(pip);
	pid = fork();

	if(pid == 0){
		dup2(pip[1], 1);
		close(pip[0]);
		close(pip[1]);
		execlp("find", "find", ".", NULL);
	}else{
		wait(NULL);
	}
	pid = fork();
	if(pid == 0){
		dup2(pip[0], 0);
		close(pip[0]);
		close(pip[1]);
		execlp("grep", "grep", search, NULL);
	}
	close(pip[0]);
	close(pip[1]);
	wait(NULL);
}

void python(){ 
	pid_t pid = fork();
	if(pid == 0){
		execlp("python", "python", NULL);
	}else{
		wait(NULL);
	}
}

void src(){ 
	int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755);
	char byte[1];
	while(syscall(SYS_read, fd, byte, 1))
		cout << byte;
}
