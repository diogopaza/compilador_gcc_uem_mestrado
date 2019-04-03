// The Computer Language Benchmarks Game
// https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
//
// contributed by Jeremy Zerfas
// rewritten by Аноним Легионов, inspired by fasta Rust #2 program
// use two OpenMP locks instead of one critical section
// decouples IO activity from random number generation
//
// modified by Josh Goldfoot, adding use of a buffer for fasta_repeat


// This controls the width of lines that are output by this program.
#define MAXIMUM_LINE_WIDTH	60

// This program will generate the random nucleotide sequences in parallel which
// are worked on in blocks of lines. The number of lines in those blocks is
// controlled by this setting.
#define LINES_PER_BLOCK 1024

#define CHARACTERS_PER_BLOCK (MAXIMUM_LINE_WIDTH*LINES_PER_BLOCK)

#define THREADS_TO_USE 4

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif

// intptr_t should be the native integer type on most sane systems.
typedef intptr_t intnative_t;

typedef struct
{
	char letter;
	float probability;
} nucleotide_info;


// Repeatedly print string_To_Repeat until it has printed
// number_Of_Characters_To_Create. The output is also wrapped to
// MAXIMUM_LINE_WIDTH columns.
static char* make_Sequence_Buffer(const char string_To_Repeat[])
{
	const intnative_t string_To_Repeat_Length = strlen(string_To_Repeat);

	// JG: Changed to that this writes a sequence to a buffer, which is used
	intnative_t number_Of_Characters_To_Create = string_To_Repeat_Length * MAXIMUM_LINE_WIDTH;
	char* buffer = (char*) malloc(number_Of_Characters_To_Create +
		number_Of_Characters_To_Create / MAXIMUM_LINE_WIDTH + 1);
	if (buffer == NULL)
		exit(-1);
	char* bufferOffset = buffer;

	// Create an extended_String_To_Repeat which is a copy of string_To_Repeat
	// but extended with another copy of the first MAXIMUM_LINE_WIDTH characters
	// of string_To_Repeat appended to the end. Later on this allows us to
	// generate a line of output just by doing simple memory copies using an
	// appropriate offset into extended_String_To_Repeat.
	char extended_String_To_Repeat[string_To_Repeat_Length + MAXIMUM_LINE_WIDTH];
	for (intnative_t column = 0; column<string_To_Repeat_Length + MAXIMUM_LINE_WIDTH;
		column++)
		extended_String_To_Repeat[column] =
		string_To_Repeat[column%string_To_Repeat_Length];
	intnative_t offset = 0;

	char line[MAXIMUM_LINE_WIDTH + 1];
	line[MAXIMUM_LINE_WIDTH] = '\n';

	for (intnative_t current_Number_Of_Characters_To_Create =
		number_Of_Characters_To_Create;
		current_Number_Of_Characters_To_Create>0;)
	{
		// Figure out the length of the line we need to write. If it's less than
		// MAXIMUM_LINE_WIDTH then we also need to add a line feed in the right
		// spot too.
		intnative_t line_Length = MAXIMUM_LINE_WIDTH;
		if (current_Number_Of_Characters_To_Create<MAXIMUM_LINE_WIDTH)
		{
			line_Length = current_Number_Of_Characters_To_Create;
			line[line_Length] = '\n';
		}

		memcpy(line, extended_String_To_Repeat + offset, line_Length);

		// Update the offset, reducing it by string_To_Repeat_Length if
		// necessary.
		offset += line_Length;
		if (offset>string_To_Repeat_Length)
			offset -= string_To_Repeat_Length;

		// "Output" that line to our buffer and update the
		// current_Number_Of_Characters_To_Create.
		memcpy(bufferOffset, line, line_Length + 1); //  JG: used to be fwrite(line, line_Length + 1, 1, stdout);
		bufferOffset += line_Length + 1;
		current_Number_Of_Characters_To_Create -= line_Length;
	}
	*bufferOffset = 0;
	return buffer;
}

void repeat_And_Wrap_String(const char string_To_Repeat[], intnative_t number_Of_Characters_To_Create)
{
	/* JG: fasta_repeat repeats every len(alu) * line-length = 287 * 61 = 17507 characters.
	       So, calculate this once, then just print that buffer over and over. */
	char* sequence = make_Sequence_Buffer(string_To_Repeat);
	intnative_t sequenceLen = (intnative_t) strlen(sequence);
	intnative_t outputBytes = number_Of_Characters_To_Create + number_Of_Characters_To_Create / 60;
	while (outputBytes >= sequenceLen) {
		fwrite(sequence, sequenceLen, 1, stdout);
		outputBytes -= sequenceLen;
	}
	if (outputBytes > 0) {
		fwrite(sequence, outputBytes, 1, stdout);
		printf("\n");
	}
	free(sequence);
}
