#include "database.h"
#include "weather_database.h"

int main() {
	weather_database dbw;
	dbw.read_file("C:/Users/lohei/Desktop/Historische Wetterdaten_täglich.csv");
	float temperature = -10.0;
	int val = 15;
	try {
		weather_database dbwa = dbw.search_column(14, 30, 6);
		dbwa.print_db(5);
	}
	catch (db_error e) {
		cout << e.id << endl;
		cout << e.error_position << endl;
		cout << e.error_type << endl;
		cout << e.error_string << endl;
	}
}