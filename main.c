#include <stdbool.h>
#include <stdio.h>

#define sp (registers[SP])
#define ip (registers[IP])
#define STACK_SIZE 256

//TODO: Add more instructions
typedef enum InstructionSet {
	PSH,
	POP,
	ADD,
	SET,
	HLT
} InstructionSet;

typedef enum Registers {
	A,
	B,
	C,
	D,
	E,
	F,
	SP, //Stack Pointer
	IP, //Instruction Pointer/Program Counter
	NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

int stack[STACK_SIZE];
bool running = true;


//TODO: read from file later
const int program[] = {
	PSH, 5,
	PSH, 3,
	ADD,
	POP,
	HLT
};


int fetch() {
	return program[ip];
}

void eval(int instruction){
	switch (instruction) {
		case HLT: {
			running = false;
			printf("finished execution\n");
			break;
		}
		case PSH: {
			stack[++sp] = program[++ip]; 
			break;
		}
		case POP: {
			int val = stack[sp--];
			printf("Popped out: %d\n", val);
			break;
		}
		case ADD: {
			registers[A] = stack[sp];
			registers[B] = stack[--sp];
			sp++;
			registers[C] = registers[B] + registers[A];
			stack[++sp] = registers[C];
			break;
		}
	}
}


//------------------------------------------------------------------------------
// Debug stuff
//------------------------------------------------------------------------------

void printStack() {
	printf("Dumping Stack\n");

	for (int i = 0; i < STACK_SIZE; ++i)
	{
		printf("%d\n", stack[i]);
	}
}

void printRegisters() {
	printf("Dumping Registers\n");

	for (int i = 0; i < NUM_OF_REGISTERS; ++i)
	{
		printf("%d\n",registers[i]);
	}
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	sp = -1;
	while (running) {
		eval(fetch());
		ip++;
	}

	/**
	* Debug
	*/
	// printStack();
	// printRegisters();
	
	return 0;
}