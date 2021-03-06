#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

int getTotalLine(char *name);

int main()
{
	FILE *fp;
	char buffer[100];
	char name[] = "g_code.txt", len_buf[100][10];
	int len = getTotalLine(name);

	float **location = (float **)malloc(sizeof(float *) * len);
	for (int i = 0; i < len; i++) location[i] = (float*)malloc(sizeof(float) * 2);


	fp = fopen(name, "r");
	

	int count = 0, cnt = 0;
	while (fgets(buffer, 100, fp) != NULL)
	{
		if (buffer[0] == 'G' && buffer[1] == '1')
		{
			if (buffer[3] == 'E') continue;
			count++;
		}
		else if (buffer[0] == ';')
		{
			if (buffer[2] == 'l' && buffer[3] == 'a' && buffer[4] == 'y' && buffer[5] == 'e' && buffer[6] == 'r') // z checker
			{
				//if (buffer[12] != 'Z') continue;
				count++;
				printf("%d\n", count);
				sprintf(len_buf[cnt++], "%d", count+1);
				count = 0;
			}
		}
	}

	fclose(fp);
	fp = fopen(name, "r"); 

	int count1 = 0, cl = 2, count2 = 1;
	FILE *fpp = fopen("parsing.txt", "w+");
	char buf[100];
	fputs("const float PROGMEM xy_pos1[912][2] = { \n", fpp); // file push

	while (fgets(buffer, 100, fp) != NULL)
	{

		if (buffer[0] == 'G' && buffer[1] == '1')
		{
			if (buffer[3] == 'E') continue;
			fputs("  { ", fpp); // file push
			char buf1[10], buf2[10], toggle = 0, cnt1 = 0, cnt2 = 0;

			for (int i = 0; i < 10; i++)
			{
				if (toggle == 1)
				{
					if (buffer[2 + i] == ' ')
					{
						buf1[cnt1] = '\0';
						toggle = 0;
					}
					else buf1[cnt1++] = buffer[2 + i];
				}
				else if (buffer[2 + i] == 'X')
				{
					toggle = 1;
				}
			}
			for (int i = 0; i < 15; i++)
			{
				if (toggle == 1)
				{
					if (buffer[10 + i] == ' ')
					{
						buf2[cnt2] = '\0';
						toggle = 0;
					}
					else buf2[cnt2++] = buffer[10 + i];
				}
				else if (buffer[10 + i] == 'Y')
				{
					toggle = 1;
				}
			}

			location[count1][0] = atof(buf1);
			location[count1][1] = atof(buf2);
			count1++;
			fputs(buf1, fpp); // file push
			fputs(", ", fpp); // file push
			fputs(buf2, fpp); // file push
			fputs(" }, \n", fpp); // file push
		}
		else if (buffer[0] == ';')
		{
			if (buffer[2] == 'l' && buffer[3] == 'a' && buffer[4] == 'y' && buffer[5] == 'e' && buffer[6] == 'r') // z checker
			{
				//if (buffer[12] != 'Z') continue;
				fputs("  { ", fpp); // file push
				char buf1[10], buf2[10], toggle = 0, cnt = 0;

				buf1[0] = '-';
				buf1[1] = '1';
				buf1[2] = '.';
				buf1[3] = buffer[8];
				if (buffer[9] != ',')
				{
					buf1[4] = buffer[9];
					buf1[5] = '\0';
				}
				else buf1[4] = '\0';

				for (int i = 0; i < 15; i++)
				{
					if (toggle == 1)
					{
						if (buffer[10 + i] == ' ') continue;
						if (buffer[10 + i] == '\n')
						{
							buf2[cnt] = '\0';
							toggle = 0;
							i = 10;
						}
						else buf2[cnt++] = buffer[10 + i];
					}
					else if (buffer[10 + i] == '=')
					{
						toggle = 1;
					}
				}
				count++;
				printf("%d \n", count1 + 1);

				char d[10];
				sprintf(d, "%d", cl++);

				fputs(buf1, fpp); // file push
				fputs(", ", fpp); // file push
				fputs(buf2, fpp); // file push
				fputs(" }, \n", fpp); // file push
				fputs("}; \n", fpp); // file push
				fputs("const float PROGMEM xy_pos", fpp);
				fputs(d, fpp);
				fputs("[", fpp);
				fputs(len_buf[count2++], fpp);
				fputs("][2] = { \n", fpp); // file push
			}
		}

	}
	fputs("};", fpp); // file push

	char h[10];
	sprintf(h, "%d", cnt);
	fputs("const int len_cnt[", fpp);
	fputs(h, fpp);
	fputs("] = { \n", fpp);
	for (int i = 0; i < cnt; i++) 
	{
		fputs(len_buf[i], fpp);
		fputs(", \n", fpp);
	}
	fputs("};", fpp); // file push

	printf("%d", count + 1);

	if (0)
	{
		printf("const float PROGMEM xy_pos[911][2] = { \n");
		for (int i = 0; i < len; i++)
		{
			printf("{ ");
			for (int j = 0; j < 2; j++)
			{
				printf("%.3f ", location[i][j]);
				printf(", ");
			}
			printf("}, \n");
		}
		printf("};");
	}

	fclose(fp);
	return 0;
}


int getTotalLine(char *name)
{
	FILE *fp;
	int line = 0;
	char c;
	fp = fopen(name, "r");
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n') line++;

	fclose(fp);
	return(line);
}
