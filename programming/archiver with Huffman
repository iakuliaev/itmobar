
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
	unsigned char name[256];
	int size;
	int priority;
	struct node* left;
	struct node* right;

};


int getsize(FILE* File)
{
	int size = 0;

	fseek(File, 0, SEEK_SET);
	while (fgetc(File) != EOF)
		size++;
    
	fseek(File, 0, SEEK_SET);

	return size;
}

unsigned char* readfile(int size, char* filename)
{
	FILE* fp;
	fp = fopen(filename, "rb");
	unsigned char* strings;
	strings = (unsigned char*)malloc(size);
	fread(strings, size, 1, fp);
	fclose(fp);
	return strings;
}

struct node* haffmantree(int size, unsigned char* file)
{
	int mas[256];
	int uniq = 0;
	for (int j = 0; j < 256; j++)
		mas[j] = 0;
	for (int i = 0; i < size; i++)
		mas[(int)file[i]]++;
	for (int i = 0; i < 256; i++)
	{
		if (mas[i] != 0)
			uniq++;
	}
	struct node* tree;
	tree = (struct node*)malloc(uniq * sizeof(struct node));
	if (uniq == 1)
	{
		for (int i = 0; i < 256; i++)
		{
			if (mas[i] != 0)
			{
				tree[0].name[0] = (unsigned char)i;
				tree[0].priority = mas[i];
				tree[0].size = 1;
				tree[0].left = NULL;
				tree[0].right = &tree[1];
				tree[1].name[0] = (unsigned char)i;
				tree[1].priority = mas[i];
				tree[1].size = 1;
				tree[1].left = NULL;
				tree[1].right = NULL;
				return &tree[0];
			}
		}
	}
	int j = 0, min1, min2;
	for (int i = 0; i < 256; i++)
	{
		if (mas[i] != 0)
		{
			tree[j].priority = mas[i];
			tree[j].name[0] = (unsigned char)i;
			tree[j].size = 1;
			tree[j].left = NULL;
			tree[j].right = NULL;
			j++;
		}
	}
	int index1 = 0, index2 = 1;
	for (int f = 0; f < uniq - 1; f++)
	{
		unsigned char* min1name, * min2name;
		min1 = tree[0].priority;
		min1name = tree[0].name;
		min2 = tree[1].priority;
		min2name = tree[1].name;
		index1 = 0;
		index2 = 1;
		if (min2 < min1)
		{
			int tmp = min1;
			unsigned char* tmpname = min1name;
			min1 = min2;
			min1name = min2name;
			min2 = tmp;
			min2name = tmpname;
			index2 = 0;
			index1 = 1;
		}
		for (int i = 2; i < uniq; i++)
		{
			if (tree[i].priority < min2)
			{
				if (tree[i].priority < min1)
				{
					min2 = min1;
					index2 = index1;
					min2name = min1name;
					min1 = tree[i].priority;
					min1name = tree[i].name;
					index1 = i;
				}
				else
				{
					min2 = tree[i].priority;
					min2name = tree[i].name;
					index2 = i;
				}
			}
		}
		struct node* tree1copy;
		tree1copy = (struct node*)malloc(sizeof(struct node));
		struct node* tree2copy;
		tree2copy = (struct node*)malloc(sizeof(struct node));
		*tree1copy = tree[index1];
		*tree2copy = tree[index2];
		for (int i = 0; i < tree[index2].size; i++)
			tree[index1].name[tree[index1].size + i] = tree[index2].name[i];
		tree[index1].size = tree1copy->size + tree2copy->size;
		tree[index1].priority = tree1copy->priority + tree2copy->priority;
		tree[index1].left = tree1copy;
		tree[index1].right = tree2copy;
		tree[index2].priority = 1000000000;
	}
	return &tree[index1];
}

int exists(unsigned char* mas, int size, unsigned char symbol)
{
	for (int i = 0; i < size; i++)
		if (mas[i] == symbol)
			return 1;
	return 0;
}

unsigned char* code(struct node tree, unsigned char symbol)
{
	unsigned char* str;
	str = (unsigned char*)malloc(256);
	int a = 0;
	for (int i = 0; i < 256; i++)
		str[i] = (unsigned char)0;
	struct node copytree = tree;
	if (exists(copytree.name, copytree.size, symbol) == 0)
		return str;
	while (copytree.left != NULL || copytree.right != NULL)
	{
		if ((copytree.left == NULL) || exists(copytree.left->name, copytree.left->size, symbol) == 0)
		{
			str[a++] = '0';
			copytree = *copytree.right;
		}
		else
		{
			str[a++] = '1';
			copytree = *copytree.left;
		}
	}
	return str;
}

void unzip(FILE* arc)
{
	int sizeoffile = 0;
	unsigned char string[100];
	fread(string, 4, 1, arc);
	for (int i = 0; i < 4; i++)
		sizeoffile += (int)string[i] * pow(256, i);
	memset(string, 0, 100);
	fread(string, 1, 1, arc);
	int sizeofname = 0;
	sizeofname = (int)string[0];
	memset(string, 0, 100);
	fread(string, sizeofname, 1, arc);
	unsigned char newstring[100];
	fread(newstring, 1, 1, arc);
	int uniqsymbols = (int)newstring[0];
	memset(newstring, 0, 100);
	unsigned char** arr;
	arr = (unsigned char**)malloc(256 * sizeof(unsigned char*));
	for (int i = 0; i < 256; i++)
		arr[i] = (unsigned char*)malloc(256 * sizeof(unsigned char));
	for (int i = 0; i < 256; i++)
		arr[i][0] = '\0';
	for (int i = 0; i < uniqsymbols; i++)
	{
		fread(newstring, 1, 1, arc);
		int index = (int)newstring[0];
		memset(newstring, 0, 100);
		fread(newstring, 1, 1, arc);
		int lengthofcode = (int)newstring[0];
		memset(newstring, 0, 100);
		fread(newstring, lengthofcode, 1, arc);
		for (int j = 0; j < lengthofcode; j++)
		{
			arr[index][j] = newstring[j];
			if (j == lengthofcode - 1)
				arr[index][j + 1] = '\0';
		}
		memset(newstring, 0, 100);
	}
	struct node* tree;
	tree = (struct node*)malloc(sizeof(struct node));
	tree->left = NULL;
	tree->right = NULL;
	struct node* first;
	first = (struct node*)malloc(sizeof(struct node));
	first = tree;
	for (int i = 0; i < 256; i++)
	{
		if (arr[i][0] != '\0')
		{
			int j = 0;
			while (arr[i][j] != '\0')
			{
				if (arr[i][j] == '0')
				{
					if (tree->right != NULL)
						tree = tree->right;
					else
					{
						struct node* newtree;
						newtree = (struct node*)malloc(sizeof(struct node));
						tree->right = newtree;
						newtree->left = NULL;
						newtree->right = NULL;
						tree = newtree;
					}
				}
				else
				{
					if (tree->left != NULL)
						tree = tree->left;
					else
					{
						struct node* newtree;
						newtree = (struct node*)malloc(sizeof(struct node));
						tree->left = newtree;
						newtree->left = NULL;
						newtree->right = NULL;
						tree = newtree;
					}
				}
				j++;
			}
			if (arr[i][j] == '\0')
				*tree->name = (char)i;
		}
		tree = first;
	}
	int count = 0;
	FILE* original;
	original = fopen(string, "wb");
	int t;
	unsigned char bytes[8];
	while (1)
	{
		memset(newstring, 0, 100);
		fread(newstring, 1, 1, arc);
		if (count == sizeoffile)
		{
			fclose(original);
			return;
		}
		t = 7;
		for (int i = 0; i < 8; i++)
			bytes[i] = 0;
		while (newstring[0] > 0)
		{
			bytes[t--] = newstring[0] % 2;
			newstring[0] /= 2;
		}
		for (int k = 0; k < 8; k++)
		{
			if ((tree->left != NULL) || (tree->right != NULL))
			{
				if (bytes[k] == 0)
					tree = tree->right;
				else
					tree = tree->left;

			}
			if ((tree->left == NULL) && (tree->right == NULL))
			{
				fprintf(original, "%c", tree->name[0]);
				tree = first;
				count++;
				if (count == sizeoffile)
				{
					fclose(original);
					return;
				}
			}
		}
		for (int i = 0; i < 8; i++)
			bytes[i] = 0;
	}
	fclose(original);
}

char* arc(char* filename)
{
	unsigned char string[8];
	FILE* fin = fopen(filename, "rb");
	int sizeoffile = getsize(fin);
	fclose(fin);
	int copysizeoffile = sizeoffile;
	unsigned char* allfile = readfile(sizeoffile, filename);
	struct node* tree = haffmantree(sizeoffile, allfile);
	unsigned char* arr[256];
	for (int i = 0; i < 256; i++)
	{
		arr[i] = code(*tree, i);
	}
	int b = 0, c = 0;
	int chislo = 0;
	FILE* arc;
	unsigned char* name;
	name = (unsigned char*)malloc(100);
	for (int i = 0; i < 100; i++)
	{
		if (filename[i] != '.')
			name[c++] = filename[i];
		if (filename[i] == '.')
			break;
	}
	name[c++] = '.';
	name[c++] = 'a';
	name[c++] = 'r';
	name[c++] = 'c';
	name[c] = '\0';
	arc = fopen(name, "wb");
	for (int i = 0; i < 4; i++)
	{
		fprintf(arc, "%c", sizeoffile % 256);
		sizeoffile /= 256;
	}
	sizeoffile = copysizeoffile;
	fprintf(arc, "%c", strlen(filename));
	fprintf(arc, "%s", filename);
	fprintf(arc, "%c", tree->size);
	for (int i = 0; i < 256; i++)
	{
		if (arr[i][0] != '\0')
			fprintf(arc, "%c%c%s", i, strlen(arr[i]), arr[i]);
	}
	for (int i = 0; i < sizeoffile; i++)
	{
		int j = 0;
		while (arr[allfile[i]][j] != (char)0)
		{
			string[b++] = arr[allfile[i]][j];
			j++;
			if (b == 8)
			{
				for (int i = 7; i >= 0; i--)
				{
					if (string[7 - i] == '1')
						chislo += pow(2, i);
				}
				fprintf(arc, "%c", chislo);
				chislo = 0;
				b = 0;
			}
		}
	}
	if (b != 8)
	{
		while (b != 8)
			string[b++] = '0';
		for (int i = 7; i >= 0; i--)
			if (string[7 - i] == '1')
				chislo += pow(2, i);
		fprintf(arc, "%c", chislo);
	}
	fclose(arc);
	return name;
}

void arcfiles(char* arcname, char** filesforarc, int count)
{
	FILE* finalarc;
	finalarc = fopen(arcname, "wb");
	fprintf(finalarc, "%c", count);
	for (int i = 0; i < count; i++)
	{
		char* name = arc(filesforarc[i]);
		FILE* open = fopen(name, "rb");
		while (1)
		{
			char Byte = fgetc(open);
			if (feof(open) != 0)
				break;
			fprintf(finalarc, "%c", Byte);
		}
		fclose(open);
		remove(name);
	}
	fclose(finalarc);
}

void unzipfiles(char* filename)
{
	FILE* fin = fopen(filename, "rb");
	int n = fgetc(fin);
	for (int i = 0; i < n; i++)
	{
		unzip(fin);
	}
	fclose(fin);
}

char* printlist(FILE* arc)
{
	int sizeoffile = 0;
	unsigned char* string;
	string = (unsigned char*)malloc(100);
	fread(string, 4, 1, arc);
	for (int i = 0; i < 4; i++)
		sizeoffile += (int)string[i] * pow(256, i);
	memset(string, 0, 100);
	fread(string, 1, 1, arc);
	int sizeofname = 0;
	sizeofname = (int)string[0];
	memset(string, 0, 100);
	fread(string, sizeofname, 1, arc);
	unsigned char newstring[100];
	fread(newstring, 1, 1, arc);
	int uniqsymbols = (int)newstring[0];
	memset(newstring, 0, 100);
	unsigned char** arr;
	arr = (unsigned char**)malloc(256 * sizeof(unsigned char*));
	for (int i = 0; i < 256; i++)
		arr[i] = (unsigned char*)malloc(256 * sizeof(unsigned char));
	for (int i = 0; i < 256; i++)
		arr[i][0] = '\0';
	for (int i = 0; i < uniqsymbols; i++)
	{
		fread(newstring, 1, 1, arc);
		int index = (int)newstring[0];
		memset(newstring, 0, 100);
		fread(newstring, 1, 1, arc);
		int lengthofcode = (int)newstring[0];
		memset(newstring, 0, 100);
		fread(newstring, lengthofcode, 1, arc);
		for (int j = 0; j < lengthofcode; j++)
		{
			arr[index][j] = newstring[j];
			if (j == lengthofcode - 1)
				arr[index][j + 1] = '\0';
		}
		memset(newstring, 0, 100);
	}
	struct node* tree;
	tree = (struct node*)malloc(sizeof(struct node));
	tree->left = NULL;
	tree->right = NULL;
	struct node* first;
	first = (struct node*)malloc(sizeof(struct node));
	first = tree;
	for (int i = 0; i < 256; i++)
	{
		if (arr[i][0] != '\0')
		{
			int j = 0;
			while (arr[i][j] != '\0')
			{
				if (arr[i][j] == '0')
				{
					if (tree->right != NULL)
						tree = tree->right;
					else
					{
						struct node* newtree;
						newtree = (struct node*)malloc(sizeof(struct node));
						tree->right = newtree;
						newtree->left = NULL;
						newtree->right = NULL;
						tree = newtree;
					}
				}
				else
				{
					if (tree->left != NULL)
						tree = tree->left;
					else
					{
						struct node* newtree;
						newtree = (struct node*)malloc(sizeof(struct node));
						tree->left = newtree;
						newtree->left = NULL;
						newtree->right = NULL;
						tree = newtree;
					}
				}
				j++;
			}
			if (arr[i][j] == '\0')
				*tree->name = (char)i;
		}
		tree = first;
	}
	int count = 0;
	int t;
	unsigned char bytes[8];
	while (1)
	{
		memset(newstring, 0, 100);
		fread(newstring, 1, 1, arc);
		if (count == sizeoffile)
		{
			return string;
		}
		t = 7;
		for (int i = 0; i < 8; i++)
			bytes[i] = 0;
		while (newstring[0] > 0)
		{
			bytes[t--] = newstring[0] % 2;
			newstring[0] /= 2;
		}
		for (int k = 0; k < 8; k++)
		{
			if ((tree->left != NULL) || (tree->right != NULL))
			{
				if (bytes[k] == 0)
					tree = tree->right;
				else
					tree = tree->left;

			}
			if ((tree->left == NULL) && (tree->right == NULL))
			{
				tree = first;
				count++;
				if (count == sizeoffile)
				{
					return string;
				}
			}
		}
		for (int i = 0; i < 8; i++)
			bytes[i] = 0;
	}
}

void listunzipfiles(char* filename)
{
	FILE* fin = fopen(filename, "rb");
	int n = fgetc(fin);
	for (int i = 0; i < n; i++)
	{
		puts(printlist(fin));
	}
	fclose(fin);
}

void main(int argc, char** argv)
{
	char* arc_name = NULL;
	char** files = NULL;
	int i;
	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][2] == 'f')
			arc_name = argv[i + 1];
		if (argv[i][0] == '-' && argv[i][2] == 'c')
		{
			files = &argv[i + 1];
			arcfiles(arc_name, files, argc - i - 1);
			return;
		}
		if (argv[i][0] == '-' && argv[i][2] == 'e')
		{
			unzipfiles(arc_name);
			return;
		}
		if (argv[i][0] == '-' && argv[i][2] == 'l')
		{
			listunzipfiles(arc_name);
			return;
		}
	}
	return;
}
