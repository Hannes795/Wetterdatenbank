#pragma once
#include "database.h"
#include "weather_dataset.h"
#include <string>

using namespace std;

class weather_database : public database<weather_dataset>
{
public:
	void read_file(string file);
	void print_db();
	void print_db(int index);
	bool operate(int operation_id, int value_1, int value_2);
	bool operate(int operation_id, float value_1, float value_2);
	bool operate(int operation_id, int year, int month, int day, date d);
	void sort_column(int column, bool rising=true, int algorithm=1);
	void quicksort_column(int column, int startindex, int endindex, bool rising = true);
	weather_database search_column(int column, int value, int operation_id);
	weather_database search_column(int column, float value, int operation_id);
	weather_database search_date(int year, int month, int day, int operation_id);
	weather_database intersection(weather_database wdb);
	weather_database union_db(weather_database wdb);
	weather_database difference_db(weather_database wdb);
	weather_dataset average_values();
};

