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
// symbol	code	symbol	code	
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


