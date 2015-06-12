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
	operator=(Airport& left, Airport& right)	{ left.setAirport(right.getAirport); left.setCity(right.getCity); }
	bool operator==(const Airport& left, const Aiport& right);
	friend ostream & operator<<(ostream & os, const Airport &right);

};

ostream & operator<<(ostream & os, const Airport &right)
{
	os << right.airport << " " << right.city << endl;
	return os;
}
bool Airport::operator==(const Airport& left, const Aiport& right)
{
	if (left.getAirport() == right.getAirport() && left.getCity() == right.getCity())
		return true;
	else
		return false;
}
#endif