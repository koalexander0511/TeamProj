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
	Airport(string a, string c)					{ airport = a; city = c; }
	Airport(const Airport& airport)				{ this->airport = airport.getAirport(); this->city = airport.getCity(); }
	string getAirport()	const					{ return airport; }
	string getCity() const						{ return city; }
	void setAirport(string str)					{ airport = str; }
	void setCity(string str)					{ city = str; }
	Airport& operator=(Airport& right)	{ setAirport(right.getAirport()); setCity(right.getCity()); }
	bool operator==(const Airport& right);
	friend ostream & operator<<(ostream & os, const Airport &right);

};

ostream & operator<<(ostream & os, const Airport &right)
{
	os << right.airport << " " << right.city << endl;
	return os;
}

bool Airport::operator==(const Airport& right)
{
	if (getAirport() == right.getAirport() && getCity() == right.getCity())
		return true;
	else
		return false;
}
#endif
