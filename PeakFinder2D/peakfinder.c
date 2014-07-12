#include<stdio.h>



int max_finder(int* a, int col, int rows,int cols)
{
	int max = -1;
	int index = -1;

	int i;
	for(i=0;i<rows;i++)
	{
		if( a[i*cols+col] > max )
		{
			max = a[i*cols+col];
			index = i;
		}
	}
	return index;
}


int peak_finder(int *a, int start, int end, int rows, int cols)
{
	/*
	Do a binary search on the cols
	*/

	// Base case 
	if( start == end )
	{
		int val = max_finder(a,start,rows,cols);
		return a[ val * cols + start ];
	}
	//Recursive case

	int mid_col = start + (end-start)/2;

	int max_row = max_finder(a,mid_col,rows,cols);

	int max_val = a[ max_row * cols + mid_col ];

	if( (mid_col+1 < cols)  &&  max_val < a[ max_row * cols + mid_col + 1 ] )
	{
		return peak_finder(a, mid_col+1, end, rows, cols );
	}
	else if( (mid_col-1 >= 0 ) && max_val < a[ max_row * cols + mid_col - 1 ] )
	{
		
		return peak_finder(a, start, mid_col-1, rows, cols );
	}
	else
	{
		return max_val;
	}	
}


int main()
{
	int* matrix;
	int i,j;
	printf("ENTER M, N :");
	int m,n;
	scanf("%d %d",&m,&n);

	matrix = (int*)malloc(sizeof(int)*m*n);

	// Take matrix

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",matrix+(n*i)+j);
		}
	}
	printf("The matrix is \n");

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",*(matrix+(n*i)+j));
		}
		printf("\n");
	}
	printf("Peak is %d\n", peak_finder(matrix, 0, n-1, m, n ));
}
