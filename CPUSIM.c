/*	
 *	RISK CPU SIMULATOR
 *	N3cr0 1.1.2021.
*/
//make -B
//gcc -lm CPUSIM.c -o CPUSIM
#include <math.h>
#include <stdio.h>
#include <string.h>
//Instructions are char loner for null terminators
//32bit instruction:
char I[33];
//		     |  REG H    REG L |
//  00000000 00000000 00000000 00000000
// | OPCODE |   REG  |       DATA      |
//Instructions are two bites /a word
//Instruction pinter/counterc
char IP[17];
//Instruction pointer is x2 in memory
//because instructions are 2 16bits long
//Status flags
char SF[17];
//
// 00000000 00000000
//  V S Z C  UNUSED
//  1 3 5 7
//  V - Overflow Flag
//  S - Negative Result
//  Z - Zero Result
//  C - Carry Flag
//General purpose registers:
//16bit registers
//Address Register:
char A[17];	
//Base Register:
char B[17];
//Count register:	
char C[17];
//Data register:
char D[17];	
//Stack
//Stack pointer:
char SP[17];
//Base pointer:
char BP[17];
//MEMORY
FILE* MEMORY;
//Memory file
char* FileName = "memory";
//External file with 65535 lines (addressees)
//MAR
char MAR[17];
//MDR
char MDR[17];
//Support functions from C
//Binary char string to int
//DONE
int toInt(char* c)
	{
		int ret=0;
		int len=strlen(c);
		for(int i=strlen(c); i > -1; i--)
			{
				//printf("%c", c[i]);
				if(c[i] == '0')
					{
						continue;
					}
				else
					{
						ret = ret + pow(2, (len-i-1));
					}
			}
		return ret;
	}
//READ MEMORY
//DONE
void READMEM()
	{
		int linen = toInt(MAR);
		MEMORY = fopen(FileName, "r");
		char line[18];
		int n=0;
		while(fgets(line, sizeof(line), MEMORY))
			{
				if(n==linen)
					{
						strncpy(MDR, line, 16);	
						break;
					}
				n++;
			}
		fclose(MEMORY);
	}
//Write memory
//DONE
void WRITEMEM()
	{
		int linen = toInt(MAR);
		FILE *TEMP;
		MEMORY = fopen(FileName, "r");
		TEMP = fopen("memory.tmp", "w");
		char line[18];
		int n=0;
		while(fgets(line, sizeof(line), MEMORY))
			{
				if(n==linen)
					{
						fprintf(TEMP, "%s\n", MDR);
					}
				else
					{
						fputs(line, TEMP);
					}
				n++;
			}
		fclose(MEMORY);
		fclose(TEMP);
		remove(FileName);
		rename("memory.tmp", FileName);
	}
//TODO
//PADMEMORY 00 maybe:
//Instruction set:
//Reset flags:
//RSF
// FILL FS WITH 0
void RSF()
	{
		strcpy(SF, "0000000000000000");	
	}
//Moving memory:
//PUT
// REG <- DATA
void PUT(char* REG, char* RD)
	{
		strcpy(REG, RD);	
	}
// REG <- REG (DATA REG H)
void MOV(char* REG1, char* REG2)
	{
		strcpy(REG1, REG2);	
	}
//LOAD
// REG <- MEM
void LOAD(char* REG, char* MEM)
	{
		strcpy(MAR, MEM);	
		READMEM();
		strcpy(REG, MDR);	
	}
//STORE
// MEM <- REG
void STORE(char* REG, char* MEM)
	{
		strcpy(MAR, MEM);	
		strcpy(MDR, REG);	
		WRITEMEM();
	}
//SR
// REG <- REG
void SR(char* REG)
	{
		for(int i=(strlen(REG)-1); i>-1 ; i--)
			{
				REG[i] = REG[i-1];
			}
		REG[0] = '0';
	}
//SL
// REG <- REG
void SL(char* REG)
	{
		for(int i=0; i<(strlen(REG)-1); i++)
			{
				REG[i] = REG[i+1];
			}
		REG[strlen(REG)-1] = '0';
	}
//RL
// REG <- REG
void RL(char* REG)
	{
		SF[7]=REG[0];
		for(int i=0; i<(strlen(REG)-1); i++)
			{
				REG[i] = REG[i+1];
			}
		REG[strlen(REG)-1] = SF[7];
	}
//RR
// REG <- REG
void RR(char* REG)
	{
		SF[7] = REG[strlen(REG)-1];
		for(int i=(strlen(REG)-1); i>-1 ; i--)
			{
				REG[i] = REG[i-1];
			}
		REG[0] = SF[7];
	}

//Boolean logic:
//AND
//REG <- REG & REG
void AND(char* REG1, char* REG2)
	{
		for(int i=0; i<(strlen(REG1)); i++)
			{
				if((REG1[i] == '1') && (REG2[i] == '1'))
					{
						REG1[i] = '1';
					}
				else
					{
						REG1[i] = '0';
					}
			}

	}
//OR
//REG <- REG & REG
void OR(char* REG1, char* REG2)
	{
		for(int i=0; i<(strlen(REG1)); i++)
			{
				if((REG1[i] == '1') || (REG2[i] == '1'))
					{
						REG1[i] = '1';
					}
				else
					{
						REG1[i] = '0';
					}
			}

	}
//XOR
//REG <- REG & REG
void XOR(char* REG1, char* REG2)
	{
		for(int i=0; i<(strlen(REG1)); i++)
			{
				if( ((REG1[i] == '1') || (REG2[i] == '1')) && !((REG1[i] == '1' ) && (REG2[i] == '1')))
					{
						REG1[i] = '1';
					}
				else
					{
						REG1[i] = '0';
					}
			}

	}
//NOT
//REG <- REG & REG
void NOT(char* REG)
	{
		for(int i=0; i<(strlen(REG)); i++)
			{
				if(REG[i] == '0')
					{
						REG[i] = '1';
					}
				else
					{
						REG[i] = '0';
					}
			}
	}

//Arithemtic:
//ADD
// REG <- REG + REG (SET FLAGS)
void ADD(char* REG1,char* REG2)
	{
		RSF();
		for(int i=strlen(REG1)-1; i>-1; i--)
			{
				int S=0;
				if(REG1[i]=='1')
					{
						S++;
					}
				if(REG2[i]=='1')
					{
						S++;
					}
				if(SF[7]=='1')
					{
						S++;
					}
				switch (S)
					{
						case 0:
							REG1[i] = '0';
						break;
						case 1:
							REG1[i] = '1';
							SF[7] = '0';
						break;
						case 2:
							REG1[i] = '0';
							SF[7] = '1';
						break;
						case 3:
							REG1[i] = '1';
							SF[7] = '1';
						break;
					}
			}
		if( SF[7] == '1' )
			{
				SF[1]='1';
			}
	}
//INC 
// REG+1
void INC(char* REG)
	{
		char ONE[17] = "0000000000000001";
		ADD(REG, ONE); 
	}
//TEST
//REG, REG, SETS S AND Z FLAGS
void TEST(char* REG1, char* REG2)
	{
		//Compares 
		for(int i=0; i<(strlen(REG1)); i++)
			{
				if(REG1[i] == REG2[i])
					{
						SF[5] = '1';
					}
				else
					{
						SF[5] = '0';
						break;
					}
			}
		//Sets Sigb flag if most significant bit is altered
		if( (REG1[0] == REG1[0]) && (REG1[0] == '1') )
			{
				SF[3] = '1';
			}
		
	}
//SUB
// REG <- REG - REG (SET FLAGS)
void SUB(char* REG1, char* REG2)
	{
		char TMP[17];
		strcpy(TMP, REG2);	
		//TURNS REG2 IN 2s COMPEMENT
		NOT(TMP);
		INC(TMP);
		RSF();
		//Rests for zero flag
		TEST(REG1, REG2);
		//Adds REG1 with REG2s 2s Complement
		ADD(REG1, TMP);
		if(SF[1] == '0' && SF[7] == '0')
			{
				SF[3] = '1';
			}
	}
//DEC
// REG-1
void DEC(char* REG)
	{
		char ONE[17] = "0000000000000001";
		//Adds REG1 with ONEs 2s Complement
		SUB(REG, ONE);
	}
//Stack operations:
//PUSH
// ST <- REG
void PUSH(char* REG)
	{
		RSF();
		strcpy(MAR, SP);	
		strcpy(MDR, REG);
		WRITEMEM();
		INC(SP);
	}
//POP
// REG <- ST-1
void POP(char* REG)
	{
		RSF();
		DEC(SP);
		strcpy(MAR, SP);	
		READMEM();
		strcpy(REG, MDR);	
	}
//SSP set stack pointer
// ST <- REG
void SSP(char* REG)
	{
		MOV(SP, REG);
	}
//SBP set base pointer
//BP <- REG
void SBP(char* REG)
	{
		MOV(BP, REG);
	}

//CMP
//REG, REG
void CMP(char* REG1, char* REG2)
	{
		char TMP[17];
		strcpy(TMP, REG1);
		RSF();
		SUB(TMP, REG2);
	}


//JUMP:
//JMP
// Alwasy jump to REGA
void JMP(char* REG)
	{
		strcpy(IP, REG);
	}
//JE
//Jump if equal
void JE(char* REG)
	{
		if(SF[1] == '1' && SF[3] == '0' && SF[5] == '1' && SF[7] == '1')
			{
				strcpy(IP, REG);
			}
	}
//JGT
//Jump if grater then
void JGT(char* REG)
	{
		if(SF[1] == '1' && SF[3] == '0' && SF[5] == '0' && SF[7] == '1')
			{
				strcpy(IP, REG);
			}
	}
//JLT
//jump if less then
void JLT(char* REG)
	{
		if(SF[1] == '0' && SF[3] == '1' && SF[5] == '0' && SF[7] == '0')
			{
				strcpy(IP, REG);
			}
	}
//JGE
//Jump if grater then or equal
void JGE(char* REG)
	{
		if((SF[1] == '1' && SF[3] == '0' && SF[5] == '0' && SF[7] == '1') || (SF[1] == '1' && SF[3] == '0' && SF[5] == '1' && SF[7] == '1'))
			{
				strcpy(IP, REG);
			}
	}
//JLE
//Jump if less then or equal
void JLE(char* REG)
	{
		if((SF[1] == '0' && SF[3] == '1' && SF[5] == '0' && SF[7] == '0') || (SF[1] == '1' && SF[3] == '0' && SF[5] == '1' && SF[7] == '1'))
			{
				strcpy(IP, REG);
			}
	}
//CALL
//Calls a subprogram
void CALL(char* REG)
	{
		PUSH(SF);
		PUSH(IP);
		PUSH(A);
		PUSH(B);
		PUSH(C);
		PUSH(D);
		MOV(IP, REG);
		RSF();
	}
//RET
//Returns from subprogram
void RET()
	{
		char TMP[17];
		POP(D);
		POP(C);
		POP(B);
		POP(A);
		POP(TMP);
		RSF();
		INC(TMP);
		MOV(IP, TMP);
		POP(SF);
	}

///FETCH / DECODE / EXECUTE 

char OPCODE[9];
char REGISTER[9];	
char DATA[17];

//Gets instruction from meory
void FETCH()
	{
		char INS[17];
		strcpy(INS, IP);
		ADD(INS, INS);
		strcpy(MAR, INS);	
		READMEM();
		strcpy(I, MDR);	
		INC(INS);
		strcpy(MAR, INS);	
		READMEM();
		strcat(I, MDR);
		INC(IP);
	}
void DECODE()
	{
		memcpy( OPCODE, &I[0], 8 );
		OPCODE[8] = '\0';
		memcpy( REGISTER, &I[8], 15 );
		REGISTER[8] = '\0';
		memcpy( DATA, &I[16], 32 );
		DATA[16] = '\0';
	}
void EXECUTE()
	{
		int O = toInt(OPCODE);
		int RAT = toInt(REGISTER);
		//regB
		char TMP[9];
		memcpy( TMP, &DATA[9], 8 );
		TMP[8]='\0';
		int RBT = toInt(TMP);
		char* RA;
		char* RB;
		switch (RAT)
			{
				case 1:
					RA = A;
				break;
				case 2:
					RA = B;
				break;
				case 3:
					RA = C;
				break;
				case 4:
					RA = D;
				break;
			}
		switch (RBT)
			{
				case 1:
					RB = A;
				break;
				case 2:
					RB = B;
				break;
				case 3:
					RB = C;
				break;
				case 4:
					RB = D;
				break;
			}
		switch (O)
			{
				case 0:
					MOV(RA, RB);
				break;
				case 1:
					PUT(RA, DATA);
				break;
				case 2:
					LOAD(RA, DATA);
				break;
				case 3:
					STORE(RA, DATA);
				break;
				case 4:
					NOT(RA);
				break;
				case 5:
					AND(RA, RB);
				break;
				case 6:
					OR(RA, RB);
				break;
				case 7:
					XOR(RA, RB);
				break;
				case 8:
					SL(RA);
				break;
				case 9:
					SR(RA);
				break;
				case 10:
					RL(RA);
				break;
				case 11:
					RR(RA);
				break;
				case 12:
					ADD(RA, RB);
				break;
				case 13:
					SUB(RA, RB);
				break;
				case 14:
					INC(RA);
				break;
				case 15:
					DEC(RA);
				break;
				case 16:
					TEST(RA, RB);
				break;
				case 17:
					CMP(RA, RB);
				break;
				case 18:
					JMP(RA);
				break;
				case 19:
					JE(RA);
				break;
				case 20:
					JGT(RA);
				break;
				case 21:
					JGE(RA);
				break;
				case 22:
					JLT(RA);
				break;
				case 23:
					JLE(RA);
				break;
				case 24:
					PUSH(RA);
				break;
				case 25:
					POP(RB);
				break;
				case 26:
					SSP(RA);
				break;
				case 27:
					SBP(RA);
				break;
				case 28:
					RSF();
				break;
				case 29:
					CALL(DATA);
				break;
				case 30:
					RET();
				break;
			}
	}
//Prints CPU reegisters
void printCPU()
	{
		printf("Instruction:\n");
		printf("IP:\t%s\n", IP);
		printf("I:\t%s\n", I);
		printf("FLAGS:\t V S Z C\n");
		printf("SF:\t%s\n", SF);
		printf("\n");
		printf("Mermoy:\n");
		printf("MAR:\t%s\n", MAR);
		printf("MDR:\t%s\n", MDR);
		printf("\n");
		printf("Registers:\n");
		printf("A:\t%s\n", A);
		printf("B:\t%s\n", B);
		printf("C:\t%s\n", C);
		printf("D:\t%s\n", D);
		printf("\n");
		printf("Stack:\n");
		printf("SP:\t%s\n", SP);
		printf("BP:\t%s\n", BP);
		printf("---------------------------\n\n");
	}
//Clears all registers on CPU to simulate boot
void setupCPU()
	{
		//Setup Memory:
		strcpy(MAR, "0000000000000000");	
		strcpy(MDR, "0000000000000000");	
		//Setup inscrution registers
		strcpy(IP, "0000000000000000");	
		strcpy(I, "00000000000000000000000000000000");	
		strcpy(SF, "0000000000000000");	
		//Setup registers;
		strcpy(A, "0000000000000000");	
		strcpy(B, "0000000000000000");	
		strcpy(C, "0000000000000000");	
		strcpy(D, "0000000000000000");	
		//Setup Stack	
		strcpy(SP, "0000000000000000");	
		strcpy(BP, "0000000000000000");	
	}
int main(int argc, char* argv[])
	{
		setupCPU();
		for(int i=0; i<8; i++)	
			{
	 			FETCH();
				DECODE();
				EXECUTE();
				printCPU();
			}
		return 0;
	}
