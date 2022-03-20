#include "error.h"
#include "database.h"
#include "weather_dataset.h"
#include "weather_database.h"
#include <vector>

class menu {
private:
	weather_database wdb{};
public:
	bool file_menu(string file_namem = "", int lines=-1);
	void start_menu();
	void sort_data_menu();
	void search_data_menu();
	void calculate_average_menu();
	void print_menu();
};

bool menu::file_menu(string file_namem, int lines) {
	bool ret = false;
	while (!ret) {
		if (file_namem == "") 
		{
			cout << "--------------------------------------------------" << endl;
			cout << "Please enter the name of the file, which should be processed, or [X] to abort.\nThe file should contain weather data in a specific format.\nIf you do not know which format, please contact our customer service ;-),\nwhich is available Monday-Friday from 24:00-25:00. " << endl;
		}
		try {
			string file_name;
			if (file_namem == "")
				cin >> file_name;
			else
				file_name = file_namem;
			wdb.read_file(file_name, lines);
			if (file_name == "X") {
				return false;
			}
			if (wdb.get_length() > 0) {
				return true;
			}
			else
			{
				cout << "An error occurred while reading the database. The database is empty. Please try again with a valid file." << endl;
			}
		}
		catch (error e) {
			e.print_error();
		}
		catch (...) {
			cout << "An unexspected error occurred probably due to an invalid file-path or invalid file. Please try again!" << endl;
		}
	}
}

void menu::start_menu() {
	bool ret = false;
	while (!ret) {
		cout << "------------------------------------------------------------" << endl;
		cout << "Main Menu -> What do you want to do?" << endl;
		cout << "[1] Sort data" << endl;
		cout << "[2] Search data" << endl;
		cout << "[3] Calculate average" << endl;
		cout << "[4] Print data" << endl;
		cout << "[0] Close" << endl;
		cout << "User input:\t";
		int answer = -1;
		try {
			cin >> answer;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		switch (answer) {
		case 0:
			ret = true;
			break;
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
		int user_input_column = -1;
		try {
			cin >> user_input_column;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (user_input_column == 0) {
			ret = true;
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
		int user_input_algorithm = -1;
		try {
			cin >> user_input_algorithm;
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
		if (user_input_column > 16 || user_input_column < 0) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
		}
		else if(user_input_algorithm != 4) {
			wdb.sort_column(user_input_column, rising, user_input_algorithm);
		}
		else {
			wdb.quicksort_column(user_input_column, 0, wdb.get_length() - 1, rising);
		}
		ret = true;
	}
}

void menu::print_menu() {
	bool ret = false;
	while (!ret) {
		cout << "--------------------------------------------------" << endl;
		cout << "Enter the number of datasets that should be printed ([-1] for all/[0] to abort):" << endl;
		int number = -1;
		try {
			cin >> number;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (number == -1) {
			wdb.print_db();
			ret = true;
		}
		else if (number == 0) {
			ret = true;
		}
		else if (number > 0 && number <= wdb.get_length()) {
			wdb.print_db(number - 1);
			ret = true;
		}
		else {
			cout << "The database does not have that many values." << endl;
		}
	}
}

void menu::calculate_average_menu() {
	wdb.average_values().print_dataset();
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
		cout << "Please enter the column to search:\t" << endl;
		int number = -1;
		try {
			cin >> number;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (number == 0) {
			ret = true;
			continue;
		}
		else if (number < 0 || number > 16) {
			continue;
		}
		float value = 0.0;
		cout << "Enter a reference value: " << endl;
		try {
			cin >> value;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		cout << "How should the reference value compare to the data to search?" << endl;
		cout << "[0] Abort" << endl;
		cout << "[1] Reference value equals data" << endl;
		cout << "[1] Reference value does not equal data" << endl;
		cout << "[1] Reference value is greater than or equal to data" << endl;
		cout << "[1] Reference value is less than or equal to data" << endl;
		cout << "[1] Reference value is greater than data" << endl;
		cout << "[1] Reference value is less than data" << endl;
		int operation = 0;
		try {
			cin >> operation;
		}
		catch (...) {
			cout << "Invalid user-input. Please try again to enter a valid input!" << endl;
			continue;
		}
		if (operation == 0) {
			ret = true;
			continue;
		}
		else if (operation < 0 || operation > 16) {
			continue;
		}
		weather_database result = wdb.search_column(number, value, operation);
		result.print_db();
		ret = true;
	}
}

//C:/Users/lohei/Desktop/Informatik-Projekt/Historische_Wetterdaten_taeglich.csv




int main(int argc, const char* argv[]) {
	menu mmenu{};
	switch (argc) {
	case 1:
		if(mmenu.file_menu())
			mmenu.start_menu();
		break;
	case 2:
		if(mmenu.file_menu(string(argv[1])))
			mmenu.start_menu();
		break;
	case 3:
		if(mmenu.file_menu(string(argv[1]), atoi(argv[2])))
			mmenu.start_menu();
		break;
	}
}