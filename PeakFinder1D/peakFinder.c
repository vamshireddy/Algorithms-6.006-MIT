#include<stdio.h>

/*
	Peak finder problem where the peak is the number in the array whose neighbors are less than the number itself
*/

int peak_finder(int a[],int start,int end)
{
	if( start >= end )
	{
		return a[start];
	}
	
	int mid = start + (end-start)/2;
	if( a[mid] < a[mid+1] )
	{
		peak_finder(a,mid+1,end);
	}
	else if( a[mid] < a[mid-1] )
	{
		peak_finder(a,start,mid-1);
	}
	else
	{
		return a[mid];
	}
}

int main()
{
	int a[10] = {1,2,2,2,2,2,6,6,6,6};
	printf("The peak is %d\n",peak_finder(a,0,9));
}	
