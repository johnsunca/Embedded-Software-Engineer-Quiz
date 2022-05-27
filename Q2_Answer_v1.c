/*
	== Answer to Q2 - v1 ==
	Changes: using modulus and int division to get a, b, and c, 
	         rather than brute force in 3 nested for-loop
	Credit: to anonymous interviewer for the feedback
	        
	a) 
	The mapping function is an inverse function of polynomial. 
	The code map table (mapping a character 0-9/a-z/A-Z to an integer 0-61) is as follows:
	0->27   1->34   2->33   3->23   4->42   5->21   6->25     7->1    8->31   9->36
	a->53   b->60   c->4    d->16   e->46   f->54   g->52     h->48   i->3    j->44
	k->61   l->59   m->17   n->19   o->15   p->30   q->38     r->57   s->37   t->56
	u->29   v->8    w->18   x->2    y->12   z->9    A->10     B->24   C->0    D->22
	E->32   F->55   G->7    H->26   I->49   J->51   K->58     L->39   M->6    N->14
	O->28   P->5    Q->40   R->50   S->45   T->13   U->47     V->20   W->35   X->41
	Y->43   Z->11
	
	b) 
	Input     Output
	30001     GIF
	55555     NOi
	77788     VNQ
	
	c)
	The upper limit of this mapping function is:
	61 * 62 * 62 + 61 * 62 + 61 = 238327
	
	d)
	To run the program, put the data source file "Embedded_Software_Engineer_Quiz_Resource.csv"
	to the same folder as the source file.	
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *file_path = "Embedded_Software_Engineer_Quiz_Resource.csv";
unsigned int code_map[62]; //map characters 0-9, a-z, A-Z to a non-negative integer

unsigned int get_index(const unsigned char c); //get index of a character in code_map
unsigned char get_character(const unsigned int index); //get character of an index in code_map
void create_map(const unsigned char *file_path); //create map entries in code_map table
unsigned char* mapping_function(unsigned int num); //given an input number, find it's output string
void print_output(const unsigned int num); //print output for a given input

int main() {
	//create map table
	create_map(file_path);

	//print the map
	puts("=== Character Mapped To Integer ===");
	for (unsigned int i = 0; i < 62; i++) {
		if (i % 10 == 0) putchar('\n'); //print 10 per line
		printf("%c->%d\t", get_character(i), code_map[i]);
	}
	puts("\n\n");

	//print outputs for the 3 specific inputs
	print_output(30001);  //GIF
	print_output(55555); //NOi
	print_output(77788); //VNQ

	//read input from the user, print the output
	const int MAX = 61 * 62 * 62 + 61 * 62 + 61;
	printf("\n\nEnter input number (0 to %d, -1 to stop): ", MAX);
	unsigned int num;
	scanf("%d", &num);
	while (num != -1) {
		print_output(num);
		printf("Enter input number (0 to %d, -1 to stop): ", MAX);
		scanf("%d", &num);
	}
	puts("=== Game Over ===");
}

//get index of a char in code_map
unsigned int get_index(const unsigned char c) {
	if (islower(c)) return c - 'a' + 10; //a-z
	if (isupper(c)) return c - 'A' + 36; //A-Z
	return c - '0'; //0-9
}

//get character from an index in code_map
unsigned char get_character(const unsigned int index) {
	if (index < 10) return index + '0'; //0-9
	if (index < 36) return index - 10 + 'a'; //a-z
	return index - 36 + 'A'; //A-Z
}

//create map entries in code_map table
//- NOTE: with the given data, '5' is not mapped to a number and 21 is not mapped from a character
void create_map(const unsigned char *file_path) {
	//init to -1 (can't be 0 as zero is a valid value in mapping)
	for (unsigned int i = 0; i < 62; i++)
		code_map[i] = -1;
	FILE *file = fopen(file_path, "r"); //open file for reading
	if (file == NULL) {
		printf("Cannot open the file for reading.");
		exit(1);
	}
	unsigned int A; //number in column A
	unsigned char B[4]; //string in column B
	unsigned int stop; //early stop tag
	fscanf(file, "%d,%s", &A, B); //read a line
	while(!feof(file)) { //read resource file line by line
		code_map[get_index(B[0])] = A / (62 * 62);
		A %= (62 * 62);
		code_map[get_index(B[1])] = A / 62;
		A %= 62;
		code_map[get_index(B[2])] = A;
		fscanf(file, "%d,%s", &A, B); //read next line
	}
	fclose(file);
	code_map[get_index('5')] = 21; //TEMP: mannually mapping '5' to 21
}

//given an input number, find it's output string
//- NOTE: code_map must have been created
unsigned char* mapping_function(unsigned int num) {
	//put value in heap, otherwise returning a local value is not a good practice
	unsigned char *output = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	strcpy(output, "???");
	int a = num / (62 * 62);
	num %= (62 * 62);
	int b = num / 62;
	num %= 62;
	int c = num;
	for (unsigned int i = 0; i < 62; i++) { //look up the map table
		if (code_map[i] == a)
			output[0] = get_character(i);
		if (code_map[i] == b)
			output[1] = get_character(i);
		if (code_map[i] == c)
			output[2] = get_character(i);
	}
	return output;
}

//print output for a given input
void print_output(const unsigned int num) {
	unsigned char *output = mapping_function(num);
	printf("  >> %d is mapped to %s\n", num, output);
	free(output);
}
