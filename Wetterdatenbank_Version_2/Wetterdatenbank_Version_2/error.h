#pragma once
#include <iostream>
#include <string>

using namespace std;

//The class error_id collects all the errors that can occur 
//in our programm and assigns an id to each error.
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

//error-class
class error {
protected:
	// The id is used to identify the error-type within the programm
	error_id id;
	// The error-type is used to show the user/developer which error occured
	string error_type;
	// The error-string is used to print an error message to the console.
	// It is used to store previous errors for a stack-trace with string-concatenation too.
	string error_string;
	// The class/function, in which the error occured
	string error_position;
public:
	// default-constructor
	error();
	// copy-constructor
	error(const error& errorc);
	// constructor which assigns the arguments to the attributes
	error(error_id idc, string error_typec, string error_stringc, 
		string error_positionc, string previous_error_string="");

	// get- and set-methods for the class-attributes
	void set_id(error_id idm);
	error_id get_id();
	void set_error_type(string error_typem);
	string get_error_type();
	void set_error_string(string error_stringm);
	string get_error_string();
	void set_error_position(string error_positionm);
	string get_error_position();

	// print the error to console
	void print_error();
	// used mainly for the stack-trace
	string error_output_string();

	// for copying errors
	error& operator = (const error& errorm);
};