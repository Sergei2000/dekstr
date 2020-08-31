#include <iostream>
#include <vector>
#include <string>
#define  NO_CON -1
#define CUR_POINT 0
#define NO_MORE 0xfffffff //infinity
using  std::vector;
using  std::cout;
using  std::endl;
using  std::string;
using  std::to_string;
static vector<bool> used{false,false,false,false,false,false};
struct node
{
    vector<int> _connections;
    int _minimal_distance=NO_CON;
    string _min_way="";
    string _name;
    bool _used=false;
    node(){}
    void fill(vector<int>connections,size_t n)
    {
        _connections.resize(connections.size());
        for (size_t i=0;i<connections.size();++i)
        {
            _name=to_string(n);
            _connections[i]=connections[i];
        }
    }

    node(const vector<int> &connections)
    {
        _connections.resize(connections.size());
        for (size_t i=0;i<connections.size();++i)
        {
            _connections[i]=connections[i];
        }
    }

    void print_connections()
    {
      for (auto a: _connections)
          cout<<a<<endl;
    }
};
size_t find_unused_points(const vector<node>&graph_scheme)
{
    int min= NO_MORE;
    size_t index=NO_MORE;
    for (size_t i=0;i<graph_scheme.size();++i)
    {
        if ((!graph_scheme[i]._used)&&(graph_scheme[i]._minimal_distance!=NO_CON)&&(graph_scheme[i]._minimal_distance<min))
        {
            index=i;
            min=graph_scheme[i]._minimal_distance;
        }
    }
    return index;
}
size_t find_minimal_point_connection(vector<node>&graph_scheme,size_t index)
{
    int min=NO_MORE;
    size_t ind=NO_MORE;
    for (size_t i=0;i<graph_scheme[index]._connections.size();++i)
    {
        if (graph_scheme[index]._connections[i]!=NO_CON)
        {
            if (graph_scheme[i]._minimal_distance==NO_CON)
            {
                graph_scheme[i]._minimal_distance=graph_scheme[index]._connections[i]+graph_scheme[index]._minimal_distance;
                graph_scheme[i]._min_way=graph_scheme[index]._min_way+"->"+to_string(i+1);
            }
            else if ((graph_scheme[index]._minimal_distance+graph_scheme[index]._connections[i])<graph_scheme[i]._minimal_distance)
            {
                graph_scheme[i]._minimal_distance= graph_scheme[index]._minimal_distance+graph_scheme[index]._connections[i];
                graph_scheme[i]._min_way=graph_scheme[index]._min_way+"->"+to_string(i+1);
            }
        }
        if ((graph_scheme[i]._minimal_distance!=NO_CON)&&(min>graph_scheme[i]._minimal_distance)&&(!used[i])&&((graph_scheme[i]._minimal_distance>CUR_POINT)))
        {
            min=graph_scheme[i]._minimal_distance;
            ind=i;
        }
    }
    graph_scheme[index]._used=true;
    used[index]=true;
    return ind;
}
void Dekstra(vector<node>&graph_scheme,size_t n)
{
     graph_scheme[n]._minimal_distance=CUR_POINT;
     size_t next_index;
     graph_scheme[n]._min_way=to_string(n+1);

     next_index=find_minimal_point_connection(graph_scheme,n);

     while (next_index!=NO_MORE)
     next_index=find_minimal_point_connection(graph_scheme,next_index);
}
int main()
{
    vector<vector<int>> scheme{
        {0,7,9,NO_CON,NO_CON,14},
        {7,0,10,15,NO_CON,NO_CON},
        {9,10,0,11,NO_CON,2},
        {NO_CON,15,11,0,6,NO_CON},
        {NO_CON,NO_CON,NO_CON,6,0,9},
        {14,NO_CON,2,NO_CON,9,0}
    };
    vector<node> graph;
    graph.resize(scheme.size());

    for (size_t i=0 ;i<scheme.size();++i)    
    graph[i].fill(scheme[i],i);

    Dekstra(graph,2);

    for (const auto &a: graph)
    cout<<a._minimal_distance<<":"<<a._min_way<<endl;

    return 0;
}
