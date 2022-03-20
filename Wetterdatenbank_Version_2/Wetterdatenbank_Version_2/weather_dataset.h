#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "error.h"

using namespace std;

enum class date_format {
	dmy,
	mdy,
	ymd,
	ydm,
	dym,
	myd,
	dm,
	md,
	dy,
	yd,
	my,
	ym,
	d,
	m,
	y,
};

enum class rskf_type {
	no_rainfall,
	only_rain,
	precipitation_of_unknown_kind=4,
	only_rain_automatic_station=6,
	only_snow_automatic_station,
	rain_and_snow,
	missing_value,
};

class date {
private:
	int year{};
	int month{};
	int day{};
public:
	date();
	date(int yearc, int monthc, int dayc);

	void set_year(int yearm);
	void set_month(int monthm);
	void set_day(int daym);
	int get_year();
	int get_month();
	int get_day();

	string print_date(date_format format = date_format::dmy, bool four_digit_year=true, bool add_zeros=true, string connector=".");
	void print_date_to_console(date_format format = date_format::dmy, bool four_digit_year = true, bool add_zeros = true, string connector = ".");
};

class weather_dataset {
private:
	date measurement_date;	//Datum im Format "yyyy-mm-dd" der Daten
	int qn4;				//Qualitaetsniveau der nachfolgenden Spalten
	float tmk;				//Tagesmittel der Temperatur °C
	float txk;				//Tagesmaximum der Lufttemperatur in 2m H�he °C
	float tnk;				//Tagesminimum der Lufttemperatur in 2m H�he °C	
	float tgk;				//Minimum der Lufttemperatur am Erdboden in 5cm H�he °C
	float upm;				//Tagesmittel der Relativen Feuchte %
	float rsk;				//taegliche Niederschlagshoehe mm
	rskf_type rskf;				//Niederschlagsform
	float sdk;				//taegliche Sonnenscheindauer h
	float shk_tag;			//Tageswert Schneehoehe cm
	float nm;				//Tagesmittel des Bedeckungsgrades 1/8
	float vpm;				//Tagesmittel des Dampfdruckes hPa
	float pm;				//Tagesmittel des Luftdrucks hPa
	int qn3;				//Qualitaetsniveau der nachfolgenden Spalten 
	float fx;				//Tagesmaximum Windspitze m/s
	float fm;				//Tagesmittel Windgeschwindigkeit m/s
public:
	weather_dataset();
	weather_dataset(string);
	weather_dataset(date measurement_datek, int qn4k, float tmkk, float txkk, float tnkk, float tgkk, float upmk, float rskk, rskf_type rskfk, float sdkk, float shk_tagk, float nmk, float vpmk, float pmk, int qn3k, float fxk, float fmk);
	void print_dataset();
	date get_measurement_date();
	int get_qn4();
	float get_tmk();
	float get_txk();
	float get_tnk();
	float get_tgk();
	float get_upm();
	float get_rsk();
	rskf_type get_rskf();
	float get_sdk();
	float get_shk_tag();
	float get_nm();
	float get_vpm();
	float get_pm();
	int get_qn3();
	float get_fx();
	float get_fm();
	float get_column_as_float(int index);
	void operator += (weather_dataset dt);
	void operator /= (int value);
};


