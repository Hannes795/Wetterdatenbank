#include "error.h"

// default-constructor
error::error() {
	id = error_id::undefined_error;
	error_string = "An undefined error occured.";
	error_type = "Undefined";
	error_position = "Undefined";
}

// constructor which assigns given values to the attributes
error::error(error_id idc, string error_typec, string error_stringc, 
	string error_positionc, string previous_error_stringc) {
	id = idc;
	error_type = error_typec;
	error_position = error_positionc;
	if (previous_error_stringc.compare("") != 0) {
		string concat_helper = "\nThis error occurred because of following error:\n";
		error_string = error_stringc + concat_helper + previous_error_stringc;
	}
	else {
		error_string = error_stringc;
	}
}

// copy-constructor
error::error(const error& errorc) {
	*this = errorc;
}

// get- and set-methods for the attributes
void error::set_id(error_id idm) {
	id = idm;
}

error_id error::get_id() {
	return id;
}

void error::set_error_type(string error_typem) {
	error_type = error_typem;
}

string error::get_error_type() {
	return error_type;
}

void error::set_error_string(string error_stringm) {
	error_string = error_stringm;
}

string error::get_error_string() {
	return error_string;
}

void error::set_error_position(string error_positionm) {
	error_position = error_positionm;
}

string error::get_error_position() {
	return error_position;
}

// returns a string with an error-message; mainly used for stacktracing errors
string error::error_output_string() {
	string output_string;
	string part1 = "------------------------------\n";
	string part2 = "An unexspected error occured!\n";
	string part3 = "Error ID: \t";
	string part4 = "\nError in: \t";
	string part5 = "\nError type: \t";
	string line_break = "\n";
	output_string = part1 + part2 + part3 + to_string(int(id)) + part4 + error_position + 
		part5 + error_type + line_break + error_string;
	return output_string;
}

// Show the error on the console
void error::print_error() {
	cout << "------------------------------" << endl;
	cout << "An unexspected error occured!" << endl;
	cout << "Error ID: " << "\t" << int(id) << endl;
	cout << "Error in: " << "\t" << error_position << endl;
	cout << "Error type: " << "\t" << error_type << endl;
	cout << error_string << endl;
	cout << "------------------------------" << endl;
}

// for copying errors
error& error::operator = (const error& errorm) {
	id = errorm.id;
	error_position = errorm.error_position;
	error_type = errorm.error_type;
	error_string = errorm.error_string;
	return *this;
}