#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class error_id { 
	undefined_error = -1, 
	null_type_error,
	empty_structure_error,
	index_out_of_bounds_error,
	end_of_structure_error,
	no_active_element_error,
	invalid_argument_error,
	file_not_found_error,
};

class error {
protected:
	error_id id;
	string error_type;
	string error_string;
	string error_position;
public:
	error();
	error(const error& errorc);
	error(error_id idc, string error_typec, string error_stringc, string error_positionc, string previous_error_string="");

	void set_id(error_id idm);
	error_id get_id();
	void set_error_type(string error_typem);
	string get_error_type();
	void set_error_string(string error_stringm);
	string get_error_string();
	void set_error_position(string error_positionm);
	string get_error_position();

	void print_error();
	string error_output_string();

	error& operator = (const error& errorm);
};