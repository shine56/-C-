#include <stdio.h>
#include <stdlib.h>
int p(const void*a, const void*b)
{
	return (*(int*)a - *(int*)b);
}
int hh[20010], tt[20010];
int main()
{
	int h, t, i;
	
	while(scanf("%d %d", &h, &t))
	{
		if(h==0 && t==0) break;
		int min=1e9;
		for(i=0; i<h; i++)
		{
			scanf("%d", &hh[i]);
			if(hh[i]<min)
			min=hh[i];
		}
		for(i=0; i<t; i++)
			scanf("%d", &tt[i]);
		if(h>t)
			printf("Loowater is doomed!\n");
		else{	
			qsort(tt, t, sizeof(tt[0]), p);
			qsort(hh, h, sizeof(hh[0]), p);
			int j=0, sum=0, d=0;
			for(i=0; i<t; i++)
			{
				if(tt[i]>=min)
				{
					//printf("tt[%d]=%d, hh[%d]=%d\n", i, tt[i], j, min);
					if(tt[i]>=hh[j])
					{
						sum+=tt[i];
						j++;
					//	printf("j=%d\n", j);
						if(j==h)
						{
							d=1;
							printf("%d\n", sum);
							break;
						}
					}
				}
			}
			if(d==0)
				printf("Loowater is doomed!\n");
		}
	}
	return 0;
}
