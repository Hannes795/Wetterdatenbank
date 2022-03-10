#include "weather_dataset.h"
#include "database.h"

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
	rskf = 0;
	sdk = 0;
	shk_tag = 0;
	nm = 0;
	vpm = 0;
	pm = 0;
	qn3 = 0;
	fx = 0;
	fm = 0;
}

weather_dataset::weather_dataset(date measurement_datek, int qn4k, float tmkk, float txkk, float tnkk, float tgkk, int upmk, float rskk, int rskfk, float sdkk, int shk_tagk, float nmk, float vpmk, float pmk, int qn3k, float fxk, float fmk) {
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
	time_stream >> measurement_date.year;
	time_stream >> measurement_date.month;
	time_stream >> measurement_date.day;
	zstream >> qn4;
	zstream >> tmk;
	zstream >> txk;
	zstream >> tnk;
	zstream >> tgk;
	zstream >> upm;
	zstream >> rsk;
	zstream >> rskf;
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
	cout << "Datum im Format \"yyyy-mm-dd\":\t\t\t\t\t\t" << measurement_date.year << "-" << measurement_date.month << "-" << measurement_date.day << endl;
	cout << "Qualitaetsniveau der nachfolgenden Werte:\t\t\t\t" << qn4 << endl;
	cout << "Tagesmittel der Temperatur in Grad Celsius:\t\t\t\t" << tmk << endl;
	cout << "Tagesmaximum der Lufttemperatur in 2m Hoehe in Grad Celsius:\t\t" << txk << endl;
	cout << "Tagesminimum der Lufttemperatur in 2m Hoehe in Grad Celsius:\t\t" << tnk << endl;
	cout << "Minimum der Lufttemperatur am Erdboden in 5cm Hoehe in Grad Celsius:\t" << tgk << endl;
	cout << "Tagesmittel der Relativen Feuchte in Prozent:\t\t\t\t" << upm << endl;
	cout << "taegliche Niederschlagshoehe in mm:\t\t\t\t\t" << rsk << endl;
	cout << "Niederschlagsform:\t\t\t\t\t\t\t" << rskf << endl;
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

int weather_dataset::get_upm() {
	return upm;
}

float weather_dataset::get_rsk() {
	return rsk;
}

int weather_dataset::get_rskf() {
	return rskf;
}

float weather_dataset::get_sdk() {
	return sdk;
}

int weather_dataset::get_shk_tag() {
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

float weather_dataset::get_float_column(int column) {
	switch(column){
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
	case 7:
		return rsk;
		break;
	case 9:
		return sdk;
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
	case 15:
		return fx;
		break;
	case 16:
		return fm;
		break;
	default:
		db_error invalid_column_error;
		invalid_column_error.id = 6;
		invalid_column_error.error_position = "weather_database::search_column(int, float, int)";
		invalid_column_error.error_type = "InvalidColumn";
		string part1 = "The column is invalid(";
		string part2 = to_string(column);
		string part3 = "). The column has to be 2, 3, 4, 5, 7, 9, 11, 12, 13, 15 or 16 to look for an integer value.";
		invalid_column_error.error_string = part1 + part2 + part3;
		throw invalid_column_error;
		break;
	}
}

int weather_dataset::get_int_column(int column) {
	switch (column)
	{
	case 1:
		return qn4;
		break;
	case 6:
		return upm;
		break;
	case 8:
		return rskf;
		break;
	case 10:
		return shk_tag;
		break;
	case 14:
		return qn3;
		break;
	default:
		db_error invalid_column_error;
		invalid_column_error.id = 6;
		invalid_column_error.error_position = "weather_database::search_column(int, int, int)";
		invalid_column_error.error_type = "InvalidColumn";
		string part1 = "The column is invalid(";
		string part2 = to_string(column);
		string part3 = "). The column has to be 1, 6, 8, 10 or 14 to look for an integer value.";
		invalid_column_error.error_string = part1 + part2 + part3;
		throw invalid_column_error;
		break;
	}
}

void weather_dataset::operator += (weather_dataset dt) {
	tmk += dt.get_tmk();
	txk += dt.get_txk();
	tnk += dt.get_tnk();
	tgk += dt.get_tgk();
	rsk += dt.get_rsk();
	sdk += dt.get_sdk();
	nm += dt.get_nm();
	vpm += dt.get_vpm();
	pm += dt.get_pm();
	fx += dt.get_fx();
	fm += dt.get_fm();
}

void weather_dataset::operator /= (int value) {
	tmk /= value;
	txk /= value;
	tnk /= value;
	tgk /= value;
	rsk /= value;
	sdk /= value;
	nm /= value;
	vpm /= value;
	pm /= value;
	fx /= value;
	fm /= value; 
}

void weather_dataset::set_qn3(int value) {
	qn3 = value;
}

void weather_dataset::set_qn4(int value) {
	qn4 = value;
}

void weather_dataset::set_upm(int value) {
	upm = value;
}
void weather_dataset::set_shk_tag(int value) {
	shk_tag = value;
}