#include<bits/stdc++.h>
using namespace std;

int faulty=0,l1=0,l2=0,lft1_check=0,lft2_check=0;
int attack=1,wait=0;

//In total 3 classes are created ...one for commander and 2 for lieutenants
// if a process is faulty , then we dont care about it's state

class lieutenant1 {
    public:
    void message1(int a){
        l1=l1+a;
        //after a message is received increase lft_check by 1
        lft1_check++;
        //since leutenant1 will get 2 values one from commander and another from lieutenant2 
        if(lft1_check>=2)
            return;
        if(faulty==1){
            cout << "lieutenant1 is a faulty process"<<endl;
            //when faulty , l1 gives wrong message to l2
            l2=l2+ (int)(!a);
        }
        else{
            //when l1 is not faulty, it gives correct message to l2
            if(a==1)
              l2++;
        }
        
    }
    
    // here if majority signal is for attack , then attack , else l1 will wait
    void decide1(){
        if(faulty != 1 && l1==2)
            cout << "lieutenant1 decides to Attack"<<endl;
        else if(faulty != 1 && l1<2)
            cout << "lieutenant1 decides to Wait"<<endl;
    }
};

class lieutenant2 {
    public:
    void message2(int a){
        l2=l2+a;
        // once this func is invocated , then increment this lft2_check by 1...
        lft2_check++;
        if(lft2_check>1)
            return;
            
        lieutenant1 lft1;
        
        if(faulty==2){
            // if l2 is faulty , then it gives wrong message to l1
            cout << "lieutenant2 is a faulty process"<<endl;
            lft1.message1(!a);
        }
        else{
            // if l2 not faulty , then it gives correct message to l1
            lft1.message1(a);
        }
    }
    
    // here if majority signal is for attack ,then attack, else wait
    void decide2(){
        if(faulty != 2 && l2==2)
            cout << "lieutenant2 decides to Attack"<<endl;
        else if(faulty != 2 && l2<2)
            cout << "lieutenant2 decides to Wait"<<endl;
    }
};

class Commander{
    public:
    void choice(int n){
       // int attack=1 , wait=0;
        lieutenant1 ltr1;
        lieutenant2 ltr2;
        if(n==1){
            cout << "Commander decides to Attack"<<endl;
            ltr1.message1(attack);
            ltr2.message2(attack);
        }
        else if(n==2){
            cout << "Commander decides to Wait"<<endl;
            ltr1.message1(wait);
            ltr2.message2(wait);
        }
        else{
            //here one of the process will be traitor ...decision will be random
            // srand(unsigned(time(0)));
             faulty=((int)rand() % 3)+1;
            // faulty==1 = lieutenant1 is traitor
            // faulty==2 = lieutenant2 is traitor
            // faulty==3 = commander is traitor
            // faulty==0 = no one is traitor
            if(faulty==3){
                // When commander is traitor he will send Attack to lieutenant1 and wait to lieutenant2 or vice versa
                cout << "Commander is a faulty process"<<endl;
                ltr1.message1(attack);
                ltr2.message2(wait);
            }
            else{
                // One of lietenant is faulty and assuming , commander sends wait to both
                cout <<"Commander decides to Wait"<<endl;
                ltr1.message1(wait);
                ltr2.message2(wait);
            }
        }
    }
};


int main()
{
    int n;
    Commander cdr;
    lieutenant1 lf1;
    lieutenant2 lf2;
    while(1){
        //In choic 1 and 2 there will be no traitors and in choice 3 there will be a traitor
        cout << "1. Attack 2. Wait 3. One traitor process 4. To Exit"<<endl;
        cin>>n;
        
        switch (n){
            case 1: cdr.choice(n);
                    break;
            case 2: cdr.choice(n);
                    break;
            case 3: cdr.choice(n);
                    break;
            default : exit(0);
        }
        
        lf1.decide1();
        lf2.decide2();
        //resetting the values 
        l1 = 0;
        l2 = 0;
        lft1_check =0;
        lft2_check =0;
        faulty = 0;
    }
    return 0;
}