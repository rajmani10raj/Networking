#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    double time_to_reach_sink;
    vector<pair<double,pair<double,int>>> que;
    vector<pair<double,pair<double,int>>> sink;
    cout<<"enter number of source ";
    cin>>n;
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
    
     
   
   
    double packet_sending_rate= 2;
    double time_of_simulation = 20;
    double t_time;
    int r=0,s=1;
    for(int i=0;i<time_of_simulation*packet_sending_rate;i++)
    {
        for(int j=0;j<n;j++)
        {
            t_time= ((time_to_reach_s) * (s++));      //(((r++)*(1/packet_sending_rate)) + ((time_to_reach_s) * (s++)));
            que.push_back(make_pair(t_time,make_pair(-1,i)));
            cout<<t_time<<" ";
        }

     }
      
      
      sort(que.begin(),que.end());
   
       int k=0;
      double temp_time=que[0].first;
      cout<<endl;

     while(temp_time + time_to_reach_sink <= time_of_simulation)
    {
        que[k].second.first = temp_time + time_to_reach_sink;
        temp_time = que[k].second.first;
        k++;
       cout<<temp_time<<" ";

    }
     cout<<endl;
      double total_time=0;
      int total_packet_reached=k;
      int a=0;
      int raj = k;
      cout<<"no of p = "<<k<<endl;
      for(int i=0;i<=k-1;i++)
      {
          
          
          total_time += ((que[i].second.first) - ((a++)*(1/packet_sending_rate)));
           // cout<<total_time<<" ";
            //raj--;
          
      }
      cout<<"\ntotal time "<<total_time<<endl;
      double avg_time =0;
      avg_time = total_time/total_packet_reached;

      cout<<"avg time is "<<avg_time<<endl;



    return 0;
}