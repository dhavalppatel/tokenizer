/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *addchr( char *orig, char c);
char *checkEscChar(char *token);
char* replaceEscChar(char *token, int index, char *hex);

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

//Tokenizer struct with separators and stream.
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

//If the stream is inputed is empty then return NULL
	if(strlen(ts) < 1)
	{
		return NULL;
	}

//Creates tokenizer object. Malloc the object, the stream string and the separators string
	TokenizerT *temp;
	temp =  malloc(sizeof(TokenizerT));
	temp->separators = (char*)malloc(sizeof(char)*(strlen(separators)));;
	temp->stream = (char*)malloc(sizeof(char)*(strlen(ts)));;
//Copy the input arguments into struct
	strcpy(temp->separators, separators);
	strcpy(temp->stream, ts);

	return temp;

}

//Adds a single character to the end of a string and returns the new string.
char *addchr(char *orig, char c)
{
//Malloc original size + 2: for the single character and the null terminator
    int size = strlen(orig);
    char *str = malloc(size + 2);
    strcpy(str, orig);
    str[size] = c;
    str[size + 1] = '\0';
    return str;
}

//A helper method to replace the escape character into the appropriate hex number
char* replaceEscChar(char *token, int index, char *hex)
{
	char *ret = (char*)malloc(sizeof(char)*(strlen(token)+strlen(hex))-1);
	strncpy(ret, token, index);
	ret[index] = '\0';
	strcat(ret, hex);

	if(c != 'n')
	strcat(ret, token+index+2);
	else
	strcat(ret, token+index+1);

	return ret;
}

//Given a token, this method checks if there's a escape character and calls a helper method to replace the hex
//Checks for a \ with a special character, if there is no special esc chars, then the \ is removed
char *checkEscChar(char *token)
{
	int size = strlen(token);
	char *hex;
    int index=0;

    while(index <= size)
	{

//Checks for the special escape characters and
//if its none of the special characters, the \ is removed. A modified token is returned.
		if(token[index] == '\\' && token[index+1] == 'n'){

			hex = "[0x0a]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
		}
		else if(token[index] == '\\' && token[index+1] == 't'){
			hex = "[0x09]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
					}
		else if(token[index] == '\\' && token[index+1] == 'v'){
			hex = "[0x0b]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
					}
		else if(token[index] == '\\' && token[index+1] == 'b'){
			hex = "[0x08]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
					}
		else if(token[index] == '\\' && token[index+1] == 'r'){
			hex = "[0x0d]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
					}
		else if(token[index] == '\\' && token[index+1] == 'f'){
			hex = "[0x0c]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
					}
		else if(token[index] == '\\' && token[index+1] == '\"' ){
			hex = "[0x22]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
				}
		else if(token[index] == '\\' && token[index+1] == 'a'){
			hex = "[0x07]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
		}
		else if(token[index] == '\\'){

			if(token[index+1] == '\\'){
			hex = "[0x5c]";
			token = replaceEscChar(token, index, hex);
			index = index+5;
			}
//If there is no special escape char, then the \ is completely removed.
			else {
				char *modify =  (char*)malloc(sizeof(char)*(strlen(token)-1));
				strncpy(modify, token, index);
				modify[index] = '\0';
				strcat(modify, token+1+index);
				strcpy(token, modify);
				free(modify);
				index++;
			}
		}

//size is updated
		size = strlen(token);
		index++;

	}


	return token;
}
/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk)
{
		free(tk->separators);
		free(tk->stream);
		free(tk);
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


// Creates a temporary array to store the the remainder of the stream
	char *token = "";
	int foundToken = 0;
	int counter = 0;
	char *remainder = malloc(sizeof(strlen(tk->stream)));

// Outer loop runs to the end of the stream string
// Inner loop runs to the end of the separators string
	while(counter < strlen(tk->stream))
	{
		int i;
		for(i = 0 ; i < strlen(tk->separators); i++)
		{
// Checks current separator with current character. If yes then checks if token has been found yet
// If no, then the character is added to the current token
			char currsep = tk->separators[i];
			if( tk->stream[counter] == currsep)
			{
// Error case: If separators are in the beginning of the string.
				if(counter == 0)
				{
// Error case: IF separator is at the beginning and stream has been truncated:
// Add null terminator to end of token and stream
					if(counter == strlen(tk->stream)-1)
						{
							tk->stream = '\0';
							char addthis = '\0';
							token = addchr(token, addthis);
							return token;
						}
					tk->stream++;
					counter= -1;
					break;
				}
// If token is found already, truncate stream to remainder and return token
				if(foundToken != 0)
				{
					int tokenindex = counter + 1;
					strncpy(remainder, tk->stream + tokenindex, strlen(tk->stream) - strlen(token));
					tk->stream = remainder;
					char addthis = '\0';
					token = addchr(token, addthis);
					return token;

				}
			}else
			{
// Since current separator is not current character:
// Add to token
				if(i == strlen(tk->separators) -1){
					foundToken = 1;
					char addthis = tk->stream[counter];
					token = addchr(token, addthis);
				}

// Checks if we have reached end of the string and end of separators, if yes then
// Manually add null terminator to the stream if we have reached the end of the stream
				if(counter == strlen(tk->stream)-1 && i == strlen(tk->separators) -1)
				{
					tk->stream = '\0';
					char addthis = '\0';
					token = addchr(token, addthis);
					return token;
				}
			}
		}

		counter++;

	}

 return 0;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

//Create tokeinzer object with input arguments
	TokenizerT *start = TKCreate(argv[1], argv[2]);

//If there are no separators, then print out the whole stream and return;
	if(strlen(argv[1]) == 0)
	{
		char *token = argv[2];
		token = checkEscChar(token);
		printf("%s\n", token);
		return 0;
	}

//If there is no string given in the argument
	if(strlen(argv[2]) == 0){
		return 0;
	}

//Call GetNextToken and print out each token until stream reaches a null terminator
	while((start->stream) != '\0' )
	{

		char *token = TKGetNextToken(start);
				if(token == NULL)
				{
					break;
				}

		token = checkEscChar(token);
		printf("%s\n", token);

	}

	TKDestroy(start);
	return 0;
}
