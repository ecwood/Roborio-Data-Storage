#include "read_psv.h"

std::vector<std::string> Read_PSV::split_string(std::string input, std::string delimiter){
	std::string temp_string = input;
	std::vector<std::string> split_vector;
	int filled_count = 0;
	for (int index = 0; index < input.length(); index++){
		if (std::string(1, input[index]) == delimiter){
			std::size_t comma_index = temp_string.find_last_of(",");
			if (comma_index == -1){
				comma_index = 0;
			} else{
				comma_index++;
			}
			split_vector.push_back(input.substr(comma_index, index - comma_index));
			temp_string[index] = ',';
		}
	}
	return split_vector;
}

void Read_PSV::read_psv(){
	std::string inputstring;
	std::fstream input_file(filename);

	if (input_file.is_open()){
		std::string line;
		int count = 0;
		while (getline(input_file, line)){
			psv_vector.push_back(split_string(line, delimiter));
		}
	}
}

float Read_PSV::get_value(int row, int column){
	std::string string_value = psv_vector[row][column];
	std::stringstream ss_value(string_value);
	float int_value;
	ss_value >> int_value;
	return int_value;
}