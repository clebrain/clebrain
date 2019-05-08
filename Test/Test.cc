#include <clebrain/bciCompetitionIV/Table.hh>
#include <clebrain/bciCompetitionIV/TableReader.hh>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char *argv[])
{
    ifstream
        cnt("../clebrain-data/BCICIV_calib_ds1a_cnt.txt", ifstream::in),
        mrk("../clebrain-data/BCICIV_calib_ds1a_mrk.txt", ifstream::in),
        nfo("../clebrain-data/BCICIV_calib_ds1a_nfo.txt", ifstream::in);

    clebrain::bciCompetitionIV::TableReader reader(
        cnt, mrk, nfo);
    clebrain::bciCompetitionIV::Table table;
    reader.Read(table);

    cout << "fs: " << table.fs() << '\n'
         << "classes: " << table.classes().first
         << ", " << table.classes().second << '\n';
    return 0;
}