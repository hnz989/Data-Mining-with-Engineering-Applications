#include "csvreader.h"
#include "logger.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <iomanip>

using namespace std;

extern string field_number, field_year, field_month, field_day, field_hour;
extern string field_pm_value, field_dwep, field_temperature, field_pressure;
extern string field_cbwd, field_iws, field_is,field_ir;
extern int field_number_index,field_year_index,field_month_index,field_day_index,field_hour_index;
extern int field_pm_value_index,field_dwep_index,field_temperature_index,field_pressure_index;
extern int field_cbwd_index,field_iws_index,field_is_index,field_ir_index;

/*CsvReader :: CsvReader(string file_name)
{
	this->file_name = file_name;

}*/

vector<vector<string> > CsvReader :: read_csv(map<string, map<string, int> >& freq_table)
{

	INFOLOG("Start reading csv file for input.\n");
	vector<vector<string> > csv_data;
	vector<string> tuple;
	string number, year, month, day, hour, pm_value,dwep,temperature, pressure,cbwd,iws,is,ir;
	string csv_file_name = "C:/Users/Kyle Zheng/Desktop/589-Proj1/StarCube/input/sample.csv";

    ifstream csv_file(csv_file_name);

    if(!csv_file.is_open()){
		ERRORLOG("Problem in file open()\n");
		return csv_data;
	}

   //getline ( csv_file, field_hour, ',' );
    //freq_table[field_hour] = map<string, int>();
    //field_hour_index = 0;

    getline ( csv_file, field_pm_value, ',' );
    freq_table[field_pm_value] = map<string, int>();
    field_pm_value_index = 0;

    getline ( csv_file, field_temperature, ',' );
    freq_table[field_temperature] = map<string, int>();
    field_temperature_index = 1;

    getline ( csv_file, field_pressure, ',' );
    freq_table[field_pressure] = map<string, int>();
    field_pressure_index = 2;

    getline ( csv_file, field_cbwd, '\n' );
    freq_table[field_cbwd] = map<string, int>();
    field_cbwd_index = 3;

    //if(INFO)

		string  info_log = "pm_value : " +  field_pm_value +  ", temperature : " + field_temperature + ", pressure : "+ field_pressure + ",cbwd : " +field_cbwd;

         const char *log_string = info_log.c_str();
         INFOLOG("%s\n",log_string);


    while ( csv_file.good() )
	{
        //getline ( csv_file, number, ',' );

        getline ( csv_file, pm_value, ',' );
	     tuple.push_back(pm_value);

        getline ( csv_file, temperature, ',' );
	     tuple.push_back(temperature);

	     getline ( csv_file, pressure, ',' );
	     tuple.push_back(pressure);

	     getline ( csv_file, cbwd, '\n' );
	     tuple.push_back(cbwd);

         csv_data.push_back(tuple);
	     tuple.clear();

	    // if(INFO)

         string  info_log = "pm_value : " +  pm_value +  ", temperature : " + temperature + ", pressure : "+ pressure + ",cbwd : " +cbwd;
         const char *log_string = info_log.c_str();
         INFOLOG("%s\n",log_string);


	     freq_table[field_pm_value][pm_value]++;
	     freq_table[field_temperature][temperature]++;
	     freq_table[field_pressure][pressure]++;
	     freq_table[field_cbwd][cbwd]++;

        }

	return csv_data;
}


void CsvReader :: printdata(vector<vector<string> > &csvdata)
{

    cout << "--------------------------------------------"<<endl;

    int size = (int) csvdata.size();
    for(int i = 0; i < size ; i++ )
    {
        cout << "|" << setw(5)<< csvdata[i][0]  <<  " |  " << setw(5)<< csvdata[i][field_temperature_index] <<  " |  " << setw(5) <<   csvdata[i][field_pressure_index] <<  " |  " << setw(5) <<   csvdata[i][field_cbwd_index] <<  " |  "<< setw(5) << csvdata[i][field_cbwd_index+1] << " |"<<endl;
		cout << "|------|--------|--------|--------|--------|"<<endl;

    }
	cout << "Number of tuples : " << csvdata.size()  <<endl;
	cout << "Number of atrributes : " << csvdata[0].size()  <<endl;
}


