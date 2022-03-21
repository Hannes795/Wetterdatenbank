#pragma once
#include <iostream>
#include "error.h"


// A datatuple is one tuple of the database, which is implemented as a double-linked-list, so the tuple has a pointer to the next and previous element.
// The data has to be the entire data of the "line" or tuple and is in the weather-database subclass a weather dataset.
// The id is used to distinguish the tuple from other tuples with the same data, but actually unnecessary, at least for our application.
template<class T> struct datatuple {
	T data;
	datatuple<T>* next{};
	datatuple<T>* previous{};
	int id{};
};

template<class T> class database {
protected:
	// ID for the next added datatuple. The ID is only changed after a datatuple is added,
	// so it is unique for every element in the database. Even if two datatuples in the database have the same data,
	// the unique ID makes it possible to distinguish between the two datatuples. 
	int id;
	// Current count of datatuples in the database.
	int length;
	// Index of the current element, -1 if there is no current element.
	int current_index;
	// Three pointer to the first, last and current element of the database. The current element is NULL, as long as it is not set with 
	// to_first(), to_last() or to_index(int index).
	datatuple<T>* first;
	datatuple<T>* last;
	datatuple<T>* current;
public:
	// constructor for default-values
	database();
	//copy-constructor
	//database(database<T>& db);

	// Method to add an element to the database at the position of the index
	void add(T dataset, int index);
	// Method to remove an element of the database at the given position
	void remove(int index);
	// Method to move an element from the index_1 to index_2
	void move(int index_1, int index_2);

	// Method to move the current element to the desired position
	void to_first();
	void to_last();
	void to_index(int index);
	void to_next();
	void to_previous();

	// Method to print the database to the console
	// default: The Datatuple ID's are printed in order to the console
	// Should be implemented for the specific data by its subclasses.
	virtual void print_db();

	// returns the value of the attributes
	int get_length();
	int get_current_index();
	int get_current_id();

	// returns the dataset of the current datatuple
	T get_current_dataset();

	// for copying databases
	//database& operator = (database<T>& db);
};

// constructor to set default values for the database
template<class T> database<T>::database() {
	id = 0;
	length = 0;
	current_index = -1;
	first = NULL;
	last = NULL;
	current = NULL;
}
/*
// copy-constructor
template<class T> database<T>::database(database<T>& db) {
	length = 0;
	current_index = db.current_index;
	db.to_first();
	id = db.get_current_id();
	add(db.get_current_dataset(), get_length());
	for (int i = 0; i < db.get_length() - 1; i++) {
		db.to_next();
		id = db.get_current_id();
		add(db.get_current_dataset(), get_length());
	}
	id = db.id;
	try {
		db.to_index(current_index);
	}
	catch (error e) {
		db.current_index = current_index;
	}
}
*/
// Method to add an element to the database at the position of the index
template<class T> void database<T>::add(T dataset, int index) {
	// Condition for an empty database -> All pointer are NULL until the first element is added
	if (length == 0) {
		datatuple<T>* dt = new datatuple<T>;
		dt->data = dataset;
		dt->id = id;
		dt->next = NULL;
		dt->previous = NULL;
		first = dt;
		last = dt;
		id++;
		length++;
	}
	// Condition for adding at the front of the database, the connection to the previous element has to be left out, because there is none.
	else if (index == 0) {
		datatuple<T>* dt = new datatuple<T>;
		dt->data = dataset;
		dt->id = id;
		dt->next = first;
		dt->previous = NULL;
		first->previous = dt;
		first = dt;
		id++;
		length++;
		if (index <= current_index) {
			current_index++;
		}
	}
	// Condition for adding at the end of the database, the connection to the next element has to be left out, because there is none.
	else if (index == length) {
		datatuple<T>* dt = new datatuple<T>;
		dt->data = dataset;
		dt->id = id;
		dt->next = NULL;
		dt->previous = last;
		last->next = dt;
		last = dt;
		id++;
		length++;
	}
	// Condition for adding in the middle of the database 
	else if (index > 0 && index < length) {
		datatuple<T>* dt_c = first;
		for (int i = 0; i < index; i++) {
			dt_c = dt_c->next;
		}
		datatuple<T>* dt = new datatuple<T>;
		dt->data = dataset;
		dt->id = id;
		dt->next = dt_c;
		dt->previous = dt_c->previous;
		dt_c->previous = dt;
		dt->previous->next = dt;
		id++;
		length++;
		if (index <= current_index) {
			current_index++;
		}
	}
	// Condition for a wrong index
	else {
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		string error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		error index_error{error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::add"};
		throw index_error;
	}
}

// Method to remove an element of the database at the given position
template<class T> void database<T>::remove(int index) {
	if (index >= 0 && index < length) {
		// Condition for an afterwards empty database
		if (length == 1) {
			first = NULL;
			last = NULL;
			current = NULL;
			length = 0;
			current_index = -1;
		}
		// Condition for removing the first element
		else if (index == 0) {
			first = first->next;
			first->previous = NULL;
			length--;
			if (index == current_index) {
				current = NULL;
				current_index = -1;
			}
			else if (index < current_index) {
				current_index--;
			}
		}
		// Condition for removing the last element
		else if (index == length - 1) {
			last = last->previous;
			last->next = NULL;
			length--;
			if (index == current_index) {
				current = NULL;
				current_index = -1;
			}
		}
		// Condition for removing an element in the middle of the database
		else {
			datatuple<T>* dt_c = first;
			for (int i = 0; i < index; i++) {
				dt_c = dt_c->next;
			}
			dt_c->previous->next = dt_c->next;
			dt_c->next->previous = dt_c->previous;
			length--;
			if (index == current_index) {
				current = NULL;
				current_index = -1;
			}
			else if (index < current_index) {
				current_index--;
			}
		}
	}
	// Condition for a wrong index
	else {
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		string error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		error index_error{error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::remove"};
		throw index_error;
	}
}

// Method to move an element from the index_1 to index_2
template<class T> void database<T>::move(int index_1, int index_2) {
	if (index_1 < length && index_2 < length && index_1 >= 0 && index_2 >= 0) {
		if (index_1 != index_2) {
			datatuple<T>* dt;
			//Condition if the element that will be moved is the first element
			if (index_1 == 0) {
				dt = first;
				first = first->next;
				first->previous = NULL;
			}
			//Condition if the element that will be moved is the last element
			else if (index_1 == length - 1) {
				dt = last;
				last = last->previous;
				last->next = NULL;
			}
			//Condition if the element that will be moved is an element in the middle of the database
			else {
				datatuple<T>* dt_c = first;
				for (int i = 0; i < index_1; i++) {
					dt_c = dt_c->next;
				}
				dt = dt_c;
				dt->previous->next = dt->next;
				dt->next->previous = dt->previous;
			}
			//Condition if the element will be moved to the front of the database
			if (index_2 == 0) {
				dt->next = first;
				dt->previous = NULL;
				first->previous = dt;
				first = dt;
			}
			//Condition if the element will be moved to the end of the database
			else if (index_2 == length - 1) {
				dt->previous = last;
				dt->next = NULL;
				last->next = dt;
				last = dt;
			}
			//Condition if the element will be moved somewhere to the middle of the database
			else {
				datatuple<T>* dt_c = first;
				for (int i = 0; i < index_2; i++) {
					dt_c = dt_c->next;
				}
				dt->previous = dt_c->previous;
				dt->next = dt_c;
				dt_c->previous->next = dt;
				dt_c->previous = dt;
			}
			//Update the index of the current element
			if (index_1 == current_index) {
				current_index = index_2;
			}
			else if (index_1 < current_index && index_2 >= current_index) {
				current_index--;
			}
			else if (index_1 > current_index && index_2 <= current_index) {
				current_index++;
			}
		}
	}
	else {
		// Conditions for a wrong index
		if ((index_1 >= length || index_1 < 0) && (index_2 >= length || index_2 < 0)) {
			string part_1 = "The given indices(";
			string part_2 = to_string(index_1);
			string part_3 = ", ";
			string part_4 = to_string(index_2);
			string part_5 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_6 = to_string(length);
			string part_7 = ").";
			string error_string = part_1 + part_2 + part_3 + part_4 + part_5 + part_6 + part_7;
			error index_error{error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::move"};
			throw index_error;
		}
		else if (index_1 >= length || index_1 < 0) {
			string part_1 = "The given index_1(";
			string part_2 = to_string(index_1);
			string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_4 = to_string(length);
			string part_5 = ").";
			string error_string = part_1 + part_2 + part_3 + part_4 + part_5;
			error index_error{ error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::move" };
			throw index_error;
		}
		else {
			string part_1 = "The given index_2(";
			string part_2 = to_string(index_1);
			string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_4 = to_string(length);
			string part_5 = ").";
			string error_string = part_1 + part_2 + part_3 + part_4 + part_5;
			error index_error{ error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::move" };
			throw index_error;
		}
	}
}

//Method to set the first element as the current element of the database
template<class T> void database<T>::to_first() {
	if (length > 0) {
		current = first;
		current_index = 0;
	}
	else {
		error zero_length_error{error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::to_first"};
		throw zero_length_error;
	}
}

//Method to set the last element as the current element of the database
template<class T> void database<T>::to_last() {
	if (length > 0) {
		current = last;
		current_index = length - 1;
	}
	else {
		error zero_length_error{ error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::to_last" };
		throw zero_length_error;
	}
}

//Method to set the next element as current element
template<class T> void database<T>::to_next() {
	if (current_index >= 0 && current_index < length - 1) {
		current = current->next;
		current_index++;
	}
	else if (length == 0) {
		error zero_length_error{ error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::to_next" };
		throw zero_length_error;
	}
	else if (current_index == -1) {
		error no_active_element_error{ error_id::no_active_element_error, "NoActiveElementError", "There is no active element. Set an active element with the methods to_first, to_last or to_index first.", "database::to_next" };
		throw no_active_element_error;
	}
	else {
		error end_of_db_error{ error_id::end_of_structure_error, "EndOfStructureError", "You have reached the last element of the database, there is no next element.", "database::to_next" };
		throw end_of_db_error;
	}
}

//Method to set the previous element as current element
template<class T> void database<T>::to_previous() {
	if (current_index > 0 && current_index <= length - 1) {
		current = current->previous;
		current_index--;
	}
	else if (length == 0) {
		error zero_length_error{ error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::to_previous" };
		throw zero_length_error;
	}
	else if (current_index == -1) {
		error no_active_element_error{ error_id::no_active_element_error, "NoActiveElementError", "There is no active element. Set an active element with the methods to_first, to_last or to_index first.", "database::to_previous" };
		throw no_active_element_error;
	}
	else {
		error end_of_db_error{ error_id::end_of_structure_error, "EndOfStructureError", "You have reached the last element of the database, there is no next element.", "database::to_previous" };
		throw end_of_db_error;
	}
}

//Method to set the element at the index "index" as current element
template<class T> void database<T>::to_index(int index) {
	if (index >= 0 && index < length) {
		current = first;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		current_index = index;
	}
	else if (length == 0) {
		error zero_length_error{ error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::to_index" };
		throw zero_length_error;
	}
	else {
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		string error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		error index_error{ error_id::index_out_of_bounds_error, "IndexOutOfBoundsError", error_string, "database::to_index" };
		throw index_error;
	}
}

// virtual-method: prints the ids of the elements in the database->shoulb be overwritten to print the content of the datatuple and not its id
template<class T> void database<T>::print_db() {
	if (length > 0) {
		cout << "------------------------------------" << endl;
		cout << "Database is printed!" << endl;
		datatuple<T>* dt_c = first;
		cout << "Datatuple: " << dt_c->id << endl;
		for (int i = 0; i < length - 1; i++) {
			dt_c = dt_c->next;
			cout << "Datatuple: " << dt_c->id << endl;
		}
		cout << "------------------------------------" << endl;
	}
	else {
		error zero_length_error{ error_id::empty_structure_error, "EmptyStructureError", "The database has a length of 0. Add an element.", "database::print_db" };
		throw zero_length_error;
	}
}

//returns the length of the database
template<class T> int database<T>::get_length() {
	return length;
}

//returns the current index of the database
template<class T> int database<T>::get_current_index() {
	return current_index;
}

//returns the data of the current element
template<class T> T database<T>::get_current_dataset() {
	if (current_index != -1) {
		return current->data;
	}
	else {
		error no_active_element_error{ error_id::no_active_element_error, "NoActiveElementError", "There is no active element. Set an active element with the methods to_first, to_last or to_index first.", "database::get_current_dataset" };
		throw no_active_element_error;
	}
}

//returns the id of the current element
template<class T> int database<T>::get_current_id() {
	if (current_index != -1) {
		return current->id;
	}
	else {
		error no_active_element_error{ error_id::no_active_element_error, "NoActiveElementError", "There is no active element. Set an active element with the methods to_first, to_last or to_index first.", "database::get_current_id" };
		throw no_active_element_error;
	}
}
/*
//For copying elements
template<class T> database<T>& database<T>::operator = (database<T>& db) {
	length = 0;
	current_index = db->current_index;
	db.to_first();
	id = db.get_current_id();
	add(db.get_current_dataset(), get_length());
	for (int i = 0; i < db.get_length() - 1; i++) {
		db.to_next();
		id = db.get_current_id();
		add(db.get_current_dataset(), get_length());
	}
	id = db->id;
	try {
		db.to_index(current_index);
	}
	catch(error e) {
		db.current_index = current_index;
	}
	return *this;
}*/