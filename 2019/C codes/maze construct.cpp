#include<stdio.h>

int main()
{
	int FLOODVAL;
	for(int i=0; i<16; i++)
	{
		for(int j=0; j<16; j++)
		{
			if (i <= 7 && j <= 7)
            FLOODVAL = (7 - i) + (7- j) ;
      
            else if (i <= 7 && j >= 8)
            FLOODVAL = (7 - i) + (j - 8) ;
      
            else if (i >= 8 && j <= 7)
            FLOODVAL = (i - 8) + (7 - j) ;

            else
            FLOODVAL = (i - 8) + (j - 8) ;
            
            printf("%d  ",FLOODVAL);
		}
		 
		 printf("\n");
		
	}
}
