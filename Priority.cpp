#include<iostream>
#include<fstream>
using namespace std ;

int completion_time;

int scheduler(int **a, int n)
{
	int x = 0 ;
    int pri = a[x][3];
    //cout<<cpt<<"_";
	for( int i = 1 ; i < n ; i++)
	{
		if( a[i][3] < pri && a[i][1] <= completion_time )
		{
            pri = a[i][3];
            //cout<<"//";
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
    return 0;
}

void completed(int **arr, int n ,int x )
{
	for( int i = x ; i < n-1 ; i++ )
	{
		for( int j = 0 ; j < 4 ; j++)
		{
			arr[i][j] = arr[i+1][j];
		}
	}
}
void consume(int** arr,int n,int p)
{
    if(arr[p][2] == 1)
    {
        arr[p][4] =  completion_time+1;
        completion_time+=1;
        completed(arr,n,p);
    }
    else
    {
        arr[p][2]--;
        completion_time++;
    }
}
void respresent(int *arr , int size)
{
    for( int i = 0 ; i < size ; i++)
    {
        switch(i)
        {
            case 0:
                cout<<"|  "<<arr[i]<<"  ";
                break;
            case 1:
                cout<<"|      "<<arr[i]<<"       ";
                break;
            case 2:
                cout<<"|      "<<arr[i]<<"      ";
                break;
            case 3:
                cout<<"|     "<<arr[i]<<"     ";
                break;
            case 4:
                cout<<"|        "<<arr[i]<<"       ";
                if(arr[i]<10)
		            cout<<" ";
                
                break;
            case 5:
                cout<<"|   "<<arr[i]<<"  ";
                if(arr[i]<10)
		            cout<<" ";
                break;
            case 6:
                cout<<"|  "<<arr[i]<<"  ";
                break;

        }
            
        
    }
}
int main()
{
    ifstream fin("input.txt");
	
	int n ;
	cout<<"Enter the number of process : ";
    fin>>n;
	cout<<n<<endl;
	int size = n ;
	int **arr = (int**)new int[n];
	int **pro = (int**)new int[n];

    int pid;
	int p;
	completion_time = 0 ;

	for( int i = 0 ; i < n ; i++)
	{
		arr[i] = (int*)new int[7];
		pro[i] = (int*)new int[7];
		cout<<"Enter the  ID ,arrival Time , Burst time , Priority of P"<<i+1<<" : ";
		for( int j = 0 ; j < 4 ; j++)
		{
			fin>>arr[i][j];
			cout<<arr[i][j]<<" ";
			pro[i][j] =arr[i][j] ;
		}
		cout<<endl;
	}
    //cout<<completion_time;
    cout<<endl<<endl;
    while(1)
    {
        pid = scheduler(arr, n) ;
        cout<<"P"<<pid<<" ";
		p= index(arr, n,pid);
		//cout<<p<<endl;
        if(n == 1)
        {
            pro[pid-1][4] = completion_time + arr[p][2];
            n--;
            //cout<<completion_time;
            goto next;
        }
        else if(arr[p][2] == 1)
        {
            pro[pid-1][4] =  completion_time+1;
            completion_time+=1;
            //cout<<completion_time<<endl;
            completed(arr,n,p);
            //consume(arr,n,p);
            n--;
        }
        else
            consume(arr,n,p);

        //cout<<completion_time<<endl;
    }
    next:
    int AWT = 0;
    int TAT = 0;
    for( int i = 0 ; i < size ; i++)
	{
		pro[i][5] = pro[i][4] - pro[i][1];
        TAT+=pro[i][5];
		pro[i][6] = pro[i][5] - pro[i][2];
        AWT+=pro[i][6];
	}
    for( int i = 0 ; i < size ; i++)
	{
        free(arr[i]);
	}
    free(arr);
    cout<<endl<<endl<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"| PID | Arrival Time |  Burst time |  Priority | Completion Time |  TAT  |  WT  |"<<endl;
    cout<<"|-----+--------------+-------------+-----------+--------------------------------|"<<endl;
    for( int i = 0 ; i < size ; i++)
	{
        respresent(pro[i],7);
		if(pro[i][6]>=10)
		    cout<<"|"<<endl;
        else
            cout<<" |"<<endl;
	}
    cout<<"ATAT :  "<<(float)TAT/size<<endl;
    cout<<"AWT   : "<<(float)AWT/size<<endl;
}