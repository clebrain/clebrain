// Copyright (c) 2019 Clebrain. All rights reserved.

#ifndef __H_CLEBRAIN_BCICOMPETITIONIV_TABLEREADER__
#define __H_CLEBRAIN_BCICOMPETITIONIV_TABLEREADER__

#include <clebrain/bciCompetitionIV/Table.hh>

#include <iostream>
#include <map>
#include <vector>

namespace clebrain
{

namespace bciCompetitionIV
{

class TableReader final
{
  private:
    std::istream &_cntCalib, &_cntEval, &_mrk, &_nfo;

  public:
    TableReader(
        std::istream &cnt_calib,
        std::istream &cnt_eval,
        std::istream &mrk,
        std::istream &nfo)
        : _cntCalib(cnt_calib),
          _cntEval(cnt_eval),
          _mrk(mrk),
          _nfo(nfo)
    {
        _ValidateStream(cnt_calib);
        _ValidateStream(cnt_eval);
        _ValidateStream(mrk);
        _ValidateStream(nfo);
    }
    TableReader(TableReader const &table_reader)
        : _cntCalib(table_reader._cntCalib),
          _cntEval(table_reader._cntEval),
          _mrk(table_reader._mrk),
          _nfo(table_reader._nfo) {}
    TableReader &operator=(TableReader const &) = delete;
    void Read(Table &table);

  private:
    static std::map<std::string, std::vector<std::string>> _ReadInfo(std::istream &i);
    static std::vector<std::vector<float>> _ReadMatrix(std::istream &i);
    static void _ValidateStream(std::istream &i);
};

} // namespace bciCompetitionIV

} // namespace clebrain

#endif