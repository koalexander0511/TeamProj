#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <iostream>
class Airport
{
private:
	string airport;
	string city;
public:
	Airport()									{ airport = "???"; city = "Unknown_City"; }
	Airport(string a, string c)					{ airpot = a; city = c; }
	Airport(const Airport& airport)				{ airport = airport.getAirport(); city = airport.getCity(); }
	string getAirport()							{ return airport; }
	string getCity()							{ return city; }
	void setAirport(string str)					{ airport = str; }
	void setCity(string str)					{ city = str; }
	Airport& operator=(Airport& left, Airport& right);
	bool operator==(const Airport& left, const Aiport& right);
	friend ostream & operator<<(ostream & os, const Airport &right);

};

ostream & operator<<(ostream & os, const Airport &right)
{
	os << right.airport << " " << right.city << endl;
	return os;
}
Airport& operator=(Airport& right)
{ 
	setAirport(right.getAirport);
	setCity(right.getCity);
	return right;
}
bool Airport::operator==(const Aiport& right)
{
	if (getAirport() == right.getAirport() && getCity() == right.getCity())
		return true;
	else
		return false;
}
#endif