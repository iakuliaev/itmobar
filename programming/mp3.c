#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

void myprint(char* string, int megaN)
{
	for (int i = 0; i < megaN; i++)
	{
		if (string[i] == '\0')
			string[i] = ' ';
		printf("%c", string[i]);
	}
	printf("\n");
}

int supermegareader(char* superArray, int megaN,FILE *myfile)
{
	unsigned char mem ;
	for (int i = 0; i < megaN; i++)
	{
		mem = fgetc(myfile);
		if (mem == EOF)
			return 0;
		superArray[i] = mem;
	}
	return 1;
}

int hex(char* s, int n)
{
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		result += s[i] * pow(16, (n - 1 - i));
	}
	return result;
}

void show(FILE* fp)
{
	int a = 0, tmp, b = 1, utf = 0, le = 0, be = 0;
	char strings[100000];
	char lecod[100000];
	if (fp == NULL)
		return 0;
	b = supermegareader(&strings[0], 10, fp);//çàãîëîâîê
	//myprint(strings, 3);
	memset(strings, 0, 100000);
	while (b == 1)
	{
		if (b == 0)
			break;
		b = supermegareader(&strings[0], 4, fp);//id ôðåéìà
		if (strings[0] != 0)
			printf("%s: ", strings);
		memset(strings, 0, 100000);
		if (strings == "")
			break;
		b = supermegareader(&strings[0], 4, fp);//ñêîê áàéòîâ íàäî ïîä õðàíåíèå èíôû
		tmp = hex(strings, 4);// ïðåîáðàçîâàëè èç 16--> â 10
		if (tmp == 0)
			break;
		memset(strings, 0, 100000);
		if (b == 0)
			break;
		b = supermegareader(&strings[0], 2, fp);//ñ÷èòûâàíèå äâóõ ôëàãîâ(ïðîñòî åñòü)
		memset(strings, 0, 100000);
		supermegareader(&strings[0], 1, fp);
		utf = (int)strings[0];
		if ((utf != 1) && (utf != 0))
			printf("%c", strings[0]);
		memset(strings, 0, 100000);
		if (utf == 1)
		{
			supermegareader(&strings[0], 2, fp);
			unsigned char first, second;
			first = (unsigned char)strings[0];
			second = (unsigned char)strings[1];
			if (first == 255)
				le = 1;
			else
				be = 1;
			if ((first == 0) && (second == 0))
			{
				memset(strings, 0, 100000);
				supermegareader(&strings[0], tmp - 3, fp);
				myprint(strings, tmp - 3);
				utf = 0;
			}
		}
		memset(strings, 0, 100000);
		if (utf == 1)
		{
			supermegareader(&strings[0], tmp - 3, fp);//ñ÷èòûâàíèå ñàìîé èíôû
			if (le == 1)
			{
				for (int c = 0; c < 100000; c++)
					lecod[c] = 0;
				int d = 0;
				for (int c = 0; c < tmp - 3; c++)
				{
					lecod[c] = strings[d];
					d += 2;
				}
				myprint(lecod, tmp - 3);
			}
		}
		else
		{
			b = supermegareader(&strings[0], tmp - 1, fp);//ñ÷èòûâàíèå ñàìîé èíôû
			if (strings[0] != 0)
				myprint(strings, tmp - 1);
			else
			{
				int probel = 0;
				while ((probel < 100000) && (strings[probel++] == ' '))
					;
				if (probel < 100000)
					printf("%s\n", &strings[probel]);
			}
			memset(strings, 0, 100000);
			if (b == 0)
				break;
		}
		memset(strings, 0, 100000);
	}

}

void myget(FILE* fp, char* met)
{
	int a = 0, tmp, b = 1, utf = 0, le = 0, be = 0, flag = 0;
	char strings[100000];
	char lecod[100000];
	if (fp == NULL)
		return 0;
	b = supermegareader(&strings[0], 10, fp);//çàãîëîâîê
	memset(strings, 0, 100000);
	while (b == 1)
	{
		if (b == 0)
			break;
		b = supermegareader(&strings[0], 4, fp);//id ôðåéìà
		if ((strings[0] != 0) && (strcmp(strings, met) == 0))
		{
			flag = 1;
			printf("%s: ", strings);
		}
		memset(strings, 0, 100000);
		if (strings == "")
			break;
		b = supermegareader(&strings[0], 4, fp);//ñêîê áàéòîâ íàäî ïîä õðàíåíèå èíôû
		tmp = hex(strings, 4);// ïðåîáðàõîâàëè èç 16--> â 10
		if (tmp == 0)
			break;
		memset(strings, 0, 100000);
		if (b == 0)
			break;
		b = supermegareader(&strings[0], 2, fp);//ñ÷èòûâàíèå äâóõ ôëàãîâ
		memset(strings, 0, 100000);
		supermegareader(&strings[0], 1, fp);
		utf = (int)strings[0];
		if ((utf != 1) && (utf != 0))
			if (flag == 1)
				printf("%c", strings[0]);
		memset(strings, 0, 100000);
		if (utf == 1)
		{
			supermegareader(&strings[0], 2, fp);
			unsigned char first, second;
			first = (unsigned char)strings[0];
			second = (unsigned char)strings[1];
			if (first == 255)
				le = 1;
			else
				be = 1;
			if ((first == 0) && (second == 0))
			{
				memset(strings, 0, 100000);
				supermegareader(&strings[0], tmp - 3, fp);
				if (flag == 1)
					myprint(lecod, tmp - 3);
				utf = 0;
			}
		}
		memset(strings, 0, 100000);
		if (utf == 1)
		{
			supermegareader(&strings[0], tmp - 3, fp);//ñ÷èòûâàíèå ñàìîé èíôû
			if (le == 1)
			{
				for (int c = 0; c < 100000; c++)
					lecod[c] = 0;
				int d = 0;
				for (int c = 0; c < tmp - 3; c++)
				{
					lecod[c] = strings[d];
					d += 2;
				}
				if (flag == 1)
					myprint(lecod, tmp - 3);
			}
		}

		else
		{
		
			b = supermegareader(&strings[0], tmp - 1, fp);//ñ÷èòûâàíèå ñàìîé èíôû
			if ((strings[0] != 0) && (flag == 1))
				myprint(strings, tmp - 1);
			else
			{
				int probel = 0;
				while ((probel < 100000) && (strings[probel++] == ' '))
					;
				if ((probel < 100000) && (flag == 1))
					printf("%s\n", &strings[probel]);
			}
			memset(strings, 0, 100000);
			if (b == 0)
				break;
			
		}
		memset(strings, 0, 100000);
		if (flag == 1)
			return;
	}
}

void set(FILE* fp, char* param, char* value, char* filename)
{
	if (fp == NULL)
		return 0;
	long long size = 0;
	int i = 0;
	int counter = 10;
	while (fgetc(fp) != EOF)
		size++;
	fseek(fp, 0, SEEK_SET);

	unsigned char* filebytes;
	filebytes = (unsigned char*)malloc(size);

	fread(filebytes, 1, size, fp);
	fseek(fp, 0, SEEK_SET);
	//for (int j = 0; j < size; j++)
		//printf("%c", filebytes[j]);
	fseek(fp, 0, SEEK_SET);
	int a = 0, tmp, b = 1, utf = 0, le = 0, be = 0, flag = 0;
	char strings[100000];
	b = supermegareader(&strings[0], 10, fp);//çàãîëîâîê
	memset(strings, 0, 100000);
	while (b == 1)
	{
		b = supermegareader(&strings[0], 4, fp);//id ôðåéìà
		counter += 4;
		if ((strings[0] != 0) && (strcmp(strings, param) == 0))
			flag = 1;
		memset(strings, 0, 100000);
		b = supermegareader(&strings[0], 4, fp);//ñêîê áàéòîâ íàäî ïîä õðàíåíèå èíôû
		counter += 4;
		tmp = hex(strings, 4);// ïðåîáðàõîâàëè èç 16--> â 10
		if (tmp == 0)
			break;
		memset(strings, 0, 100000);
		if (b == 0)
			break;
		b = supermegareader(&strings[0], 2, fp);//ñ÷èòûâàíèå äâóõ ôëàãîâ
		counter += 2;
		memset(strings, 0, 100000);
		if (flag == 1)
		{
			int newsize = 0;
			while (value[newsize] != NULL)
				newsize++;
			newsize++;
			filebytes[counter - 6] = (newsize >> 24) & 15;
			filebytes[counter - 5] = (newsize >> 16) & 15;
			filebytes[counter - 4] = (newsize >> 8) & 15;
			filebytes[counter - 3] = newsize & 15;
			char* before, *after, *addnew;
			before = (char*)malloc(counter);
			for (int i = 0; i < counter; i++)
				before[i] = filebytes[i];
			addnew = (char*)malloc(newsize);
			addnew[0] = 0;
			for (int i = 0; i < newsize - 1; i++)
				addnew[i + 1] = value[i];
			after = (char*)malloc(size - counter - tmp);
			for (int i = 0; i < size - counter - tmp; i++)
				after[i] = filebytes[counter + tmp + i];
			char* newfile;
			newfile = (char*)malloc(size + newsize - tmp);
			for (int i = 0; i < counter; i++)
				newfile[i] = before[i];
			for (int i = counter; i < newsize + counter; i++)
				newfile[i] = addnew[i - counter];
			for (int i = newsize + counter; i < newsize + size - tmp; i++)
				newfile[i] = after[i - newsize - counter];
			fclose(fp);
			FILE* finalfile;
			finalfile = fopen(filename, "wb");
			fwrite(&newfile[0], 1, size + newsize - tmp, finalfile);
			fclose(finalfile);
			return;
		}
		b = supermegareader(&strings[0], tmp, fp);
		memset(strings, 0, 100000);
		counter += tmp;
	}

}

int main(int argc, char* argv[])
{
	FILE* fp;
	char command[100];
	if (argc >= 3)
	{
		memcpy(command, argv[1], 100);
		fp = fopen(&command[11], "rb");
		if (command[2] != 'f')
			return 0;
		if ((argv[2][2] == 's') && (argv[2][3] == 'h'))
			show(fp);
		memcpy(command, argv[2], 100);
		if (argv[2][2] == 'g')
			myget(fp, &command[6]);
		memcpy(command, argv[2], 100);
		if ((argv[2][2] == 's') && (argv[2][3] == 'e'))
			set(fp, &command[6], &argv[3][8], &argv[1][11]);
	}
	return 0;
}
