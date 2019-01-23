#include "cpu.h"
#include "stdio.h"
#include "string.h"

#define DATA_LEN 6

// Write the given value to the LS8's RAM at the given address
void cpu_ram_write(struct cpu *cpu, unsigned char MDR, unsigned char MAR) {
  cpu->ram[MAR] = MDR;
}

// Read the value at address and return it
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char MAR) {
  return cpu->ram[MAR];
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    // 2. Figure out how many operands this next instruction requires

    unsigned int num_of_operands = IR >> 6;
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA;
    unsigned char operandB;
    if (num_of_operands == 2) {
      operandA = cpu_ram_read(cpu, cpu->PC + 1);
      operandB = cpu_ram_read(cpu, cpu->PC + 2);
    } else if (num_of_operands == 1) {
      operandA = cpu_ram_read(cpu, cpu->PC + 1);
    } else {

    }

    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    switch(IR) {
      case HLT:
        // Break the loop
        running = 0;
        break;
      case LDI:
        // set the current operation to the next operation
        cpu->reg[operandA] = operandB;
        break;
      case PRN:
        // Print the value at the given register
        printf("%d\n", cpu->reg[operandA]);
        break;

    }

    // 6. Move the PC to the next instruction.
    // cpu->PC += (IR >> 6) + 1; <- could also eleminate the num_of_operands
                                //  and have the bitshift here as (IR >> 6) will
                                //  return the same value as num_of_operands
                                
    cpu->PC += num_of_operands + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  memset(cpu->reg, 0, sizeof(cpu->reg));
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
