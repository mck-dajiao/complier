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

// for reading a file
FILE *fp;
FILE *stream;
int flen;
char *p;

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
WORD* scanner();

// read from file
int rFile();

void main(){
	
	int over = 1;
	WORD* oneword = NULL;
	// output stream pointer
	stream = fopen("e:\\newoutput.txt", "w+");
	//WORD* oneword = new WORD;
	printf("Enter Your words(end with #))");
	// read the source code into buffer , end with # , multiline is avaliable
	// scanf("%[^#]s", input);		
	rFile();
	p_input = 0;
	printf("Your words:\n%s\n", p);
	
	// analysis the source code end with #
	while(over<1000 && over!=-1){

		// get a new word
		oneword = scanner();
		if(oneword->typenum < 1000){
				// print the typenum and word
				fprintf(stream, "(%d, %s)\n", oneword->typenum, oneword->word);
		}

		over = oneword->typenum;
	}

	printf("\npress # to exit:");
	scanf("%[^#]s", input);
	fclose(stream);
     	free(p);

}

// get char from input buffer
char m_getch(){
	ch = p[p_input];
	p_input = p_input + 1;
	return (ch);
}

// ignore the empty symbol before a word
void getbc(){
	while(ch ==' ' || ch == 10){
		ch = p[p_input];
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

WORD* scanner(){
	// TODO allocate room for a new WORD
	// allocate char room while need
	WORD* myword = (WORD*)malloc(sizeof(WORD));

	myword->typenum = 10;
	myword->word = "";
	p_token = 0;
	m_getch();
	getbc();

	if(letter()){
		while(letter() || digit()){
			concat();
			m_getch();
		}
		retract();
		myword->typenum = reserve();
		myword->word = token;
		return(myword);
	}else if(digit()){
		while(digit()){
			concat();
			m_getch();
		}
		retract();
		myword->typenum = 11;
		myword->word = token;
		return(myword);
	}else switch(ch){
		case '=' : m_getch();
				   if(ch == '='){
					   myword->typenum = 39;
					   myword->word = "==";
					   return (myword);
				   }
				   retract();
				   myword->typenum = 25;
				   myword->word = "="; 
				   return(myword);
				   break;
		case '+' : myword->typenum = 13;
				   myword->word = "+";
				   return(myword);
				   break;
		case '-' :
				   myword->typenum = 14;
				   myword->word = "=";
			   	   return(myword);	   
			   	   break;
		case '*':
				   myword->typenum = 15;
				   myword->word = "*";
			   	   return(myword);
			   	   break;
		case '/':
				   myword->typenum = 16;
				   myword->word = "/";
			       	   return(myword);
			   	   break;
	
		case '(':
				   myword->typenum = 27;
				   myword->word = "(";
				   return(myword);
				   break;
		case ')':
				   myword->typenum = 28;
				   myword->word = ")";
				   return(myword);
				   break;
				   //TODO
		case '[':
				   myword->typenum = 30;
				   myword->word = "[";
				   return(myword);
				   break;
				   //TODO
		case ']':
				   myword->typenum = 31;
				   myword->word = "]";
				   return(myword);
				   break;
				   //TODO
		case '{':
				   myword->typenum = 32;
				   myword->word = "{";
				   return(myword);
				   break;
				   //TODO
		case '}':
				   myword->typenum = 33;
				   myword->word = "}";
				   return(myword);
				   break;
				   //TODO
		case ',':
				   myword->typenum = 34;
				   myword->word = ",";
				   return(myword);
				   break;
		case ':':
				   m_getch();
				   if(ch == '='){
				   	myword->typenum = 18;
					myword->word = ":=";
					return (myword);
				   }
				   retract();
				   myword->typenum = 17;
				   myword->word = ":";
				   return(myword);
				   break;
		case ';':
				   myword->typenum = 26;
				   myword->word = ";";
				   return(myword);
				   break;
		case '>':
				   m_getch();
				   if(ch == '='){
					   myword->typenum = 24;
					   myword->word = ">=";
					   return(myword);
				   }
				   retract();
				   myword->typenum = 23;
				   myword->word = ">";
				   return(myword);
				   break;
		case '<':
				   m_getch();
				   if(ch == '='){
					   myword->typenum = 22;
					   myword->word = "<=";
					   return(myword);
				   }else if(ch == '>'){
					   myword->typenum = 21;
					   myword->word = "<>";
					   return(myword);
				   }
				   retract();
				   myword->typenum = 20;
				   myword->word = "<";
				   return(myword);
				   break;
		case '!':
				   m_getch();
				   if(ch == '='){
					   myword->typenum = 40;
					   myword->word = "<";
					   return(myword);
				   }
				   retract();
				   myword->typenum = -1;
				   myword->word = "ERROR";
				   return(myword);
				   break;
		case '\0':
				   myword->typenum = 1000;
				   myword->word = "OVER";
				   return(myword);
				   break;
		case '#':	
				   myword->typenum = 0;
				   myword->word = "#";
				   return(myword);
		default:
				   myword->typenum = -1;
				   myword->word = "ERROR";
				   return(myword);
				   break;
		
	}

}

int rFile(){    
    int i;
    
    printf("read success!");
    if((fp = fopen ("e:\\test.txt","r"))==NULL)
    {
        printf("\nfile open error\n");
        exit(0);
    }
    fseek(fp,0L,SEEK_END); 
    flen=ftell(fp); 
    p=(char *)malloc(flen); 
    if(p==NULL){
        fclose(fp);
        return 0;
    }
    fseek(fp,0L,SEEK_SET); 

    fread(p,flen,1,fp); 

    for(i = 0; i < flen; i++){
		if(p[i] == '\n'){
			p[i] = ' ';
		}else if(p[i] == '/' && p[i+1] == '/'){
			while(p[i+2] != '\n'){
				p[i] = ' ';
				i++;
			}
			p[i] = p[i+1] = ' ';
		}
    }

    p[flen-1]= '\0'; 
	for(i = 0; i< flen; i++){
		printf("%c", p[i]);
	}
    //printf("%s",p);
    fclose(fp);
    getch();
    return 0;
}

