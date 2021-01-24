#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using std::cout;
using std::endl;


constexpr inline double calc_dividend(double& dividend)
{
	double div = 4. / ((dividend) * (dividend + 1.) * (dividend + 2.));
	return div;
}


double calc_pi(std::ofstream& file_logger)
{
	double hldr = 3.;
	bool sign = true;
	const unsigned int approx_pi_places = 1'000'000;
	double dividend = 2.;
	for (unsigned int i = 0; i < approx_pi_places; ++i)
	{
		double factor = calc_dividend(dividend);
		if (sign)
		{
			hldr += factor;
			sign = false;
		}
		else
		{
			hldr -= factor;
			sign = true;
		}
		dividend += 2;
		file_logger << "Places: " << i+1  << ":" << hldr << "\n";
	}

	return hldr;
}


int main()
{
	const int places = 15;
	double calcc;

	std::ofstream off("out.txt", std::ofstream::out);

	if (off)
	{
		off << std::setprecision(places + 1);
		calcc = calc_pi(off);
	}

	off.flush();
	off.close();

	std::stringstream format;
	format << "%." << places << "f\n";
	printf(format.str().c_str(), calcc);

	return 0;
}
