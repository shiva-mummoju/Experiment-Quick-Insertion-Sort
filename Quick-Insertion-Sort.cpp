#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//the data where sort is taking place
struct node{
	//sample array for each small case
	long long *arr;
	long long len;
	//number of writes that took place in that particular array while sorting it.
	long long writes;
	//for comparisons
	long long comparisons;
	//the M value under which insertion sort took place for this particular array.
	long long M;
	//no of swaps
	long long swaps;
	// writes plus comparisons
	long long total;
};

struct trial{
	//m 25
	long long M;
	//1000 element array where your storing all the wwrites of 1000 times sort. 
	long long *writes;
	// 1000 element array 
	long long *comparisons;
	//1000 element array
	long long *swaps;
	// 1000 element arrays.
	long long *total;
	//adding all the values in the *writes array and doing avg
	long double write_avg;
	// comparisons /1000
	long double comp_avg;
	long double swap_avg;
	long double total_avg;
};


void display(node* test){
	for(long long i=0;i<test->len;i++)
	{
		cout<<test->arr[i]<<" ";
	}
	cout<<endl;
}

void insertion_sort(node* test,long long left,long long right){
	long long i,j,key;
	
	for(j = left + 1; j <= right; j++){
		//selecting each element in the input array to be inserted to the sorted sub array
		key = test->arr[j];
		test->writes++;
		//finding the place in the sorted sub array where they can fit
		for(i = j - 1; (i >= 0) && ( test->arr[i]> key); i-- ){
			//increment all the values position by 1
			test->arr[i+1]= test->arr[i];
			test->comparisons++;
			test->writes++;
		}
		//placing key in the empty slot created.
		 test->arr[i+1]= key;
		 test->writes++;
	}
}


long long return_partition(node* test,long long left,long long right){
	//l is the pivot element and i am choosing pivot to be first element.
	int l = test->arr[left];
	test->writes++;
	long long  i = left - 1;
	long long  j = right + 1;
	long long  temp;
	
	do{
		
		do{
			j--;
			test->comparisons++;
		}while(l < test->arr[j]);
		
		do{
			i++;
			test->comparisons++;
		}while(l >  test->arr[i]);
		
		
		if( i < j){
			test->comparisons++;
			test->swaps++;
			temp = test->arr[i];
			 test->arr[i]=  test->arr[j];
			test->arr[j]= temp;
		}
		
	
		test->comparisons++;
	
	}while(i < j);
	
	
	// during the quick sort, the index of pivot will change, J represents the index of the changed place of pivot(new Index of pivot)
	return j;
}

// test.M test->M

void insertion_quick_sort(node* test,long long  left,long long  right){
	long long  pivot;
	//when the array lengh is less than M.
	if(  (right-left)    <  test->M ) {
		//do insertion sort
		insertion_sort(test,left,right);
		return ;
		//if the len is greater than M, do  regular quick sort
	}else if(left<right){
		//selecting a pivot element. Pivot element selected by return_partition array. This function also sorts the arrray acc to quick sort
		pivot = return_partition(test,left,right);
		test->writes++;
		//do quick sort to the sub array left of pivot
		insertion_quick_sort(test,left,pivot);
		//do quick sort to the sub array right of pivot
		insertion_quick_sort(test,pivot+1,right);
	}
}


int main(){
	//for each K value you need 50 M values where sorting has to be done
	node test[50];
	//for each M value, you need 1000 places or spaces to remember all the writes and comparisons etc.
	trial t[50];
	long long  i = 10000;
	srand(time(NULL));
	long long p = 0;
	cout<<"Enter range of the values: (100 or 1000): ";
	cin>>p;
	//intitializing the values
	for(long long  j=0;j<50;j++){
		//dynammically allocaing memory 
		
		//size of input array is 10000 each time for each M for each trial 
		test[j].arr = (long long * )malloc(10000*sizeof(long long ));
		test[j].len = 10000;
		// to store the 1000 trials for each M value.
		t[j].comparisons = (long long * )malloc(1000*sizeof(long long ));
		t[j].swaps = (long long * )malloc(1000*sizeof(long long ));
		t[j].total = (long long * )malloc(1000*sizeof(long long ));
		t[j].writes = (long long * )malloc(1000*sizeof(long long ));
		test[j].M = j+1;
		t[j].M = j+1;
		test[j].comparisons=0;
		t[j].comp_avg =0;
		test[j].swaps = 0;
		t[j].swap_avg =0;
		test[j].writes =0;
		t[j].write_avg =0;
		t[j].total_avg =0;
		test[j].total =0;
	}
	
	
	// where we do for a given K value, 1-50M and for each M thouand trials
	for(long long  q=0;q<1000;q++){
		//refreshing the output window
		if(q%10==0){
			system("CLS");
			cout<<"Loading... "<<q/10<<"%";
		}
		//each trial sorting all 50 M values.
		for(long long  j=0;j<50;j++){
			//in each test, 10000 inputs( length of the array)
			for(long long  i =0;i<10000;i++){
				//initiallizing the test array with random values. rand()%k indicates rand() reuturns value less than K
				test[j].arr[i] = rand()%p;
			}
			
			test[j].total =0;
			test[j].writes =0;
			test[j].swaps = 0;
			test[j].comparisons=0;
			//quick insertion sort called for each value of M
			insertion_quick_sort(&test[j],0,test[j].len-1);
	
		}
		//storing the values of each trial(0-1000) in the trial structure
		for(long long  z=0;z<50;z++){
			t[z].comparisons[q] = test[z].comparisons;
			t[z].swaps[q] = test[z].swaps;
			
			t[z].writes[q] = test[z].writes;
			t[z].total[q] = test[z].comparisons + test[z].writes;
		}
	}
	system("CLS");
	//finding out the average values for 1000 trials
	long double w=0.000,c=0.000,s=0.000,to=0.000;
	for(long long  i=0;i<50;i++){
		w=0.000;c=0.000;s=0.000;to=0.000;
		for(long long  j=0;j<1000;j++){
			//summing all writes
			w = w + t[i].writes[j];
			c = c + t[i].comparisons[j];
			s = s + t[i].swaps[j];
			to = to + t[i].total[j];
		}
		//finding avg
		t[i].comp_avg = c/1000;
		t[i].swap_avg = s/1000;
		t[i].total_avg = to/1000;
		t[i].write_avg = w/1000;
	}

	cout<<"value of K: "<<p<<endl;
	cout<<"\t  M  \t  Writes \t  Compar \t  swaps   \t  total \n";
	cout<<"---------------------------------------------------------------------"<<endl;
	for(long long j=0;j<50;j++){
		cout<<"\t  "<<t[j].M<<"  \t  "<<t[j].write_avg<<"  \t  "<< t[j].comp_avg<<"  \t  "<<t[j].swap_avg<<"  \t  "<<t[j].total_avg<<endl;
	}

	return 1;
}
