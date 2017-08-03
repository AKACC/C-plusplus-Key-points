

// TODO: add your headers here
#include "passenger.h"
#include <iostream>
#include <cstring>
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
		if(m_name != nullptr && m_destination != nullptr){
			if(strlen(m_name) != 0 && strlen(m_destination) != 0 ){
				if(strcmp(m_name,"\0") != 0 && strcmp(m_destination,"\0") != 0){
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
}
