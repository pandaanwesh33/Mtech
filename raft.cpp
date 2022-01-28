#include<bits/stdc++.h>
using namespace std;

class node{
    int id;     // id of the node created;
    int data;   // data
    int committed_data;
    int state;  // a node can be in any of three state : 1.leader , 2.candidate, 3.follower
    int vote;   // a node gives it's vote
    int votes_obtained;
    public :
    node(int x){
        id = x;
        state = 3;  //initially all the nodes are followers
        votes_obtained = 0; // if not standing for election votes_obtained will remain 0
        data=INT_MIN;
        committed_data = INT_MIN;
    }
    void reset(){
        data = INT_MIN;
        committed_data = INT_MIN;
        state = 3;
        votes_obtained = 0;
    }

    void update_data(int x){
        data = x;
    }
    void commit(){
        committed_data = data;
    }

    int get_data(){
        return data;
    }
    int voting(int id1,int id2){
        // A node will give vote to either id1, id2 or none of them (indicated by 0)
        // if return value is 0 then a tie will occur
        vector<int> options;
        options.push_back(0);
        options.push_back(id1);
        options.push_back(id2);
        int random = rand()%3;
        return options[random];  
    }
    
    void change_state(int x){
        state = x;
    }
    void inc_vote(){
        votes_obtained++;
    }
    int get_id(){
        return id;
    }

};

int leader_election(node A,node B,node C){
    int id1 = A.get_id();
    int id2 = B.get_id();
    int res = C.voting(id1,id2); // C gives vote to any one of the id1 and id2..Note if C doesn't gives vote then tie and no leader will be elected
    return res;  // this returned id is the leader.
}

int candidates(node A, node B,node C){   // node C is not changed here
    A.change_state(2); B.change_state(2); //state changed to candidate
    A.inc_vote(); B.inc_vote();           // each candidate vote itselt
    int res = leader_election(A,B,C);     // election is between A and B
    if(res == 0){        // no leader
        
    } 
    else{        // elected leader's vote incremented by 1 due to the third node's vote
        if(res == 1)
            A.inc_vote();
        else if(res == 2)
            B.inc_vote();
        else
            C.inc_vote();
    }
    return res; //return id of leader 
    
}

void replicate(node obj[],int leader){
    for(int i=0;i<3 && i != leader-1 ;i++){ // since only 3 nodes 
        obj[i].update_data(obj[leader-1].get_data());
    }
}

void term_over(node obj[]){
    obj[0].reset();
    obj[1].reset();
    obj[2].reset();
}

int main(){
    int term=1;
    int n;
    node obj[] = {node(1), node(2),node(3)}; // All the nodes declared will be initialized as follower in the constructor
    while(1){
        cout<<"Term "<<term<<" starts"<<endl;
        int leader = candidates(obj[0],obj[1],obj[2]);
        if(leader == 0){
            cout<<"Its a tie in the result...no leader elected for term "<<term<<endl<<endl;
            term++;
            continue;
        }
        cout<<"The elected leader is : node "<<leader<<endl;
        cout<<"Enter the data : (enter -1 to exit the program) ";
        cin>>n;
        if(n == -1)
            exit(0);
        cout<<"----First leaders data is updated----"<<endl;
        obj[leader-1].update_data(n);  // uncommitted data
        cout<<"Now, leader's data is : "<<obj[leader-1].get_data()<<endl;
        cout<<"Updated data is replicated to other nodes "<<endl;
        replicate(obj,leader);
        cout<<"All the nodes have the latest data and each sends a reply to the leader"<<endl;
        cout<<"Now Leader finally commits the data"<<endl;
        cout<<"Term "<<term<<" gets over...Then again the leader election will happen"<<endl<<endl;
        term_over(obj);
        term++;
    }
    

}