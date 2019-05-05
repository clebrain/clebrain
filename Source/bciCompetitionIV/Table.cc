// Copyright (c) 2019 Clebrain. All rights reserved.

#include <clebrain/bciCompetitionIV/Table.hh>

#include <iostream>

void clebrain::bciCompetitionIV::Foo()
{
    Table t;
    t.fs(5);
    std::cout << t.fs() << std::endl;
}