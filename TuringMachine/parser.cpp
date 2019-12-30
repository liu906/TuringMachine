//
// Created by lau on 2019/12/8.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "parser.h"
#include "TM.h"
using namespace std;


TM parser(string path){
    TM tm;
    // /home/lau/CLionProjects/Turing/palindrome_detector_2tapes.tm
    ifstream in(path);
    if(!in){
        cout<<"open file error "<<endl;
        return tm;
    }
    char str[255];
    while(in)
    {
        in.getline(str,255);
        if(str[0] == ';')
        {
            continue;
        }

        else if(str[0] == '#' && str[1] == 'Q')
        {
            int i = 0;
            while(i < 255)
            {
                if(str[i]=='}')
                {
                    break;
                }
                while(str[i]==' '||str[i]=='{'||str[i]=='='||str[i]=='Q'||str[i]=='#'||str[i]==',')
                {
                    i++;
                }
                int j = i+1;
                string sub = "";
                sub += str[i];
                while(j<255&&str[j]!=' '&&str[j]!='{'&&str[j]!='='&&str[j]!='Q'&&str[j]!='#'&&str[j]!=','&&str[j]!='}')
                {
                    sub += str[j];
                    j++;
                }
                i = j;

                tm.states.push_back(sub);
            }
        }

        else if(str[0] == '#' && str[1] == 'S')
        {
            int i=6;
            while(str[i]!='}')
            {
                if(str[i]==',')
                {
                    i++;
                    continue;
                }
                tm.symbols.push_back(str[i]);
                i++;
            }
//            tm.print_symbols();
        }
        else if(str[0] == '#' && str[1] == 'G')
        {
            int i=6;
            while(str[i]!='}')
            {
                if(str[i]==',')
                {
                    i++;
                    continue;
                }
                tm.tape_symbols.push_back(str[i]);
                i++;
            }
//            tm.print_tape_symbols();
        }

        else if(str[0] == '#' && str[1] == 'q' && str[2]=='0')
        {
            tm.start_state = str[6];
//            tm.print_start_state();

        }
        else if(str[0] == '#' && str[1] == 'B')
        {
            tm.blank = str[5];
//            tm.print_blank();
        }
        else if(str[0] == '#' && str[1] == 'F')
        {
            int i = 6;
            while(str[i]!='}')
            {
                if(str[i]==',')
                {
                    i++;
                    continue;
                }
                string sub = "";
                int j = i;
                while(str[j] != ',' && str[j] != '}')
                {
                    sub += str[j];
                    j++;
                }
//                cout<<"sub is "<<sub<<endl;
                ///////
                tm.final_state.push_back(sub);
                i = j;
            }
//            tm.print_final_state();
        }
        else if(str[0] == '#' && str[1] == 'N')
        {
            int i = 5;
            int sum = 0;
            while(str[i]>='0'&&str[i]<='9')
            {
                sum = (str[i] - '0') + 10 * sum;
                i++;
            }
            tm.num_tapes = sum;

        }
        // in else branch, read transition function
        else if(strlen(str)==0)
        {
            continue;
        }
        else
        {
            Transition trans;
            int i = 0;
            string sub = "";
            while(str[i]!=' ')
            {
                sub += str[i];
                i++;
            }
            trans.old_state = sub;
            i++;
            int j=i;
            for(j=i;j<i+tm.num_tapes;j++)
            {
                trans.old_chas.push_back(str[j]);
            }
            i = j+1;
            for(j=i;j<i+tm.num_tapes;j++)
            {
                trans.new_chas.push_back(str[j]);
            }
            i = j+1;
            for(j=i;j<i+tm.num_tapes;j++)
            {
                trans.directions.push_back(str[j]);
            }
            i = j+1;
            j = i;
            string next_state = "";
            while(str[j] != ' ' && j < strlen(str))
            {
                next_state += str[j];
                j++;
            }
            trans.new_state = next_state;
            tm.tran_funcs.push_back(trans);

        }

    }

    in.close();
    return tm;
}