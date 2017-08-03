//TODO: add header guards here  //same as #pragma once
#ifndef HOLIDAY_PASSENGER_H
#define HOLIDAY_PASSENGER_H
// TODO: holiday namespace here
namespace holiday{
    // TODO: declare the class Passenger here
	class Passenger{
        // TODO: add the class the attributes,
	private:
		char m_name[32];
		char m_destination[32];
		int m_departureYear;
		int m_departureMonth;
		int m_departureDay;



        //       the member function already provided,
	public:
		Passenger();
		Passenger(const char pName[], const char pDestination[]);
        //       and the member functions that you must implement
		bool isEmpty() const;
		bool canTravelWith(const Passenger&) const;
		void display(bool nameOnly = false) const;
	};
}
#endif
