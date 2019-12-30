//
// Created by lau on 2019/12/8.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

#include "parser.h"
#include "TM.h"
#include "simulator.h"
using namespace std;

const int max_len = 500;
Transition search_rule(TM tm, string old_state, string old_chars)
{


//    cout<<"old state is "<<old_state<<endl;
    vector<Transition> res;

    auto v = tm.tran_funcs.begin();
    while(v!=tm.tran_funcs.end())
    {
        if(v->old_state==old_state)
        {
            int i=0;
            for(i=0;i<old_chars.size();i++)
            {
                if(old_chars[i]==v->old_chas[i]||v->old_chas[i]=='*')
                {
                    continue;
                }
                else{
                    break;
                }
            }
            if(i==old_chars.size())
            {
                res.push_back(*v);
            }
        }
        v++;
    }
    int min = 1000;
    Transition best;
    for(int i=0;i<res.size();i++)
    {
        int sum_star = 0;
        for(int j=0;j<res[i].directions.size();j++)
        {
            if(res[i].directions[j]=='*') sum_star++;
        }
        for(int j=0;j<res[i].new_chas.size();j++)
        {
            if(res[i].new_chas[j]=='*') sum_star++;
        }
        for(int j=0;j<res[i].old_chas.size();j++)
        {
            if(res[i].old_chas[j]=='*') sum_star++;
        }
        if(sum_star<min)
        {
            best = res[i];
            min = sum_star;
        }
    }
    return best;
//    Transition ts;
//    ts.new_state = "Halt";
//    return ts;
}
bool isin(string str,vector<string> &arr)
{
    auto v = arr.begin();
    while(v!=arr.end())
    {
        if(str==*v){
            return true;
        }
        v++;
    }
    return false;
}
void simulate(string directory, string tm_path, string txt_path)
{
    ofstream console;
    ofstream result;
    console.open("./"+ directory + "/console.txt");
    result.open("./" + directory + "/result.txt");

    TM tm = parser(tm_path);
    ifstream in(txt_path);
    if(!in){
        cout<<"open file error "<<endl;
        return;
    }
    string str;
    while(std::getline(in,str))
    {
        console<<"Input:"<<str<<endl;
        int i=0;
        bool flag = true;
        for(int i = 0; i<str.size();i++)
        {

            if(tm.symbols.find(str[i])==string::npos)
            {
                console<<"==================== ERR ===================="<<endl;
                console<<"The input "<<str<<" is illegal"<<endl;
                result<<"Error"<<endl;
                console<<"==================== END ===================="<<endl;
                flag = false;
                break;
            }
        }
        if(!flag){
            continue;
        }
        else{
            console<<"==================== RUN ===================="<<endl;
            // simulate for input line str, give every ID of tm.
            int step=0;
            string state = "";
            vector<string> tape;
            vector<int> head;
            vector<deque<int>> index;

            while(!isin(state,tm.final_state)) // edit later
            {
//                cout<<"step is "<<step<<endl;

                if(step==0)
                {
//                    cout<<"step equals 0"<<endl;
                    tape.push_back(str);
                    head.push_back(0);
                    //index manage
                    deque<int> row;
                    row.push_back(0);
                    index.push_back(row);

                    for(int i=1;i<tm.num_tapes;i++)
                    {
                        tape.push_back("_");
                        head.push_back(0);

                        deque<int> row;
                        row.push_back(0);
                        index.push_back(row);
                    }
                    state = tm.start_state;
                }
                else
                {
//                    cout<<"need search"<<endl;

                    string old_chas = "";
                    for(int i=0;i<tm.num_tapes;i++)
                    {
                        old_chas += tape[i][head[i]];
                    }
//                    cout<<"old chas is "<<old_chas<<endl;

                    Transition tran = search_rule(tm,state,old_chas);
//                    cout<<"new directions are "<<tran.directions[0]<<tran.directions[1]<<endl;
                    // change to new state

                    vector<char> direction = tran.directions;
                    //rewrite tape
                    for(int i=0;i<tm.num_tapes;i++)
                    {
                        if(tran.new_chas[i]!='*')
                        {
                            tape[i][head[i]] = tran.new_chas[i];
                        }
                    }

                    //change head location
                    for(int i=0;i<tm.num_tapes;i++)
                    {
                        if(tran.directions[i]=='l')
                        {
                            head[i]--;
                        }
                        else if(tran.directions[i]=='r')
                        {
                            head[i]++;
                        }
                        else if(tran.directions[i]=='*')
                        {
                            ;
                        }
                        else
                        {
//                            cout<<"direction error"<<endl;
                            return;
                        }
                        if(head[i]<0)
                        {
                            head[i] = 0;
                            index[i].push_front(index[i].front()+1);
                            tape[i].insert(tape[i].begin(),'_');
                        }
                        else if(head[i]>index[i].back())
                        {
                            index[i].push_back(head[i]);
                        }
                        state = tran.new_state;
                        old_chas = tran.new_chas;

                    }

                }
                console<<"Step\t:\t"<<step<<endl;
                for(int i=0;i<tm.num_tapes;i++)
                {
                    //complete tape
                    while(head[i] >= tape[i].size())
                    {
                        tape[i] += '_';
                    }


                    // print index
                    console<<"Index"<<i<<"\t:";

                    for(int idx=0;idx<index[i].size();idx++)
                    {

                        console<<"\t"<<index[i][idx];

                    }
                    console<<endl;



                    // print tape
                    console<<"Tape"<<i<<"\t:";
                    for(int j=0;j<tape[i].size();j++)
                    {
                        console<<"\t"<<tape[i][j];
//                        if(tape[i][j]!=tm.blank||step==0)
//                        {
//                            cout<<"\t"<<tape[i][j];
//                        }

                    }
                    console<<endl;
                    console<<"Head"<<i<<"\t:\t";
                    for(int j=0;j<head[i];j++)
                    {
                        console<<"\t";
                    }
                    console<<"^"<<endl;
                }

                console<<"State\t:\t"<<state<<endl;
                console<<"------------------------------------------------------"<<endl;

                step++;
            }
            console<<"Result: ";
            string str_res = "";
            for(int i=0;i<tape[0].size();i++)
            {
                if(tape[0][i]=='_')
                {
                    continue;
                }
                str_res += tape[0][i];
                console<<tape[0][i];
            }
            console<<endl;
            console<<"==================== END ===================="<<endl;

            if(str_res=="True"||state=="halt_accept")
            {
                result<<"True"<<endl;
            }
            else if(str_res=="False"||state=="halt_reject")
            {
                result<<"False"<<endl;

            }
        }

    }
    console.close();
}
