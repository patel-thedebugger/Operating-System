#include<iostream>
#include<fstream>
using namespace std ;

int scheduler(int **a, int n)
{
	int x = 0 ;
	for( int i = 0 ; i < n ; i++)
	{
		if(a[x][1] > a[i][1] )
		{
			x = i ;
		}
	}
	return a[x][0] ;
}
int index(int **a, int n,int pid)
{
	
	for( int i = 0 ; i < n ; i++)
	{
		if(a[i][0] == pid )
		{
			return i;
		}
	}
}
void completed(int **arr, int n ,int x )
{
	for( int i = x ; i < n-1 ; i++ )
	{
		for( int j = 0 ; j < 3 ; j++)
		{
			arr[i][j] = arr[i+1][j];
		}
	}
}
int main()
{
	ifstream fin("input.txt");
	
	int n ;
	cout<<"Enter the number of process : ";fin>>n;
	cout<<n<<endl;
	int size = n ;
	int **arr = (int**)new int[n];
	int **pro = (int**)new int[n];
	for( int i = 0 ; i < n ; i++)
	{
		arr[i] = (int*)new int[6];
		pro[i] = (int*)new int[6];
		cout<<"Enter the  ID ,arrival Time , Burst time of P"<<i+1<<" : ";
		for( int j = 0 ; j < 3 ; j++)
		{
			
			fin>>arr[i][j];
			cout<<arr[i][j]<<" ";
			pro[i][j] =arr[i][j] ;
		}
		cout<<endl;
	}
	int pid;
	int p;
	int completion_time = 0 ;
	for( int i = 0 ; i < size ; i++)
	{
		pid = scheduler(arr, n) - 1;
		p= index(arr, n,pid+1);
		//cout<<p<<endl;
		completion_time += arr[p][2];
		pro[pid][3] = completion_time;
		if(i!=size-1)
		{
			completed(arr, n ,p );
			n--;
		}
		//cout<<endl<<i<<" "<<pid<<" "<<n<<endl ;
		//cout<<"arr :"<<endl;
		/*for( int i = 0 ; i < n ; i++)
		{
			for( int j = 0 ; j < 4 ; j++)
			{
				cout<<arr[i][j]<<" ";
			}
			cout<<endl;
		}*/
		
	}
	cout<<"Answer : "<<endl;
	for( int i = 0 ; i < size ; i++)
	{
		pro[i][4] = pro[i][3] - pro[i][1];
		pro[i][5] = pro[i][4] - pro[i][2];
	}
	for( int i = 0 ; i < size ; i++)
	{
		for( int j = 0 ; j < 6 ; j++)
		{
			cout<<pro[i][j]<<" ";
		}
		cout<<endl;
	}
}
