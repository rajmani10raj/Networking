#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAX 1000003
typedef struct packet
{
    double start_time;
    double end_time;
    double crnt_time;
    int packet_id;
    int packet_source;
    int type;
} packet;
typedef struct source
{
    int source_id;
    double source_to_switch_time;
    double sending_rate;
} source;
double link_used_till[50];
typedef struct swich
{
    double last_arrived;
    int arrived_from_source;
} swich;
double last_arrived_at_sink = 0;
double swich_to_sink_time;

struct Comparetime
{
    bool operator()(packet *p1, packet *p2)
    {
        return p1->crnt_time >= p2->crnt_time;
    }
};

int main()
{
    for (int i = 0; i < 50; i++)
        link_used_till[i] = 0;
    cout << "Enter the number of nodes you want to use\n";
    int no_of_source;
    cin >> no_of_source;
    source src[no_of_source];
    cout << "Enter the sending rate and time to reach switch for each source\n";
    for (int i = 0; i < no_of_source; i++)
    {
        src[i].source_id = i;
        cin >> src[i].sending_rate >> src[i].source_to_switch_time;
    }
    cout << "Enter the time to reach sink from switch\n";
    cin >> swich_to_sink_time;
    priority_queue<packet *, vector<packet *>, Comparetime> Q;
    packet pck[10000];
    int no_of_packets = 0;
    for (int i = 0; i < no_of_source; i++)
    {
        for (double tme = 0; tme < 10; tme += src[i].sending_rate)
        {
            pck[no_of_packets].start_time = tme;
            pck[no_of_packets].end_time = 9999;
            pck[no_of_packets].crnt_time = tme;
            pck[no_of_packets].packet_id = no_of_packets;
            pck[no_of_packets].packet_source = i;
            pck[no_of_packets].type = 0;
            Q.push(pck + no_of_packets);
            no_of_packets++;
        }
    }
    while (!Q.empty())
    {
        packet *p = Q.top();
        Q.pop();
        //cout<<"packet_id="<<p->packet_id<<" crnt_time "<<p->crnt_time<<"type="<<p->type<<"\n";
        if (p->type == 0)
        {
            int from_source = p->packet_source;
            if (p->start_time >= link_used_till[from_source])
            {
                p->crnt_time = p->start_time + src[from_source].source_to_switch_time;
                p->type = 1;
                link_used_till[from_source] = p->crnt_time;
                Q.push(p);
            }
            else if (p->start_time + src[from_source].source_to_switch_time >= link_used_till[from_source])
            {
                p->crnt_time = link_used_till[from_source] + src[from_source].source_to_switch_time;
                p->type = 1;
                link_used_till[from_source] = p->crnt_time;
                Q.push(p);
            }
        }
        else if (p->type == 1)
        {
            if (p->crnt_time >= last_arrived_at_sink)
            {
                p->end_time = p->crnt_time + swich_to_sink_time;
                last_arrived_at_sink = p->end_time;
                p->type = 2;
            }
            else if (p->crnt_time + swich_to_sink_time >= last_arrived_at_sink)
            {
                p->end_time = last_arrived_at_sink + swich_to_sink_time;
                last_arrived_at_sink = p->end_time;
                p->type = 2;
            }
            //cout<<"packet_id="<<p->packet_id<<"end_time="<<p->end_time<<"type="<<p->type<<"\n";
        }
    }
    double dlay = 0;
    int total_packets = 0;
    for (int i = 0; i < no_of_packets; i++)
    {
        if (pck[i].end_time < 10)
        {

            //cout<<pck[i].start_time<<" "<<pck[i].end_time<<"\n";
            dlay += (pck[i].end_time - pck[i].start_time);
            total_packets++;
        }
    }
    cout << (dlay / total_packets) << "\n";
    return 0;
}