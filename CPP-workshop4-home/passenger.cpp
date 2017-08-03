

// TODO: add your headers here
#include "passenger.h"
#include <iostream>
#include <string.h>
// TODO: add the namespaces that you will be using here
using namespace std;
// TODO: holiday namespace here
namespace holiday{

    // TODO: add the default constructor here
	Passenger::Passenger(){

			m_departureDay = 0;
			m_departureMonth = 0;
			m_departureYear = 0;
			strcpy(m_name, "");
			strcpy(m_destination, "");
	}
    // TODO: add the constructor with 2 parameters here
	Passenger::Passenger(const char pName[], const char pDestination[]){

			if( pName != nullptr &&
			 pDestination != nullptr){
				if(strlen(pName) != 0 && strlen(pDestination) != 0){
					strcpy(m_name, pName);
					strcpy(m_destination, pDestination);
					m_departureYear = 2017;
					m_departureMonth = 7;
					m_departureDay = 1;
				}else{
					m_departureDay = 0;
					m_departureMonth = 0;
					m_departureYear = 0;
					strcpy(m_name, "");
					strcpy(m_destination, "");
				}
			}else{
				m_departureDay = 0;
				m_departureMonth = 0;
				m_departureYear = 0;
				strcpy(m_name, "");
				strcpy(m_destination, "");
			}



	}
	// TODO: add the constructor with 5 parameters here
	Passenger::Passenger(const char pName[], const char pDestination[], int pYear, int pMonth, int pDay){

		if(pName != nullptr &&
				pDestination != nullptr &&
				strlen(pName) != 0 && strlen(pDestination)!= 0 &&
				pYear<= 2020 && pYear >=2017 &&
				pMonth >=1 && pMonth <=12 &&
				pDay >= 1 && pDay <=31){

			strcpy(m_name, pName);
			strcpy(m_destination, pDestination);
			m_departureYear = pYear;
			m_departureMonth = pMonth;
			m_departureDay = pDay;
		}else{
			m_departureDay = 0;
			m_departureMonth = 0;
			m_departureYear = 0;
			strcpy(m_name, "");
			strcpy(m_destination, "");
		}

	}

    // TODO: add the canTravelWith(...) function here
	bool Passenger::canTravelWith(const Passenger& passenger) const{
		bool result = false;
		if(strcmp(this->m_destination,passenger.m_destination) == 0){
			if(this->m_departureYear == passenger.m_departureYear &&
			   this->m_departureMonth == passenger.m_departureMonth &&
			   this->m_departureDay == passenger.m_departureDay){
				result = true;
			}
		}
		return result;
	}
    // TODO: add the isEmpty() function here
	bool Passenger::isEmpty() const{

		bool result = true;
//		if(strlen(this->m_name) != 0 && this->m_name != nullptr && strlen(this->m_destination) != 0 && this->m_destination != nullptr){
//			result = false;
//		}
		if(this->m_name != nullptr && this->m_destination != nullptr){
			if(strlen(this->m_name) != 0 && strlen(this->m_destination) != 0 ){
				if(strcmp(this->m_name,"") != 0 && strcmp(this->m_destination,"") != 0){

						result = false;
				}
			}
		}

		return result;
	}
    // below is the member function already provided
    // TODO: read it and understand how it accomplishes its task
	void Passenger::display(bool nameOnly) const
	{

		if (false == this->isEmpty())
		{

			cout << this->m_name;
			if (false == nameOnly)
			{
				cout << " will travel to " << this->m_destination << ". "
				     << "The journey will start on "
				     << this->m_departureYear << "-"
					 << this->m_departureMonth << "-"
					 << this->m_departureDay
				     << "." << endl;
			}
		}
		else
		{
			cout << "Invalid passenger!" << endl;
		}
	}
	void Passenger::display(const Passenger arr[],int num,int size) const
	{
		if(num == 0){
			cout<<"Nobody can join "<<this->m_name<<" on vacation!"<<endl;
		}
		else{
			if(num == size){
				cout<<"Everybody can join "<<this->m_name<<" on vacation!"<<endl;
			}
			cout<< this->m_name << " will be accompanied by ";
			for(int i = 0; i < num ; i++){
				cout<< arr[i].m_name;
				if(i == (num - 1)){
					cout<<"."<<endl;
				}else{
					cout<<", ";
				}
			}

		}
	}
	void Passenger::travelWith(const Passenger* arrPassengers, int size){
		int j = 0;
		Passenger tgtFrd[7];
		for(int i = 0; i < size; i++){
			if(this->canTravelWith(arrPassengers[i])){

				tgtFrd[j] = arrPassengers[i];
				j++;
			}
		}
		this->display(tgtFrd, j, size);

	}

}
