#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> names;
std::vector<std::vector<double>> values;

void remove_whitespaces(std::string& str)
{
	std::stringstream ss;
	ss << str;
	str.clear();
	std::string buffer;
	while (ss >> buffer) {
		str += buffer;
	}
}

void parse_file(const char* filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
		throw  std::ios_base::failure("Error! The file was not opened");
	std::string buffer;
	std::getline(in, buffer);
	std::stringstream ss;
	ss << buffer;
	while (!ss.eof()) {
		std::getline(ss, buffer, ',');
		remove_whitespaces(buffer);
		names.push_back(buffer);
	}
	while (!in.eof()) {
		std::getline(in, buffer);
		ss.clear();
		ss.str(std::string());
		ss << buffer;
		std::vector<double> temp_vec;
		temp_vec.reserve(names.size());
		while (!ss.eof()) {
			double x;
			ss >> x;
			if (ss.fail())
				throw std::ios_base::failure("Error! Incorrect format");
			temp_vec.push_back(x);
			ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
		}
		if (temp_vec.size() != names.size())
			throw std::ios_base::failure("Error! Incorrect number of elements");
		values.push_back(temp_vec);
	}
}

void print_data()
{
	for (int i = 0; i < names.size(); ++i)
		std::cout << names[i] << ' ';
	std::cout << '\n';
	for (int i = 0; i < values.size(); ++i) {
		for (int j = 0; j < values[i].size(); ++j)
			std::cout << values[i][j] << ' ';
		std::cout << '\n';
	}
}

int main() {
	try {
		parse_file("data.txt");
		print_data();
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	return 0;
}