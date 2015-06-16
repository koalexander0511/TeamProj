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
	Airport& operator=(const Airport& right);
	bool operator==(const Airport& right) const;

	friend ostream & operator<<(ostream & os, const Airport &right);
};

ostream & operator<<(ostream & os, const Airport &right)
{
	os << right.getAirport() << " " << right.getCity() << endl;
	return os;
}
Airport& Airport::operator=(const Airport& right)
{
	setAirport(right.getAirport());
	setCity(right.getCity());
	return *this;
}
bool Airport::operator==(const Airport& right) const
{
	if (airport == right.getAirport() && city == right.getCity())
		return true;
	else
		return false;
}
#endif
