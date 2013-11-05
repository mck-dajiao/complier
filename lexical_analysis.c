// a exstremly simple lexical program 
//________________________________________
//
// keywords : begin if then while do end 
//________________________________________
//
// operation symbol and delimiter:
// := + - * / < <= <> > >= = ; #  
//________________________________________
//
// identifier(ID) && int num define:
// ID = letter(letter|digit)*
// NUM = digit digit*
//________________________________________
//
// symbol	typenum symbol	typenum	
// **********************************
// begin	1		:		17
// if		2		:=		18
// then		3		<		20
// while	4		<>		21
// do		5		<=		22
// end		6		>		23
// ID		10		>= 		24
// NUM		11		=		25
// +		13		;		26
// -		14		(		27
// *		15		)		28
// /		16		#		0
//________________________________________ 
//
//INPUT:
//	string of program source code
//OUTPUT:
//	list of binary tuple (syn, token, sum)
//	eg.
//	input:
//	" begin x:=9; if x>0 then x:= 2*x + 1/3; end # "
//	output:
//	(1, begin)(10, 'x')(18, :=)(11, 9)(26, ;)(2, if)...
//_________________________________________
//	
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define end of keyword
#define _KEY_WORD_END "waiting for your expanding"

// define the binary tuple for word
typedef struct{
	int		typenum;
	char*	word;
}WORD;

// input buffer
char input[255];

// word buffer
char token[255] = "";

// pointer for input buffer 
int p_input;

// pointer for word buffer
int p_token; 

// current char
char ch;

// keyword array (can extend when needed)
char* rwtab[] = {"begin", "if", "then", "while", "do", "end", _KEY_WORD_END};

// lexical sanner function
WORD* scaner();

void main(){
	
	int over = 1;
	WORD* oneword = new WORD;
	printf("Enter Your words(end with #))");
	// read the source code into buffer , end with # , multiline is avaliable
	scanf("%[^#]s", input);		
	p_input = 0;
	printf("Your words:\n%s\n",input);
	
	// analysis the source code end with #
	while(over<1000 && over!=-1){

		// get a new word
		oneword = scanner();
		if(oneword->typenum < 1000){
				// print the typenum and word
				printf("(%d, %s)", oneword->typenum, oneword->word);
		}

		over = oneword->typenum;
	}

	printf("\npress # to exit:");
	scanf("%[^#]s", input);
}

// get char from input buffer
char m_getch(){
	ch = input[p_input];
	p_input = p_input + 1;
	return (ch);
}

// split empty symbol
void getbc(){
	while(ch ==' ' || ch == 10){
		ch = input[p_input];
		p_input = p_input + 1;
	}
}

// concat a word
void concat(){
	token[p_token] = ch;
	p_token = p_token + 1;
	token[p_token] = '\0';
}

// letter judge
int letter(){
	if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') return 1;
	else return 0;
}

// digit judge
int digit(){
	if(ch >= '0' && ch <= '9') return 1;
	else return 0;
};

// reserve the keyword table
int reserve(){
	int i = 0;
	while(strcmp(rwtab[i], _KEY_WORD_END)){
		if(!strcmp(rwtab[i], token)){
			return i+1;
		}
		i = i + 1;
	}

	return 10;
}

// rollback a bit
void retract(){
	p_input = p_input - 1;
}

// TODO digit 2 binary
char* dtb(){
	return NULL;
}
