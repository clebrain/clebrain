// Copyright (c) 2019 Clebrain. All rights reserved.

#ifndef __H_CLEBRAIN_BCICOMPETITIONIV_TABLEREADER__
#define __H_CLEBRAIN_BCICOMPETITIONIV_TABLEREADER__

#include <clebrain/bciCompetitionIV/Table.hh>

#include <iostream>

namespace clebrain
{

namespace bciCompetitionIV
{

class TableReader final
{
  private:
    std::ostream &_cnt, &_mrk, &_nfo;

  public:
    TableReader(std::ostream &cnt, std::ostream &mrk, std::ostream &nfo)
        : _cnt(cnt), _mrk(mrk), _nfo(nfo) {}
    TableReader(TableReader const &table_reader)
        : _cnt(table_reader._cnt), _mrk(table_reader._mrk), _nfo(table_reader._nfo) {}
    TableReader &operator=(TableReader const &) = delete;
    void Read(Table &table);
};

} // namespace bciCompetitionIV

} // namespace clebrain

#endif