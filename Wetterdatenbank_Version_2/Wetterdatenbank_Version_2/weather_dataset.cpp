#include "weather_dataset.h"

// default-constructor
date::date()
{
	year = 1950;
	month = 1;
	day = 1;
}

// constructor
date::date(int yearc, int monthc, int dayc) {
	// condition to check for extreme values, e.g. 56-70-3923
	if (yearc < 1950 || yearc > 2050 || 
		monthc < 1 || monthc > 12 || 
		dayc < 1 || dayc > 31) 
	{
		string part_1 = "The given date: ";
		string part_2 = "-";
		string part_3 = " is invalid. A valid date has to be between 1950-1-1 and 2050-12-31.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(dayc) + part_2 + to_string(monthc) + part_2 + to_string(yearc) + part_3, "date::date(int, int, int)" };
	}
	// condition for a day that does not exist in the given month, e.g. 31.02.
	else if ((dayc > 30 && (monthc == 4 || monthc == 6 || monthc == 9 || monthc == 11)) || (dayc > 29 && monthc == 2)) {
		string part_1 = "The given date: ";
		string part_2 = "-";
		string part_3 = " is invalid. Because the given month does not include the given day.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(dayc) + part_2 + to_string(monthc) + part_2 + to_string(yearc) + part_3, "date::date(int, int, int)" };
	}
	// condition to check for a leap year
	else if (dayc > 28 && monthc == 2 && (yearc % 4 != 0 || (yearc % 100 == 0 && yearc % 400 != 0))) {
		string part_1 = "The given date: ";
		string part_2 = "-";
		string part_3 = " is invalid. Because the given month does not include the given day.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(dayc) + part_2 + to_string(monthc) + part_2 + to_string(yearc) + part_3, "date::date(int, int, int)" };
	}
	// condition for correct dates
	else {
		day = dayc;
		month = monthc;
		year = yearc;
	}
}

void date::set_year(int yearm) {
	// condition for months that are not February
	if (yearm >= 1950 && yearm <= 2050 && month != 2) {
		year = yearm;
	}
	// condition for a day in February that is not the 29 
	else if (yearm >= 1950 && yearm <= 2050 && day <= 28) {
		year = yearm;
	}
	// condition for a 29-February but a leap-year
	else if (yearm >= 1950 && yearm <= 2050 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		year = yearm;
	}
	// condition for a 29-February and the given year is not a leap-year
	else {
		string part_1 = "The given year: ";
		string part_2 = " is invalid. A valid year has to be between 1950 and 2050 and has to be a leap year if the day is the 29 February.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(yearm) + part_2, "date::set_year(int)" };
	}
}

void date::set_month(int monthm) {
	// condition for a valid month
	if (monthm >= 1 && monthm <= 12 && day <= 28) {
		month = monthm;
	}
	// condition for a invalid month
	else if (monthm < 1 || monthm > 12) {
		string part_1 = "The given month: ";
		string part_2 = " is invalid. A valid month has to be between 1 and 12.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(monthm) + part_2, "date::set_year(int)" };
	}
	// condition for the day 31 and the months with 31 days
	else if (day <= 31 && monthm != 2 && monthm != 4 && monthm != 6 && monthm != 9 && monthm != 11) {
		month = monthm;
	}
	// condition for the day 30 and the month with 30 days
	else if (day <= 30 && month != 2) {
		month = monthm;
	}
	// condition for the day 29 and February
	else if (day <= 29 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		month = monthm;
	}
	// condition for a invalid month for the given day
	else {
		string part_1 = "The given month: ";
		string part_2 = " is invalid, because it does not include the given day.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(monthm) + part_2, "date::set_year(int)" };
	}
}

void date::set_day(int daym) {
	// condition for a valid day
	if (daym >= 1 && daym <= 28) {
		day = daym;
	} 
	// condition for a invalid day
	else if (daym < 1 || daym > 31) {
		string part_1 = "The given day: ";
		string part_2 = " is invalid. A valid day has to be between 1 and 31.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(daym) + part_2, "date::set_year(int)" };
	}
	// condition for month with 30 days and day 30
	else if (daym >= 1 && daym <= 30 && month != 2) {
		day = daym;
	}
	// condition for month with 31 days and day 31
	else if (daym >= 1 && daym <= 31 && month != 2 && month != 4 && month != 6 && month != 9 && month != 11) {
		day = daym;
	}
	// condition for the 29th of February
	else if (daym >= 1 && daym <= 29 && month == 2 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		day = daym;
	}
	// condition for an invalid day
	else {
		string part_1 = "The given day: ";
		string part_2 = " is invalid, because it does not exist in the given month";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(daym) + part_2, "date::set_year(int)" };
	}
}

//get-methods for the attributes
int date::get_year() {
	return year;
}

int date::get_month() {
	return month;
}

int date::get_day() {
	return day;
}

//return a string with the date
string date::print_date(date_format format, bool four_digit_year, bool add_zeros, string connector) {
	string days = to_string(day);
	string months = to_string(month);
	string years = to_string(year);
	string dates;
	string zero = "0";
	if (day < 10 && add_zeros)
		days = zero + days;
	if (month < 10 && add_zeros)
		months = zero + months;
	if (!four_digit_year)
		years = years.at(2) + years.at(3);
	switch (format)
	{
	case date_format::dmy:
		dates = days + connector + months + connector + years;
		break;
	case date_format::mdy:
		dates = months + connector + days + connector + years;
		break;
	case date_format::ymd:
		dates = years + connector + months + connector + days;
		break;
	case date_format::ydm:
		dates = years + connector + days + connector + months;
		break;
	case date_format::dym:
		dates = days + connector + years + connector + months;
		break;
	case date_format::myd:
		dates = months + connector + years + connector + days;
		break;
	case date_format::dm:
		dates = days + connector + months;
		break;
	case date_format::md:
		dates = months + connector + days;
		break;
	case date_format::dy:
		dates = days + connector + years;
		break;
	case date_format::yd:
		dates = years + connector + days;
		break;
	case date_format::my:
		dates = months + connector + years;
		break;
	case date_format::ym:
		dates = years + connector + months;
		break;
	case date_format::d:
		dates = days;
		break;
	case date_format::m:
		dates = months;
		break;
	case date_format::y:
		dates = years;
		break;
	default:
		throw error{error_id::invalid_argument_error, "InvalidArgumentError", "The given date_format is not valid.", "date::print_date(date_format, bool, bool, string)"};
		break;
	}
	return dates;
}

// default-constructor
weather_dataset::weather_dataset()
{
	measurement_date = date();
	qn4 = 0;
	tmk = 0;
	txk = 0;
	tnk = 0;
	tgk = 0;
	upm = 0;
	rsk = 0;
	rskf = rskf_type::missing_value;
	sdk = 0;
	shk_tag = 0;
	nm = 0;
	vpm = 0;
	pm = 0;
	qn3 = 0;
	fx = 0;
	fm = 0;
}

// assigns the values to the attributes
weather_dataset::weather_dataset(date measurement_datek, int qn4k, float tmkk, float txkk, float tnkk, float tgkk, float upmk, float rskk, rskf_type rskfk, float sdkk, float shk_tagk, float nmk, float vpmk, float pmk, int qn3k, float fxk, float fmk) {
	measurement_date = measurement_datek;
	qn4 = qn4k;
	tmk = tmkk;
	txk = txkk;
	tnk = tnkk;
	tgk = tgkk;
	upm = upmk;
	rsk = rskk;
	rskf = rskfk;
	sdk = sdkk;
	shk_tag = shk_tagk;
	nm = nmk;
	vpm = vpmk;
	pm = pmk;
	qn3 = qn3k;
	fx = fxk;
	fm = fmk;
	if (fm < -1 || fm > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "fm is out of its valid range -> fm: " + to_string(fm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)"};
	}
	if (fx < -1 || fx > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "fx is out of its valid range -> fx: " + to_string(fx), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (qn3 < -1 || qn3 > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "qn3 is out of its valid range -> qn3: " + to_string(qn3), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (pm < 900 || pm > 1100) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "pm is out of its valid range -> pm: " + to_string(pm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (upm < -1 || upm > 5000) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "upm is out of its valid range -> upm: " + to_string(upm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (nm < -1 || nm > 10) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "nm is out of its valid range -> nm: " + to_string(nm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (shk_tag < -1 || shk_tag > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "shk_tag is out of its valid range -> shk_tag: " + to_string(shk_tag), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (sdk < -1 || sdk > 25) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "sdk is out of its valid range -> sdk: " + to_string(sdk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (rsk < -1 || rsk > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "rsk is out of its valid range -> rsk: " + to_string(rsk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (upm < -1 || upm > 101) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "upm is out of its valid range -> upm: " + to_string(upm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tgk < -50 || tgk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tgk is out of its valid range -> tgk: " + to_string(tgk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tnk < -50 || tnk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tnk is out of its valid range -> tnk: " + to_string(tnk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (txk < -50 || txk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "txk is out of its valid range -> txk: " + to_string(txk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tmk < -50 || tmk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tmk is out of its valid range -> tmk: " + to_string(tmk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (qn4 < -1 || qn4 > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "qn4 is out of its valid range -> qn4: " + to_string(qn4), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
}

// reads a line from the csv-file and converts it to a weather_dataset
weather_dataset::weather_dataset(string linec)
{
	// sometimes in the csv-file there are missing data, which is represented so: ;; 
	// this leads to an error, because the following data is now stored in the wrong column
	// solved by inserting a 0 between two semicolon
	int last_occurance = -5;
	int index = 0;
	string line = linec;
	while (index < line.length()) {
		int current_occurance = line.find(";", index);
		if (abs(current_occurance - last_occurance) == 1) {
			line = line.insert(current_occurance, "0");
			last_occurance = current_occurance + 1;
			index = current_occurance + 2;
		}
		else if (current_occurance == -1) {
			break;
		}
		else {
			last_occurance = current_occurance;
			index = current_occurance + 1;
		}
	}

	// replace semicolon with a space to divide the string to be able to use the stringstream properly
	replace(line.begin(), line.end(), ';', ' ');
	// convert the line to a stringstream
	istringstream zstream(line);

	// read the line until the next space is found and store the data
	string time_string;
	zstream >> time_string;
	replace(time_string.begin(), time_string.end(), '\"', ' ');
	replace(time_string.begin(), time_string.end(), '-', ' ');
	istringstream time_stream{ time_string };
	measurement_date = date();
	int year;
	time_stream >> year;
	measurement_date.set_year(year);
	int month;
	time_stream >> month;
	measurement_date.set_month(month);
	int day;
	time_stream >> day;
	measurement_date.set_day(day);
	zstream >> qn4;
	zstream >> tmk;
	zstream >> txk;
	zstream >> tnk;
	zstream >> tgk;
	zstream >> upm;
	zstream >> rsk;
	int rskfi;
	zstream >> rskfi;
	rskf = static_cast<rskf_type>(rskfi);
	zstream >> sdk;
	zstream >> shk_tag;
	zstream >> nm;
	zstream >> vpm;
	zstream >> pm;
	zstream >> qn3;
	zstream >> fx;
	zstream >> fm;
	// Check for a valid value range of the attributes
	if (fm < -1 || fm > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "fm is out of its valid range -> fm: " + to_string(fm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (fx < -1 || fx > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "fx is out of its valid range -> fx: " + to_string(fx), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (qn3 < -1 || qn3 > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "qn3 is out of its valid range -> qn3: " + to_string(qn3), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (pm < 900 || pm > 1100) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "pm is out of its valid range -> pm: " + to_string(pm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (upm < -1 || upm > 5000) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "upm is out of its valid range -> upm: " + to_string(upm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (nm < -1 || nm > 10) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "nm is out of its valid range -> nm: " + to_string(nm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (shk_tag < -1 || shk_tag > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "shk_tag is out of its valid range -> shk_tag: " + to_string(shk_tag), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (sdk < -1 || sdk > 25) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "sdk is out of its valid range -> sdk: " + to_string(sdk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (rsk < -1 || rsk > 500) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "rsk is out of its valid range -> rsk: " + to_string(rsk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (upm < -1 || upm > 101) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "upm is out of its valid range -> upm: " + to_string(upm), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tgk < -50 || tgk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tgk is out of its valid range -> tgk: " + to_string(tgk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tnk < -50 || tnk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tnk is out of its valid range -> tnk: " + to_string(tnk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (txk < -50 || txk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "txk is out of its valid range -> txk: " + to_string(txk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (tmk < -50 || tmk > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "tmk is out of its valid range -> tmk: " + to_string(tmk), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
	if (qn4 < -1 || qn4 > 50) {
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", "qn4 is out of its valid range -> qn4: " + to_string(qn4), "weather_dataset::weather_dataset(date, int, float, float, float, float, float, float, float, rskf_type, float, float, float, float, float, int, float, float)" };
	}
}

// print the weather-dataset to the console
void weather_dataset::print_dataset()
{
	cout << "------------------------------Beginn des Datensatzes------------------------------" << endl;
	cout << "Datum im Format \"yyyy-mm-dd\":\t\t\t\t\t\t" << measurement_date.print_date(date_format::ymd, true, true, "-") << endl;
	cout << "Qualitaetsniveau der nachfolgenden Werte:\t\t\t\t" << qn4 << endl;
	cout << "Tagesmittel der Temperatur in Grad Celsius:\t\t\t\t" << tmk << endl;
	cout << "Tagesmaximum der Lufttemperatur in 2m Hoehe in Grad Celsius:\t\t" << txk << endl;
	cout << "Tagesminimum der Lufttemperatur in 2m Hoehe in Grad Celsius:\t\t" << tnk << endl;
	cout << "Minimum der Lufttemperatur am Erdboden in 5cm Hoehe in Grad Celsius:\t" << tgk << endl;
	cout << "Tagesmittel der Relativen Feuchte in Prozent:\t\t\t\t" << upm << endl;
	cout << "taegliche Niederschlagshoehe in mm:\t\t\t\t\t" << rsk << endl;
	cout << "Niederschlagsform:\t\t\t\t\t\t\t" << (int)rskf << endl;
	cout << "taegliche Sonnenscheindauer in h:\t\t\t\t\t" << sdk << endl;
	cout << "Tageswert Schneehoehe in cm:\t\t\t\t\t\t" << shk_tag << endl;
	cout << "Tagesmittel des Bedeckungsgrades 1/8:\t\t\t\t\t" << nm << endl;
	cout << "Tagesmittel des Dampfdruckes hPa:\t\t\t\t\t" << vpm << endl;
	cout << "Tagesmittel des Luftdrucks hPa:\t\t\t\t\t\t" << pm << endl;
	cout << "Qualitaetsniveau der nachfolgenden Spalten:\t\t\t\t" << qn3 << endl;
	cout << "Tagesmaximum Windspitze m/s:\t\t\t\t\t\t" << fx << endl;
	cout << "Tagesmittel Windgeschwindigkeit m/s:\t\t\t\t\t" << fm << endl;
	cout << "-------------------------------Ende des Datensatzes-------------------------------" << endl;
}

// get-methods for the attributes
date weather_dataset::get_measurement_date() {
	return measurement_date;
}

int weather_dataset::get_qn4() {
	return qn4;
}

float weather_dataset::get_tmk() {
	return tmk;
}

float weather_dataset::get_txk() {
	return txk;
}

float weather_dataset::get_tnk() {
	return tnk;
}

float weather_dataset::get_tgk() {
	return tgk;
}

float weather_dataset::get_upm() {
	return upm;
}

float weather_dataset::get_rsk() {
	return rsk;
}

rskf_type weather_dataset::get_rskf() {
	return rskf;
}

float weather_dataset::get_sdk() {
	return sdk;
}

float weather_dataset::get_shk_tag() {
	return shk_tag;
}

float weather_dataset::get_nm() {
	return nm;
}

float weather_dataset::get_vpm() {
	return vpm;
}

float weather_dataset::get_pm() {
	return pm;
}

int weather_dataset::get_qn3() {
	return qn3;
}

float weather_dataset::get_fx() {
	return fx;
}

float weather_dataset::get_fm() {
	return fm;
}

// get the specified column
float weather_dataset::get_column_as_float(int column) {
	switch (column) {
	case 1:
		return (float)qn4;
		break;
	case 2:
		return tmk;
		break;
	case 3:
		return txk;
		break;
	case 4:
		return tnk;
		break;
	case 5:
		return tgk;
		break;
	case 6: 
		return upm;
		break;
	case 7:
		return rsk;
		break;
	case 8:
		return (float)rskf;
		break;
	case 9:
		return sdk;
		break;
	case 10:
		return shk_tag;
		break;
	case 11:
		return nm;
		break;
	case 12:
		return vpm;
		break;
	case 13:
		return pm;
		break;
	case 14:
		return (float)qn3;
		break;
	case 15:
		return fx;
		break;
	case 16:
		return fm;
		break;
	default:
		string part_1 = "The column is invalid(";
		string part_3 = "). The column has to be between 1 and 16.";
		throw error{ error_id::invalid_argument_error, "InvalidArgumentError", part_1 + to_string(column) + part_3, "weather_dataset::get_column_as_float(int)"};
		break;
	}
}

// override the += operator to be able to add two datasets together
void weather_dataset::operator += (weather_dataset dt) {
	qn4 += dt.get_qn4();
	tmk += dt.get_tmk();
	txk += dt.get_txk();
	tnk += dt.get_tnk();
	tgk += dt.get_tgk();
	upm += dt.get_upm();
	rsk += dt.get_rsk();
	sdk += dt.get_sdk();
	shk_tag += dt.get_shk_tag();
	nm += dt.get_nm();
	vpm += dt.get_vpm();
	pm += dt.get_pm();
	qn3 += dt.get_qn3();
	fx += dt.get_fx();
	fm += dt.get_fm();
}

// override the /=-operator to calculate the average in combination with the +=-operator
void weather_dataset::operator /= (int value) {
	qn4 /= value;
	tmk /= value;
	txk /= value;
	tnk /= value;
	tgk /= value;
	upm /= value;
	rsk /= value;
	sdk /= value;
	shk_tag /= value;
	nm /= value;
	vpm /= value;
	pm /= value;
	qn3 /= value;
	fx /= value;
	fm /= value;
}