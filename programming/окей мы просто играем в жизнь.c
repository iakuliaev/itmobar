#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>


int width = 0;
int height = 0;


int charTOint(char* number)
{
	int i = 0, count = 0, result = 0;
	while (number[i++] != NULL)
		count++;
	for (int j = 0; j < count; j++)
		result += (number[j] - 48) * pow(10, count - 1 - j);
	return result;
}

unsigned char* intTOchar(int number)
{
	unsigned char *res;
	res = (unsigned char*)malloc(1000);
	for (int i = 0; i < 1000; i++)
		res[i] = 0;
	int c = number, count = 0;
	while (c > 0)
	{
		count++;
		c = c / 10;
	}
	for (int i = 0; i < count; i++)
	{
		res[count - 1 - i] = number % 10 + 48;
		number = number / 10;
	}
	res[count++] = '.';
	res[count++] = 'b';
	res[count++] = 'm';
	res[count++] = 'p';
	return res;
}
int getsize(unsigned char* strings, int size)
{
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		int left = 0, right = 0;
		right = strings[i] % 16;
		left = (strings[i] / 16) % 16;
		result += right * pow(16, (double)(2 * i)) + left * pow(16, (double)(2 * i + 1));
	}
	return result;
}

void print(int** bitmap)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if(bitmap[j][i] == 0)
				printf("**");
			else
				printf("  ");
		}
		printf("\n");
	}
}

int** getbitmap(unsigned char* filename)
{
	FILE* fp;
	fp = fopen(filename, "rb");
	unsigned char strings[100000];
	if (fp == NULL)
		return 0;
	fread(strings, 18, 1, fp);
	memset(strings, 0, 18);
	fread(strings, 4, 1, fp);//øèðèíà
	width = getsize(strings, 4);
	memset(strings, 0, 4);
	fread(strings, 4, 1, fp);//âûñîòà
	height = getsize(strings, 4);
	memset(strings, 0, 4);// åñòü ðàçìåð êàðòèíêè
	fread(strings, 36, 1, fp);//ñêèïàåì ìóñîð
	memset(strings, 0, 36);
	int** bitmap;
	bitmap = (int**)malloc(height * sizeof(int));
	for(int i = 0; i < height; i++)
		bitmap[i] = (int*)malloc(width * sizeof(int));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			bitmap[i][j] = 0;
	int bignumber = 0;
	for (int i = 0; i < height; i++)
	{
		int count = 0;
		for (int j = 0; j < width; j++)
		{
			if (count % 32 == 0)
			{
				count = 0;
				fread(strings, 4, 1, fp);
				bignumber = (strings[0] << 24) + (strings[1] << 16) + (strings[2] << 8) + strings[3];
				memset(strings, 0, 4);
			}
			bitmap[i][j] = (bignumber >> (32 - 1 - count)) & 1;
			count++;
		}
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (bitmap[j][i] == 0)
				bitmap[j][i] = 1;
			else
				bitmap[j][i] = 0;
		}
	}
	fclose(fp);
	//print(bitmap);
	return(bitmap);
}



int neighbours(int** bitmap, int x, int y) //x - øèðèíà; y - âûñîòà
{
	int result = 0;
	if (x == width - 1)
	{
		if (y == height - 1)
		{
			result += bitmap[y - 1][x - 1] + bitmap[y][x - 1] + bitmap[y - 1][x];
			return result;
		}
		if (y == 0)
		{
			result += bitmap[y][x - 1] + bitmap[y + 1][x - 1] + bitmap[y + 1][x];
			return result;
		}
		result += bitmap[y][x - 1] + bitmap[y + 1][x] + bitmap[y - 1][x] + bitmap[y - 1][x - 1] + bitmap[y + 1][x - 1];
		return result;
	}
	if (x == 0)
	{
		if (y == height - 1)
		{
			result += bitmap[y - 1][x + 1] + bitmap[y - 1][x] + bitmap[y][x + 1];
			return result;
		}
		if (y == 0)
		{
			result += bitmap[y][x + 1] + bitmap[y + 1][x] + bitmap[y + 1][x + 1];
			return result;
		}
		result += bitmap[y][x + 1] + bitmap[y + 1][x] + bitmap[y - 1][x] + bitmap[y - 1][x + 1] + bitmap[y + 1][x + 1];
		return result;
	}
	if (y == 0)
	{
		result += bitmap[y][x + 1] + bitmap[y][x - 1] + bitmap[y + 1][x + 1] + bitmap[y + 1][x - 1];
		return result;
	}
	if (y == height - 1)
	{
		result += bitmap[y][x + 1] + bitmap[y][x - 1] + bitmap[y - 1][x + 1] + bitmap[y - 1][x - 1];
		return result;
	}
	result += bitmap[y][x + 1] + bitmap[y + 1][x + 1] + bitmap[y - 1][x + 1] + bitmap[y + 1][x] + bitmap[y - 1][x] + bitmap[y][x - 1] + bitmap[y + 1][x - 1] + bitmap[y - 1][x - 1];
	return result;

}
int** getnewgeneration(int** bitmap)
{
	int** newbitmap;
	newbitmap = (int**)malloc(height * sizeof(int));
	for (int i = 0; i < height; i++)
		newbitmap[i] = (int*)malloc(width * sizeof(int));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			newbitmap[i][j] = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if ((bitmap[i][j] == 0) && (neighbours(bitmap, j, i) == 3))
				newbitmap[i][j] = 1;
			if ((bitmap[i][j] == 1) && ((neighbours(bitmap, j, i) == 2) || (neighbours(bitmap, j, i) == 3)))
				newbitmap[i][j] = 1;
		}
	for (int i = 0; i < height; i++)
		free(bitmap[i]);
	free(bitmap);
	//print(newbitmap);
	return newbitmap;
}

unsigned char* makeSuperMegapicture(unsigned char* filename, int** newbitmap,int count,unsigned char* directory)
{
	FILE* fp;
	fp = fopen(filename, "rb");
	unsigned char strings[100000];
	fread(strings, 62, 1, fp);
	fclose(fp);
	unsigned char* newfile;
	newfile = (unsigned char*)malloc(2000);
	for (int i = 0; i < 2000; i++)
		newfile[i] = 0;
	int i = 0;
	while (directory[i] != 0)
	{
		newfile[i] = directory[i];
		i++;
	}
	newfile[i++] = '\\';
	int j = 0;
	unsigned char* adress = intTOchar(count);
	for (int j = 0; j < 1000; j++)
		newfile[i++] = adress[j];
	FILE* finalfile;
	finalfile = fopen(newfile, "wb");
	fwrite(&strings[0], 62, 1, finalfile);
	for(int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			if (newbitmap[j][i] == 0)
				newbitmap[j][i] = 1;
			else
				newbitmap[j][i] = 0;
		}
	int newcount;
	unsigned char buffer[4];
	for (int i = 0; i < 4; i++)
		buffer[i] = 0;
	for (int j = 0; j < height; j++)
	{
		newcount = 0;
		for (int i = 0; i < width; i++)
		{
			if (newcount == 32)
			{
				fwrite(&buffer[0], 4, 1, finalfile);
				newcount = 0;
				for (int i = 0; i < 4; i++)
					buffer[i] = 0;
			}
			buffer[newcount / 8] += newbitmap[j][i] * pow(2, (7 - newcount % 8));
			newcount++;
		}
		fwrite(&buffer[0], 4, 1, finalfile);
		newcount = 0;
		for (int i = 0; i < 4; i++)
			buffer[i] = 0;
	}
	for (int i = 0; i < height; i++)
		free(newbitmap[i]);
	free(newbitmap);
	fclose(finalfile);
	return newfile;
}



int main(int argc, char* argv[])
{
	unsigned char task[100];
	unsigned char* command;
	command = (unsigned char*)malloc(10000);
	unsigned char* dirrectory;
	dirrectory = (unsigned char*)malloc(10000);
	int count = 100;
	int freq = 1;
	for (int i = 0; i < argc; i++)
	{
		if (argv[i][2] == 'i')
			command = argv[i + 1];
		if (argv[i][2] == 'o')
			dirrectory = argv[i + 1];
		if (argv[i][2] == 'm')
			count = charTOint(argv[i + 1]);
		if (argv[i][2] == 'd')
			freq = charTOint(argv[i + 1]);
	}
	command = makeSuperMegapicture(command, getnewgeneration(getbitmap(command)), 1, dirrectory);
	for(int j = 2; j <= count * freq ; j++)
		command = makeSuperMegapicture(command, getnewgeneration(getbitmap(command)), j, dirrectory);
	
	for (int j = 1; j <= count * freq; j++)
		if (j % freq != 0)
		{
			char newdirrectory[10000];
			for (int e = 0; e < 10000; e++)
				newdirrectory[e] = dirrectory[e];
			int m = 0;
			while (newdirrectory[m] != NULL)
			{
				if (newdirrectory[m] == '\\')
					newdirrectory[m] = '/';
				m++;
			}
			
			newdirrectory[m++] = '/';
			unsigned char* newJ = intTOchar(j);
			for (int r = 0; r < 1000; r++)
				newdirrectory[m++] = newJ[r];
			
			remove(newdirrectory);
		}
	return 0;
}
