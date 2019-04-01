#include <bits/stdc++.h>
using namespace std;
int main()
{
int n;
cout<<"ENTER THE NUMBER OF SOURCES-";
cin>>n;
vector <double> time_pack;
vector<int> n_packs;
vector<pair<double,pair<int,int> > > queuez,queuez2;
double bh;
cout<<"time to travel from source to switch-";
cin>>bh; // PACKET_SIZE/BANDWIDTH
map<int,map<int,double > >start;
for(int ef=1;ef<=n;ef++)
{
double e;
cout<<"time to produce a packet-";
cin>>e;
time_pack.push_back(e);
int n_pk;
cout<<"enter the number of packets-";
cin>>n_pk;
n_packs.push_back(n_pk);
}
for(int e=1;e<=n;e++)
{
double st=0;
double last=-1;
double time_packet=time_pack[e-1];
for(int f=0;f<n_packs[e-1];f++)
{

	if(f*time_packet>=last)
{
    start[e][f+1]=f*time_packet;
	last=f*time_packet+bh;
	

	queuez.push_back(make_pair(last,make_pair(e,f+1)));//time,object,no_packet
}
else
{   last=last+bh;
   
	queuez.push_back(make_pair(last,make_pair(e,f+1)));//time,object,no_packet
}
}
}
sort(queuez.begin(),queuez.end());

double last=-1;
for(int e=0;e<queuez.size();e++)
{
if(queuez[e].first>=last)
{

	last=queuez[e].first+bh;
	

	queuez2.push_back(make_pair(last,make_pair(queuez[e].second.first,queuez[e].second.second)));
}
else
{   last=last+bh;
   
	queuez2.push_back(make_pair(last,make_pair(queuez[e].second.first,queuez[e].second.second)));
}

}
vector<double > avg(100);
for(int g=0;g<queuez2.size();g++)
{

double reach=queuez2[g].first;
int source=queuez2[g].second.first;
avg[source]=avg[source]+reach-start[source][queuez2[g].second.second];


}

for(int e=1;e<=n;e++)
{	avg[e]=avg[e];
	cout<<avg[e]<<endl;
	cout<<n_packs[e-1]<<endl;
}

}