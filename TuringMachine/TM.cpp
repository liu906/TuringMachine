//
// Created by lau on 2019/12/8.
//

#include "TM.h"

void TM::print_tran_funcs()
{
    vector<Transition>::iterator v = tran_funcs.begin();
    cout<<"all transition functions of tm :"<<endl;
    while(v!=tran_funcs.end()){
        cout<<"=============== transition ==================="<<endl;
        cout<<"old state : "<<v->old_state<<endl;
        cout<<"old characters : ";
        for(int i = 0;i < v->old_chas.size();i++)
        {
            cout<<v->old_chas[i]<<" ";
        }
        cout<<endl;

        cout<<"new characters : ";
        for(int i = 0;i < v->new_chas.size();i++)
        {
            cout<<v->new_chas[i]<<" ";
        }
        cout<<endl;

        cout<<"directions : ";
        for(int i = 0;i < v->directions.size();i++)
        {
            cout<<v->directions[i]<<" ";
        }
        cout<<endl;

        cout<<"new state : "<<v->new_state<<endl;
        v++;
    }

}
void TM::print_states(){
    vector<string>::iterator v = states.begin();
    cout<<"all states of tm"<<endl;
    while(v!=states.end()){
        cout<<*v<<endl;
        v++;
    }

}
void TM::print_symbols(){
    cout<<"all input symbols of tm"<<symbols<<endl;
}
void TM::print_tape_symbols()
{
    cout<<"all tape symbols of tm"<<tape_symbols<<endl;
}
void TM::print_final_state()
{
    cout<<"final states of tm"<<endl;
    vector<string>::iterator v = final_state.begin();
    while(v!=final_state.end())
    {
        cout<<*v<<" ";
        v++;
    }
    cout<<endl;

}
void TM::print_blank()
{
    cout<<"blank symbol is "<<blank<<endl;
}
void TM::print_start_state()
{
    cout<<"start state is "<<start_state<<endl;
}
void TM::print_num_tapes()
{
    cout<<"num of tapes : "<<num_tapes<<endl;

}

