// OOP244 Workshop 2: at-home
// File kingdom.cpp
// Version 1.0
// Date 2017-01-29
// Author Jack Ou
// Description
//  Function overloading
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////


// TODO: include the necessary headers
#include <iostream>
#include <cstring>
#include "kingdom.h"

using namespace std;
// TODO: the westeros namespace
namespace westeros{

    // TODO:definition for display(...)
	void display(Kingdom& kd){
		cout<<kd.m_name<<", population "<<kd.m_population<<endl;
	}



	void display(Kingdom Kingdoms[], int num){
		int totalPop = 0;
			cout<<"------------------------------"<<endl;
			cout<<"Kingdoms of Westeros"<<endl;
			cout<<"------------------------------"<<endl;
			for(int i = 0;i < num; i++){
				cout<<i+1<<". "<<Kingdoms[i].m_name<<", population "<<Kingdoms[i].m_population<<endl;
				totalPop += Kingdoms[i].m_population;
			}
			cout<<"------------------------------"<<endl;
			cout<<"Total population of Westeros: "<< totalPop<<endl;
 			cout<<"------------------------------"<<endl;
	}
	void display(Kingdom Kingdoms[], int num, int min){

				cout<<"------------------------------"<<endl;
				cout<<"Kingdoms of Westeros with more than "<<min<<" people"<<endl;
				cout<<"------------------------------"<<endl;
				for(int i = 0;i < num; i++){
					if(Kingdoms[i].m_population >= min){
						cout<<Kingdoms[i].m_name<<", population "<<Kingdoms[i].m_population<<endl;
					}
				}
	 			cout<<"------------------------------"<<endl;
	}
	void display(Kingdom Kingdoms[], int num,const char* name){
				int found = -1;
				cout<<"------------------------------"<<endl;
				cout<<"Searching for kingdom "<<name<<" in Westeros"<<endl;
				cout<<"------------------------------"<<endl;
				for(int i = 0;i < num; i++){
					if(strcmp(Kingdoms[i].m_name,name) == 0){
						found = i;
					}

				}
				if(found != -1){
					cout<<Kingdoms[found].m_name<<", population "<<Kingdoms[found].m_population<<endl;
				}else{
					cout<<name<<" is not part of Westeros."<<endl;
				}
		 		cout<<"------------------------------"<<endl;
	}


}
