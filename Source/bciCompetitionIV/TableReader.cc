// Copyright (c) 2019 Clebrain. All rights reserved.

#include <clebrain/bciCompetitionIV/TableReader.hh>

#include <cctype>
#include <stdexcept>
#include <string>
#include <utility>

void clebrain::bciCompetitionIV::TableReader::Read(clebrain::bciCompetitionIV::Table &table)
{
    {
        auto nfo = _ReadInfo(_nfo);
        table.fs((unsigned)std::stoi(nfo["fs"][0]));
        table.classes(
            std::make_pair(
                std::move(nfo["classes"][0]),
                std::move(nfo["classes"][1])));
        table.clab(std::move(nfo["clab"]));

        {
            auto &xpos = nfo["xpos"];
            auto &ypos = nfo["ypos"];
            std::vector<std::pair<float, float>> pos(xpos.size());
            for (size_t i = 0, l = xpos.size(); i < l; ++i)
                pos[i] = std::make_pair(std::stof(xpos[i]), std::stof(ypos[i]));
            table.pos(std::move(pos));
        }
    }

    table.eval(_ReadMatrix(_cntEval));
    table.calib(_ReadMatrix(_cntCalib));

    {
        auto mrk = _ReadMatrix(_mrk);
        std::vector<std::pair<float, bool>> target_cue_info_struct(mrk.size());
        for (size_t i = 0, l = mrk.size(); i < l; ++i)
            target_cue_info_struct[i] = std::make_pair(mrk[i][0], mrk[i][1] == 1.0f);

        table.targetCueInfoStruct(std::move(target_cue_info_struct));
    }
}

std::map<
    std::string,
    std::vector<std::string>>
clebrain::bciCompetitionIV::TableReader::_ReadInfo(std::istream &i)
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

std::vector<std::vector<float>> clebrain::bciCompetitionIV::TableReader::_ReadMatrix(std::istream &i)
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

void clebrain::bciCompetitionIV::TableReader::_ValidateStream(std::istream &i)
{
    if (!i)
        throw std::exception();
}
