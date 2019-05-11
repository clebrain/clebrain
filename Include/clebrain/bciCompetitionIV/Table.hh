// Copyright (c) 2019 Clebrain. All rights reserved.

#ifndef __H_CLEBRAIN_BCICOMPETITIONIV_TABLE__
#define __H_CLEBRAIN_BCICOMPETITIONIV_TABLE__

#include <paxbun/Helpers.hh>

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace clebrain
{

namespace bciCompetitionIV
{

class Table final
{
  private:
    unsigned int _fs;
    std::pair<std::string, std::string> _classes;
    std::vector<std::pair<float, bool>> _targetCueInfoStruct;
    std::vector<std::string> _clab;
    std::vector<std::pair<float, float>> _pos;
    std::vector<std::vector<float>> _calib;
    std::vector<std::vector<float>> _eval;

  public:
    //Getters and Setters (using paxbun helpers)
    PAXBUN_VAL_GET(fs);
    PAXBUN_REF_GET(classes);
    PAXBUN_REF_GET(targetCueInfoStruct);
    PAXBUN_REF_GET(clab);
    PAXBUN_REF_GET(pos);
    PAXBUN_REF_GET(calib);
    PAXBUN_REF_GET(eval);

    PAXBUN_VAL_SET(fs);
    PAXBUN_COPY_SET(classes);
    PAXBUN_COPY_SET(targetCueInfoStruct);
    PAXBUN_COPY_SET(clab);
    PAXBUN_COPY_SET(pos);
    PAXBUN_COPY_SET(calib);
    PAXBUN_COPY_SET(eval);

    PAXBUN_MOVE_SET(classes);
    PAXBUN_MOVE_SET(targetCueInfoStruct);
    PAXBUN_MOVE_SET(clab);
    PAXBUN_MOVE_SET(pos);
    PAXBUN_MOVE_SET(calib);
    PAXBUN_MOVE_SET(eval);

  private:
    static std::map<std::string, std::vector<std::string>> _ReadInfo(std::istream &i);
    static std::vector<std::vector<float>> _ReadMatrix(std::istream &i);
    static void _ValidateStream(std::istream &i);

  public:
    //Constructor
    Table() : _fs(0)
    {
    }

    Table(Table const &table)
        : _fs(table._fs),
          _classes(table._classes),
          _targetCueInfoStruct(table._targetCueInfoStruct),
          _clab(table._clab),
          _pos(table._pos),
          _calib(table._calib),
          _eval(table._eval) {}

    Table(Table &&table) noexcept
        : _fs(table._fs),
          _classes(std::move(table._classes)),
          _targetCueInfoStruct(std::move(table._targetCueInfoStruct)),
          _clab(std::move(table._clab)),
          _pos(std::move(table._pos)),
          _calib(std::move(table._calib)),
          _eval(std::move(table._eval))
    {
        table._fs = 0;
    }

    //Operator Overloading
    Table &operator=(Table const &table)
    {
        if (this != &table)
        {
            _fs = table._fs;
            _classes = table._classes;
            _targetCueInfoStruct = table._targetCueInfoStruct;
            _clab = table._clab;
            _pos = table._pos;
            _calib = table._calib;
            _eval = table._eval;
        }
        return *this;
    }

    Table &operator=(Table &&table) noexcept
    {
        if (this != &table)
        {
            _fs = table._fs;
            _classes = std::move(table._classes);
            _targetCueInfoStruct = std::move(table._targetCueInfoStruct);
            _clab = std::move(table._clab);
            _pos = std::move(table._pos);
            _calib = std::move(table._calib);
            _eval = std::move(table._eval);
            table._fs = 0;
        }
        return *this;
    }

    //Destructor
    ~Table() {}

    static Table ReadFromStream(
        std::istream &cnt_calib,
        std::istream &cnt_eval,
        std::istream &mrk,
        std::istream &nfo);
};

} // namespace bciCompetitionIV

} // namespace clebrain

#endif