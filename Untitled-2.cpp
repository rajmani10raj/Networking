#include <bits/stdc++.h>
using namespace std;


int pageFaults(int pages[], int n, int capacity) 
{ 
    unordered_set<int> s; 
  
    unordered_map<int, int> indexes; 
  
    int page_faults = 0; 
    for (int i=0; i<n; i++) 
    { 
        if (s.size() < capacity) 
        { 
            if (s.find(pages[i])==s.end()) 
            { 
                s.insert(pages[i]); 
  
                page_faults++; 
            } 
  
            indexes[pages[i]] = i; 
        } 
  
        else
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                int lru = INT_MAX, val; 
                for (auto it=s.begin(); it!=s.end(); it++) 
                { 
                    if (indexes[*it] < lru) 
                    { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
  
                s.erase(val); 
  
                s.insert(pages[i]); 
  
                page_faults++; 
            } 
  
            indexes[pages[i]] = i; 
        } 
    } 
  
    return page_faults; 
} 









int main()
{

freopen("test.txt", "r",stdin);
int frames;
while(cin>>frames)
{
int n=0,h;
vector<int > arr;
while(cin>>h)
{

if(h==-1)
	break;
arr.push_back(h);
++n;
}
int freq[1111]={0};
int uu=0;
int uu2=0;
int house[500][500]={0},current[500];
for(int t=0;t<500;t++)
for(int y=0;y<500;y++)
	house[t][y]=-1;
int time[500]={0};
for(int t=0;t<500;t++)
{time[t]=0;
current[t]=-2;
}
for(int e=0;e<n;e++)
{
int a=arr[e];
int maxx=-99999999,pos;
int zz=-1;

for(int q=0;q<frames;q++)
{
if(a==current[q])
	zz=1;

}

if(zz==1){
	++uu;

freq[a]+=1;
	continue;
}
int mint=99999991;
for(int ev=0;ev<frames;ev++)
{
	if(current[ev]==-2)
	{
pos=ev;
break;

	}

if(freq[current[ev]]<mint)
{
mint=freq[current[ev]];
pos=ev;
maxx=time[ev];
}
else if(freq[current[ev]]==mint)
{

if(time[ev]>maxx)
{

maxx=time[ev];
pos=ev;

}


}

time[ev]+=1;

}

int t=current[pos];
current[pos]=arr[e];
++uu2;
time[pos]=0;

for(int w=0;w<frames;w++)
	house[w][e]=current[w];


freq[a]+=1;
if(t!=-2)
	freq[t]=0;


}


for(int e=0;e<frames;e++)
{
for(int v=0;v<n;v++)
{
if(house[e][v]==-2)
{
	house[e][v]=0;

	cout<<house[e][v]<<" ";

}
else if(house[e][v]==-1)
cout<<"  ";

else
cout<<house[e][v]<<" ";
}
cout<<endl;
}
cout<<"NO OF HITS="<<uu;
cout<<endl;
cout<<"NO OF FAULTS="<<uu2;
cout<<endl;
}

}