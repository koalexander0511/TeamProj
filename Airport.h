
#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <iostream>

using namespace std;

class Airport
{
private:
	string airport;
	string city;
public:
	Airport()									{ airport = "???"; city = "Unknown_City"; }
	Airport(string a, string c)					{ setAirport(a); setCity(c); }
	Airport(const Airport& aport)				{ setAirport(aport.airport); setCity(aport.city); }
	string getAirport()	const					{ return airport; }
	string getCity() const						{ return city; }
	void setAirport(string str)					{ airport = str; }
	void setCity(string str)					{ city = str; }
	Airport& operator=(const Airport& right);
	bool operator==(const Airport& right) const;
	bool operator< (const Airport& port) const;

	friend ostream& operator<<(ostream& os, const Airport& right);
};

ostream& operator<<(ostream &os, const Airport &right)
{
	os << right.airport << " " << right.city;
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

bool Airport::operator< (const Airport& port) const {
    // compares 3 letter airport code
    return airport < port.airport;
}

#endif
