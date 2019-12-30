#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include "TM.h"
#include "simulator.h"
using namespace std;

int main(int argc, char** argv)
{    // ont argument in command line: case-directory
    if(argc != 2)
    {
        cout<<"parameter error"<<endl;
        return 1;
    }
    string directory = argv[1];

    string tm_path = "./" + directory + "/test.tm";
    string input_path = "./" + directory + "/input.txt";

    cout<<"turing machine .tm path is "<<tm_path<<endl;
    cout<<"input.txt path is "<<input_path<<endl;


    simulate(directory,tm_path,input_path);
    cout<<"---------------------------"<<endl;
    cout<<"output console.txt successfully"<<endl;
    cout<<"output result.txt successfully"<<endl;
    return 0;

}