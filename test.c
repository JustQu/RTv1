#include "stdio.h"
#include "time.h"

enum{
	b,g,r,a
};

typedef	union s_color
{
	int				color;
	unsigned char	bgra[4];
}				t_color;
int main()
{
	t_color col;
	t_color	atmp ={.color = 0xaabbcc};
	float	btmp = 0.5;
	int		g;
	int t1;
	int t2;
	float acc1;
	float acc2;

	acc1 = acc2 = 0;
	for (int j = 0; j < 100; j++)
	{
	t1 = clock();
	for (int i = 0; i < 10000000; i++)
	{
		g = i % 10;
		col = (t_color){.bgra[0] = atmp.bgra[0] * g,
						.bgra[1] = atmp.bgra[1] * g,
						.bgra[2] = atmp.bgra[2] * g};
	}
	acc1 += (clock() - t1) / (float)CLOCKS_PER_SEC;
	//printf("%f\n", (double)(clock() - t1) / CLOCKS_PER_SEC);

	t2 = clock();
	for (int i = 0; i < 10000000; i++)
	{
		g = i % 10;
		col.bgra[0] = atmp.bgra[0] * g;
		col.bgra[1] = atmp.bgra[2] * g;
		col.bgra[2] = atmp.bgra[2] * g;
		//col = (t_color){.bgra[0] = atmp.bgra[0] * g,
		//				.bgra[1] = atmp.bgra[1] * g,
		//				.bgra[2] = atmp.bgra[2] * g};
	}
	acc2 += (clock() - t2) / (float)CLOCKS_PER_SEC;
	//printf("%f\n", (double)(clock() - t1) / CLOCKS_PER_SEC);
	}
	printf("%f\n%f\n", acc1, acc2);
	printf("%d %d %d %d %.8x\n", col.bgra[b], col.bgra[g], col.bgra[r], col.bgra[a], col.color);
}
