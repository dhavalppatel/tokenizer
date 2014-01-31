/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *addchr(const char *orig, char c);
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {

	char *separators;
	char *stream;

};

typedef struct TokenizerT_ TokenizerT;

/*
 *
 *
 *
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts)
{
	if(strlen(ts) < 1)
	{
		return NULL;
	}

	TokenizerT *temp;
	temp =  malloc(sizeof(TokenizerT));
	temp->separators = (char*)malloc(strlen(separators) * sizeof(char));
	temp->stream = (char*)malloc(strlen(ts) * sizeof(char));
	temp->separators = separators;
	temp->stream = ts;
	return temp;

}


/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

	char foundToken = 'f';
	int counter = 0;

	while(counter < strlen(tk->stream))
	{
		int i;
		for(i = 0 ; i < strlen(tk->separators); i++)
		{

			char currsep = tk->separators[i];
			if( tk->stream[counter] == currsep && foundToken != 'f')
			{
				int size = strlen(tk->stream) - counter;
				int tokenindex = counter + 1;
				char remainder[size];
				strncpy(remainder, tk->stream + tokenindex, size + 1);
				tk->stream = remainder;
				printf("%s\n", token);
				return token;
			
			}else
			{
				//set true
				foundToken = 't';
				char addthis = tk->stream[counter];
				token = addchr(token, addthis);
			}
		}
		//printf("%d\n", counter);
		counter++;

	}

 return 0;
}


char *addchr(const char *orig, char c)
{
    int size = strlen(orig);
    char *str = malloc(size + 2);
    strcpy(str, orig);
    str[size] = c;
    str[size + 1] = '\0';
    return str;
}


/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {


	TokenizerT *start = TKCreate(argv[1], argv[2]);
	if(strcmp(argv[1], "") == 0)
	{
		printf("%s\n", argv[2]);
	}
	if(start == NULL){
		return 1;
	}
	int x = 0;
	while(x < 20)
	{
		//printf("%d", strlen(start->stream));
		char *token = TKGetNextToken(start);
				if(token == NULL)
				{
					x++;
					continue;
				}
				//printf("%s\n", token);
				x++;
	}

	return 0;
}
