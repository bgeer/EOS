#include <iostream>
#include <string>
using namespace std;

int translate(char variabele, string input){
	int count = 0;
	for(unsigned int i = 0; i < input.size();i++){
		if(input[i] == variabele){
			count++;
		}
	}
return count; 
}

int main(int argc, char *argv[]){
       	string s;

  	if(argc != 2){
		cerr << "Deze functie heeft exact 1 argument nodig";
    		return -1; 
	}

  	while(true){
	       	cin >> s;
    		if(cin.eof()){ return 0; }
    		cout << translate(argv[1][0], s) << endl; } }
