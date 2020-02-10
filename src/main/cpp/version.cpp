#include <version.h>

int Version::SaveVersionNumber(){
	std::string filename = std::string("/home/lvuser/") + filesnippet + std::string(".txt");
	std::ifstream file_in;
	std::ofstream file_out;
	file_in.open(filename.c_str());
	std::string data;
	std::getline(file_in, data);
	file_out.open(filename.c_str());
	int returnval;
	if (data.length() > 0){
		int data_i = std::atoi(data.c_str());
		file_out << data_i + 1<<std::endl;
		returnval = data_i + 1;
	}
	else{
		file_out <<"1"<<std::endl;
		returnval = 1;
	}
	file_in.close();
	file_out.close();
	version_number = returnval;
	return returnval;
}

void Version::CreateSaveFile(std::string inputstring){ // Create function that takes reference to an ofstream object
	std::ofstream output_file;
	std::time_t current_time = time(0);
	std::string time_string = std::ctime(&current_time); // Parameter takes pointer to time object
	std::string time_string_clear = "";

	for (int loop = 0; loop < time_string.length(); loop++)
	{
		if (time_string[loop] == ' ' || time_string[loop] == ':'){
			time_string[loop] = '-';
		}
		else if (time_string[loop] == '\n'){
			time_string[loop] = '.';
		}
	}
	std::stringstream version_ss;
	version_ss << version_number;
	time_string_clear = "_V" + version_ss.str() + std::string(time_string) + "txt";
	std::string filename = std::string("/home/lvuser/") + filesnippet + time_string_clear;
	output_file.open(filename.c_str());
	output_file << inputstring;
	output_file.close();
}

std::string Version::ToString(float integer){
	std::stringstream int_ss;
	int_ss << integer;
	std::string int_s = int_ss.str();
	return int_s;
}

void Version::AddToPipeDelimitedFile(std::string topic, std::string value, std::string &storage_topic, std::string &storage_value, bool print){
	if (print) std::cout<<topic<<": "<<value<<std::endl;
	storage_value = storage_value + value + "|";
	std::string topic_pipe = topic + std::string("|");
	if (storage_topic.find(topic_pipe) == std::string::npos) {
		storage_topic = storage_topic + topic_pipe;
	}
}

void Version::EndLoop(std::string &storage_value){
	storage_value = storage_value + "\n";
}

std::string Version::GetFileName(){
	return filesnippet;
}
