#include "error.h"
#include "database.h"
#include "weather_dataset.h"
#include "weather_database.h"

class menu {
private:
	weather_database wdbs[6] = { weather_database(), weather_database(), weather_database(), weather_database(), weather_database(), weather_database()};
	int active_db = 0;
	bool initialized [6] = {true, false, false, false, false, false};
	bool additional_initialized = false;
public:
	bool file_menu(string file_namem = "", int endline=-1, int startline=-1);
	void start_menu();
	void create_database_menu();
	void sort_data_menu();
	void search_data_menu();
	void calculate_average_menu();
	void switch_database_menu();
	void print_menu();
};

bool menu::file_menu(string file_namem, int endline, int startline) {
	string file_namea = file_namem;
	int endlinea = endline;
	int startlinea = startline;
	while (true) {
		if (file_namea == "") 
		{
			cout << "--------------------------------------------------" << endl;
			cout << "Please enter the name of the file, which should be processed, or [X] to abort.\nThe file should contain weather data in a specific format.\nIf you do not know which format, please contact our customer service ;-),\nwhich is available Monday-Friday from 24:00-25:00. " << endl;
		}
		try {
			string file_name;
			if (file_namea == "")
				cin >> file_name;
			else
				file_name = file_namea;
			if (file_name == "X") {
				return false;
			}
			wdbs[0].read_file(file_name, endlinea, startlinea);
			if (wdbs[0].get_length() > 0) {
				return true;
			}
			else
			{
				cout << "An error occurred while reading the database. The database is empty. Please try again with a valid file." << endl;
				file_namea = "";
				startlinea = -1;
				endlinea = -1;
			}
		}
		catch (error e) {
			file_namea = "";
			startlinea = -1;
			endlinea = -1;
			e.print_error();
		}
		catch (...) {
			file_namea = "";
			startlinea = -1;
			endlinea = -1;
			cout << "An unexspected error occurred probably due to an invalid file-path or invalid file. Please try again!" << endl;
		}
	}
}

void menu::start_menu() {
	bool ret = false;
	string answer = "-1";
	int answeri = stoi(answer);
	while (!ret) {
		cout << "------------------------------------------------------------" << endl;
		cout << "Main Menu -> What do you want to do?" << endl;
		cout << "[1] Sort data" << endl;
		cout << "[2] Search data" << endl;
		cout << "[3] Calculate average" << endl;
		cout << "[4] Print data" << endl;
		cout << "[5] Create a database from an existing one" << endl;
		cout << "[6] Switch database" << endl;
		cout << "[7] Close" << endl;
		cout << "User input:\t";
		cin >> answer;
		try {
			answeri = stoi(answer);
		}
		catch (...) {
			answeri = 0;
		}
		switch (answeri) {
		case 1:
			sort_data_menu();
			break;
		case 2:
			search_data_menu();
			break;
		case 3:
			calculate_average_menu();
			break;
		case 4:
			print_menu();
			break;
		case 5:
			create_database_menu();
			break;
		case 6: 
			switch_database_menu();
			break;
		case 7:
			ret = true;
			break;
		default:
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			break;
		}
	}
}

void menu::sort_data_menu() {
	bool ret = false;
	while (!ret) {
		cout << "--------------------------------------------------" << endl;
		cout << "[0] Abort" << endl;
		cout << "[1] Qualitaetsniveau der nachfolgenden Werte" << endl;
		cout << "[2] Tagesmittel der Temperatur in Grad Celsius" << endl;
		cout << "[3] Tagesmaximum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
		cout << "[4] Tagesminimum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
		cout << "[5] Minimum der Lufttemperatur am Erdboden in 5cm Hoehe in Grad Celsius" << endl;
		cout << "[6] Tagesmittel der Relativen Feuchte in Prozent" << endl;
		cout << "[7] taegliche Niederschlagshoehe in mm" << endl;
		cout << "[8] Niederschlagsform" << endl;
		cout << "[9] taegliche Sonnenscheindauer in h" << endl;
		cout << "[10] Tageswert Schneehoehe in cm" << endl;
		cout << "[11] Tagesmittel des Bedeckungsgrades 1/8" << endl;
		cout << "[12] Tagesmittel des Dampfdruckes hPa" << endl;
		cout << "[13] Tagesmittel des Luftdrucks hPa" << endl;
		cout << "[14] Qualitaetsniveau der nachfolgenden Spalten" << endl;
		cout << "[15] Tagesmaximum Windspitze m/s" << endl;
		cout << "[16] Tagesmittel Windgeschwindigkeit m/s" << endl;
		cout << "Please enter the column to sort by:\t" << endl;
		string user_input_columns = "-1";
		int user_input_column = -1;
		try {
			cin >> user_input_columns;
			user_input_column = stoi(user_input_columns);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (user_input_column == 0) {
			ret = true;
			continue;
		}		
		if (user_input_column < 0 || user_input_column > 16) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		bool rising = true;
		cout << "Should the data be sorted low values first[Y][default] or high values first[N] or press [X] to abort:\t" << endl;
		string user_input_rising;
		try {
			cin >> user_input_rising;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (user_input_rising == "X") {
			continue;
		}
		else if (user_input_rising == "N") {
			rising = false;
		}
		cout << "[0] Abort" << endl;
		cout << "[1] Selection Sort" << endl;
		cout << "[2] Insertion Sort" << endl;
		cout << "[3] Bubble Sort" << endl;
		cout << "[4] Quick Sort" << endl;
		cout << "Enter the sorting algorithm which should be used:\t" << endl;
		string user_input_algorithms = "-1";
		int user_input_algorithm = -1;
		try {
			cin >> user_input_algorithms;
			user_input_algorithm = stoi(user_input_algorithms);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (user_input_algorithm == 0)
			continue;
		else if (user_input_algorithm >= 5 || user_input_algorithm < 0) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if(user_input_algorithm != 4) {
			wdbs[active_db].sort_column(user_input_column, rising, user_input_algorithm);
		}
		else {
			float time1 = 0.0, tstart;
			tstart = clock();
			wdbs[active_db].quicksort_column(user_input_column, 0, wdbs[active_db].get_length() - 1, rising);
			time1 += clock() - tstart;
			time1 = time1 / CLOCKS_PER_SEC;
			cout << "time = " << time1 << " sec." << endl;
		}
		ret = true;
	}
}

void menu::print_menu() {
	bool ret = false;
	while (!ret) {
		cout << "--------------------------------------------------" << endl;
		cout << "Enter the number of datasets that should be printed ([-1] for all/[0] to abort):" << endl;
		string numbers = "-1";
		int number = -1;
		try {
			cin >> numbers;
			number = stoi(numbers);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (number == -1) {
			wdbs[active_db].print_db();
			ret = true;
		}
		else if (number == 0) {
			ret = true;
		}
		else if (number > 0 && number <= wdbs[active_db].get_length()) {
			wdbs[active_db].print_db(number - 1);
			ret = true;
		}
		else {
			cout << "The database does not have that many values." << endl;
		}
	}
}

void menu::calculate_average_menu() {
	wdbs[active_db].average_values().print_dataset();
}

void menu::search_data_menu() {
	bool ret = false;
	while (!ret) {
		cout << "--------------------------------------------------" << endl;
		cout << "[0] Abort" << endl;
		cout << "[1] Qualitaetsniveau der nachfolgenden Werte" << endl;
		cout << "[2] Tagesmittel der Temperatur in Grad Celsius" << endl;
		cout << "[3] Tagesmaximum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
		cout << "[4] Tagesminimum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
		cout << "[5] Minimum der Lufttemperatur am Erdboden in 5cm Hoehe in Grad Celsius" << endl;
		cout << "[6] Tagesmittel der Relativen Feuchte in Prozent" << endl;
		cout << "[7] taegliche Niederschlagshoehe in mm" << endl;
		cout << "[8] Niederschlagsform" << endl;
		cout << "[9] taegliche Sonnenscheindauer in h" << endl;
		cout << "[10] Tageswert Schneehoehe in cm" << endl;
		cout << "[11] Tagesmittel des Bedeckungsgrades 1/8" << endl;
		cout << "[12] Tagesmittel des Dampfdruckes hPa" << endl;
		cout << "[13] Tagesmittel des Luftdrucks hPa" << endl;
		cout << "[14] Qualitaetsniveau der nachfolgenden Spalten" << endl;
		cout << "[15] Tagesmaximum Windspitze m/s" << endl;
		cout << "[16] Tagesmittel Windgeschwindigkeit m/s" << endl;
		cout << "[17] Datum" << endl;
		cout << "Please enter the column to search:\t" << endl;
		string numbers = "-1";
		int number = -1;
		try {
			cin >> numbers;
			number = stoi(numbers);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (number == 0) {
			ret = true;
			continue;
		}
		else if (number < 0 || number > 17) {
			continue;
		}
		string values = "0.0";
		float value = 0.0;
		if (number != 17)
			cout << "Enter a reference value: " << endl;
		else
			cout << "Enter a reference date(YYYY-MM-DD): " << endl;
		try {
			cin >> values;
			value = stof(values);
			cout << "hä: " << values << " haha: " << value << endl;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}

		cout << "How should the reference value compare to the data to search?" << endl;
		cout << "[0] Abort" << endl;
		cout << "[1] Reference value equals data" << endl;
		cout << "[2] Reference value does not equal data" << endl;
		cout << "[3] Reference value is greater than or equal to data" << endl;
		cout << "[4] Reference value is less than or equal to data" << endl;
		cout << "[5] Reference value is greater than data" << endl;
		cout << "[6] Reference value is less than data" << endl;
		string operations = "-1";
		int operation = -1;
		try {
			cin >> operations;
			operation = stoi(operations);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (operation == 0) {
			ret = true;
			continue;
		}
		else if (operation < 0 || operation > 6) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		try {
			weather_database result;
			if (number != 17) {
				result = wdbs[active_db].search_column(number, value, operation);
			}
			else {
				replace(values.begin(), values.end(), '-', ' ');
				istringstream time_stream{ values };
				int year;
				time_stream >> year;
				int month;
				time_stream >> month;
				int day;
				time_stream >> day;
				result = wdbs[active_db].search_date(year, month, day, operation);
			}
			result.print_db();
			cout << "If you want to save the data in an XML-File please enter [Y]: " << endl;
			string answer;
			try {
				cin >> answer;
			}
			catch (...) {
				cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
				continue;
			}
			if (answer == "Y") {
				cout << "Enter the file-path: ";
				string path;
				try {
					cin >> path;
				}
				catch (...) {
					cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
					continue;
				}
				result.to_xml(path);
			}
			ret = true;
		}
		catch (error e) {
			e.print_error();
		}	
		catch (...) {
			cout << "Invalid file!" << endl;
		}
	}
}



void menu::create_database_menu() {
	bool operation_specified = false;
	int operation = -1;
	while (!operation_specified) {
		cout << "--------------------------------------------------" << endl;
		cout << "[0] Abort" << endl;
		cout << "[1] Search active database" << endl;
		cout << "[2] First n values of active database" << endl;
		if (additional_initialized) {
			cout << "[3] Union of two databases" << endl;
			cout << "[4] Intersection of two databases" << endl;
			cout << "[5] Difference of two databases" << endl;
		}
		cout << "Please enter the way the new database should be created:\t" << endl;
		string operations = "-1";
		try {
			cin >> operations;
			operation = stoi(operations);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (operation == 0) {
			break;
		}
		else if (operation < 0 || operation > 5) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
		}
		else if (operation > 2 && !additional_initialized) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
		}
		else {
			operation_specified = true;
		}
	}
	if (operation_specified) {
		switch (operation) {
		case 1:
		{
			bool column_specified = false;
			int column = -1;
			while (!column_specified) {
				cout << "----------------------------------------" << endl;
				cout << "[0] Abort" << endl;
				cout << "[1] Qualitaetsniveau der nachfolgenden Werte" << endl;
				cout << "[2] Tagesmittel der Temperatur in Grad Celsius" << endl;
				cout << "[3] Tagesmaximum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
				cout << "[4] Tagesminimum der Lufttemperatur in 2m Hoehe in Grad Celsius" << endl;
				cout << "[5] Minimum der Lufttemperatur am Erdboden in 5cm Hoehe in Grad Celsius" << endl;
				cout << "[6] Tagesmittel der Relativen Feuchte in Prozent" << endl;
				cout << "[7] taegliche Niederschlagshoehe in mm" << endl;
				cout << "[8] Niederschlagsform" << endl;
				cout << "[9] taegliche Sonnenscheindauer in h" << endl;
				cout << "[10] Tageswert Schneehoehe in cm" << endl;
				cout << "[11] Tagesmittel des Bedeckungsgrades 1/8" << endl;
				cout << "[12] Tagesmittel des Dampfdruckes hPa" << endl;
				cout << "[13] Tagesmittel des Luftdrucks hPa" << endl;
				cout << "[14] Qualitaetsniveau der nachfolgenden Spalten" << endl;
				cout << "[15] Tagesmaximum Windspitze m/s" << endl;
				cout << "[16] Tagesmittel Windgeschwindigkeit m/s" << endl;
				cout << "[17] Datum" << endl;
				cout << "Please enter the column to search:\t" << endl;
				string columns = "-1";
				try {
					cin >> columns;
					column = stoi(columns);
				}
				catch (...) {
					cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
					continue;
				}
				if (column == 0) {
					break;
				}
				else if (column < 0 || column > 17) {
					cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
					continue;
				}
				else {
					column_specified = true;
				}
			}
			bool value_specified = false;
			string values = "0.0";
			float value = 0.0;
			if (column_specified) {
				while (!value_specified) {
					if (column != 17)
						cout << "Enter a reference value or [X] to abort:\t" << endl;
					else
						cout << "Enter a reference date(YYYY-MM-DD) or [X] to abort:\t" << endl;
					try {
						cin >> values;
						if (values == "X")
							break;
						value = stof(values);
						value_specified = true;
					}
					catch (...) {
						cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
						continue;
					}
				}
			}
			bool cmp_operation_specified = false;
			string cmp_operations = "-1";
			int cmp_operation = -1;
			if (column_specified && value_specified) {
				while (!cmp_operation_specified) {
					cout << "How should the reference value compare to the data to search?" << endl;
					cout << "[0] Abort" << endl;
					cout << "[1] Reference value equals data" << endl;
					cout << "[2] Reference value does not equal data" << endl;
					cout << "[3] Reference value is greater than or equal to data" << endl;
					cout << "[4] Reference value is less than or equal to data" << endl;
					cout << "[5] Reference value is greater than data" << endl;
					cout << "[6] Reference value is less than data" << endl;
					try {
						cin >> cmp_operations;
						cmp_operation = stoi(cmp_operations);
					}
					catch (...) {
						cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
						continue;
					}
					if (operation == 0) {
						break;
					}
					else if (operation < 0 || operation > 6) {
						cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
						continue;
					}
					else {
						cmp_operation_specified = true;
					}
				}
			}
			if (column_specified && value_specified && cmp_operation_specified) {
				bool ret = false;
				while (!ret) {
					cout << "In which database-space should the new database be stored?" << endl;
					cout << "[X] Abort" << endl;
					for (int i = 1; i < 6; i++) {
						cout << "[" << to_string(i) << "] ";
						if (initialized[i])
							cout << "Database" << to_string(i) << endl;
						else
							cout << "Empty slot" << endl;
					}
					string slots = "";
					int slot = -1;
					try {
						cin >> slots;
						if (slots == "X")
							break;
						slot = stoi(slots);
					}
					catch (...) {
						cout << "Invalid Input. Please try again!" << endl;
						continue;
					}
					int year = 0;
					int month = 0;
					int day = 0;
					if (column == 17) {
						replace(values.begin(), values.end(), '-', ' ');
						istringstream time_stream{ values };
						time_stream >> year;
						time_stream >> month;
						time_stream >> day;
					}					
					if (slot >= 1 && slot <= 5) {
						if (column != 17 && wdbs[active_db].search_column(column, value, cmp_operation).get_length() > 0) {
							wdbs[slot] = wdbs[active_db].search_column(column, value, cmp_operation);
							additional_initialized = true;
							initialized[slot] = true;
						}
						else if (column == 17 && wdbs[active_db].search_date(year, month, day, cmp_operation).get_length() > 0) {
							wdbs[slot] = wdbs[active_db].search_date(year, month, day, cmp_operation);
							additional_initialized = true;
							initialized[slot] = true;
							cout << "Die Länge ist: " << wdbs[slot].get_length() << endl;
						}
						else {
							cout << "The created database is empty. Returning to main menu." << endl;
						}						
						ret = true;
					}
					else {
						cout << "Invalid Input!" << endl;
						continue;
					}
				}
			}
			break;
		}
		case 2:
		{
			bool ret = false;
			while (!ret) {
				cout << "Enter the number of elements that should be added or [X] to abort:\t";
				string numbers = "";
				int number = -1;
				try {
					cin >> numbers;
					if (numbers == "X") {
						break;
					}
					number = stoi(numbers);
				}
				catch (...) {
					cout << "Invalid Input!" << endl;
					continue;
				}
				if (number > 0 && number <= wdbs[active_db].get_length()) {
					weather_database dbr{};
					wdbs[active_db].to_first();
					for (int i = 0; i < number; i++) {
						dbr.add(wdbs[active_db].get_current_dataset(), dbr.get_length());
						if (i < number - 1)
							wdbs[active_db].to_next();
					}
					bool ret2 = false;
					while (!ret2) {
						cout << "In which database-space should the new database be stored?" << endl;
						cout << "[X] Abort" << endl;
						for (int i = 1; i < 6; i++) {
							cout << "[" << to_string(i) << "] ";
							if (initialized[i])
								cout << "Database" << to_string(i) << endl;
							else
								cout << "Empty slot" << endl;
						}
						string slots = "";
						int slot = -1;
						try {
							cin >> slots;
							if (slots == "X")
								break;
							slot = stoi(slots);
						}
						catch (...) {
							cout << "Invalid Input. Please try again!" << endl;
							continue;
						}
						if (slot >= 1 && slot <= 5) {
							wdbs[slot] = dbr;
							additional_initialized = true;
							initialized[slot] = true;
							ret2 = true;
						}
						else {
							cout << "Invalid Input!" << endl;
							continue;
						}
					}
					ret = true;
				}
				else {
					cout << "The number of elements does not exist." << endl;
				}
			}
			break;
		}
		case 3:
		case 4:
		case 5:
		{
			cout << "With which database should the union be formed?" << endl;
			cout << "[X] Abort" << endl;
			for (int i = 0; i < 6; i++) {
				if (i == active_db) {
					cout << "[-] Database" << to_string(i) << " (active database)" << endl;
					continue;
				}
				cout << "[" << to_string(i) << "] ";
				if (initialized[i])
					cout << "Database" << to_string(i) << endl;
				else
					cout << "Empty slot" << endl;
			}
			bool ret = false;
			while (!ret) {
				cout << "Please enter the slot-number of the database:\t" << endl;
				string slots = "";
				int slot = -1;
				try {
					cin >> slots;
					if (slots == "X") {
						break;
					}
					slot = stoi(slots);
				}
				catch (...) {
					cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
					continue;
				}
				if (slot == active_db) {
					cout << "The database is the active one. Operation not permitted. Returning to main menu." << endl;
					ret = true;
				}
				else if (slot >= 0 && slot <= 5 && initialized[slot]) {
					weather_database wdbret{};
					switch (operation)
					{
					case 3:
						wdbret = wdbs[active_db].union_db(wdbs[slot]);
						break;
					case 4:
						wdbret = wdbs[active_db].intersection(wdbs[slot]);
						break;
					case 5:
						wdbret = wdbs[active_db].difference_db(wdbs[slot]);
						break;
					}
					if (wdbret.get_length() > 0) {
						bool ret2 = false;
						while (!ret2) {
							cout << "In which database-space should the new database be stored?" << endl;
							cout << "[X] Abort" << endl;
							for (int i = 1; i < 6; i++) {
								cout << "[" << to_string(i) << "] ";
								if (initialized[i])
									cout << "Database" << to_string(i) << endl;
								else
									cout << "Empty slot" << endl;
							}
							string slots = "";
							int slot = -1;
							try {
								cin >> slots;
								if (slots == "X")
									break;
								slot = stoi(slots);
							}
							catch (...) {
								cout << "Invalid Input. Please try again!" << endl;
								continue;
							}
							if (slot >= 1 && slot <= 5) {
								wdbs[slot] = wdbret;
								additional_initialized = true;
								initialized[slot] = true;
								ret2 = true;
							}
							else {
								cout << "Invalid Input!" << endl;
								continue;
							}
						}
					}
					else {
						cout << "The database created is empty. Returning to the main menu." << endl;
					}
					ret = true;
				}
				else if (slot >= 0 && slot <= 5 && !initialized[slot]) {
					cout << "There is no database in the specified slot. Please enter the number of a slot that contains a database!" << endl;
				}
				else {
					cout << "The slot number " << to_string(slot) << " does not exist. Please enter a valid slot number[0-5]." << endl;
				}
			}
		}
		}
	}
}

void menu::switch_database_menu() {
	cout << "--------------------------------------------------" << endl;
	cout << "[X] Abort" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "[" << to_string(i) << "] ";
		if (i == active_db)
			cout << "Database" << to_string(i) << " (active database)" << endl;
		else if (initialized[i])
			cout << "Database" << to_string(i) << endl;
		else
			cout << "Empty slot" << endl;
	}
	bool ret = false;
	while (!ret) {
		cout << "Please enter the slot-number of the database that should be switched to:\t" << endl;
		string slots = "";
		int slot = -1;
		try {
			cin >> slots;
			if (slots == "X") {
				break;
			}
			slot = stoi(slots);
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (slot == active_db) {
			cout << "The database is already the active one. Returning to the main menu." << endl;
			ret = true;
		}
		else if (slot >= 0 && slot <= 5 && initialized[slot]) {
			active_db = slot;
			ret = true;
		}
		else if(slot >= 0 && slot <= 5 && !initialized[slot]) {
			cout << "There is no database in the specified slot. Please enter the number of a slot that contains a database!" << endl;
		}
		else {
			cout << "The slot number " << to_string(slot) << " does not exist. Please enter a valid slot number[0-5]." << endl;
		}
	}
}

//C:/Users/lohei/Desktop/Informatik-Projekt/Historische_Wetterdaten_taeglich.csv
int main(int argc, const char* argv[]) {
	menu mmenu{};
	switch (argc) {
	case 1:
		if (mmenu.file_menu())
			mmenu.start_menu();
		break;
	case 2:
		if (mmenu.file_menu(string(argv[1])))
			mmenu.start_menu();
		break;
	case 3:
		if (mmenu.file_menu(string(argv[1]), atoi(argv[2])))
			mmenu.start_menu();
		break;
	case 4:
		string dates1 = string(argv[2]);
		string dates2 = string(argv[3]);
		cout << "Date1: " << dates1 << endl;
		cout << "Date2: " << dates2 << endl;
		replace(dates1.begin(), dates1.end(), '-', ' ');
		istringstream time_stream1{ dates1 };
		int year1 = 0;
		time_stream1 >> year1;
		int month1 = 0;
		time_stream1 >> month1;
		int day1 = 0;
		time_stream1 >> day1;
		replace(dates2.begin(), dates2.end(), '-', ' ');
		istringstream time_stream2{ dates2 };
		int year2 = 0;
		time_stream2 >> year2;
		int month2 = 0;
		time_stream2 >> month2;
		int day2 = 0;
		time_stream2 >> day2;
		try {
			date date1 = date(year1, month1, day1), date2 = date(year2, month2, day2);
			int year = 1972, month = 11, day = 1;
			if (year1 < year || year2 < year || year2 < year1) {
				throw error();
			}
			else if ((year1 == year && month1 < month) || (year2 == year && month2 < month) || (year1 == year2 && month2 < month1)) {
				throw error();
			}
			else if (year1 == year2 && month2 == month1 && day2 < day1) {
				throw error();
			}
			else {
				int difference1 = 1;
				int difference2 = 1;
				bool update1 = true;
				while ((year2 > year) || (year2 == year && month2 > month) || (year2 == year && month2 == month && day2 > day)) {
					if (update1 && !((year1 > year) || (year1 == year && month1 > month) || (year1 == year && month1 == month && day1 > day)))
						update1 = false;
					if (day < 28) {
						day++;
						if (update1)
							difference1++;
						difference2++;
					}
					else if (day < 30 && month != 2) {
						day++;
						if (update1)
							difference1++;
						difference2++;
					}
					else if (day < 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
						day++;
						if (update1)
							difference1++;
						difference2++;
					}
					else if (day < 29 && month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
						day++;
						if (update1)
							difference1++;
						difference2++;
					}
					else if (month < 12) {
						day = 1;
						month++;
						if (update1)
							difference1++;
						difference2++;
					}
					else {
						day = 1;
						month = 1;
						year++;
						if (update1)
							difference1++;
						difference2++;
					}
				}
				cout << "Difference1: " << difference1 << endl;
				cout << "Difference2: " << difference2 << endl;
				if (mmenu.file_menu(string(argv[1]), difference2, difference1)) {
					mmenu.start_menu();
				}
			}
		}
		catch (...) {
			if (mmenu.file_menu())
				mmenu.start_menu();
		}
		break;
	}
}