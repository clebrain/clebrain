// Copyright (c) 2019 Clebrain. All rights reserved.

#include <clebrain/bciCompetitionIV/Table.hh>

#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using namespace std::literals::string_literals;

int main()
{
    ifstream
        calib(CLEBRAIN_BCICOMPETITIONIV_DATA_DIR "BCICIV_calib_ds1a_cnt.txt", ifstream::in),
        eval(CLEBRAIN_BCICOMPETITIONIV_DATA_DIR "BCICIV_eval_ds1a_cnt.txt", ifstream::in),
        mrk(CLEBRAIN_BCICOMPETITIONIV_DATA_DIR "BCICIV_calib_ds1a_mrk.txt", ifstream::in),
        nfo(CLEBRAIN_BCICOMPETITIONIV_DATA_DIR "BCICIV_calib_ds1a_nfo.txt", ifstream::in);

    clebrain::bciCompetitionIV::Table table;
    
    table = clebrain::bciCompetitionIV::Table::ReadFromStream(
        calib, eval, mrk, nfo);

    if (table.fs() != 100)
        return 1;

    if (table.classes() != std::make_pair("left"s, "foot"s))
        return 2;

    if (table.targetCueInfoStruct().size() != 200)
        return 3;

    if (table.calib().size() != 190594)
        return 4;

    if (table.eval().size() != 240558)
        return 5;

    return 0;
}