#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct cityloc
{
 char name[25];
 float x;
 float y;
 float pop;
};

struct cityloc cl[50];
struct cityloc cp;
int amount;

void un_sp (int i)
{
    int rep=1;

    while(1)
    {
        if(cl[i].name[rep] == 0)
            return;

        if(cl[i].name[rep] == '_')
            cl[i].name[rep] = ' ';

        rep++;
    }
}

void sp_un (int i)
{
    int rep=1;

    while(1)
    {
        if(cl[i].name[rep] == 0)
            return;

        if(cl[i].name[rep] == ' ')
            cl[i].name[rep] = '_';

        rep++;
    }
}

void dbread(void)
{

	FILE* fp;
	int rep;

	fp = fopen("data.txt", "r");

	if(fp == NULL)
    {
        printf("Error with opening file");
        exit(1);
    }

	for (rep = 0; rep <= 100; rep++)
	{
        if(feof(fp))
        {
            amount = rep;
            break;
        }
		fscanf(fp, "%s", cl[rep].name);
		fscanf(fp, "%f", &cl[rep].x);
		fscanf(fp, "%f", &cl[rep].y);
		fscanf(fp, "%f", &cl[rep].pop);
		un_sp(rep);
	}

	fclose(fp);
}

void city_list(void)
{
    int num;

    printf("NUM  NAME                   X    Y     POP.\n");

    for(num = 0; num <= (amount - 1); num++)
    {
        printf("%3d. %-20s %4.0f %4.0f %5.0f tys.\n", num, cl[num].name, cl[num].x, cl[num].y, cl[num].pop);
    }
}

void distance(void)
{
    int f_city, t_city;
    double dx, dy;

    printf("from: ");
    scanf("%d", &f_city);
    printf("to: ");
    scanf("%d", &t_city);

    while(getchar() != 10);

    if(f_city > amount-1 || f_city < 0 || t_city > amount-1 || t_city < 0)
    {
        printf("\nError, there is no such city\n");
        return;
    }

    dx = fabs(cl[f_city].x-cl[t_city].x);
    dy = fabs(cl[f_city].y-cl[t_city].y);

    printf("from %s to %s is %.2fkm\n", cl[f_city].name, cl[t_city].name, (sqrt(dx*dx+dy*dy))*3.336758893);
}

void swap_loc(int src, int dest)
{
    strcpy(cp.name, cl[dest].name);
    cp.x = cl[dest].x;
    cp.y = cl [dest].y;
    cp.pop = cl[dest].pop;

    strcpy(cl[dest].name, cl[src].name);
    cl[dest].x = cl[src].x;
    cl[dest].y = cl[src].y;
    cl[dest].pop = cl[src].pop;

    strcpy(cl[src].name, cp.name);
    cl[src].x = cp.x;
    cl[src].y = cp.y;
    cl[src].pop = cp.pop;
}

void swap_city(void)
{
    int city_s, city_d;

    printf("first city: ");
    scanf("%d", &city_s);
    printf("second city: ");
    scanf("%d", &city_d);

    while(getchar() != 10);

    if(city_s == city_d)
    {
        printf("\nError, you can't swap same city\n");
        return;
    }

    if(city_s > amount-1 || city_s < 0 || city_d > amount-1 || city_d < 0)
    {
        printf("\nError, there is no such city\n");
        return;
    }

    swap_loc(city_s, city_d);
}

void sort_x_city(void)
{
    int cx, ci, j;

    for(j = 0; j < amount-1; j++)
    {
        for(ci = j+1, cx = j; ci < amount; ci++)
            if(cl[cx].x > cl[ci].x)
                cx = ci;

        if(j != cx)
            swap_loc(cx, j);
    }
}

void sort_y_city(void)
{
    int cy, ci, j;

    for(j = 0; j < amount-1; j++)
    {
        for(ci = j+1, cy = j; ci < amount; ci++)
            if(cl[cy].y > cl[ci].y)
                cy = ci;

        if(j != cy)
            swap_loc(cy, j);
    }
}

void sort_name(void)
{
    int cn, ci, j, ret;

    for(j = 0; j < amount-1; j++)
    {
        for(ci = j+1, cn = j; ci < amount; ci++)
        {
            ret = strcmp(cl[cn].name, cl[ci].name);

            if(ret > 0)
                cn = ci;
            }

            if(j != cn)
                swap_loc(cn, j);
    }

}

void sort_pop(void)
{
    int cp, ci, j;

    for(j = 0; j < amount-1; j++)
    {
        for(ci = j+1, cp = j; ci < amount; ci++)
            if(cl[cp].pop < cl[ci].pop)
                cp = ci;

        if(j != cp)
            swap_loc(cp, j);
    }
}

void sort_pop2(void)
{
    int st, nd, i=0;

    while(i < amount-1)
    {
        for(st = 0, nd = st +1; nd < amount; st++, nd++)
            if(cl[st].pop > cl[nd].pop)
                swap_loc(st, nd);

        i++;
    }
}

void list_copy(void)
{
    FILE* fp;
	int rep;
	char file_name[50];

	printf("name new file: ");
	scanf("%s", file_name);

	strcat(file_name, ".txt");


	while(getchar() != 10);

	fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        fp = fopen(file_name, "w");
    }
    else
    {
        printf("\nERROR, there is already this file\n");
        return;
    }

    for (rep = 0; rep < amount; rep++)
    {
        sp_un(rep);
        fprintf(fp, "%s %.0f %.0f %.0f", cl[rep].name, cl[rep].x, cl[rep].y, cl[rep].pop);
        un_sp(rep);

        if(rep < amount-1)
        {
            fprintf(fp, "\n");
        }
    }


	fclose(fp);
}

void new_load(void)
{
    FILE* fp;
	int rep;
	char base[25];

    printf("what is file name of data base: ");
    scanf("%s", base);

    while(getchar() != 10);

    strcat(base, ".txt");

	fp = fopen(base, "r");

	if(fp == NULL)
    {
        printf("Error there is no such file");
        return;
    }

	for (rep = 0; rep <= 100; rep++)
	{
        if(feof(fp))
        {
            amount = rep;
            break;
        }
		fscanf(fp, "%s", cl[rep].name);
		un_sp(rep);
		fscanf(fp, "%f", &cl[rep].x);
		fscanf(fp, "%f", &cl[rep].y);
		fscanf(fp, "%f", &cl[rep].pop);

	}

	fclose(fp);
}

void help(void)
{
    printf("    c - city list\n");
    printf("    d - distance\n");
    printf("    x - sort by x\n");
    printf("    y - sort by y\n");
    printf("    n - sort by name\n");
    printf("    p - sort by population h->l\n");
    printf("    r - sort by population l->h\n");
    printf("    s - swap places\n");
    printf("    w - save data base\n");
    printf("    l - start program with other data base\n");
    printf("    ? - help\n");
    printf("    q - exit\n");
}

int main()
{
    char comm=0;
    int rep=0, ln=0;

    dbread();

    while(rep < 1)
    {
        ln = 0;

        printf("> ");

        comm = getchar();

        printf("\n");

        if(comm != 10)
            while(getchar() != 10);

        if(comm == 'c')
        {
            city_list();
            ln = 1;
        }

        else if(comm == 'd')
        {
            distance();
            ln = 1;
        }

        else if(comm == 'q')
        {
            exit(0);
            ln = 1;
        }

        else if(comm == 's')
        {
            swap_city();
            ln = 1;
        }

        else if(comm == 'x')
        {
            sort_x_city();
            ln = 1;
        }

        else if(comm == 'y')
        {
            sort_y_city();
            ln = 1;
        }

        else if(comm == 'n')
        {
            sort_name();
            ln = 1;
        }

        else if(comm == '?')
        {
            help();
            ln = 1;
        }

        else if(comm == 'p')
        {
            sort_pop();
            ln = 1;
        }

        else if(comm == 'w')
        {
            list_copy();
            ln = 1;
        }

        else if(comm == 'r')
        {
            sort_pop2();
            ln = 1;
        }

        else if(comm == 'l')
        {
            new_load();
            ln = 1;
        }

        else if (comm == '0')
        {
            printf("amount(0 counts)%4d\n", amount-1);
            ln = 1;
        }


        if(ln == 1)
            printf("\n");
        comm = 0;
    }
}
