/*
 *  a simple grammar parser 
 *  Date:		2013/11/13
 *  */

#include <stdio.h>
#include <malloc.h>

char *line = NULL;
char *word = NULL;
int syn = 0;
int i, j, k = 0;
int kk = 0;
FILE * file = NULL;
int flag = 1;
int endFlag = 0;

// function define
void scaner();
void statement();
void expression();
void term();
void factor();
void yucu();


void scaner(){
	int temp = 0;

	word = (char *)malloc(sizeof(char)*26);

	if(fgets(line, 29, file) == NULL){
		printf("end of file");
		flag = 0;
	}

	// get the syn number
	
	 
	i = 1;
	syn = 0;
	while(line[i] != ',' && i <= 10){
		temp = line[i] - 48;	
		syn = syn * 10 + temp;
		i++;
	}

	// get the word
	
	i += 2;
	j = 0;
	while(line[i] != ')' && j <= 26){
		word[j] = line[i];
		i++;
		j++;
	}
	word[j] = '\0';
}

void errorHandler(){

	if(!endFlag) printf("%s", line);

	if(syn==10) {
		printf("yucu error");
		kk = 1;
	}

	if(syn==6 && !endFlag){
	    printf("yucu error");
		kk = 1;
	}

	while(!(syn==26 || syn==6)){
		scaner();
	}

	if(syn==6 && endFlag) {
		kk = 1;
		return;
	}
	scaner();

	statement();
}


void statement(){

	if(syn == 10){

		scaner();
		if(syn == 18){

			scaner();
			expression();
		}else{
			printf("expression error");
			kk = 1;
			errorHandler();
		}

	}else if(syn == 6){
		return ;
	}else{
		printf("statement error");
		kk = 1;
		errorHandler();
	}
}

void expression(){

	term();
	while(syn == 13 || syn == 14){
		scaner();
		term();
	}
	return ;
}

void term(){

	factor();
	while(syn == 15 || syn == 16){
		scaner();
		factor();
	}

	return ; 
}

void factor(){
	
	if(syn == 10 || syn == 11){
		scaner();
		return ;
	}else if(syn == 27){
		scaner();
		expression();

		if(syn == 28){
			scaner();
		}else{
			printf(") error");
			kk = 1;
			errorHandler();
		}

	}else{
		printf("factor expression error");
		kk = 1;
		errorHandler();

	}	

	return ;

}

void yucu(){

	statement();
	while(syn == 26){
		scaner();
		statement();
	}

	endFlag = 1;
	errorHandler();

	return ;
}

void lyparser(){
	if(syn == 1){
		scaner();
		yucu();

		if(syn == 6){

			scaner();
			if(syn == 0 && kk == 0) printf("success");

		}else {
			if(kk!=1) printf("lack of end");
			kk = 1;
		}

	}else{
		printf("error with begin");
		kk = 1;
		yucu();
	}

	return ;

}

 void main(){

	if((file = fopen("e:\\newoutput.txt", "r"))==NULL){
		printf("Can't open file");
		exit(0);
	}

	line = (char*)malloc(sizeof(char)*30);

	scaner();

	lyparser();

}
