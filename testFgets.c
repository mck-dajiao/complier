#include "stdio.h"
#include "malloc.h"

char *line = NULL;
char *word = NULL;
int syn = 0;
int i, j;
FILE * file = NULL;
int flag = 1;


void scaner(){
	int temp = 0;

	word = (char *)malloc(sizeof(char)*26);

	if(fgets(line, 29, file) == NULL){
		printf("end of file");
		flag = 0;
	}

	// get the syn number
	
	printf("%s", line);
	 
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

void main(){
	
	int i = 0;

	line = (char*)malloc(sizeof(char)*30);
	
	file = fopen("e://output.txt", "r");

	while(flag != 0){

		scaner();
		printf(" %d %s", syn, word);
		i++;
	}

	printf("%d", i);

	fclose(file);
}
