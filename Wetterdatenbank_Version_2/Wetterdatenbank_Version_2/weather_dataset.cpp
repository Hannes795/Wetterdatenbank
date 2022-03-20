#include "weather_dataset.h"


date::date()
{
	year = 1950;
	month = 1;
	day = 1;
}

date::date(int yearc, int monthc, int dayc) {
	if (yearc < 1950 || yearc > 2050 || 
		monthc < 1 || monthc > 12 || 
		dayc < 1 || dayc > 31) 
	{
		cout << "The given date: " << yearc << "-" << monthc << "-" << dayc << " is invalid.";
		cout << "A valid date has to be between 1950-1-1 and 2050-12-31." << endl;
	}
	else if ((dayc > 30 && (monthc == 4 || monthc == 6 || monthc == 9 || monthc == 11)) || (dayc > 29 && monthc == 2)) {
		cout << "The given date: " << yearc << "-" << monthc << "-" << dayc << " is invalid.";
		cout << "The given month: " << monthc << " does not have 31 days. So the given day: " << dayc << " is invalid." << endl;
	}
	else if (dayc > 28 && monthc == 2 && (yearc % 4 != 0 || (yearc % 100 == 0 && yearc % 400 != 0))) {
		cout << "The given date: " << yearc << "-" << monthc << "-" << dayc << " is invalid.";
		cout << "The given month: " << monthc << " does not have 31 days. So the given day: " << dayc << " is invalid." << endl;
	}
	else {
		day = dayc;
		month = monthc;
		year = yearc;
	}
}

void date::set_year(int yearm) {
	if (yearm >= 1950 && yearm <= 2050 && month != 2) {
		year = yearm;
	}
	else if (yearm >= 1950 && yearm <= 2050 && day <= 28) {
		year = yearm;
	}
	else if (yearm >= 1950 && yearm <= 2050 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		year = yearm;
	}
	else {
		cout << "The given year: " << yearm << "is invalid. A valid year has to be between 1950 and 2050." << endl;
	}
}

void date::set_month(int monthm) {
	if (monthm >= 1 && monthm <= 12 && day <= 28) {
		month = monthm;
	}
	else if (monthm < 1 && monthm > 12) {
		cout << "The given month: " << monthm << " is invalid. A valid month has to be between 1 and 12." << endl;
	}
	else if (day <= 31 && monthm != 2 && monthm != 4 && monthm != 6 && monthm != 9 && monthm != 11) {
		month = monthm;
	}
	else if (day <= 30 && month != 2) {
		month = monthm;
	}
	else if (day <= 29 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		month = monthm;
	}
	else {
		cout << "The given month: " << monthm << " is invalid, because of the day: " << day << ".Please note that some months do not have as many days as others." << endl;
	}
}

void date::set_day(int daym) {
	if (daym >= 1 && daym <= 28) {
		day = daym;
	} 
	else if (daym < 1 || daym > 31) {
		cout << "The given day: " << daym << "is invalid. A valid day has to be between 1 and 31." << endl;
	}
	else if (daym >= 1 && daym <= 30 && month != 2) {
		day = daym;
	}
	else if (daym >= 1 && daym <= 31 && month != 2 && month != 4 && month != 6 && month != 9 && month != 11) {
		day = daym;
	}
	else if (daym >= 1 && daym <= 29 && month == 2 && year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0))) {
		day = daym;
	}
	else {
		cout << "The given day: " << daym << "is for the given month: " << month << " invalid. Please regard that some months have less days than others." << endl;
	}
}

int date::get_year() {
	return year;
}

int date::get_month() {
	return month;
}

int date::get_day() {
	return day;
}

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
		throw error{error_id::invalid_argument_error, "InvalidArgumentError", "The given date_format is not valid.", "date::print_date"};
		break;
	}
	return dates;
}

void date::print_date_to_console(date_format format, bool four_digit_year, bool add_zeros, string connector) {
	cout << print_date(format, four_digit_year, add_zeros, connector);
}

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
}
weather_dataset::weather_dataset(string line)
{
	/// <summary>
	/// Dem Konstruktor wird eine Zeile der CSV-Datei �bergeben, die er dann anschlie�end verarbeitet
	/// </summary>
	/// <param name="zeile"></param>
	replace(line.begin(), line.end(), ';', ' ');
	istringstream zstream(line);

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
}


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
		error invalid_column_error;
		invalid_column_error.set_id(error_id::invalid_argument_error);
		invalid_column_error.set_error_position("weather_dataset::get_column_as_float");
		invalid_column_error.set_error_type("InvalidArgumentError");
		string part1 = "The column is invalid(";
		string part2 = to_string(column);
		string part3 = "). The column has to be between 1 and 16.";
		invalid_column_error.set_error_string(part1 + part2 + part3);
		throw invalid_column_error;
		break;
	}
}

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