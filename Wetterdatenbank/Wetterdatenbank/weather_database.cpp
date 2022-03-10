#include "weather_database.h"

void weather_database::read_file(string file) {
	ifstream wetterdatencsv{ file };
	if (!wetterdatencsv) {
		cout << "Dateifehler" << endl;
	}

	int zeilennummer = 0;

	while (wetterdatencsv) {
		string zeile;
		getline(wetterdatencsv, zeile);
		if (!wetterdatencsv)
			break;
		if (zeilennummer == 0)
		{
			zeilennummer++;
			continue;
		}
		//if (zeilennummer == 6)
		//	break;
		weather_dataset w = weather_dataset(zeile);
		add(w, length);
		zeilennummer++;
	}
}

void weather_database::print_db() {
	if (length > 0) {
		datatuple<weather_dataset>* dt_c = first;
		dt_c->data.print_dataset();
		for (int i = 0; i < length - 1; i++) {
			dt_c = dt_c->next;
			dt_c->data.print_dataset();
		}
	}
	else {
		db_error zero_length_error;
		zero_length_error.id = 2;
		zero_length_error.error_type = "ZeroLengthError";
		zero_length_error.error_position = "weather_database::print_wdb";
		zero_length_error.error_string = "The database has a length of 0. Add an element.";
		throw zero_length_error;
	}
}

void weather_database::print_db(int index) {
	if (index >= 0 && index < length) {
		if (length > 0) {
			datatuple<weather_dataset>* dt_c = first;
			dt_c->data.print_dataset();
			for (int i = 0; i < index; i++) {
				dt_c = dt_c->next;
				dt_c->data.print_dataset();
			}
		}
		else {
			db_error zero_length_error;
			zero_length_error.id = 2;
			zero_length_error.error_type = "ZeroLengthError";
			zero_length_error.error_position = "weather_database::print_wdb";
			zero_length_error.error_string = "The database has a length of 0. Add an element.";
			throw zero_length_error;
		}
	}
	else {
		db_error index_error;
		index_error.id = 0;
		index_error.error_type = "IndexOutOfBoundsError";
		index_error.error_position = "weather_database::print_wdb(int)";
		string part_1 = "The given index(";
		string part_2 = to_string(index);
		string part_3 = ") is not valid. A valid index is in the range between 0 and the current database length(";
		string part_4 = to_string(length);
		string part_5 = ").";
		index_error.error_string = part_1 + part_2 + part_3 + part_4 + part_5;
		throw index_error;
	}
	
}


bool weather_database::operate(int operation_id, int value_1, int value_2) {
	switch (operation_id) {
	case 1:
		return value_1 == value_2;
		break;
	case 2:
		return value_1 != value_2;
		break;
	case 3:
		return value_1 >= value_2;
		break;
	case 4:
		return value_1 <= value_2;
		break;
	case 5:
		return value_1 > value_2;
		break;
	case 6:
		return value_1 < value_2;
		break;
	default:
		db_error invalid_operation_id_error;
		invalid_operation_id_error.id = 5;
		invalid_operation_id_error.error_position = "weather_database::operate(int, int, int)";
		invalid_operation_id_error.error_type = "InvalidOperationId";
		string part1 = "The operation ID is invalid(";
		string part2 = to_string(operation_id);
		string part3 = "). The operation ID has to be in the range between 1 and 6.";
		invalid_operation_id_error.error_string = part1 + part2 + part3;
		throw invalid_operation_id_error;
		break;
	}
}

bool weather_database::operate(int operation_id, float value_1, float value_2) {
	switch (operation_id) {
	case 1:
		return value_1 == value_2;
		break;
	case 2:
		return value_1 != value_2;
		break;
	case 3:
		return value_1 >= value_2;
		break;
	case 4:
		return value_1 <= value_2;
		break;
	case 5:
		return value_1 > value_2;
		break;
	case 6:
		return value_1 < value_2;
		break;
	default:
		db_error invalid_operation_id_error;
		invalid_operation_id_error.id = 5;
		invalid_operation_id_error.error_position = "weather_database::operate(float, float, float)";
		invalid_operation_id_error.error_type = "InvalidOperationId";
		string part1 = "The operation ID is invalid(";
		string part2 = to_string(operation_id);
		string part3 = "). The operation ID has to be in the range between 1 and 6.";
		invalid_operation_id_error.error_string = part1 + part2 + part3;
		throw invalid_operation_id_error;
		break;
	}
}

bool weather_database::operate(int operation_id, int year, int month, int day, date d) {
	switch (operation_id) {
	case 1:
		if (year == d.year || year == 0) {
			if (month == d.month || month == 0) {
				if (day == d.day || day == 0) {
					return true;
				}
			}
		}
		return false;
		break;
	case 2:
		if (year == d.year || year == 0) {
			if (month == d.month || month == 0) {
				if (day == d.day || day == 0) {
					if (year != 0 || month != 0 || day != 0) {
						return false;
					}
				}
			}
		}
		return true;
		break;
	case 3:
		if (year > d.year) {
			return true;
		}
		else if (year == d.year || year == 0) {
			if(month > d.month) {
				return true;
			}
			else if (month == d.month || month == 0) {
				if (day > d.day) {
					return true;
				}
				else if (day == d.day || day == 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	case 4:
		if (year < d.year) {
			return true;
		}
		else if (year == d.year || year == 0) {
			if (month < d.month) {
				return true;
			}
			else if (month == d.month || month == 0) {
				if (day < d.day) {
					return true;
				}
				else if (day == d.day || day == 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	case 5:
		if (year > d.year) {
			return true;
		}
		else if (year == 0) {
			if (month > d.month) {
				return true;
			}
			else if (month == 0) {
				if (day > d.day) {
					return true;
				}
				else if (day == 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	case 6:
		if (year < d.year) {
			return true;
		}
		else if (year == 0) {
			if (month < d.month) {
				return true;
			}
			else if (month == 0) {
				if (day < d.day) {
					return true;
				}
				else if (day == 0) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	default:
		db_error invalid_operation_id_error;
		invalid_operation_id_error.id = 5;
		invalid_operation_id_error.error_position = "weather_database::operate(float, float, float)";
		invalid_operation_id_error.error_type = "InvalidOperationId";
		string part1 = "The operation ID is invalid(";
		string part2 = to_string(operation_id);
		string part3 = "). The operation ID has to be in the range between 1 and 6.";
		invalid_operation_id_error.error_string = part1 + part2 + part3;
		throw invalid_operation_id_error;
		break;
	}
}

weather_database weather_database::search_column(int column, int value, int operation_id) {
	weather_database wdb;
	datatuple<weather_dataset>* dt = first;
	for (int i = 0; i < length - 1; i++) {
		if (operate(operation_id, value, dt->data.get_int_column(column))) {
			wdb.add(dt->data, wdb.get_length());
		}
		dt = dt->next;
	}
	if (operate(operation_id, value, dt->data.get_int_column(column))) {
		wdb.add(dt->data, wdb.get_length());
	}
	return wdb;
}

weather_database weather_database::search_column(int column, float value, int operation_id) {
	weather_database wdb;
	datatuple<weather_dataset>* dt = first;
	for (int i = 0; i < length - 1; i++) {
		if (operate(operation_id, value, dt->data.get_float_column(column))) {
			wdb.add(dt->data, wdb.get_length());
		}
		dt = dt->next;
	}
	if (operate(operation_id, value, dt->data.get_float_column(column))) {
		wdb.add(dt->data, wdb.get_length());
	}
	return wdb;
}

weather_database weather_database::search_date(int year, int month, int day, int operation_id) {
	weather_database wdb;
	datatuple<weather_dataset>* dt = first;
	for (int i = 0; i < length - 1; i++) {
		if (operate(operation_id, year, month, day, dt->data.get_measurement_date())) {
			wdb.add(dt->data, wdb.get_length());
		}
		dt = dt->next;
	}
	if (operate(operation_id, year, month, day, dt->data.get_measurement_date())) {
		wdb.add(dt->data, wdb.get_length());
	}
	return wdb;
}

void weather_database::sort_column(int column, bool rising, int algorithm) {
	datatuple<weather_dataset>* dt = first;
	switch (algorithm) {
	case 1: //Selection Sort
		switch (column) {
		case 1:
		case 6:
		case 8:
		case 10:
		case 14:
			for (int j = 0; j < length - 1; j++) {
				for (int k = 0; k < j; k++) {
					dt = dt->next;
				}
				int min = dt->data.get_int_column(column);
				int min_index = j;
				for (int i = j; i < length - 1; i++) {
					if ((dt->data.get_int_column(column) < min && rising) || (dt->data.get_int_column(column) > min && !rising)) {
						min_index = i;
						min = dt->data.get_int_column(column);
					}
					dt = dt->next;
				}
				if ((dt->data.get_int_column(column) < min && rising) || (dt->data.get_int_column(column) > min && !rising)) {
					min_index = length - 1;
					min = dt->data.get_int_column(column);
				}
				move(min_index, j);
				dt = first;
			}
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 7:
		case 9:
		case 11:
		case 12:
		case 13:
		case 15:
		case 16:
			for (int j = 0; j < length - 1; j++) {
				int min_index = j;
				for (int k = 0; k < j; k++) {
					dt = dt->next;
				}
				float min = dt->data.get_float_column(column);
				for (int i = j; i < length - 1; i++) {
					if ((dt->data.get_float_column(column) < min && rising) || (dt->data.get_float_column(column) > min && !rising)) {
						min_index = i;
						min = dt->data.get_float_column(column);
					}
					dt = dt->next;
				}
				if ((dt->data.get_float_column(column) < min && rising) || (dt->data.get_float_column(column) > min && !rising)) {
					min_index = length - 1;
					min = dt->data.get_float_column(column);
				}
				move(min_index, j);
				dt = first;
			}
			break;
		default:
			break;
		}
		break;
	case 2://Insertion Sort
		switch (column) {
		case 1:
		case 6:
		case 8:
		case 10:
		case 14:
			for (int j = 0; j < length; j++) {
				for (int k = 0; k < j; k++) {
					dt = dt->next;
				}
				int element = dt->data.get_int_column(column);
				int tauschindex = j;
				for (int i = j; i > 0; i--) {
					dt = dt->previous;
					if ((dt->data.get_int_column(column) > element && rising) || (dt->data.get_int_column(column) < element && !rising)) {
						tauschindex = i - 1;
					}
					else {
						break;
					}
				}
				move(j, tauschindex);
				dt = first;
			}
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 7:
		case 9:
		case 11:
		case 12:
		case 13:
		case 15:
		case 16:
			for (int j = 0; j < length; j++) {
				for (int k = 0; k < j; k++) {
					dt = dt->next;
				}
				float element = dt->data.get_float_column(column);
				int tauschindex = j;
				for (int i = j; i > 0; i--) {
					dt = dt->previous;
					if ((dt->data.get_float_column(column) > element && rising) || (dt->data.get_float_column(column) < element && !rising)) {
						tauschindex = i-1;
					}
					else {
						break;
					}
				}
				move(j, tauschindex);
				dt = first;
			}
			break;
		default:
			break;
		}
		break;
	case 3: //Bubble Sort
		bool vertauscht = true;
		switch (column) {
		case 1:
		case 6:
		case 8:
		case 10:
		case 14:
			vertauscht = true;
			while (vertauscht) {
				vertauscht = false;
				for (int j = 0; j < length-1; j++) {
					if ((dt->data.get_int_column(column) > dt->next->data.get_int_column(column) && rising) || (dt->data.get_int_column(column) < dt->next->data.get_int_column(column) && !rising)) {
						move(j, j + 1);
						vertauscht = true;
					}
					dt = dt->next;
				}
				dt = first;
			}
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 7:
		case 9:
		case 11:
		case 12:
		case 13:
		case 15:
		case 16:
			vertauscht = true;
			while (vertauscht) {
				vertauscht = false;
				for (int j = 0; j < length - 1; j++) {
					if ((dt->data.get_float_column(column) > dt->next->data.get_float_column(column) && rising) || (dt->data.get_float_column(column) < dt->next->data.get_float_column(column) && !rising)) {
						move(j, j + 1);
						vertauscht = true;
					}
					else {
						dt = dt->next;
					}
				}
				dt = first;
			}
			break;
		default:
			break;
		}
		break;
	}
}

void weather_database::quicksort_column(int column, int startindex, int endindex, bool rising) {
	if (startindex == endindex) {
		return;
	}
	to_index(endindex);
	datatuple<weather_dataset>* dt_pivot = current;
	datatuple<weather_dataset>* dt_ch = current;

	to_index(startindex);
	datatuple<weather_dataset>* dt_low = current;
	datatuple<weather_dataset>* dt_high = dt_pivot->previous;
	int ind_low = startindex;
	int ind_high = endindex - 1;
	switch (column) {
	case 1:
	case 6:
	case 8:
	case 10:
	case 14:
		if (startindex == endindex - 1) {
			if (dt_low->data.get_int_column(column) > dt_pivot->data.get_int_column(column)) {
				move(endindex, startindex);
			}
			return;
		}
		while (ind_high > ind_low && ind_low < endindex && ind_high > startindex) {
			if (dt_low->data.get_int_column(column) > dt_pivot->data.get_int_column(column) && dt_high->data.get_int_column(column) <= dt_pivot->data.get_int_column(column)) {
				move(ind_high, ind_low);
				move(ind_low + 1, ind_high);
				dt_ch = dt_high;
				dt_high = dt_low;
				dt_low = dt_ch;
			}
			while (dt_low->data.get_int_column(column) <= dt_pivot->data.get_int_column(column) && ind_low < endindex) {
				dt_low = dt_low->next;
				ind_low++;
			}
			while (dt_high->data.get_int_column(column) > dt_pivot->data.get_int_column(column) && ind_high > startindex) {
				dt_high = dt_high->previous;
				ind_high--;
			}
		}
		if (ind_low < endindex) {
			move(endindex, ind_low);
			move(ind_low + 1, endindex);
			if (ind_low - 1 >= startindex)
				quicksort_column(column, startindex, ind_low - 1, rising);
			quicksort_column(column, ind_low + 1, endindex, rising);
		}
		else {
			quicksort_column(column, startindex, ind_low - 1, rising);
		}
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 7:
	case 9:
	case 11:
	case 12:
	case 13:
	case 15:
	case 16:
		if (startindex == endindex - 1) {
			if (dt_low->data.get_float_column(column) > dt_pivot->data.get_float_column(column)) {
				move(endindex, startindex);
			}
			return;
		}
		while (ind_high > ind_low && ind_low < endindex && ind_high > startindex) {
			if (dt_low->data.get_float_column(column) > dt_pivot->data.get_float_column(column) && dt_high->data.get_float_column(column) <= dt_pivot->data.get_float_column(column)) {
				move(ind_high, ind_low);
				move(ind_low + 1, ind_high);
				dt_ch = dt_high;
				dt_high = dt_low;
				dt_low = dt_ch;
			}
			while (dt_low->data.get_float_column(column) <= dt_pivot->data.get_float_column(column) && ind_low < endindex) {
				dt_low = dt_low->next;
				ind_low++;
			}
			while (dt_high->data.get_float_column(column) > dt_pivot->data.get_float_column(column) && ind_high > startindex) {
				dt_high = dt_high->previous;
				ind_high--;
			}
		}
		if (ind_low < endindex) {
			move(endindex, ind_low);
			move(ind_low + 1, endindex);
			if(ind_low - 1 >= startindex)
				quicksort_column(column, startindex, ind_low - 1, rising);
			quicksort_column(column, ind_low + 1, endindex, rising);
		}
		else {
			quicksort_column(column, startindex, ind_low - 1, rising);
		}
		break;
	default:
		break;
	}
}

weather_database weather_database::intersection(weather_database wdb) {
	datatuple<weather_dataset>* dt = first;
	weather_database wdb_ret;
	for (int i = 0; i < length; i++) {
		wdb.to_first();
		int year = dt->data.get_measurement_date().year;
		int month = dt->data.get_measurement_date().month;
		int day = dt->data.get_measurement_date().day;
		for (int j = 0; j < wdb.get_length(); j++) {
			if (operate(1, year, month, day, wdb.get_current_dataset().get_measurement_date())) {
				wdb_ret.add(wdb.get_current_dataset(), wdb_ret.get_length());
			}
			if(j != wdb.get_length()-1)
				wdb.to_next();
		}
		if(i != length - 1)
			dt = dt->next;	
	}
	return wdb_ret;
}

weather_database weather_database::union_db(weather_database wdb) {
	datatuple<weather_dataset>* dt = first;
	weather_database wdb_ret;
	for (int i = 0; i < length; i++) {
		wdb_ret.add(dt->data, wdb_ret.get_length());
		if (i != length - 1)
			dt = dt->next;
	}
	wdb.to_first();
	for (int i = 0; i < wdb.get_length(); i++) {
		int year = wdb.get_current_dataset().get_measurement_date().year;
		int month = wdb.get_current_dataset().get_measurement_date().month;
		int day = wdb.get_current_dataset().get_measurement_date().day;
		bool add_ds = true;
		wdb_ret.to_first();
		for (int j = 0; j < wdb_ret.get_length(); j++) {
			if (operate(1, year, month, day, wdb_ret.get_current_dataset().get_measurement_date())) {
				add_ds = false;
				break;
			}
			if (j != wdb_ret.get_length() - 1)
				wdb_ret.to_next();
		}
		if (add_ds)
			wdb_ret.add(wdb.get_current_dataset(), wdb_ret.get_length());
		if (i != wdb.get_length() - 1)
			wdb.to_next();
	}
	return wdb_ret;
}

weather_database weather_database::difference_db(weather_database wdb) {
	datatuple<weather_dataset>* dt = first;
	weather_database wdb_ret;
	for (int i = 0; i < length; i++) {
		int year = dt->data.get_measurement_date().year;
		int month = dt->data.get_measurement_date().month;
		int day = dt->data.get_measurement_date().day;
		bool add_ds = true;
		wdb.to_first();
		for (int j = 0; j < wdb.get_length(); j++) {
			if (operate(1, year, month, day, wdb.get_current_dataset().get_measurement_date())) {
				add_ds = false;
				break;
			}
			if (j != wdb.get_length() - 1)
				wdb.to_next();
		}
		if (add_ds)
			wdb_ret.add(dt->data, wdb_ret.get_length());
		if (i != length - 1)
			dt = dt->next;
	}
	return wdb_ret;
}

weather_dataset weather_database::average_values() {
	weather_dataset ret = weather_dataset();
	to_first();
	float qn4 = 0.0;
	float qn3 = 0.0;
	float upm = 0.0;
	float shk_tag = 0.0;
	for (int i = 0; i < length; i++) {
		ret += get_current_dataset();
		qn4 += get_current_dataset().get_qn4();
		qn3 += get_current_dataset().get_qn3();
		upm += get_current_dataset().get_upm();
		shk_tag += get_current_dataset().get_shk_tag();
		if (i != length - 1)
			to_next();
	}
	ret /= length;
	ret.set_qn3((int)(qn3 / length));
	ret.set_qn4((int)(qn4 / length));
	ret.set_upm((int)(upm / length));
	ret.set_shk_tag((int)(shk_tag / length));
	return ret;
}