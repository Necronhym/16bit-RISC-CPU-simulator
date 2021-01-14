#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *ltrim(char *s)
	{
		while(isspace(*s))
			{       
				s++;
			}
		return s;
	}
char *rtrim(char *s)
	{
		char* back = s + strlen(s);
		while(isspace(*--back));
		*(back+1) = '\0';
		return s;
	}
char *trim(char *s)
	{
		return rtrim(ltrim(s)); 
	}
void opcodeToBinary(char* token)
	{
		//This is horible, replace with for loop, and array;
		token = trim(token);
		//MEMORY:
		if(!strcmp(token, "mov"))
			{
				printf("%s", "00000000");
			}
		else if(!strcmp(token, "put"))
			{
				printf("%s", "00000001");
			}
		else if(!strcmp(token, "load"))
			{
				printf("%s", "00000010");
			}
		else if(!strcmp(token, "store"))
			{
				printf("%s", "00000011");
			}
		//BITWISE:
		else if(!strcmp(token, "not"))
			{
				printf("%s", "00000100");
			}
		else if(!strcmp(token, "and"))
			{
				printf("%s", "00000101");
			}
		else if(!strcmp(token, "or"))
			{
				printf("%s", "00000110");
			}
		else if(!strcmp(token, "xor"))
			{
				printf("%s", "00000111");
			}
		//SHIFT:
		else if(!strcmp(token, "sl"))
			{
				printf("%s", "00001000");
			}
		else if(!strcmp(token, "sr"))
			{
				printf("%s", "00001001");
			}
		//ROTATE:
		else if(!strcmp(token, "rl"))
			{
				printf("%s", "00001010");
			}
		else if(!strcmp(token, "rr"))
			{
				printf("%s", "00001011");
			}
		//ARITHMETIC:
		else if(!strcmp(token, "add"))
			{
				printf("%s", "00001100");
			}
		else if(!strcmp(token, "sub"))
			{
				printf("%s", "00001101");
			}
		else if(!strcmp(token, "inc"))
			{
				printf("%s", "00001110");
			}
		else if(!strcmp(token, "dec"))
			{
				printf("%s", "00001111");
			}
		//COMPARISONS:
		else if(!strcmp(token, "test"))
			{
				printf("%s", "00010000");
			}
		else if(!strcmp(token, "cmp"))
			{
				printf("%s", "00010001");
			}
		//JUMPS:
		else if(!strcmp(token, "jmp"))
			{
				printf("%s", "00010010");
			}
		else if(!strcmp(token, "je"))
			{
				printf("%s", "00010011");
			}
		else if(!strcmp(token, "jgt"))
			{
				printf("%s", "00010100");
			}
		else if(!strcmp(token, "jge"))
			{
				printf("%s", "00010101");
			}
		else if(!strcmp(token, "jlt"))
			{
				printf("%s", "00010110");
			}
		else if(!strcmp(token, "jle"))
			{
				printf("%s", "00010111");
			}
		//STACK
		else if(!strcmp(token, "push"))
			{
				printf("%s", "00011000");
			}
		else if(!strcmp(token, "pop"))
			{
				printf("%s", "00011001");
			}
		else if(!strcmp(token, "ssp"))
			{
				printf("%s", "00011010");
			}
		else if(!strcmp(token, "sbp"))
			{
				printf("%s", "00011011");
			}
		//SYSTEM:
		else if(!strcmp(token, "rsf"))
			{
				printf("%s\n", "0001110000000000");
				printf("%s", "0000000000000000");
			}
		else if(!strcmp(token, "call"))
			{
				printf("%s", "00011101");
			}
		else if(!strcmp(token, "call"))
			{
				printf("%s", "00011110");
			}
		
		//ERROR
		else
			{
				printf("%s", "Invalid opcode");
			}

	}
void regToBinary(char* token)
	{
		token = trim(token);
		
		
		//Registers:
		if(!strcmp(token, "rega"))
			{
				printf("%s", "00000001");
			}
		else if(!strcmp(token, "regb"))
			{
				printf("%s", "00000010");
			}
		else if(!strcmp(token, "regc"))
			{
				printf("%s", "00000011");
			}
		else if(!strcmp(token, "regd"))
			{
				printf("%s", "00000100");
			}
		else
			{
				printf("%s", "00000000");
			}
		printf("\n");
	}
void dataToBinary(char* token)
	{
		token = trim(token);
		
		//Registers:
		if(!strcmp(token, "rega"))
			{
				printf("%s", "0000000000000001");
			}
		else if(!strcmp(token, "regb"))
			{
				printf("%s", "0000000000000010");
			}
		else if(!strcmp(token, "regc"))
			{
				printf("%s", "0000000000000011");
			}
		else if(!strcmp(token, "regd"))
			{
				printf("%s", "0000000000000100");
			}
		else
			{
				printf("%s", token);
			}
	}
int main(int argc, char* argv[])
	{
		//TEMP:
		char* inName = "in.asm";
		char* outName = "a.out";
		//Files:
		FILE *INFILE = fopen( inName, "r" );
		FILE *OUTFILE = fopen( outName, "w");
		//Reads input file line by line:
		char buff[255];
		int i =0;
		while(fgets(buff, sizeof(buff), INFILE))
			{
				//Splits string in to tokens
				char *token = strtok(strtok(buff, "\n"), " "); 
				int j=0;
				while(token != NULL)
					{
						if(j==0)
							{
								opcodeToBinary(token);
							}
						if(j==1)
							{
								regToBinary(token);
							}
						if(j==2)
							{
								dataToBinary(token);
							}
						token = strtok(NULL, " ");
						j++;
					}
				if(j==2)
					{
						printf("%s", "0000000000000000");
					}
				j=0;
				printf("\n");
				i++;
			}
		//Clean it up
		fclose(INFILE);
		fclose(OUTFILE);


		return 0;
	}

