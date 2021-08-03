#include <stdio.h>
#include <stdlib.h>

char *ex; //postfix expression
int len; //length of ex
int count = 1; //TEMP variable count

//print commands to stdout
void print(char str[3], char c){
	if ((c-'0') < 10 && (c-'0') > 0){ //if c is a TEMP varible
		printf("%s TEMP%c\n", str, c);
		return;
	} 
	printf("%s %c\n", str, c); //if c is a normal variable
}

//pops ith element from ex and returns it
char pop(int i){
	char c = ex[i]; //get ith element
	while(i<len){
		ex[i] = ex[i+1]; //bring every element one index backwards
		i++;
	}
	--len; //reduce length of ex
	realloc(ex, sizeof(char)*len); //reallocate memory for ex
	return c; //return ith element
}

//perform necessary operaions on ex
void operation(char str[3], int i){
	print("LD", pop(i-2)); //print Load command
	print(str, pop(i-2)); //print matching operator command
	ex[i-2] = count + '0'; //replace element with current TEMP varible
	print("ST", (count++) + '0'); //print Store TEMPn command
}

//loop through ex and finds '+, -, *, /' operators
void printMachineCodes(){
	for (int i=0; i<len; i++){ // i = from 0 to len
		if (ex[i] == '+') {operation("AD", i); i-=2;}
		else if (ex[i] == '-') {operation("SB", i); i-=2;}
		else if (ex[i] == '*') {operation("ML", i); i-=2;}
		else if (ex[i] == '/') {operation("DV", i); i-=2;}
		else continue;
	}
}


//driver function
int main(){
	//get the lenth of the expression from stdin
	printf("Enter length of postfix expression : ");
	scanf("%d", &len);
	
	//allocate memory for ex with length = len
	ex = (char *)malloc(sizeof(char)*len);
	
	//get the expression from stdin
	printf("Enter postfix expression : ");
	scanf("%s", ex);
	
	//execute function
	printMachineCodes();
	return 0;
}

