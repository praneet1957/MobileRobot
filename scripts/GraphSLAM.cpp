#include "algorithms.cpp"

class node{
    public:
        vector<float> pose;
        vector<float> laser_measure;
}



class edge{
    public:
        node start;
        node end;
        vector<float> z; // observation representing the edge
        Matrix I;       // Information filter
        vector<float> z_hat; // observation coming from model

}


class GraphSLAM:private Algorithm{
    private:
        map<int,int> graph;
        vector<node> nodes;
        vector<edge> Edges;
   //   vector<vector>> edges;

    public:
        float optimization(graph)





    float optimization(){
        


    }


    float Nodeupdate(Bot &bot){
        // class pose need to define
        node node_cur;
        pose = bot.pose();
        dist = sqrt((pose.x - prev_pose.x)^2 + (pose.y - prev_pose.y)^2); // check for pow function
        if (dist< threshold){
            nodes.pushback(node_cur);
            // Edge update with z, z_hat, I,
            Edge.update();
        }
        else{
           // Skip current position
        }
    }


    float Edgeupdate(Bot &bot){
        edge E;
        E.start = node_prev;
        E.end = node_cur;
        E.z =            // should come from sensor
        E.I =             // Information matrix
        E.z_hat = GraphSLAM.sensormodel();

    }

    float Lossfunction(){
        int v_len = Edges.size();
        for(int j=0;j<v_len;j++){
            e = Edges[j];
            loss = loss + ((e.z - e.z_hat).transpose()*e.I)*(e.z - e.z_hat);
        }
    }

}