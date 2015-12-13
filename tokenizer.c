#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


struct TokenizerT_ { /*tokenizer struct holds the input string and two indexes, start and end which are the beginning and the end of tokens*/ 
	char *stoken;
    int start;
    int end;
};

typedef struct TokenizerT_ TokenizerT;


TokenizerT *TKCreate( char * ts ) {
	if(ts == NULL){
		printf("ERROR: NULL STRING"); /*return error if there is no input string*/
	}else{
		struct TokenizerT_ *tokenizer_t = malloc(sizeof(struct TokenizerT_)); /*allocate space for the tokenizer struct*/
		tokenizer_t->stoken = ts; /*tokenizer string is the input string*/
		tokenizer_t->start = 0; /*start begins at the beggining of the input string, which at creation of tokenizer is 0*/
		tokenizer_t->end = 0; /*end will not be specified until getnexttoken so for now it is 0*/
		return tokenizer_t;
	}

  return NULL;
}


void TKDestroy( TokenizerT * tk ) { /*Frees Tokenizer Struct*/
	 if(tk != NULL){
        free(tk);
    }
}

char *getmytype(char * ts){ /*getmytype returns the name of type of the token, so word, octal, hex etc, or the specific type of puntutation*/
	if(isalpha(ts[0])){
		return "word"; 
	}
	if(ispunct(ts[0])){
		char *tokenp = ts; /*create a new string to hold just the token*/
		if(strcmp(tokenp,"{") == 0){ /*checks all types of punctuation and returns type*/
			return "left brace";
		}else if(strcmp(tokenp,"}") == 0){
			return "right brace";
		}else if(strcmp(tokenp,"(") == 0){
			return "left parenthesis";
		}else if(strcmp(tokenp,")") == 0){
			return "right parenthesis";
		}else if(strcmp(tokenp,".") == 0){
			return "period";
		}else if(strcmp(tokenp,"?") == 0){
			return "question mark";
		}else if(strcmp(tokenp, "$") == 0){
			return "dollar sign";	
		}else if(strcmp(tokenp, "->") == 0){
			return "structure pointer";	
		}else if(strcmp(tokenp, "&&") == 0){
			return "logical and";	
		}else if(strcmp(tokenp, "||") == 0){
			return "logical or";
		}else if(strcmp(tokenp, "++") == 0){
			return "increment";	
		}else if(strcmp(tokenp, "--") == 0){
			return "decrement";		
		}else if(strcmp(tokenp, "-") == 0){
			return "minus";	
		}else if(strcmp(tokenp, "+") == 0){
			return "plus";	
		}else if(strcmp(tokenp, "[") == 0){
			return "left brace";	
		}else if(strcmp(tokenp, "]") == 0){
			return "right brace";	
		}else if(strcmp(tokenp, "<<") == 0){
			return "left shift";
		}else if(strcmp(tokenp, ">>") == 0){
			return "right shift";	
		}else if(strcmp(tokenp, "==") == 0){
			return "equal";
		}else if(strcmp(tokenp, "&") == 0){
			return "address";
		}else if(strcmp(tokenp, "*") == 0){
			return "multiply";
		}else if(strcmp(tokenp, "!=") == 0){
			return "equal";
		}else if(strcmp(tokenp, "~") == 0){
			return "1s  complement";
		}else if(strcmp(tokenp, "<=") == 0){
			return "less than or equal";
		}else if(strcmp(tokenp, ">=") == 0){
			return "greater than or equal";
		}else if(strcmp(tokenp, "/") == 0){
			return "divide";
		}else if(strcmp(tokenp, "<") == 0){
			return "less than";
		}else if(strcmp(tokenp, ">") == 0){
			return "greater than";
		}else if(strcmp(tokenp, "+=") == 0){
			return "plus equals";
		}else if(strcmp(tokenp, "\"") == 0){
			return "quotation mark";
		}else if(strcmp(tokenp, "%%") == 0){
			return "modulos";
		}else if(strcmp(tokenp, ";") == 0){
			return "semicolon";
		}else if(strcmp(tokenp, ":") == 0){
			return "colon";
		}else if(strcmp(tokenp, "~") == 0){
			return "1's complement";
		}else if(strcmp(tokenp, "'") == 0){
			return "apostrophe";
		}else if(strcmp(tokenp, "#") == 0){
			return "hash";
		}else if(strcmp(tokenp, "^") == 0){
			return "bitwise exclusive or";
		}else if(strcmp(tokenp, ",") == 0){
			return "commma";
		}else{
		return "punctuation";
	}	
	}if(isdigit(ts[0])){
		int countdecimal = 0; /*counts the number of . in the token*/
		int countx = 0; /*counts the number x's in the token*/
		int counte = 0; /*counts the number of e's in the token*/
		int countminus = 0; /*counts the number of minuses in the token*/
		int countplus = 0; /*counts the number of pluses in the token*/
		int amioctal = 0; /*counts how many digits in the token are 0 - 8 */
		int i = 0;/*index*/
		for(; i < strlen(ts);i++){
			if(ts[i] == '.'){
				countdecimal++; /*if decimal increase count*/
				if(ts[i+1] == '\0'){
					return "malformed floating point number";
				}if(ts[i+1] == 'e' || ts[i+1] == '+' || ts[i+1] == '-'){ /*checks to see that e,+,- is not last character in token*/
					return "malformed floating point number";
				}
			}else if(ts[i] == 'x' || ts[i] == 'X'){ /*if x increase countx*/
							countx++;
							if(ts[i+1] == '\0'){ /*checks to see that x is not last character in token*/
					return "malformed hexadecimal number";
				}else{
					continue;
				}
			}else if(ts[i] == '+'){ /*if plus increase countplus*/
				countplus++;
				if(ts[i+1] == '\0'){ /*checks to see that plus is not last character in token*/
					return "malformed floating point number";
				}else{
					continue;
				}
			}else if(ts[i] == 'e'){ /*if e increase counte*/
				counte++;
				if(ts[i+1] == '\0'){ /*if the token after is the end of the string, this is a malformed floating point number*/
					return "malformed floating point number";
				}else{
					continue;
				}
			}else if(ts[i] > 8 || ts[i] == 8){ /*if the digit is between 0 and 8, icrease the number of octal numbers in string*/
				amioctal++;
			}else if(ts[i] == '-'){ /*if minus increase countminus*/
				countminus++;
			}else{
				continue;
			}
		}
		if((counte == 1 && countdecimal == 0) || (counte == 0 && countplus > 0 ) || (counte == 0 && countminus > 0) || (countdecimal == 0 && countplus > 0) || (countdecimal == 0 && countminus > 0)){
			return "malformed floating point number";
		}if(countx == 1 && ts[0] != '0' && ts[1] != 'x'){
			return "malformed hex constant"; 
		}
		if(countdecimal > 1){ /*if the number of decimal points in the token is greater than one, this is a malformed decimal number*/
			return "malformed decimal number";
		}if(countx > 1){ /*if the number of x's is greater than one, this is a malformed hex number*/
			return "malformed hex number";
		}if(counte > 1){ /*if the number of e's in the token is greater than one, this is a malformed floating point number*/
			return "malformed floating point number";
		}if((countplus == 1 && countminus == 1) || countplus > 1 || countminus > 1){ /*if there is more than one plus, or more than one minus, or pluses and minuses, then this is a malformed floating point number*/
			return "malformed floating point number";
		}if((countdecimal == 1 && counte == 1 && countplus == 1) || (countdecimal == 1 && counte == 1 && countminus == 1) || countdecimal == 1){ /*if there is one e, one decimal, one minus/plus, or one decimal this is a floating point number*/
			return "floating point number";
		}if(ts[0] == '0' && ts[1] == 'x'){ /*if the first character is a zero and the second character is an x, then this is a hex constant*/
			return "hex constant";
		}if(ts[0] == '0' && amioctal == strlen(ts)){ /*if all the charcters are between 0 and 8 and the first digit is 0, this is an octal constant*/
			return "octal constant";
		}else{
			return "integer"; /*if none of the above apply, this is just a string of digits*/
		}
	}else{
		return "not valid type"; /*if token does not fall under one of the above punctuation, word or digits, than it is not a valid type*/
	}


}

char *TKGetNextToken( TokenizerT * tk ){
	if(tk == NULL){
        printf("ERROR: RECEIVED NULL TOKENIZER");
    }
	int current = tk->start;
	if(isspace(tk->stoken[current])){
		current = current +1;
		tk->start = current;
	}
	while(!isspace(tk->stoken[current])){
/* ALPHABET METHOD THIS GETS WORD TOKENS SEPARATED BY WHITE SPACE OR NON-ALPHABETIC CHARACTERS***************/
		if(isalpha(tk->stoken[current])){ /*if the current character is alpha*/
			while(isalpha(tk->stoken[current]) || isdigit(tk->stoken[current])){ /*while the tokens after it are still alpha, continue moving pointer*/
				current = current + 1;
			}
			tk->end = current - 1; /*characters are no longer alpha, end of the word is one before current*/
			char *newToken;
			newToken = (char*)malloc(current - tk->start);
			strncpy(newToken,tk->stoken+tk->start,(current - tk->start)); /*insert the token into new char array*/
			if(isspace(tk->stoken[current])){ /*if the character after the word is space, move the pointer beyond the whitespace*/
				tk->start = current + 1;
				return newToken;
			}else{
				tk->start = current; /*if the character after the word is not space, the next token begins at current*/
				return newToken;
			}
/* END OF ALPHABET METHOD ***********************************************************************************/
/*BEGIN PUNCTUATION IF STATEMENT CREATES PUNCTUATION OR OPERATOR TOKENS SEPARATED BY ANY OTHER TOKEN OR WHITE SPACE******/
		}else if(ispunct(tk->stoken[current])) { /*if the character at current is punctuation or operator*/
			char *mytokenone; /*create string to hold substring*/
			mytokenone = (char*)malloc(2);
			strncpy(mytokenone,tk->stoken+current,2); /*copy two characters out of the string*/
			char *newToken; /*create string, new token to return*/
			if(strcmp(mytokenone,"<<") == 0 || strcmp(mytokenone, ">>") == 0 || strcmp(mytokenone, "++") == 0 || strcmp(mytokenone, "+=") == 0 
			|| strcmp(mytokenone, "==") == 0 || strcmp(mytokenone, "!=") == 0 || strcmp(mytokenone, "&&") == 0 || strcmp(mytokenone, "||") == 0
			|| strcmp(mytokenone, ">=") == 0 || strcmp(mytokenone, "<=") == 0 || strcmp(mytokenone, "--") == 0 || strcmp(mytokenone, "->") == 0){
				newToken = (char*)malloc(4); /*check if the substring of length 2 contains any of the punctuation that have length 2*/
				strncpy(newToken,tk->stoken+current, 2); /*if it is a punctuation of length 2 create a new token with the punctuation*/
				if(isspace(tk->stoken[current+3])){ /*if there is a space after the token, move the current index past the space and reset start*/
					current = current + 3;
					tk->start = current;
					return newToken;
				}else{
					current = current + 2; /*if there is no space after the token, move current index to the next token and reset start*/
					tk->start = current;
					return newToken;
				}

			}else{
				newToken = (char*)malloc(1); /*if the punctuation is of length 1*/
				strncpy(newToken,tk->stoken+current,1); /*put punctuation into new string and returns the token*/
				if(isspace(tk->stoken[current+1])){ /*if the character after the token is a space, move the current index past the space*/
					current = current + 2;
					tk->start = current; /*reset start to current index*/
					return newToken;
				}else{
					current = current + 1; /*if the next character is not a space, move the current index to the next token*/ 
					tk->start = current;
					return newToken;
				}
			}
			/* USE \"hello\" TO USE CHARACTERS FOR " */
		
/*END OF PUNCTUATION IF-STATEMENT******************************************************************************/
/*START OF OCTAL,HEX, DECIMAL,FLOATING POINT CONSTANT***********************************************************/
		}if(isdigit(tk->stoken[current])){
			while(isdigit(tk->stoken[current]) || tk->stoken[current] == '.' || tk-> stoken[current] == 'e' || tk->stoken[current] == '-' || tk->stoken[current] == '+' || tk->stoken[current] == 'x' || tk->stoken[current] == 'X'
				|| tk->stoken[current] == 'a' || tk->stoken[current] == 'b' || tk->stoken[current] == 'c' || tk->stoken[current] == 'd' || tk->stoken[current] == 'e'
				|| tk->stoken[current] == 'f' || tk->stoken[current] == 'A' || tk->stoken[current] == 'B' || tk->stoken[current] == 'C' || tk->stoken[current] == 'D'
				|| tk->stoken[current] == 'E' || tk->stoken[current] == 'F'){
				current = current + 1;
			}
			
			tk->end = current - 1; /*characters are no longer alpha, end of the word is one before current*/
			char *newToken;
			newToken = (char*)malloc(current - tk->start);
			strncpy(newToken,tk->stoken+tk->start,(current - tk->start)); /*insert the token into new char array*/
			if(isspace(tk->stoken[current])){ /*if the character after the word is `space, move the pointer beyond the whitespace*/
				tk->start = current + 1;
				return newToken;
			}else{
				tk->start = current; /*if the character after the word is not space, the next token begins at current*/
				return newToken;
			}
		}else{ 
			current = current + 1;

		}
	}
	char* invalidtoken = "INVALID CHARACTERS";
			return invalidtoken;
}

int main(int argc, char **argv) {
   struct TokenizerT_ *tokens = TKCreate(argv[1]); /*create struct, with command line arguement as string*/
   int index = tokens->start; /*create an index that will keep track of where the tokenizer is in the string*/
   if(tokens->stoken[0] == '\0'){ /*if user has inserted an empty string, print out error message and return*/
   	printf("ERROR: CANNOT HAVE NULL TOKENIZER STRING\n");
   	return 0;
   }
   printf("Tokenizer \"%s\"\n",tokens->stoken); /*print out the full string of tokens*/
   while(index < strlen(argv[1])){ /*while we have not reached the end of the string*/
   	 char *singletoken = TKGetNextToken(tokens); /*continue to get new tokens*/
   	 char *type = getmytype(singletoken); /*identify the type of token*/
   	 printf("%s \"%s\"\n", type,singletoken); /*print out token and its type*/
   	 index = tokens->start;/*move the index*/
   }
  TKDestroy(tokens); /*free the space allocated for the the tokenizer*/
    return 0;
}