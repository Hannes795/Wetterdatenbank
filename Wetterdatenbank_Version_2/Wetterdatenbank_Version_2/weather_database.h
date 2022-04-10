#pragma once
#include "database.h"
#include "weather_dataset.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class weather_database : public database<weather_dataset>
{
public:
	// reads the given csv-file in a specific format until the line number "lines" is reached
	void read_file(string file, int endline=-1, int startline=-1);
	// prints the entire database to the console
	void print_db();
	// prints the first index + 1 elements of the database to the console
	void print_db(int index);
	// used to compare two float values
	bool operate(int operation_id, float value_1, float value_2);
	// used to compare two dates
	bool operate(int operation_id, int year, int month, int day, date d);
	// sorts the giving column
	// sorting algorithms:
	// 1 - Selection Sort
	// 2 - Insertion Sort
	// 3 - Bubble Sort -> WARNING!!!: Very slow
	void sort_column(int column, bool rising = true, int algorithm = 1);
	// uses the	quicksort algorithm to sort the database -> WARNING!!!: Stack-overflow
	void quicksort_column(int column, int startindex, int endindex, bool rising = true);
	// Search the entire database
	weather_database search_column(int column, float value, int operation_id);
	// Search for a date
	weather_database search_date(int year, int month, int day, int operation_id);
	// Set-operators
	weather_database intersection(weather_database wdb);
	weather_database union_db(weather_database wdb);
	weather_database difference_db(weather_database wdb);
	// Calculate the average of the entire db
	weather_dataset average_values();
	// Save the database as a XML-file
	void to_xml(string file);
};