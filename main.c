#include <stdio.h>
#include <malloc.h>

int main() {
	int i, fileSize, numberOfInts, *integers;

	//1. Open file, determine the file size and number of int values that it contains.
	FILE *fp = fopen("ass2data.bin", "r");
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	numberOfInts = fileSize / sizeof(int);
	printf("The file size is %d bytes\n", fileSize);
	printf("The file contains %d ints\n\n", numberOfInts);

	//2.Allocate memory dynamically to hold the int data from the binary file.
	integers = (int*) malloc(fileSize);

	//3. Read the binary file into the dynamically allocated memory.
	for (i = 0; i < numberOfInts; i++)
		fread(&integers[i], sizeof(int), 1, fp);

	//4. Display each int value in decimal, with a width of 12, six to a line
	for (i = 0; i < numberOfInts; i++) {
		printf("%-12d ", integers[i]);
		if (i % 6 == 5)
			printf("\n");
	}
	printf("\n");

	//5. Display each int value in hexadecimal, with a width of 12, six to a line.
	for (i = 0; i < numberOfInts; i++) {
		printf("0x%-10x ", integers[i]);
		if (i % 6 == 5)
			printf("\n");
	}
	printf("\n");

	//6. Extract the 3rd byte of each int and display it in hexadecimal,
	//with a width of 6, twelve to a line.
	for (i = 0; i < numberOfInts; i++) {
		integers[i] = (integers[i] >> (8)) & 0xff;
		printf("0x%-4x ", integers[i]);
		if (i % 12 == 11)
			printf("\n");
	}
	printf("\n");

	//7. Reverse the nibbles of the resulting byte and display it
	//in hexadecimal, with a width of 6, twelve to a line.
	for (i = 0; i < numberOfInts; i++) {
		integers[i] = ((integers[i] & 0x0f) << 4) | (integers[i] >> 4);
		printf("0x%-4x ", integers[i]);
		if (i % 12 == 11)
			printf("\n");
	}
	printf("\n");

	//8. Interpret each result from step 7 as a BCD (binary coded decimal) value
	//and add 32 to each. Cast each result to a char and display the secret message.
	for (i = 0; i < numberOfInts; i++) {
		integers[i] = (integers[i] >> 4) * 10 + (integers[i] & 0x0f) + 32;
		printf("%c", integers[i]);
	}
	printf("\n");

	//9. Clean up your mess.
	free(integers);
	fclose(fp);
	return 0;
}
