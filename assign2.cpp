#include <bits/stdc++.h>
using namespace std;
/*
bool sortsec( const vector<pair<double, pair<double,int>>> &b1, const vector<pair<double, pair<double,int>>> &b2)
{
    return (b1.second < b2.second);
}
*/
double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}


int main()
{
     int n;
     cout<<"enter number of source ";
    cin>>n;
    cout<<"Enter packet sending rate ";
    double packet_sending_rate;
    cin>>packet_sending_rate;


    double time_of_simulation = 200;


    srand(static_cast<unsigned int>(clock()));

    vector<pair<double, pair<double,int>>> buffer1;
    vector<pair<double, pair<double,int>>> buffer2;
    vector<pair<double, pair<double,int>>> buffer3;
    
 for(int i=0;i<200;i++)
 {
    double f=doubleRand();
    double delta_time = -log(f)/packet_sending_rate;
    buffer1.push_back(make_pair(f,make_pair(0,1)));

    f=doubleRand();
    delta_time = -log(f)/packet_sending_rate;
    buffer2.push_back(make_pair(f,make_pair(0,1)));
     f=doubleRand();
    delta_time = -log(f)/packet_sending_rate;
    buffer3.push_back(make_pair(f,make_pair(0,1)));


}

double t1=0,t2=0,t3=0;
for(int i=0;i<time_of_simulation;i++)
{
  t1 +=buffer1[i].first;
  buffer1[i].second.first= t1;

  t2 +=buffer2[i].first;
  buffer2[i].second.first =t2;

  t3 +=buffer3[i].first;
  buffer3[i].second.first =t3;


}
/*
for(int i=0;i<time_of_simulation ;i++)
{
    cout<<buffer1[i].second.first<<" ";
}
cout<<endl;*/
vector<pair<double,int>> gen_time;
   int u=0;
    for(u=0;u<time_of_simulation;u++)
    {
        gen_time.push_back(make_pair(buffer1[u].second.first,1));
        
    }
  
    for(int j=u,i=0;j<time_of_simulation*2;u++,j++,i++)
    {
        gen_time.push_back(make_pair(buffer2[i].second.first,2));
        
    }

    for(int j=u,i=0;j<time_of_simulation*3;j++,u++,i++)
    {
        gen_time.push_back(make_pair(buffer1[i].second.first,3));
    }
    
   
    sort(gen_time.begin(),gen_time.end());
/*
    for(int i=0;i<time_of_simulation * n ;i++)
    {
        cout<<gen_time[i].first<<" ";
        cout<<gen_time[i].second<<endl;
    }

*/
   
  /*cout << "expect 5 numbers within the interval [0.0, 1.0)" << endl;
  for (int i=0; i < 5; i++) {
      double f=doubleRand();
      double delta_time = -log(f)/packet_sending_rate;
    cout << f <<" "<<delta_time<< "\n";
  }*/
 // cout << endl;  

   
    double time_to_reach_sink;
    vector<pair<double,pair<double,int>>> que;
    vector<pair<double,pair<double,int>>> sink;
    
    //vector<vector<pair<double,pair<double,int>>>> source_id;
    double time_to_reach_s;
    cout<<"time taken by packet to reach switch from source  ";
    /*for(int i=0;i<n;i++)
    {
        double t;
        cin>>t;
        time_to_reach_s.push_back(t);
    }
*/
    cin>>time_to_reach_s;
    cout<<"time taken by packet to reach sink from switch  ";

    
     
    cin >>time_to_reach_sink;
    
     
   
   
        double t_time;
    int r=0,s=1;
    for(int i=0;i<time_of_simulation*packet_sending_rate*n;i++)
    
        
    {
            t_time= (time_to_reach_s) * (s++);     //(gen_time[r++].first + ((time_to_reach_s) * (s++)));
            que.push_back(make_pair(t_time,make_pair(-1,i)));
           // cout<<t_time<<" ";
        

     }
      
      
      //sort(que.begin(),que.end());
   
       int k=0;
      double temp_time=que[0].first;
      //cout<<endl;

     while(temp_time + time_to_reach_sink <= time_of_simulation)
    {
        que[k].second.first = temp_time + time_to_reach_sink;
        temp_time = que[k].second.first;
        k++;
        //cout<<temp_time<<" ";

    }
     cout<<endl;
      double total_time=0;
      int total_packet_reached=k;
      int a=0;
      int raj = k;
      for(int i=0;i<=k-1;i++)
      {
          
          
          total_time += (que[i].second.first - gen_time[a++].first);
           // cout<<total_time<<" ";
            //raj--;
          
      }
      //cout<<"\ntotal time "<<total_time<<endl;
      double avg_time =0;
      avg_time = total_time/total_packet_reached;

      cout<<"avg time is "<<avg_time<<endl;



    return 0;


}


