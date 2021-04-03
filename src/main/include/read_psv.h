#ifndef READ_PSV
#define READ_PSV

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>

class Read_PSV
{
public:
	Read_PSV(std::string filename, std::string delimiter) : filename(filename), delimiter(delimiter) {};

	void read_psv();
	float get_value(int row, int column);
private:
	std::string filename;
	std::string delimiter;

	std::vector<std::vector<int> > psv_vector;

	std::vector<int> split_string(std::string input, std::string delimiter);
	float string_to_num(std::string string_number);
};

#endif