// Copyright (c) 2019 Clebrain. All rights reserved.

#include <clebrain/bciCompetitionIV/Table.hh>

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>


clebrain::bciCompetitionIV::Table clebrain::bciCompetitionIV::Table::TableReadStream(
    std::istream &cnt_calib,
    std::istream &cnt_eval,
    std::istream &mrk,
    std::istream &nfo)
{
    _ValidateStream(cnt_calib);
    _ValidateStream(cnt_eval);
    _ValidateStream(mrk);
    _ValidateStream(nfo);

    Table table;

    {
        auto _nfo = _ReadInfo(nfo);
        table.fs((unsigned)std::stoi(_nfo["fs"][0]));
        table.classes(
            std::make_pair(
                std::move(_nfo["classes"][0]),
                std::move(_nfo["classes"][1])));
        table.clab(std::move(_nfo["clab"]));

        {
            auto &xpos = _nfo["xpos"];
            auto &ypos = _nfo["ypos"];
            std::vector<std::pair<float, float>> pos(xpos.size());
            for (size_t i = 0, l = xpos.size(); i < l; ++i)
                pos[i] = std::make_pair(std::stof(xpos[i]), std::stof(ypos[i]));
            table.pos(std::move(pos));
        }
    }

    table.eval(_ReadMatrix(cnt_eval));
    table.calib(_ReadMatrix(cnt_calib));

    {
        auto _mrk = _ReadMatrix(mrk);
        std::vector<std::pair<float, bool>> target_cue_info_struct(_mrk.size());
        for (size_t i = 0, l = _mrk.size(); i < l; ++i)
            target_cue_info_struct[i] = std::make_pair(_mrk[i][0], _mrk[i][1] == 1.0f);

        table.targetCueInfoStruct(std::move(target_cue_info_struct));
    }

    return table;
}

std::map<
    std::string,
    std::vector<std::string>>
clebrain::bciCompetitionIV::Table::_ReadInfo(std::istream &i)
{
    std::map<std::string, std::vector<std::string>> rtn;

    int in;
    std::string st;
    std::string name;
    std::vector<std::string> line;

    while (true)
    {
        if (i.eof())
            break;

        in = i.get();

        if (in == ':')
            name = std::move(st);
        else if (in == ',')
            line.push_back(std::move(st));
        else if (in == ' ')
            continue;
        else if (in == '\n')
        {
            line.push_back(std::move(st));
            rtn.insert(
                std::make_pair(std::move(name), std::move(line)));
        }
        else
            st.push_back((char)in);
    }

    return rtn;
}

std::vector<std::vector<float>> clebrain::bciCompetitionIV::Table::_ReadMatrix(std::istream &i)
{
    // TODO: With no consideration of optimization
    std::vector<std::vector<float>> rtn;

    int in;
    std::string st;
    std::vector<float> line;

    while (true)
    {
        if (i.eof())
            break;

        in = i.get();

        if (in == '\t')
        {
            float f = std::stof(st);
            line.push_back(f);
            st.clear();
        }
        else if (in == '\n')
        {
            if (st.empty())
                break;

            float f = std::stof(st);
            line.push_back(f);
            st.clear();
            rtn.push_back(std::move(line));
        }
        else
            st.push_back((char)in);
    }

    return rtn;
}

void clebrain::bciCompetitionIV::Table::_ValidateStream(std::istream &i)
{
    if (!i)
        throw std::exception();
}
