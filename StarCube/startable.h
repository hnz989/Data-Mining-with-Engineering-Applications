#ifndef STARTABLE_H
#define STARTABLE_H

#include <map>
#include <vector>
#include <string>
#include <cstring>

class StarTable
{
    public:
        int iceberg;
        StarTable(int iceberg);
        void generate_attrs_stars( std::map<std::string, int> & attrs_freq, std::vector<std::vector<std::string> > &csv_data, int attr_index, std::string star_val, int iceberg_condition);
        std::vector<std::vector<std::string> > compress_star_table(std::vector<std::vector<std::string> >& table);
        std::string  generate_key(std::vector<std::string> row);
};

#endif // STARTABLE_H
