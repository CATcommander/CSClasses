#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <time.h>

using namespace std;

#define MAX 1000

int * table = new int[MAX];

void shift_table(char * pattern);
void print_table(int * table, char * p);
int horspool(char * text, char * pattern);

int main()
{
	int position;
	char *u, * src, * p;
	int l;

	// u is the text
	// p is the pattern
	u = "TTATAGATCTCGTATTCTTTTATAGATCTCCTATTCTT";
	l = strlen(u) + 1;
	src = new char [l];
	strcpy(src, u);
	
	p = new char[strlen("TCCTATTCTT") + 1];
	strcpy(p, "TCCTATTCTT");

	shift_table(p);
	print_table(table, p);

	//clock_t startTime, endTime;
	//startTime = clock();

	//for (int i = 0; i < 1000000; ++i)
		position = horspool(src,p);

	//endTime = clock();
	//float diff = (float)(endTime - startTime) / 1000000; 

//	cout << "\ttime: " << setprecision(5) << diff << " milliseconds";// << " sec: " << sec << endl;

	if (position >= 0)
		cout << "\n\tThe desired pattern was found starting from position: " << position + 1 << endl;
	else
		cout << "\n\tThe pattern was not found in the given text\n" << endl;
	cout << "\n";

	return 0;
}

// input:  pattern to search in text
// output: input enhancement, preprocess the pattern 
//		   and make a shift table
void shift_table(char * pattern)
{
	int i, j, m;
	m = strlen(pattern);

	for (i = 0; i < MAX; i++)
		table[i] = m;
	for (j = 0; j < m - 1; j++)
		table[(int) pattern[j]] = m - 1 - j;
}

// input: the shift table and pattern
// output: shift table of Upper and lower case alphabet
void print_table(int * table, char * p)
{
	int i;

	cout << "Shift Table for pattern: " << endl;
	cout << "\tChar: ";

	for (i = 65; i < 91; ++i)
		cout << "\t" << (char)i;
	//for (i = 97; i < 123; ++i)
	//	cout << " " << (char)i;
	cout << endl;

	cout << "\tShift:";
	for (i = 65; i < 91; ++i) 
	{
		if (table[i] == 0)
			table[i] = strlen(p);
		cout << "\t" << table[i];
	}
//	for (i = 97; i < 123; ++i) 
//	{
//		if (table[i] == 0)
//			table[i] = strlen(p);
//		cout << " " << table[i];
//	}
	cout << "\n";
}

// input: text to search in and pattern to look for
// output: uses horspool's algorithm and the shift table
//		   to find the substring, returns the number of 
//		   shift, comparions and position of the match found
int horspool(char * text, char * pattern)
{
	int i, k, m, t;
	int comp = 0;
	int shift = 0;

	t = strlen(text); // length of text
	m = strlen(pattern); // length of pattern

	i = m - 1;
	while(i < t)
	{
		k = 0;
	cout << "out while k: " << k << endl;
		while ( (k < m) && ++comp && (pattern[m - 1 - k] == text[i - k]) )
		{
			cout << "\nK: "<< k << "\npatter[m-1-k]: " << pattern[m-1-k] << "\ntext[i-k]: " << text[i-k] << endl;
			k++; 
		}
		// if match is found
		if (k == m)
		{
// uncomment this to see the number of comps and shifts after match
			cout << "\n# of Comparisons: " << comp << "\n# of Shifts: " << shift << endl;
			cout << "\ni- m + 1 " << (i - m + 1) << "\ni "<< i << "\nm: " << m << "\nm+1: " << m+1 << endl;
			return (i - m + 1);
		}
		else
		{
			++shift;
			i += table[(int) text[i]];
			cout << "i " << i << "\ntable[text[i]]: " << table[(int) text[i]] << "\ntext[i]: " << text[i] << endl;
		}
	}
// uncomment this to see the number of comps and shifts upon mismatch
	cout << "\n# of Comparisons: " << comp << "\n# of Shifts: " << shift << endl;

	return -1;
}
