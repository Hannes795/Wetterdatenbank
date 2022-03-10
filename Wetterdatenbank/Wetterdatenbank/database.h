#pragma once
#include <string>
#include <iostream>

using namespace std;

struct db_error {
	int id;
	string error_type;
	string error_string;
	string error_position;
};


template<class T> struct datatuple {
	T data;
	datatuple<T>* next;
	datatuple<T>* previous;
	int id;
};



template<class T> class database {
protected:
	int id;
	int length;
	int current_index;
	datatuple<T>* first;
	datatuple<T>* last;
	datatuple<T>* current;
public:
	database();

	void add(T dataset, int index);
	void remove(int index);
	void move(int index_1, int index_2);

	void to_first();
	void to_last();
	void to_index(int index);
	void to_next();
	void to_previous();

	virtual void print_db();

	int get_length();
	int get_current_index();

	T get_current_dataset();
};


template<class T> database<T>::database() {
	id = 0;
	length = 0;
	current_index = -1;
	first = NULL;
	last = NULL;
	current = NULL;
}

template<class T> void database<T>::add(T dataset, int index) {
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
	else {
		db_error index_error;
		index_error.id = 0;
		index_error.error_type = "IndexOutOfBoundsError";
		index_error.error_position = "database::add";
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		throw index_error;
	}
}

template<class T> void database<T>::remove(int index) {
	if (index >= 0 && index < length) {
		if (length == 1) {
			first = NULL;
			last = NULL;
			current = NULL;
			length = 0;
			current_index = -1;
		}
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
		else if (index == length - 1) {
			last = last->previous;
			last->next = NULL;
			length--;
			if (index == current_index) {
				current = NULL;
				current_index = -1;
			}
		}
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
	else {
		db_error index_error;
		index_error.id = 0;
		index_error.error_type = "IndexOutOfBoundsError";
		index_error.error_position = "database::remove";
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		throw index_error;
	}
}

template<class T> void database<T>::move(int index_1, int index_2) {
	if (index_1 < length && index_2 < length && index_1 >= 0 && index_2 >= 0) {
		if (index_1 != index_2) {
			datatuple<T>* dt;
			if (index_1 == 0) {
				dt = first;
				first = first->next;
				first->previous = NULL;
			}
			else if (index_1 == length - 1) {
				dt = last;
				last = last->previous;
				last->next = NULL;
			}
			else {
				datatuple<T>* dt_c = first;
				for (int i = 0; i < index_1; i++) {
					dt_c = dt_c->next;
				}
				dt = dt_c;
				dt->previous->next = dt->next;
				dt->next->previous = dt->previous;
			}
			if (index_2 == 0) {
				dt->next = first;
				dt->previous = NULL;
				first->previous = dt;
				first = dt;
			}
			else if (index_2 == length - 1) {
				dt->previous = last;
				dt->next = NULL;
				last->next = dt;
				last = dt;
			}
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
		if ((index_1 >= length || index_1 < 0) && (index_2 >= length || index_2 < 0)) {
			db_error index_error;
			index_error.id = 0;
			index_error.error_type = "IndexOutOfBoundsError";
			index_error.error_position = "database::move";
			string part_1 = "The given indices(";
			string part_2 = to_string(index_1);
			string part_3 = ", ";
			string part_4 = to_string(index_2);
			string part_5 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_6 = to_string(length);
			string part_7 = ").";
			index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5 + part_6 + part_7;
			throw index_error;
		}
		else if (index_1 >= length || index_1 < 0) {
			db_error index_error;
			index_error.id = 0;
			index_error.error_type = "IndexOutOfBoundsError";
			index_error.error_position = "database::move";
			string part_1 = "The given index_1(";
			string part_2 = to_string(index_1);
			string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_4 = to_string(length);
			string part_5 = ").";
			index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;
			throw index_error;
		}
		else {
			db_error index_error;
			index_error.id = 0;
			index_error.error_type = "IndexOutOfBoundsError";
			index_error.error_position = "database::move";
			string part_1 = "The given index_2(";
			string part_2 = to_string(index_2);
			string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
			string part_4 = to_string(length);
			string part_5 = ").";
			index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;			throw index_error;
		}
	}
}

template<class T> void database<T>::to_first() {
	if (length > 0) {
		current = first;
		current_index = 0;
	}
	else {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::to_first";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
}

template<class T> void database<T>::to_last() {
	if (length > 0) {
		current = last;
		current_index = length - 1;
	}
	else {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::to_last";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
}

template<class T> void database<T>::to_next() {
	if (current_index >= 0 && current_index < length - 1) {
		current = current->next;
		current_index++;
	}
	else if (length == 0) {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::to_next";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
	else if (current_index == -1) {
		db_error no_active_element_error;
		no_active_element_error.id = 3;
		no_active_element_error.error_type = "NoActiveElementError";
		no_active_element_error.error_position = "database::to_next";
		no_active_element_error.error_string = "There is no active element. Set an active element with the methods to_first, to_last or to_index first.";
		throw no_active_element_error;
	}
	else {
		db_error end_of_db_error;
		end_of_db_error.id = 4;
		end_of_db_error.error_type = "EndOfDbError";
		end_of_db_error.error_position = "database::to_next";
		end_of_db_error.error_string = "You have reached the last element of the database, there is no next element.";
		throw end_of_db_error;
	}
}

template<class T> void database<T>::to_previous() {
	if (current_index > 0 && current_index <= length - 1) {
		current = current->previous;
		current_index--;
	}
	else if (length == 0) {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::to_previous";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
	else if (current_index == -1) {
		db_error no_active_element_error;
		no_active_element_error.id = 3;
		no_active_element_error.error_type = "NoActiveElementError";
		no_active_element_error.error_position = "database::to_previous";
		no_active_element_error.error_string = "There is no active element. Set an active element with the methods to_first, to_last or to_index first.";
		throw no_active_element_error;
	}
	else {
		db_error end_of_db_error;
		end_of_db_error.id = 4;
		end_of_db_error.error_type = "EndOfDbError";
		end_of_db_error.error_position = "database::to_previous";
		end_of_db_error.error_string = "You have reached the first element of the database, there is no previous element.";
		throw end_of_db_error;
	}
}

template<class T> void database<T>::to_index(int index) {
	if (index >= 0 && index < length) {
		current = first;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		current_index = index;
	}
	else if (length == 0) {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::to_index";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
	else {
		db_error index_error;
		index_error.id = 0;
		index_error.error_type = "IndexOutOfBoundsError";
		index_error.error_position = "database::to_index";
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;	
		throw index_error;
	}
}

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
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "database::print_db";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
}

template<class T> int database<T>::get_length() {
	return length;
}

template<class T> int database<T>::get_current_index() {
	return current_index;
}



template<class T> T database<T>::get_current_dataset() {
	if (current_index != -1) {
		return current->data;
	}
	else {
		db_error no_active_element_error;
		no_active_element_error.id = 3;
		no_active_element_error.error_type = "NoActiveElementError";
		no_active_element_error.error_position = "database::get_current_dataset";
		no_active_element_error.error_string = "There is no active element. Set an active element with the methods to_first, to_last or to_index first.";
		throw no_active_element_error;
	}
}

