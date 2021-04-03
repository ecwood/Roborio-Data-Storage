#include "read_psv.h"

float Read_PSV::string_to_num(std::string string_number){
	std::stringstream ss_value(string_number);
	float float_number;
	ss_value >> float_number;
	return float_number;
}

std::vector<float> Read_PSV::split_string(std::string input, std::string delimiter){
	std::string temp_string = input;
	std::vector<float> split_vector;
	int filled_count = 0;
	for (int index = 0; index < input.length(); index++){
		if (std::string(1, input[index]) == delimiter){
			std::size_t comma_index = temp_string.find_last_of(",");
			if (comma_index == -1){
				comma_index = 0;
			} else{
				comma_index++;
			}
			split_vector.push_back(string_to_num(input.substr(comma_index, index - comma_index)));
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
			if (count != 0){
				psv_vector.push_back(split_string(line, delimiter));
			}
			count++;
		}
	}
}

float Read_PSV::get_value(int row, int column){
	return psv_vector[row][column];
}