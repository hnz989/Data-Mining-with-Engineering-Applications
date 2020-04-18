#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/log/trivial.hpp>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include "csvreader.h"
#include "logger.h"
#include "startable.h"
#include "startree.h"
#include "starcube.h"
#include <time.h>

using namespace std;

int temperature_iceberg = 2;
int pressure_iceberg = 2;
int pm_value_iceberg = 2;
int cbwd_iceberg = 2;
int dwep_iceberg = 20;

string temperature_star_val = "*";
string pm_value_star_val = "*";
string pressure_star_val = "*";
string cbwd_star_val = "*";
string dwep_star_val = "dwep*";


//attributes
string field_number, field_year, field_month, field_day, field_hour;
string field_pm_value, field_dwep, field_temperature, field_pressure;
string field_cbwd, field_iws, field_is,field_ir;

int field_number_index, field_year_index, field_month_index, field_day_index, field_hour_index;
int field_pm_value_index,field_dwep_index,field_temperature_index,field_pressure_index;
int field_cbwd_index,field_iws_index,field_is_index,field_ir_index;

int main()
{
    int ice;
    printf("Please enter ice-berg condition: ");
    scanf("%d", &ice);
    INFOLOG("Start Cubing Algorithm\n");
    time_t start_time = time(nullptr); // get current time and date
    cout << asctime(localtime(&start_time))
              << start_time << " seconds since the Epoch\n";
    cout <<  "continue :" <<  endl;
    map<string, map<string, int> > freq_table;
    map<string, string> star_table;
    map<string, string> temperature_star_table;
    map<string, string> pm_value_star_table;
    vector<vector<string> > csv_data;

    CsvReader reader;

	StarTable startable(ice);
	StarTree startree;

	csv_data = reader.read_csv(freq_table);
	StarCube starcube(csv_data, ice);

    if(csv_data.size() == 0)
    {
		ERRORLOG("Error in input reading. Data size zero\n");
		return 0;
	}

    INFOLOG("Number of tuples : %d\n", (int)csv_data.size());
	INFOLOG("Freq table size : %d\n", (int)freq_table.size());

    startable.generate_attrs_stars(freq_table[field_temperature], csv_data, field_temperature_index, temperature_star_val, startable.iceberg);
    startable.generate_attrs_stars(freq_table[field_pm_value], csv_data, field_pm_value_index, pm_value_star_val, startable.iceberg);
    startable.generate_attrs_stars(freq_table[field_pressure], csv_data, field_pressure_index, pressure_star_val, startable.iceberg);
    startable.generate_attrs_stars(freq_table[field_cbwd], csv_data, field_cbwd_index, cbwd_star_val, startable.iceberg);

    cout <<  "Uncompressed table : " <<  csv_data.size() <<  ",  atrributes : " <<  csv_data[0].size() << endl;;

    csv_data = startable.compress_star_table(csv_data);
    cout << "Number of tuples in compressed table : " <<  (int)csv_data.size() << endl;;
    cout << "Freq table size : " << (int)freq_table.size() <<  endl;


    reader.printdata(csv_data);

    TreeNode* root  = new TreeNode();
    root->val = "*";
    startree.generate_star_tree(csv_data, root, 0);

    printf("\n                                  \n");
	printf("|----------------------------------|\n");
	printf("|----------------------------------|\n");
	printf("|@@@@ Start Cubing Algorithm   @@@@|\n");
	printf("|----------------------------------|\n");
	printf("|----------------------------------|\n");

	cout << "Root count : " <<  root->count <<endl;

	string cuboid[] = {"*", "A" , "B", "C", "D"};

	vector<TreeNode*> subtree;
    starcube.star_cubing1(startree, root, startree.root, 0, cuboid, subtree);
    starcube.print_cuboid();

    time_t end_time = time(nullptr);
    cout << asctime(localtime(&end_time)) << end_time << " seconds since the Epoch\n";
    cout << "Time  :  " <<  (int)(end_time-start_time) << endl;;

    return 0;
}


