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
			cout << "Bestand naam: ";
			getline(cin, str_fname);
	}
	const char * fname = str_fname.c_str();
	if(syscall(SYS_open, fname, O_RDONLY > 0)){
		cout << "File already exists, Do you want to continue?";
		cout << "(y,N): ";
		getline(cin, answer);
		cout << "\n";
	}else{
		answer = "y";
	}
	if(answer == "y"){

	}
	cout << "ToDo: Implementeer hier new_file()" << endl; 
}

void list(){ 
	cout << "ToDo: Implementeer hier list()" << endl; 
}

void find(){ 
	cout << "ToDo: Implementeer hier find()" << endl; 
}

void python(){ 
	cout << "ToDo: Implementeer hier python()" << endl; 
}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ 
	int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
	char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijg									t (leesbaar is).
  	while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gel									ezen is,
    		cout << byte;
}                                  				//   zet de gelezen byte in "byte" zodat deze geschre									ven kan worden.
