#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
struct node{
	long long *arr;
	long long len;
	long long writes;
	long long comparisons;
	long long M;
	long long swaps;
	long long total;
};

struct trial{
	long long M;
	long long *writes;
	long long *comparisons;
	long long *swaps;
	long long *total;
	long double write_avg;
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
		key = test->arr[j];
		test->writes++;
		for(i = j - 1; (i >= 0) && ( test->arr[i]> key); i-- ){
			test->arr[i+1]= test->arr[i];
			test->comparisons++;
			test->writes++;
		}
		 test->arr[i+1]= key;
		 test->writes++;
	}
}


long long return_partition(node* test,long long left,long long right){
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
	return j;
}

void insertion_quick_sort(node* test,long long  left,long long  right){
	long long  pivot;
	
	 if(left<right){
		pivot = return_partition(test,left,right);
		test->writes++;
		insertion_quick_sort(test,left,pivot);
		insertion_quick_sort(test,pivot+1,right);
	}
}


int main(){
	node test;
	trial t;
	long long  i =10000;
	srand(time(NULL));
	long long p;
	cout<<"Enter the range of values: (100,1000..): ";
	cin>> p;
	//intitializing the values
//	for(long long  j=0;j<50;j++){
	
		test.arr = (long long * )malloc(10000*sizeof(long long ));
		test.len = 10000;
		t.comparisons = (long long * )malloc(1000*sizeof(long long ));
		t.swaps = (long long * )malloc(1000*sizeof(long long ));
		t.total = (long long * )malloc(1000*sizeof(long long ));
		t.writes = (long long * )malloc(1000*sizeof(long long ));
		test.M = 0;
		t.M = 0;
		test.comparisons=0;
		t.comp_avg =0;
		test.swaps = 0;
		t.swap_avg =0;
		test.writes =0;
		t.write_avg =0;
		t.total_avg =0;
		test.total =0;
//	}

	for(long long  k=0;k<1000;k++){
		if(k%10==0){
			system("CLS");
			cout<<"Loading... "<<k/10<<"%";
		}
		//each trial sorting all 50
//		for(long long  j=0;j<50;j++){
			//in each test, 1000 inputs
			for(long long  i =0;i<10000;i++){
				test.arr[i] = rand()%p;
			}
	
			test.total =0;
			test.writes =0;
			test.swaps = 0;
			test.comparisons=0;
			insertion_quick_sort(&test,0,test.len-1);
	
//		}
		
//		for(long long  z=0;z<50;z++){
			t.comparisons[k] = test.comparisons;
			t.swaps[k] = test.swaps;
			
			t.writes[k] = test.writes;
			t.total[k] = test.comparisons + test.writes;
//		}
	}
	system("CLS");

	long double w=0.000,c=0.000,s=0.000,to=0.000;
//	for(long long  i=0;i<50;i++){
		w=0.000;c=0.000;s=0.000;to=0.000;
		for(long long  j=0;j<1000;j++){
			w = w + t.writes[j];
			c = c + t.comparisons[j];
			s = s + t.swaps[j];
			to = to + t.total[j];
		}
		
		t.comp_avg = c/1000;
		t.swap_avg = s/1000;
		t.total_avg = to/1000;
		t.write_avg = w/1000;
//	}

	cout<<"value of K: "<<p<<endl;
	cout<<"\t  M  \t  Writes \t  Compar \t  swaps   \t  total \n";
	cout<<"---------------------------------------------------------------------"<<endl;
//	for(long long j=0;j<50;j++){
		cout<<"\t  "<<"  \t  "<<t.write_avg<<"  \t  "<< t.comp_avg<<"  \t  "<<t.swap_avg<<"  \t  "<<t.total_avg<<endl;
//	}

	return 1;
}
