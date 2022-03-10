#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class date {
public:
	int year{};
	int month{};
	int day{};
};

class weather_dataset
{
private:
	date measurement_date;	//Datum im Format "yyyy-mm-dd" der Daten
	int qn4;				//Qualitaetsniveau der nachfolgenden Spalten
	float tmk;				//Tagesmittel der Temperatur °C
	float txk;				//Tagesmaximum der Lufttemperatur in 2m H�he °C
	float tnk;				//Tagesminimum der Lufttemperatur in 2m H�he °C	
	float tgk;				//Minimum der Lufttemperatur am Erdboden in 5cm H�he °C
	int upm;				//Tagesmittel der Relativen Feuchte %
	float rsk;				//taegliche Niederschlagshoehe mm
	int rskf;				//Niederschlagsform
	float sdk;				//taegliche Sonnenscheindauer h
	int shk_tag;			//Tageswert Schneehoehe cm
	float nm;				//Tagesmittel des Bedeckungsgrades 1/8
	float vpm;				//Tagesmittel des Dampfdruckes hPa
	float pm;				//Tagesmittel des Luftdrucks hPa
	int qn3;				//Qualitaetsniveau der nachfolgenden Spalten 
	float fx;				//Tagesmaximum Windspitze m/s
	float fm;				//Tagesmittel Windgeschwindigkeit m/s
public:
	weather_dataset();
	weather_dataset(string);
	weather_dataset(date measurement_datek, int qn4k, float tmkk, float txkk, float tnkk, float tgkk, int upmk, float rskk, int rskfk, float sdkk, int shk_tagk, float nmk, float vpmk, float pmk, int qn3k, float fxk, float fmk);
	void print_dataset();
	date get_measurement_date();
	int get_qn4();
	void set_qn4(int value);
	float get_tmk();
	float get_txk();
	float get_tnk();
	float get_tgk();
	int get_upm();
	void set_upm(int value);
	float get_rsk();
	int get_rskf();
	float get_sdk();
	int get_shk_tag();
	void set_shk_tag(int value);
	float get_nm();
	float get_vpm();
	float get_pm();
	int get_qn3();
	void set_qn3(int value);
	float get_fx();
	float get_fm();
	int get_int_column(int index);
	float get_float_column(int index);
	void operator += (weather_dataset dt);
	void operator /= (int value);
};

