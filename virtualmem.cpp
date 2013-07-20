#include<iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include<sys/time.h>
#include <sstream>
#include <string>
#include <fstream>
#include<iostream>
using namespace std;
int frame=5;
int seq[100];
int pg;
unsigned int opt_time;
void fifo(int b[], int n, int m)
{
int c=0,k=0,miss=0,hit=0,q=0;
int a[m];
unsigned int f_time;
struct timeval tvs,tve;
bool o=false;
for(int x=0;x<m;x++)
a[x]=-1;


cout<<"\nInitial Elements in frame\n\n";
gettimeofday(&tvs, NULL);
for(int x=0;x<m;x++)
cout<<a[x];

int i=0;
do
{

o=false;
int j=0;
while(j<m)
{
if(o==false && a[j]!=-1) 
if(a[j]==b[i])
{

hit++;
o=true;

}

j++;

}

if(o==false)
{
miss++;
q=c%m;
a[q]=b[i];
c++;
}

i++;
for(int i=0;i<m;i++)
cout<<a[i]<<"   ";
cout<<"\n";

}while(i<n); 
cout<<"\n\nFinal Solution...\n\n";
for(int i=0;i<m;i++)
cout<<a[i]<<"   ";
cout<<"\n\n";
gettimeofday(&tve, NULL);
f_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with FIFO         : "<<(miss-frame)<<'\n';
cout<<"Total time to run FIFO algorithm          : "<<f_time<<" microseconds"<<'\n';
cout<<"Total time to run Optimal algorithm            : "<<opt_time<<" microseconds"<<'\n';
	if(f_time<opt_time)
		cout<<"FIFO is "<<(float)(opt_time-f_time)/opt_time*100<<"%"<<" faster than Optimal algorithm."<<'\n';
	else
		cout<<"FIFO is "<<(float)(f_time-opt_time)/opt_time*100<<"%"<<" slower than Optimal algorithm."<<'\n';
cout<<"Hits are "<<hit<<"\n";
cout<<"Miss are "<<miss<<"\n";
}

/**************************************************************************************************************************/


void LRU(int a[], int n, int m)
{
int hit=0,miss=0,i=0,j=0,k=0;
bool flag=false;
int f[m];
unsigned int lru_time;
struct timeval tvs,tve;
for(i=0;i<m;i++)
f[i]=-1;
gettimeofday(&tvs, NULL);
for(i=0;i<n;i++)
{
	flag=false;
	for(j=0;j<m;j++)
	{
		if(f[j]==a[i])
		{
			hit++;
			flag=true;
			for(k=j;k<m-1;k++)
			{
				f[k]=f[k+1];
			}
			f[m-1]=a[i];
			break;
		}
	}
	if(flag==false)
	{
                miss++;
		for(j=0;j<m-1;j++)
		{
			f[j]=f[j+1];
		}
		f[m-1]=a[i];
	}
	for(k=0;k<m;k++)
        cout<<f[k]<<"    ";
	cout<<"\n\n";
}
cout<<"Final Frames...\n\n";
	for(k=0;k<m;k++)
        cout<<f[k]<<"    ";
	cout<<"\n\n";
gettimeofday(&tve, NULL);
lru_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with LRU-STACK          : "<<(miss-frame)<<'\n';
cout<<"Total time to run LRU-STACK algorithm          : "<<lru_time<<" microseconds"<<'\n';
cout<<"Total time to run Optimal algorithm            : "<<opt_time<<" microseconds"<<'\n';
	if(lru_time<opt_time)
		cout<<"LRU-STACK is "<<(float)(opt_time-lru_time)/opt_time*100<<"%"<<" faster than Optimal algorithm."<<'\n';
	else
		cout<<"LRU-STACK is "<<(float)(lru_time-opt_time)/opt_time*100<<"%"<<" slower than Optimal algorithm."<<'\n';
cout<<"Hits are "<<hit<<"\n";
cout<<"Miss are "<<miss<<"\n";
}

/**************************************************************************************************************************/


void LFU (int a[],int u,int o)
{
bool t=false;
int hit=0,miss=0,new_p=0,q=0,i=0,j=0,k=0,x=0,y=0,z=0,least_p=0,least_c=0;
int c[o];
int p[o];
int f[o]; 
unsigned int lfu_time;
struct timeval tvs,tve;
	for(i=0;i<o;i++)
		c[i]=0;

	for(j=0;j<o;j++)
		p[j]=j+1;

	for(k=0;k<o;k++)
		f[k]=-1;

cout<<"So initial frames along with their positions are:\n";
cout<<"Frames   Positions\n";
gettimeofday(&tvs, NULL);
        for(k=0;k<o;k++)
        cout<<f[k]<<"        "<<p[k]<<"\n";
	for(i=0;i<u;i++)
	{	
cout<<"\n\n***Check for Element "<<a[i]<<"***\n\n";

	for(int m=0;m<o;m++)
        c[m]=0;

        t=false;

	for(j=0;j<o;j++)
	if(f[j]==a[i])				
	{
	cout<<"\n\nHit is encountered\nElement hit is "<<f[j]<<"\n\n";
	hit++;
	t=true;
	}
		
	if(t!=true)
	{
cout<<"\n\nMiss is encountered, So check for replacement position for element "<<a[i]<<"\n";
miss++;
new_p=0;
least_p=p[0];
        	
        for(j=0;j<o;j++)	
	{
		k=0;	
		while(k<i)
		{
			if(f[j]==a[k])
				c[j]++;
		k++;
		}
	}
		x=1;	
		least_c=c[0];
	
	while(x<o)
	{

	if(c[x]<least_c)
	{
        least_c=c[x];
	least_p=p[x];
	new_p=x;                                  
	goto next;		
        }
        if(c[x]==least_c)
	if(p[x]<least_p)
	{
         least_p=p[x];
	 new_p=x;
        }
          
next: x++;    

          }

cout<<"\nHere is the new replacement position= "<<new_p+1<<", So now we get the frame as\n\n";
p[new_p]=i;			
f[new_p]=a[i];
			
		}	
	for(y=0;y<o;y++)
		cout<<f[y]<<"   ";
cout<<"\n";
	}
cout<<"Final Frames..."<<"\n";
	for(y=0;y<o;y++)
	cout<<f[y]<<"   ";
	cout<<"\n";
gettimeofday(&tve, NULL);
lfu_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with LFU          : "<<(miss-frame)<<'\n';
cout<<"Total time to run LFU algorithm          : "<<lfu_time<<" microseconds"<<'\n';
cout<<"Total time to run Optimal algorithm            : "<<opt_time<<" microseconds"<<'\n';
	if(lfu_time<opt_time)
		cout<<"LFU is "<<(float)(opt_time-lfu_time)/opt_time*100<<"%"<<" faster than Optimal algorithm."<<'\n';
	else
		cout<<"LFU is "<<(float)(lfu_time-opt_time)/opt_time*100<<"%"<<" slower than Optimal algorithm."<<'\n';
cout<<"\nHits are "<<hit;
cout<<"\nMiss are "<<miss<<"\n";	
}

/**************************************************************************************************************************/


void LRU_clock(int a[], int n, int m)
{
	int hit=0,miss=0,i=0,j=0,k=0;
        bool flag=false;
	int f[m];
	int c[m];
	int t=0,p=0;
unsigned int clk_time;
struct timeval tvs,tve;
	for(i=0;i<m;i++)
	{	
		f[i]=-1;
		c[i]=0;
	}
	
        for(i=0;i<m;i++)
	cout<<"Number Bit   ";
        cout<<"\n";
gettimeofday(&tvs, NULL);
	for(i=0;i<n;i++)
	{
		flag=false;
		for(j=0;j<m;j++)
		{
			if(f[j]==a[i])
			{
				hit++;
				c[j]=1;
				flag=true;
				break;
			}
		}
		if(flag==false)
		{  
                                miss++;			
				while(c[t%m]==1)
				{	
					c[t%m]=0;
					t++;
				}
				f[t%m]=a[i];
				t++;

		}	
        
	for(k=0;k<m;k++)
	cout<<f[k]<<"      "<<c[k]<<"     ";
	cout<<"\n";
	}

cout<<"\n Final Frames...\n\n";
for(i=0;i<m;i++)
	cout<<"Number Bit   ";
        cout<<"\n";
		
	for(k=0;k<m;k++)
	cout<<f[k]<<"      "<<c[k]<<"     ";
	cout<<"\n\n";
gettimeofday(&tve, NULL);
clk_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with LRU_CLOCK          : "<<(miss-frame)<<'\n';
cout<<"Total time to run LRU_CLOCK algorithm          : "<<clk_time<<" microseconds"<<'\n';
cout<<"Total time to run Optimal algorithm            : "<<opt_time<<" microseconds"<<'\n';
	if(clk_time<opt_time)
		cout<<"LRU_CLOCK is "<<(float)(opt_time-clk_time)/opt_time*100<<"%"<<" faster than Optimal algorithm."<<'\n';
	else
		cout<<"LRU_CLOCK is "<<(float)(clk_time-opt_time)/opt_time*100<<"%"<<" slower than Optimal algorithm."<<'\n';
cout<<"Hits are "<<hit<<"\n";
cout<<"Miss are "<<miss<<"\n";
		
}

/**************************************************************************************************************************/


void opt(int a[],int w, int o)
{
	int i=0,j=0,hit=0,miss=0,k=0,x=0,minp=0,max=0,new_p=0,m=0;
	bool flag=false;
	int p[o];
	int f[o];
	int max_p[o];

struct timeval tvs,tve;	
for(i=0;i<o;i++)
	f[i]=-1;	
for(i=0;i<o;i++)
	p[i]=-1;
for(i=0;i<o;i++)
	max_p[i]=w+1;
i=0;
gettimeofday(&tvs, NULL);
	while(i<w)
	{
		for(j=0;j<o;j++)
		max_p[j]=w+1;
		
flag=false;
		for(j=0;j<o;j++)
		{
			if(f[j]==a[i])				
			{
				hit++;
				flag=true;
			}
		}
	
	if(flag==false)
	{    
                   miss++;
	           minp=p[0];
                   new_p=0;
		
        	for(j=0;j<o;j++)
                 {
 			k=i;
			 while(k<w)
			 {
				   if(f[j]==a[k])
				    {
				      max_p[j]=k;
				      break;
				     }			
			  k++;
			  }
			
 		}
		        x=1;
		        max=max_p[0];
		        while(x<o)
			{
				if(max_p[x]>max)
				{
					max=max_p[x];
					minp=p[x];
					new_p=x;
				}
	
				if(max_p[x]==max)

				if(p[x]<=minp)
					{       
						minp=p[x];
						new_p=x;
					}
					
				
			x++;
			}

			f[new_p]=a[i];
			p[new_p]=i;
	}

	i++;	
	for(m=0;m<o;m++)
	cout<<f[m]<<"   ";
	cout<<"\n";

	}

cout<<"\nFinal Frames...\n\n";
	for(k=0;k<m;k++)
	cout<<f[k]<<"    ";
	cout<<"\n\n";
gettimeofday(&tve, NULL);
opt_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with OPTIMAL          : "<<(miss-frame)<<'\n';
cout<<"Total time to run OPTIMAL algorithm          : "<<opt_time<<" microseconds"<<'\n';

cout<<"Hit "<<hit;
cout<<"\nMiss "<<miss<<"\n";

} 

/**************************************************************************************************************************/


void lru_ref(int a[],int n,int m)
{
	int hit=0,miss=0,max_p=0,i=0,j=0,k=0,new_p;
	int f[m];
	int p[m];
	int ref[m][8];
	unsigned int ref_time;
	struct timeval tvs,tve;	
	bool flag=false;
gettimeofday(&tvs, NULL);
	for(i=0;i<m;i++)
	{
		f[i]=-1;
		p[i]=m-1-i;
		for(j=0;j<8;j++)
		ref[i][j]=0;
			
		ref[i][p[i]]=1;
	}
	
        for(k=0;k<m;k++)
	cout<<f[k]<<"  ";
	
	cout<<"\n";
	
	for(i=0;i<n;i++)
	{
		flag=false;
		for(j=0;j<m;j++)
		{		
			for(k=7;k>0;k--)
			ref[j][k]=ref[j][k-1];

			ref[j][0]=0;
			
			for(k=0;k<8;k++)
			{
				if(ref[j][k]==1)
				{
					p[j]=k;
					break;
				}
			}
		}
		for(j=0;j<m;j++)
		{
			if(f[j]==a[i])
			{
				hit++;				
				flag=true;
				ref[j][0]=1;
				p[j]=0;
				break;
			}
		}
		if(flag==false)
		{ 	miss++;
			max_p=p[0];
			new_p=0;
			for(j=0;j<m;j++)
			{
				if(p[j]>max_p)
				{
					max_p=p[j];
					new_p=j;
				}
			}

			f[new_p]=a[i];
			ref[new_p][0]=1;

			for(k=1;k<8;k++)
			ref[new_p][k]=0;
			
			p[new_p]=0;
		}
		for(k=0;k<m;k++)
		{
		cout<<f[k]<<"  ";
		for(j=0;j<8;j++)
		cout<<ref[k][j];
  		cout<<"  ";              
  		}
		cout<<"\n";			
	}
		cout<<"\nFinal Frames...\n\n";		
		for(k=0;k<m;k++)
		{
		cout<<f[k]<<"  ";
		for(j=0;j<8;j++)
		cout<<ref[k][j];
  		cout<<"  ";              
  		}
		cout<<"\n";			
gettimeofday(&tve, NULL);
ref_time=(((uint)tve.tv_sec-(uint)tvs.tv_sec)*1000000)+((uint)tve.tv_usec-(uint)tvs.tv_usec);
cout<<"# of page replacements with LRU_REF          : "<<(miss-frame)<<'\n';
cout<<"Total time to run LRU_REF algorithm          : "<<ref_time<<" microseconds"<<'\n';
cout<<"Total time to run Optimal algorithm            : "<<opt_time<<" microseconds"<<'\n';
	if(ref_time<opt_time)
		cout<<"LRU_REF is "<<(float)(opt_time-ref_time)/opt_time*100<<"%"<<" faster than Optimal algorithm."<<'\n';
	else
		cout<<"LRU_REF is "<<(float)(ref_time-opt_time)/opt_time*100<<"%"<<" slower than Optimal algorithm."<<'\n';
cout<<"Hits are "<<hit;
cout<<"\nMiss are "<<miss<<"\n";
}

/**************************************************************************************************************************/

int main (int argc, char* argv[]) {
int s;
int p;
int optg;
int r_policy=0;
while ( (optg= getopt(argc,argv, "hf:r:i:"))!=-1){
            switch ( optg ) {
case 'h': 
cout<<"−h : Print a usage summary with all options and exit.\n\n";
cout<<"−f available-frames : Set the number of available frames. By default it should be 5.\n\n";
cout<<"−r replacement-policy : Set the page replacement policy. It can be either\nFIFO (First-in-first-out)\nLFU (Least-frequently-used)\nLRU-STACK (Least-recently-used stack implementation)\nLRU-CLOCK ((Least-recently-used clock implementation –second chance alg.).\nLRU-REF8 (Least-recently-used Reference-bit Implementation, using 8 reference bits)\nThe default will be FIFO.\n\n";
cout<<"−i input file : Read the page reference sequence from a specified file. If not given,the sequence should be read from STDIN (ended with ENTER).\n\n";
break;  
case 'f':
if(optarg==NULL)
cout<<"No spec";
else
frame=atoi(optarg);

break;
case 'r':
                             //USER HAS GIVEN POLICY
            if(((string)optarg).compare("FIFO")==0)
            {   
            p=1;           
            r_policy=1;
            cout<<"We are using FIFO\n";
            }
            if(((string)optarg).compare("LFU")==0)
            {   
            p=1;
            r_policy=2;
            cout<<"We are using LFU\n";
            }
            if(((string)optarg).compare("LRU-STACK")==0)
            {   
            p=1;
            r_policy=3;
            cout<<"We are using LRU-STACK\n";
            }
            if(((string)optarg).compare("LRU-CLOCK")==0)
            {   
            p=1;
            r_policy=4;
            cout<<"We are using LRU-CLOCK\n";
            }
            if(((string)optarg).compare("LRU-REF8")==0)
            {   
            p=1;
            r_policy=5;
            cout<<"We are using LRU-REF8\n";
            }           
            if(p==0)
            {
            p=1;
            r_policy=1;
            cout<<"User dint enter the policy.\n";
            cout<<"Default is set to FIFO";
            }           
            break;
        case 'i':

	FILE* file = fopen ("ab.txt", "r");
	int i = 0, cnt=0;
	int k;

	while (!feof (file))
	{
	fscanf(file, "%d", &i);
	seq[cnt] = i;
	cnt++;
	}
	pg = cnt -1;
	for(int i=0;i<pg;i++)
	std::cout<<seq[i];
	fclose (file);
	break;
        
	}
}
cout<<"\nSolving for Optimal Algorithm first...\n\n";
opt(seq,pg,frame);


if(r_policy==1)
{

cout<<"\nSolving for FIFO...\n\n";
fifo(seq,pg,frame);
}

if(r_policy==2)
{

cout<<"\nSolving for LFU...\n\n";
LFU(seq,pg,frame);
}

if(r_policy==3)
{

cout<<"\nSolving for LRU_STACK...\n\n";
LRU(seq,pg,frame);
}

if(r_policy==4)
{

cout<<"\nSolving for LRU-CLOCK...\n\n";
LRU_clock(seq,pg,frame);
}

if(r_policy==5)
{

cout<<"\nSolving for LRU-REF8...\n\n";
lru_ref(seq,pg,frame);
}

}
   
