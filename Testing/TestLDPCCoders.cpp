// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Pothos/Framework.hpp>
#include <Pothos/Testing.hpp>

#include <Poco/File.h>
#include <Poco/TemporaryFile.h>

#include <fstream>
#include <iostream>

static std::string generateTestAFile()
{
    /* Autogenerated by hxtools bin2c */
    /* Autogenerated from /usr/local/share/gnuradio/fec/ldpc/n_0100_k_0042_gap_02.alist */
    static const unsigned char alistContents[2161] = {'1','0','0',' ','5','8',012,'3',' ','5',012,'1',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','3',' ','2',' ','3',' ','3',' ','3',' ','3',' ','3',' ',012,'5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ','5',' ',012,'1',' ',012,'1',' ','2',' ',012,'2',' ','3',' ','5','7',' ',012,'2',' ','4',' ','5','7',' ',012,'1',' ','5',' ','5','7',' ',012,'3',' ','6',' ','5','8',' ',012,'4',' ','7',' ','5','8',' ',012,'3',' ','8',' ','5','8',' ',012,'3',' ','8',' ','9',' ',012,'7',' ','9',' ','1','0',' ',012,'4',' ','8',' ','1','1',' ',012,'1',' ','1','1',' ','1','2',' ',012,'5',' ','1','1',' ','1','3',' ',012,'1','0',' ','1','4',' ','5','8',' ',012,'1','1',' ','1','4',' ','1','5',' ',012,'1','3',' ','1','6',' ',012,'8',' ','1','5',' ','1','7',' ',012,'6',' ','1','7',' ','1','8',' ',012,'1','6',' ','1','9',' ',012,'7',' ','1','7',' ','2','0',' ',012,'1','0',' ','1','6',' ','2','1',' ',012,'2',' ','2','0',' ','2','2',' ',012,'9',' ','2','0',' ','2','3',' ',012,'2','1',' ','2','3',' ','2','4',' ',012,'1','2',' ','2','2',' ','2','5',' ',012,'4',' ','2','2',' ','2','6',' ',012,'2','3',' ','2','5',' ','2','7',' ',012,'1','9',' ','2','8',' ',012,'1','0',' ','2','6',' ','2','9',' ',012,'3',' ','2','2',' ','3','0',' ',012,'1','9',' ','2','6',' ','3','1',' ',012,'2','2',' ','2','8',' ','3','2',' ',012,'1','2',' ','1','8',' ','3','3',' ',012,'6',' ','3','3',' ','3','4',' ',012,'2','0',' ','3','5',' ','5','7',' ',012,'5',' ','1','5',' ','3','6',' ',012,'3','3',' ','3','5',' ','3','7',' ',012,'1','3',' ','3','3',' ','3','8',' ',012,'7',' ','3','1',' ','3','9',' ',012,'5',' ','3','6',' ','4','0',' ',012,'9',' ','3','5',' ','4','1',' ',012,'1','8',' ','3','8',' ','4','2',' ',012,'2','5',' ','3','6',' ','4','3',' ',012,'2','1',' ','3','2',' ','4','4',' ',012,'4','1',' ','4','5',' ',012,'6',' ','4','5',' ','4','6',' ',012,'3','8',' ','4','6',' ','4','7',' ',012,'2','8',' ','3','9',' ','4','8',' ',012,'2','5',' ','4','7',' ','4','9',' ',012,'1','3',' ','4','7',' ','5','0',' ',012,'2',' ','4','6',' ','5','1',' ',012,'4','4',' ','4','5',' ','5','2',' ',012,'1','4',' ','3','2',' ','5','3',' ',012,'2','7',' ','4','9',' ','5','4',' ',012,'3','2',' ','4','3',' ','5','5',' ',012,'2','1',' ','4','1',' ','5','6',' ',012,'3','4',' ','4','2',' ',012,'2','6',' ','3','7',' ','5','5',' ',012,'4',' ','5','3',' ','5','6',' ',012,'1','8',' ','2','8',' ','5','1',' ',012,'1','6',' ','5','1',' ','5','2',' ',012,'1','6',' ','2','7',' ','3','7',' ',012,'9',' ','2','3',' ','3','4',' ',012,'3','7',' ','4','7',' ','5','6',' ',012,'3','0',' ','3','2',' ','4','8',' ',012,'2','7',' ','5','2',' ','5','6',' ',012,'8',' ','1','9',' ','5','5',' ',012,'1','9',' ','2','8',' ','4','5',' ',012,'3','1',' ','3','8',' ','5','4',' ',012,'2','4',' ','3','8',' ','4','2',' ',012,'4','8',' ','5','4',' ','5','6',' ',012,'3','0',' ','3','9',' ','5','3',' ',012,'3','1',' ','5','0',' ','5','4',' ',012,'2','4',' ','2','6',' ','5','7',' ',012,'2','0',' ','2','1',' ',012,'1','2',' ','5','2',' ','5','3',' ',012,'1','4',' ','5','2',' ','5','3',' ',012,'1','2',' ','4','1',' ','4','7',' ',012,'3','4',' ','4','8',' ','5','0',' ',012,'1',' ','2','9',' ','3','5',' ',012,'1','8',' ','2','9',' ','4','9',' ',012,'2','7',' ','3','5',' ','4','0',' ',012,'1','7',' ','4','0',' ','5','0',' ',012,'4','1',' ','4','3',' ','5','1',' ',012,'3','3',' ','4','0',' ','4','4',' ',012,'1','0',' ','4','2',' ','4','3',' ',012,'1','5',' ','2','3',' ','2','9',' ',012,'1','5',' ','4','9',' ','5','5',' ',012,'6',' ','2','5',' ','2','9',' ',012,'1','4',' ','4','0',' ','4','5',' ',012,'1','3',' ','3','0',' ','3','1',' ',012,'3','6',' ','4','4',' ','4','6',' ',012,'1','1',' ','4','4',' ','4','6',' ',012,'2','4',' ','4','9',' ','5','1',' ',012,'3','7',' ','4','8',' ',012,'1','7',' ','2','4',' ','4','3',' ',012,'7',' ','3','4',' ','4','2',' ',012,'3','6',' ','3','9',' ','5','0',' ',012,'5',' ','5','4',' ','5','5',' ',012,'3','0',' ','3','9',' ','5','8',' ',012,'1',' ','2',' ','5',' ','1','2',' ','8','0',' ',012,'2',' ','3',' ','4',' ','2','2',' ','5','1',' ',012,'3',' ','6',' ','8',' ','9',' ','3','0',' ',012,'4',' ','7',' ','1','1',' ','2','6',' ','5','9',' ',012,'5',' ','1','3',' ','3','6',' ','4','0',' ','9','9',' ',012,'6',' ','1','8',' ','3','4',' ','4','6',' ','8','9',' ',012,'7',' ','1','0',' ','2','0',' ','3','9',' ','9','7',' ',012,'8',' ','9',' ','1','1',' ','1','7',' ','6','7',' ',012,'9',' ','1','0',' ','2','3',' ','4','1',' ','6','3',' ',012,'1','0',' ','1','4',' ','2','1',' ','2','9',' ','8','6',' ',012,'1','1',' ','1','2',' ','1','3',' ','1','5',' ','9','3',' ',012,'1','2',' ','2','5',' ','3','3',' ','7','6',' ','7','8',' ',012,'1','3',' ','1','6',' ','3','8',' ','5','0',' ','9','1',' ',012,'1','4',' ','1','5',' ','5','3',' ','7','7',' ','9','0',' ',012,'1','5',' ','1','7',' ','3','6',' ','8','7',' ','8','8',' ',012,'1','6',' ','1','9',' ','2','1',' ','6','1',' ','6','2',' ',012,'1','7',' ','1','8',' ','2','0',' ','8','3',' ','9','6',' ',012,'1','8',' ','3','3',' ','4','2',' ','6','0',' ','8','1',' ',012,'1','9',' ','2','8',' ','3','1',' ','6','7',' ','6','8',' ',012,'2','0',' ','2','2',' ','2','3',' ','3','5',' ','7','5',' ',012,'2','1',' ','2','4',' ','4','4',' ','5','6',' ','7','5',' ',012,'2','2',' ','2','5',' ','2','6',' ','3','0',' ','3','2',' ',012,'2','3',' ','2','4',' ','2','7',' ','6','3',' ','8','7',' ',012,'2','4',' ','7','0',' ','7','4',' ','9','4',' ','9','6',' ',012,'2','5',' ','2','7',' ','4','3',' ','4','9',' ','8','9',' ',012,'2','6',' ','2','9',' ','3','1',' ','5','8',' ','7','4',' ',012,'2','7',' ','5','4',' ','6','2',' ','6','6',' ','8','2',' ',012,'2','8',' ','3','2',' ','4','8',' ','6','0',' ','6','8',' ',012,'2','9',' ','8','0',' ','8','1',' ','8','7',' ','8','9',' ',012,'3','0',' ','6','5',' ','7','2',' ','9','1',' ','1','0','0',' ',012,'3','1',' ','3','9',' ','6','9',' ','7','3',' ','9','1',' ',012,'3','2',' ','4','4',' ','5','3',' ','5','5',' ','6','5',' ',012,'3','3',' ','3','4',' ','3','7',' ','3','8',' ','8','5',' ',012,'3','4',' ','5','7',' ','6','3',' ','7','9',' ','9','7',' ',012,'3','5',' ','3','7',' ','4','1',' ','8','0',' ','8','2',' ',012,'3','6',' ','4','0',' ','4','3',' ','9','2',' ','9','8',' ',012,'3','7',' ','5','8',' ','6','2',' ','6','4',' ','9','5',' ',012,'3','8',' ','4','2',' ','4','7',' ','6','9',' ','7','0',' ',012,'3','9',' ','4','8',' ','7','2',' ','9','8',' ','1','0','0',' ',012,'4','0',' ','8','2',' ','8','3',' ','8','5',' ','9','0',' ',012,'4','1',' ','4','5',' ','5','6',' ','7','8',' ','8','4',' ',012,'4','2',' ','5','7',' ','7','0',' ','8','6',' ','9','7',' ',012,'4','3',' ','5','5',' ','8','4',' ','8','6',' ','9','6',' ',012,'4','4',' ','5','2',' ','8','5',' ','9','2',' ','9','3',' ',012,'4','5',' ','4','6',' ','5','2',' ','6','8',' ','9','0',' ',012,'4','6',' ','4','7',' ','5','1',' ','9','2',' ','9','3',' ',012,'4','7',' ','4','9',' ','5','0',' ','6','4',' ','7','8',' ',012,'4','8',' ','6','5',' ','7','1',' ','7','9',' ','9','5',' ',012,'4','9',' ','5','4',' ','8','1',' ','8','8',' ','9','4',' ',012,'5','0',' ','7','3',' ','7','9',' ','8','3',' ','9','8',' ',012,'5','1',' ','6','0',' ','6','1',' ','8','4',' ','9','4',' ',012,'5','2',' ','6','1',' ','6','6',' ','7','6',' ','7','7',' ',012,'5','3',' ','5','9',' ','7','2',' ','7','6',' ','7','7',' ',012,'5','4',' ','6','9',' ','7','1',' ','7','3',' ','9','9',' ',012,'5','5',' ','5','8',' ','6','7',' ','8','8',' ','9','9',' ',012,'5','6',' ','5','9',' ','6','4',' ','6','6',' ','7','1',' ',012,'3',' ','4',' ','5',' ','3','5',' ','7','4',' ',012,'6',' ','7',' ','8',' ','1','4',' ','1','0','0',' ',012,};

    Poco::TemporaryFile afile;
    afile.keepUntilExit();

    const std::string& afilePath = afile.path();
    std::ofstream ofile(afilePath.c_str(), std::ios::out);
    ofile.write((const char*)alistContents, sizeof(alistContents));
    ofile.close();

    return afilePath;
}

static std::string generateGenMatrixTestAFile()
{
    /* Autogenerated by hxtools bin2c */
    /* Autogenerated from /usr/local/share/gnuradio/fec/ldpc/n_0100_k_0058_gen_matrix.alist */
    static const unsigned char alistContents[5972] = {'1','0','0',' ','5','8',012,'2','9',' ','2','6',012,'1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1',' ','1','3',' ','2','7',' ','2','1',' ','1','7',' ','1','9',' ','2','5',' ','1','9',' ','2','7',' ','1','5',' ','2','5',' ','2','3',' ','1','5',' ','2','5',' ','2','3',' ','2','9',' ','1','5',' ','2','7',' ','2','1',' ','1','9',' ','7',' ','2','5',' ','1','9',' ','2','7',' ','2','5',' ','2','3',' ','1','7',' ','2','1',' ','2','1',' ','2','5',' ','2','3',' ','1','9',' ','1','3',' ','7',' ','2','3',' ','2','5',' ','2','3',' ','1','9',' ','1','7',' ','2','5',' ','2','1',' ','1','9',' ','2','3',' ',012,'2','2',' ','2','4',' ','2','3',' ','2','6',' ','2','4',' ','2','1',' ','2','0',' ','2','0',' ','1','4',' ','2','1',' ','2','0',' ','1','5',' ','2','6',' ','2','6',' ','2','2',' ','1','9',' ','1','7',' ','2','0',' ','1','5',' ','2','2',' ','1','5',' ','2','5',' ','1','4',' ','5',' ','1','9',' ','2','3',' ','8',' ','1','9',' ','5',' ','5',' ','1','1',' ','1','9',' ','1','7',' ','2','0',' ','2','2',' ','2','0',' ','1','9',' ','2','3',' ','8',' ','5',' ','1','6',' ','2','2',' ','1','8',' ','8',' ','2','0',' ','1','6',' ','1','2',' ','5',' ','8',' ','5',' ','5',' ','5',' ','5',' ','5',' ','1','7',' ','5',' ','2','1',' ','1','8',' ',012,'1',' ',012,'2',' ',012,'3',' ',012,'4',' ',012,'5',' ',012,'6',' ',012,'7',' ',012,'8',' ',012,'9',' ',012,'1','0',' ',012,'1','1',' ',012,'1','2',' ',012,'1','3',' ',012,'1','4',' ',012,'1','5',' ',012,'1','6',' ',012,'1','7',' ',012,'1','8',' ',012,'1','9',' ',012,'2','0',' ',012,'2','1',' ',012,'2','2',' ',012,'2','3',' ',012,'2','4',' ',012,'2','5',' ',012,'2','6',' ',012,'2','7',' ',012,'2','8',' ',012,'2','9',' ',012,'3','0',' ',012,'3','1',' ',012,'3','2',' ',012,'3','3',' ',012,'3','4',' ',012,'3','5',' ',012,'3','6',' ',012,'3','7',' ',012,'3','8',' ',012,'3','9',' ',012,'4','0',' ',012,'4','1',' ',012,'4','2',' ',012,'4','3',' ',012,'4','4',' ',012,'4','5',' ',012,'4','6',' ',012,'4','7',' ',012,'4','8',' ',012,'4','9',' ',012,'5','0',' ',012,'5','1',' ',012,'5','2',' ',012,'5','3',' ',012,'5','4',' ',012,'5','5',' ',012,'5','6',' ',012,'5','7',' ',012,'5','8',' ',012,'4',' ','8',' ','9',' ','1','4',' ','1','9',' ','2','1',' ','2','2',' ','2','8',' ','3','2',' ','3','5',' ','4','1',' ','5','3',' ','5','6',' ',012,'3',' ','4',' ','6',' ','1','0',' ','1','3',' ','1','4',' ','1','5',' ','1','8',' ','2','0',' ','2','2',' ','2','5',' ','2','6',' ','3','2',' ','3','3',' ','3','4',' ','3','6',' ','3','7',' ','3','8',' ','4','1',' ','4','2',' ','4','3',' ','4','5',' ','4','6',' ','5','1',' ','5','5',' ','5','7',' ','5','8',' ',012,'2',' ','4',' ','5',' ','6',' ','7',' ','8',' ','1','3',' ','1','4',' ','1','5',' ','1','6',' ','1','7',' ','1','9',' ','2','0',' ','2','1',' ','2','2',' ','2','8',' ','3','2',' ','4','4',' ','4','6',' ','5','1',' ','5','2',' ',012,'2',' ','5',' ','6',' ','7',' ','9',' ','1','1',' ','1','3',' ','1','6',' ','1','8',' ','2','0',' ','2','2',' ','2','3',' ','2','5',' ','2','7',' ','3','3',' ','3','5',' ','3','7',' ',012,'1',' ','2',' ','4',' ','5',' ','8',' ','9',' ','1','0',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','1','7',' ','2','0',' ','2','3',' ','3','3',' ','3','8',' ','4','2',' ','5','7',' ',012,'1',' ','2',' ','7',' ','1','3',' ','1','4',' ','1','5',' ','1','8',' ','1','9',' ','2','0',' ','2','1',' ','2','2',' ','2','5',' ','2','6',' ','2','8',' ','3','2',' ','3','3',' ','3','6',' ','3','8',' ','4','3',' ','4','5',' ','4','6',' ','4','7',' ','5','5',' ','5','6',' ','5','8',' ',012,'1',' ','2',' ','3',' ','4',' ','1','6',' ','1','8',' ','1','9',' ','2','0',' ','2','2',' ','2','6',' ','3','0',' ','3','1',' ','3','2',' ','3','4',' ','3','8',' ','3','9',' ','4','2',' ','4','8',' ','5','7',' ',012,'1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','1','0',' ','1','2',' ','1','4',' ','1','5',' ','1','8',' ','2','0',' ','2','2',' ','2','3',' ','2','6',' ','2','7',' ','3','3',' ','3','5',' ','3','6',' ','3','7',' ','4','3',' ','4','4',' ','4','5',' ','5','2',' ','5','5',' ','5','6',' ','5','8',' ',012,'1',' ','1','2',' ','1','3',' ','1','7',' ','1','8',' ','2','5',' ','2','8',' ','3','2',' ','3','4',' ','3','6',' ','3','8',' ','4','2',' ','4','3',' ','5','5',' ','5','7',' ',012,'1',' ','2',' ','3',' ','4',' ','6',' ','1','0',' ','1','3',' ','1','4',' ','1','5',' ','1','6',' ','1','8',' ','1','9',' ','2','0',' ','2','2',' ','2','5',' ','2','6',' ','3','2',' ','3','3',' ','3','6',' ','3','7',' ','4','1',' ','4','3',' ','4','5',' ','5','5',' ','5','8',' ',012,'3',' ','6',' ','7',' ','1','6',' ','1','8',' ','1','9',' ','2','0',' ','2','2',' ','2','3',' ','2','6',' ','2','7',' ','3','1',' ','3','4',' ','3','5',' ','3','8',' ','4','1',' ','4','2',' ','4','5',' ','4','6',' ','4','7',' ','4','9',' ','5','4',' ','5','7',' ',012,'2',' ','4',' ','5',' ','6',' ','8',' ','1','0',' ','1','1',' ','1','3',' ','1','6',' ','1','8',' ','2','0',' ','2','1',' ','2','3',' ','2','4',' ','4','2',' ',012,'4',' ','5',' ','1','0',' ','1','2',' ','1','3',' ','1','6',' ','2','1',' ','2','2',' ','2','3',' ','2','6',' ','2','7',' ','2','8',' ','3','1',' ','3','3',' ','3','4',' ','3','9',' ','4','2',' ','4','5',' ','4','6',' ','4','7',' ','4','8',' ','4','9',' ','5','4',' ','5','6',' ','5','7',' ',012,'1',' ','4',' ','5',' ','7',' ','9',' ','1','0',' ','1','1',' ','1','3',' ','1','4',' ','1','8',' ','2','0',' ','2','2',' ','2','6',' ','2','8',' ','3','0',' ','3','1',' ','3','2',' ','3','4',' ','3','8',' ','3','9',' ','4','2',' ','5','3',' ','5','7',' ',012,'1',' ','5',' ','6',' ','7',' ','8',' ','1','0',' ','1','1',' ','1','4',' ','1','5',' ','2','3',' ','2','5',' ','2','7',' ','2','8',' ','3','1',' ','3','2',' ','3','3',' ','3','4',' ','3','5',' ','3','6',' ','3','7',' ','3','8',' ','4','2',' ','4','3',' ','4','9',' ','5','0',' ','5','4',' ','5','5',' ','5','7',' ','5','8',' ',012,'2',' ','3',' ','4',' ','5',' ','7',' ','8',' ','1','0',' ','1','1',' ','1','3',' ','1','6',' ','2','1',' ','2','2',' ','2','3',' ','2','4',' ','2','6',' ',012,'3',' ','6',' ','8',' ','9',' ','1','0',' ','1','1',' ','1','3',' ','1','7',' ','1','9',' ','2','0',' ','2','1',' ','2','2',' ','2','5',' ','2','6',' ','2','8',' ','3','2',' ','3','3',' ','3','4',' ','3','5',' ','3','6',' ','3','7',' ','3','8',' ','4','2',' ','4','3',' ','5','5',' ','5','7',' ','5','8',' ',012,'2',' ','3',' ','7',' ','9',' ','1','1',' ','1','2',' ','1','4',' ','1','6',' ','1','8',' ','2','0',' ','2','1',' ','3','4',' ','3','5',' ','3','8',' ','4','1',' ','4','2',' ','4','4',' ','4','5',' ','5','2',' ','5','3',' ','5','7',' ',012,'1',' ','3',' ','4',' ','5',' ','7',' ','9',' ','1','3',' ','1','4',' ','1','5',' ','1','6',' ','1','7',' ','2','0',' ','2','1',' ','3','5',' ','4','1',' ','4','4',' ','4','5',' ','5','2',' ','5','3',' ',012,'3','3',' ','3','4',' ','4','2',' ','4','5',' ','4','6',' ','4','7',' ','5','7',' ',012,'2',' ','3',' ','4',' ','5',' ','8',' ','1','0',' ','1','3',' ','1','4',' ','1','5',' ','1','7',' ','1','8',' ','2','2',' ','2','6',' ','2','8',' ','3','1',' ','3','5',' ','3','9',' ','4','1',' ','4','2',' ','4','5',' ','4','6',' ','4','7',' ','4','8',' ','5','0',' ','5','7',' ',012,'1',' ','2',' ','3',' ','4',' ','5',' ','8',' ','1','3',' ','1','4',' ','1','5',' ','1','7',' ','1','8',' ','2','2',' ','2','6',' ','2','9',' ','3','4',' ','3','5',' ','3','8',' ','4','2',' ','5','7',' ',012,'1',' ','3',' ','5',' ','7',' ','9',' ','1','1',' ','1','4',' ','1','5',' ','1','6',' ','1','8',' ','1','9',' ','2','0',' ','2','2',' ','2','8',' ','2','9',' ','3','2',' ','3','6',' ','3','7',' ','3','8',' ','4','1',' ','4','3',' ','4','5',' ','4','6',' ','4','7',' ','4','9',' ','5','5',' ','5','8',' ',012,'1',' ','2',' ','3',' ','4',' ','5',' ','8',' ','1','0',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','1','8',' ','2','0',' ','2','2',' ','2','3',' ','2','5',' ','2','7',' ','3','4',' ','3','5',' ','3','6',' ','3','8',' ','4','0',' ','4','2',' ','5','7',' ',012,'3',' ','4',' ','5',' ','8',' ','1','0',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','2','0',' ','3','3',' ','3','4',' ','3','5',' ','3','6',' ','4','0',' ','4','1',' ','4','2',' ','4','5',' ','4','6',' ','4','7',' ','5','0',' ','5','7',' ',012,'1',' ','2',' ','3',' ','5',' ','6',' ','7',' ','1','1',' ','1','2',' ','1','7',' ','2','0',' ','2','2',' ','2','5',' ','3','6',' ','4','3',' ','4','5',' ','4','6',' ','5','1',' ',012,'2',' ','4',' ','7',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','1','6',' ','1','7',' ','2','0',' ','2','1',' ','2','5',' ','2','6',' ','3','5',' ','3','7',' ','4','0',' ','4','3',' ','4','4',' ','5','5',' ','5','8',' ',012,'1',' ','5',' ','6',' ','7',' ','8',' ','1','3',' ','1','4',' ','1','5',' ','1','6',' ','1','7',' ','1','9',' ','2','0',' ','2','6',' ','2','8',' ','3','2',' ','3','4',' ','3','5',' ','3','7',' ','5','5',' ','5','7',' ','5','8',' ',012,'1',' ','3',' ','4',' ','5',' ','6',' ','7',' ','1','0',' ','1','6',' ','1','9',' ','2','3',' ','2','5',' ','2','8',' ','2','9',' ','3','2',' ','3','3',' ','3','4',' ','3','5',' ','3','6',' ','3','7',' ','3','8',' ','4','2',' ','4','3',' ','5','5',' ','5','7',' ','5','8',' ',012,'1',' ','2',' ','4',' ','5',' ','6',' ','7',' ','8',' ','1','0',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','2','5',' ','2','6',' ','3','7',' ','3','8',' ','4','1',' ','4','5',' ','4','6',' ','4','7',' ','4','9',' ','5','8',' ',012,'1',' ','2',' ','3',' ','5',' ','6',' ','1','1',' ','1','2',' ','1','3',' ','1','4',' ','1','5',' ','1','7',' ','1','8',' ','2','5',' ','2','6',' ','2','9',' ','3','4',' ','3','8',' ','4','2',' ','5','7',' ',012,'1',' ','2',' ','3',' ','8',' ','1','0',' ','1','4',' ','1','7',' ','2','0',' ','3','5',' ','3','6',' ','4','0',' ','4','1',' ','4','5',' ',012,'3',' ','4',' ','1','6',' ','1','9',' ','2','6',' ','3','0',' ','3','1',' ',012,'3',' ','6',' ','7',' ','1','0',' ','1','1',' ','1','3',' ','1','7',' ','1','8',' ','1','9',' ','2','1',' ','2','2',' ','2','8',' ','3','2',' ','3','4',' ','3','5',' ','3','6',' ','3','8',' ','4','1',' ','4','2',' ','4','4',' ','4','5',' ','4','6',' ','5','7',' ',012,'2',' ','4',' ','5',' ','8',' ','9',' ','1','4',' ','1','5',' ','1','6',' ','2','1',' ','2','5',' ','2','6',' ','3','3',' ','3','4',' ','3','6',' ','3','7',' ','3','8',' ','4','1',' ','4','2',' ','4','3',' ','4','4',' ','4','5',' ','4','6',' ','5','5',' ','5','7',' ','5','8',' ',012,'4',' ','8',' ','9',' ','1','3',' ','1','4',' ','1','5',' ','1','9',' ','2','1',' ','2','3',' ','2','4',' ','2','6',' ','2','8',' ','3','2',' ','3','5',' ','3','6',' ','3','7',' ','3','8',' ','4','3',' ','4','7',' ','4','9',' ','5','1',' ','5','5',' ','5','8',' ',012,'1',' ','4',' ','6',' ','9',' ','1','0',' ','1','2',' ','1','4',' ','1','5',' ','1','7',' ','1','8',' ','2','2',' ','2','6',' ','2','8',' ','3','1',' ','3','3',' ','3','5',' ','3','7',' ','3','9',' ','4','8',' ',012,'2',' ','3',' ','4',' ','7',' ','8',' ','1','0',' ','1','2',' ','1','3',' ','1','6',' ','1','7',' ','2','1',' ','2','2',' ','2','3',' ','2','4',' ','2','5',' ','3','6',' ','4','3',' ',012,'2',' ','5',' ','6',' ','9',' ','1','0',' ','1','1',' ','1','4',' ','1','5',' ','1','6',' ','1','9',' ','2','2',' ','2','5',' ','2','6',' ','2','8',' ','3','2',' ','3','3',' ','3','4',' ','3','5',' ','3','6',' ','3','7',' ','3','8',' ','4','2',' ','4','3',' ','5','5',' ','5','8',' ',012,'1',' ','6',' ','7',' ','9',' ','1','1',' ','1','2',' ','2','5',' ','2','8',' ','3','1',' ','3','2',' ','3','7',' ','3','8',' ','3','9',' ','4','1',' ','4','3',' ','4','5',' ','4','6',' ','4','7',' ','5','0',' ','5','5',' ','5','8',' ',012,'1',' ','2',' ','6',' ','8',' ','1','1',' ','1','3',' ','2','2',' ','2','3',' ','2','6',' ','2','7',' ','3','7',' ','3','8',' ','4','1',' ','4','5',' ','4','6',' ','4','7',' ','4','9',' ','5','4',' ','5','8',' ',012,'2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','1','7',' ','1','8',' ','2','2',' ','2','5',' ','2','8',' ','3','0',' ','3','1',' ','3','2',' ','3','3',' ','3','5',' ','3','6',' ','3','7',' ','3','9',' ','4','3',' ','5','5',' ','5','8',' ',012,'1',' ','6','3',' ','6','4',' ','6','5',' ','6','6',' ','6','7',' ','6','8',' ','7','2',' ','7','3',' ','7','7',' ','8','0',' ','8','1',' ','8','2',' ','8','4',' ','8','6',' ','8','7',' ','8','8',' ','8','9',' ','9','0',' ','9','5',' ','9','8',' ','9','9',' ',012,'2',' ','6','1',' ','6','2',' ','6','3',' ','6','4',' ','6','5',' ','6','6',' ','6','8',' ','7','0',' ','7','4',' ','7','6',' ','7','9',' ','8','0',' ','8','2',' ','8','4',' ','8','5',' ','8','8',' ','8','9',' ','9','0',' ','9','3',' ','9','6',' ','9','7',' ','9','9',' ','1','0','0',' ',012,'3',' ','6','0',' ','6','5',' ','6','6',' ','6','8',' ','6','9',' ','7','4',' ','7','5',' ','7','6',' ','7','7',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','3',' ','8','4',' ','8','7',' ','8','9',' ','9','0',' ','9','1',' ','9','2',' ','9','6',' ','1','0','0',' ',012,'4',' ','5','9',' ','6','0',' ','6','1',' ','6','3',' ','6','5',' ','6','6',' ','6','8',' ','7','0',' ','7','1',' ','7','2',' ','7','4',' ','7','7',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','5',' ','8','7',' ','8','8',' ','9','1',' ','9','3',' ','9','4',' ','9','5',' ','9','6',' ','1','0','0',' ',012,'5',' ','6','1',' ','6','2',' ','6','3',' ','6','6',' ','7','0',' ','7','1',' ','7','2',' ','7','3',' ','7','4',' ','7','7',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','3',' ','8','4',' ','8','6',' ','8','7',' ','8','8',' ','8','9',' ','9','3',' ','9','7',' ','1','0','0',' ',012,'6',' ','6','0',' ','6','1',' ','6','2',' ','6','6',' ','6','8',' ','6','9',' ','7','0',' ','7','3',' ','7','5',' ','8','4',' ','8','6',' ','8','7',' ','8','8',' ','8','9',' ','9','2',' ','9','5',' ','9','7',' ','9','8',' ','9','9',' ','1','0','0',' ',012,'7',' ','6','1',' ','6','2',' ','6','4',' ','6','9',' ','7','2',' ','7','3',' ','7','4',' ','7','6',' ','7','7',' ','8','1',' ','8','4',' ','8','5',' ','8','6',' ','8','7',' ','8','8',' ','9','2',' ','9','6',' ','9','8',' ','1','0','0',' ',012,'8',' ','5','9',' ','6','1',' ','6','3',' ','7','0',' ','7','3',' ','7','4',' ','7','5',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','6',' ','8','8',' ','9','0',' ','9','3',' ','9','4',' ','9','6',' ','9','9',' ','1','0','0',' ',012,'9',' ','5','9',' ','6','2',' ','6','3',' ','7','2',' ','7','5',' ','7','6',' ','7','7',' ','8','1',' ','9','3',' ','9','4',' ','9','5',' ','9','7',' ','9','8',' ',012,'1','0',' ','6','0',' ','6','3',' ','6','6',' ','6','8',' ','7','0',' ','7','1',' ','7','2',' ','7','3',' ','7','4',' ','7','5',' ','7','9',' ','8','2',' ','8','3',' ','8','7',' ','8','8',' ','9','0',' ','9','2',' ','9','5',' ','9','6',' ','9','7',' ',012,'1','1',' ','6','2',' ','6','3',' ','7','0',' ','7','2',' ','7','3',' ','7','4',' ','7','5',' ','7','6',' ','8','1',' ','8','2',' ','8','3',' ','8','4',' ','8','5',' ','8','8',' ','8','9',' ','9','2',' ','9','7',' ','9','8',' ','9','9',' ',012,'1','2',' ','6','3',' ','6','6',' ','6','7',' ','7','1',' ','7','6',' ','8','2',' ','8','3',' ','8','4',' ','8','5',' ','8','8',' ','8','9',' ','9','5',' ','9','6',' ','9','8',' ',012,'1','3',' ','6','0',' ','6','1',' ','6','2',' ','6','3',' ','6','4',' ','6','7',' ','6','8',' ','7','0',' ','7','1',' ','7','2',' ','7','4',' ','7','5',' ','7','7',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','5',' ','8','6',' ','8','8',' ','8','9',' ','9','2',' ','9','4',' ','9','6',' ','9','9',' ',012,'1','4',' ','5','9',' ','6','0',' ','6','1',' ','6','3',' ','6','4',' ','6','6',' ','6','8',' ','7','2',' ','7','3',' ','7','6',' ','7','7',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','3',' ','8','5',' ','8','6',' ','8','8',' ','8','9',' ','9','0',' ','9','3',' ','9','4',' ','9','5',' ','9','7',' ',012,'1','5',' ','6','0',' ','6','1',' ','6','3',' ','6','4',' ','6','6',' ','6','8',' ','7','3',' ','7','7',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','3',' ','8','5',' ','8','6',' ','8','8',' ','8','9',' ','9','3',' ','9','4',' ','9','5',' ','9','7',' ',012,'1','6',' ','6','1',' ','6','2',' ','6','5',' ','6','8',' ','6','9',' ','7','0',' ','7','1',' ','7','4',' ','7','6',' ','7','7',' ','8','1',' ','8','5',' ','8','6',' ','8','7',' ','9','1',' ','9','3',' ','9','6',' ','9','7',' ',012,'1','7',' ','6','1',' ','6','3',' ','6','7',' ','7','5',' ','7','7',' ','7','9',' ','8','0',' ','8','4',' ','8','5',' ','8','6',' ','8','9',' ','9','0',' ','9','2',' ','9','5',' ','9','6',' ','1','0','0',' ',012,'1','8',' ','6','0',' ','6','2',' ','6','4',' ','6','5',' ','6','6',' ','6','7',' ','6','8',' ','6','9',' ','7','0',' ','7','2',' ','7','6',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','9',' ','9','2',' ','9','5',' ','1','0','0',' ',012,'1','9',' ','5','9',' ','6','1',' ','6','4',' ','6','5',' ','6','8',' ','6','9',' ','7','5',' ','8','1',' ','8','6',' ','8','7',' ','9','1',' ','9','2',' ','9','4',' ','9','7',' ',012,'2','0',' ','6','0',' ','6','1',' ','6','2',' ','6','3',' ','6','4',' ','6','5',' ','6','6',' ','6','8',' ','6','9',' ','7','0',' ','7','2',' ','7','5',' ','7','6',' ','7','7',' ','8','1',' ','8','2',' ','8','3',' ','8','4',' ','8','5',' ','8','6',' ','9','0',' ',012,'2','1',' ','5','9',' ','6','1',' ','6','4',' ','7','0',' ','7','1',' ','7','4',' ','7','5',' ','7','6',' ','7','7',' ','8','5',' ','9','2',' ','9','3',' ','9','4',' ','9','6',' ',012,'2','2',' ','5','9',' ','6','0',' ','6','1',' ','6','2',' ','6','4',' ','6','5',' ','6','6',' ','6','8',' ','6','9',' ','7','1',' ','7','2',' ','7','4',' ','7','5',' ','7','9',' ','8','0',' ','8','1',' ','8','2',' ','8','4',' ','9','2',' ','9','5',' ','9','6',' ','9','7',' ','9','9',' ','1','0','0',' ',012,'2','3',' ','6','2',' ','6','3',' ','6','6',' ','6','9',' ','7','0',' ','7','1',' ','7','3',' ','7','4',' ','8','2',' ','8','7',' ','9','4',' ','9','6',' ','9','9',' ',012,'2','4',' ','7','0',' ','7','4',' ','9','4',' ','9','6',' ',012,'2','5',' ','6','0',' ','6','2',' ','6','4',' ','6','7',' ','6','8',' ','7','3',' ','7','5',' ','8','2',' ','8','4',' ','8','5',' ','8','7',' ','8','8',' ','8','9',' ','9','3',' ','9','6',' ','9','7',' ','9','8',' ','1','0','0',' ',012,'2','6',' ','6','0',' ','6','4',' ','6','5',' ','6','6',' ','6','8',' ','6','9',' ','7','1',' ','7','2',' ','7','4',' ','7','5',' ','7','9',' ','8','0',' ','8','5',' ','8','6',' ','8','8',' ','8','9',' ','9','1',' ','9','3',' ','9','4',' ','9','5',' ','9','7',' ','9','9',' ',012,'2','7',' ','6','2',' ','6','6',' ','6','9',' ','7','1',' ','7','3',' ','8','2',' ','9','9',' ',012,'2','8',' ','5','9',' ','6','1',' ','6','4',' ','6','7',' ','7','1',' ','7','2',' ','7','3',' ','7','5',' ','7','9',' ','8','1',' ','8','6',' ','8','7',' ','9','2',' ','9','4',' ','9','5',' ','9','7',' ','9','8',' ','1','0','0',' ',012,'2','9',' ','8','0',' ','8','1',' ','8','7',' ','8','9',' ',012,'3','0',' ','6','5',' ','7','2',' ','9','1',' ','1','0','0',' ',012,'3','1',' ','6','5',' ','6','9',' ','7','1',' ','7','2',' ','7','3',' ','7','9',' ','9','1',' ','9','5',' ','9','8',' ','1','0','0',' ',012,'3','2',' ','5','9',' ','6','0',' ','6','1',' ','6','4',' ','6','5',' ','6','7',' ','6','8',' ','7','2',' ','7','3',' ','7','5',' ','8','1',' ','8','6',' ','8','7',' ','9','2',' ','9','4',' ','9','7',' ','9','8',' ','1','0','0',' ',012,'3','3',' ','6','0',' ','6','2',' ','6','3',' ','6','4',' ','6','6',' ','6','8',' ','7','1',' ','7','3',' ','7','5',' ','7','8',' ','8','3',' ','8','7',' ','9','3',' ','9','5',' ','9','7',' ','1','0','0',' ',012,'3','4',' ','6','0',' ','6','5',' ','6','7',' ','6','9',' ','7','1',' ','7','2',' ','7','3',' ','7','5',' ','7','6',' ','7','8',' ','8','0',' ','8','2',' ','8','3',' ','8','6',' ','8','7',' ','8','9',' ','9','2',' ','9','3',' ','9','7',' ',012,'3','5',' ','5','9',' ','6','2',' ','6','6',' ','6','9',' ','7','3',' ','7','5',' ','7','6',' ','7','7',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','5',' ','8','6',' ','8','7',' ','9','0',' ','9','2',' ','9','4',' ','9','5',' ','9','7',' ','1','0','0',' ',012,'3','6',' ','6','0',' ','6','4',' ','6','6',' ','6','7',' ','6','8',' ','7','3',' ','7','5',' ','8','1',' ','8','2',' ','8','3',' ','8','4',' ','8','7',' ','9','0',' ','9','2',' ','9','3',' ','9','4',' ','9','6',' ','9','7',' ','1','0','0',' ',012,'3','7',' ','6','0',' ','6','2',' ','6','6',' ','6','8',' ','7','3',' ','7','5',' ','8','1',' ','8','5',' ','8','6',' ','8','7',' ','8','8',' ','9','3',' ','9','4',' ','9','5',' ','9','7',' ','9','8',' ','9','9',' ','1','0','0',' ',012,'3','8',' ','6','0',' ','6','3',' ','6','4',' ','6','5',' ','6','7',' ','6','9',' ','7','2',' ','7','3',' ','7','5',' ','7','6',' ','8','0',' ','8','1',' ','8','2',' ','8','7',' ','8','8',' ','8','9',' ','9','2',' ','9','3',' ','9','4',' ','9','7',' ','9','8',' ','9','9',' ',012,'3','9',' ','6','5',' ','7','1',' ','7','2',' ','7','9',' ','9','5',' ','9','8',' ','1','0','0',' ',012,'4','0',' ','8','2',' ','8','3',' ','8','5',' ','9','0',' ',012,'4','1',' ','5','9',' ','6','0',' ','6','8',' ','6','9',' ','7','6',' ','7','7',' ','7','9',' ','8','1',' ','8','3',' ','8','8',' ','9','0',' ','9','2',' ','9','3',' ','9','8',' ','9','9',' ',012,'4','2',' ','6','0',' ','6','3',' ','6','5',' ','6','7',' ','6','9',' ','7','0',' ','7','1',' ','7','2',' ','7','3',' ','7','5',' ','7','6',' ','7','8',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','7',' ','8','9',' ','9','2',' ','9','3',' ','9','7',' ',012,'4','3',' ','6','0',' ','6','4',' ','6','6',' ','6','7',' ','6','8',' ','7','3',' ','7','5',' ','8','1',' ','8','4',' ','8','5',' ','8','7',' ','9','3',' ','9','4',' ','9','6',' ','9','7',' ','9','8',' ','1','0','0',' ',012,'4','4',' ','6','1',' ','6','6',' ','7','6',' ','7','7',' ','8','5',' ','9','2',' ','9','3',' ',012,'4','5',' ','6','0',' ','6','4',' ','6','6',' ','6','8',' ','6','9',' ','7','1',' ','7','6',' ','7','7',' ','7','8',' ','7','9',' ','8','1',' ','8','3',' ','8','4',' ','8','8',' ','9','0',' ','9','2',' ','9','3',' ','9','8',' ','9','9',' ',012,'4','6',' ','6','0',' ','6','1',' ','6','4',' ','6','9',' ','7','1',' ','7','8',' ','7','9',' ','8','1',' ','8','3',' ','8','4',' ','8','8',' ','9','2',' ','9','3',' ','9','8',' ','9','9',' ',012,'4','7',' ','6','4',' ','6','9',' ','7','1',' ','7','8',' ','7','9',' ','8','1',' ','8','3',' ','8','8',' ','9','4',' ','9','8',' ','9','9',' ',012,'4','8',' ','6','5',' ','7','1',' ','7','9',' ','9','5',' ',012,'4','9',' ','6','9',' ','7','1',' ','7','3',' ','8','1',' ','8','8',' ','9','4',' ','9','9',' ',012,'5','0',' ','7','3',' ','7','9',' ','8','3',' ','9','8',' ',012,'5','1',' ','6','0',' ','6','1',' ','8','4',' ','9','4',' ',012,'5','2',' ','6','1',' ','6','6',' ','7','6',' ','7','7',' ',012,'5','3',' ','5','9',' ','7','2',' ','7','6',' ','7','7',' ',012,'5','4',' ','6','9',' ','7','1',' ','7','3',' ','9','9',' ',012,'5','5',' ','6','0',' ','6','4',' ','6','6',' ','6','7',' ','6','8',' ','7','3',' ','7','5',' ','8','1',' ','8','5',' ','8','6',' ','8','7',' ','9','3',' ','9','4',' ','9','7',' ','9','8',' ','1','0','0',' ',012,'5','6',' ','5','9',' ','6','4',' ','6','6',' ','7','1',' ',012,'5','7',' ','6','0',' ','6','3',' ','6','5',' ','6','7',' ','6','9',' ','7','1',' ','7','2',' ','7','3',' ','7','5',' ','7','6',' ','7','8',' ','7','9',' ','8','0',' ','8','2',' ','8','3',' ','8','6',' ','8','7',' ','8','9',' ','9','2',' ','9','3',' ',012,'5','8',' ','6','0',' ','6','4',' ','6','6',' ','6','8',' ','7','3',' ','7','5',' ','8','1',' ','8','5',' ','8','6',' ','8','7',' ','8','8',' ','9','3',' ','9','4',' ','9','7',' ','9','8',' ','9','9',' ','1','0','0',' ',012,};

    Poco::TemporaryFile afile;
    afile.keepUntilExit();

    const std::string& afilePath = afile.path();
    std::ofstream ofile(afilePath.c_str(), std::ios::out);
    ofile.write((const char*)alistContents, sizeof(alistContents));
    ofile.close();

    return afilePath;
}

POTHOS_TEST_BLOCK("/fec/tests", test_ldpc_coder_symmetry)
{
    constexpr float sigma = 0.5f;
    constexpr size_t maxIterations = 50;

    const auto testAFilepath = generateTestAFile();
    POTHOS_TEST_TRUE(Poco::File(testAFilepath).exists());

    auto ldpcEncoder = Pothos::BlockRegistry::make(
                           "/fec/ldpc_encoder",
                           testAFilepath);
    POTHOS_TEST_EQUAL(
        testAFilepath,
        ldpcEncoder.call<std::string>("afilePath"));

    auto ldpcDecoder = Pothos::BlockRegistry::make(
                           "/fec/ldpc_decoder",
                           testAFilepath,
                           sigma,
                           maxIterations);
    POTHOS_TEST_EQUAL(
        testAFilepath,
        ldpcDecoder.call<std::string>("afilePath"));
    POTHOS_TEST_EQUAL(sigma, ldpcDecoder.call<float>("sigma"));
    POTHOS_TEST_EQUAL(maxIterations, ldpcDecoder.call<size_t>("maxIterations"));
}

// TODO: can this be paired in a symmetry test?
POTHOS_TEST_BLOCK("/fec/tests", test_ldpc_par_matrix_encoder)
{
    constexpr unsigned int gap = 2;

    const auto testAFilepath = generateTestAFile();
    POTHOS_TEST_TRUE(Poco::File(testAFilepath).exists());

    auto ldpcParMatrixEncoder = Pothos::BlockRegistry::make(
                                    "/fec/ldpc_par_matrix_encoder",
                                    testAFilepath,
                                    gap);
    POTHOS_TEST_EQUAL(
        testAFilepath,
        ldpcParMatrixEncoder.call<std::string>("afilePath"));
    POTHOS_TEST_EQUAL(gap, ldpcParMatrixEncoder.call<unsigned int>("gap"));
}

POTHOS_TEST_BLOCK("/fec/tests", test_ldpc_bit_flip_decoder_G)
{
    const auto matrixType = "G";
    constexpr unsigned int gap = 2;
    constexpr size_t maxIterations = 100;

    const auto testAFilepath = generateGenMatrixTestAFile();
    POTHOS_TEST_TRUE(Poco::File(testAFilepath).exists());

    auto ldpcBitFlipDecoderG = Pothos::BlockRegistry::make(
                                   "/fec/ldpc_bit_flip_decoder",
                                   testAFilepath,
                                   matrixType,
                                   gap,
                                   maxIterations);
    POTHOS_TEST_EQUAL(
        testAFilepath,
        ldpcBitFlipDecoderG.call<std::string>("afilePath"));
    POTHOS_TEST_EQUAL(
        matrixType,
        ldpcBitFlipDecoderG.call<std::string>("matrixType"));
    POTHOS_TEST_EQUAL(
        gap,
        ldpcBitFlipDecoderG.call<unsigned int>("gap"));
    POTHOS_TEST_EQUAL(
        maxIterations,
        ldpcBitFlipDecoderG.call<size_t>("maxIterations"));
}

POTHOS_TEST_BLOCK("/fec/tests", test_ldpc_bit_flip_decoder_H)
{
    const auto matrixType = "H";
    constexpr unsigned int gap = 2;
    constexpr size_t maxIterations = 100;

    const auto testAFilepath = generateTestAFile();
    POTHOS_TEST_TRUE(Poco::File(testAFilepath).exists());

    auto ldpcBitFlipDecoderH = Pothos::BlockRegistry::make(
                                   "/fec/ldpc_bit_flip_decoder",
                                   testAFilepath,
                                   matrixType,
                                   gap,
                                   maxIterations);
    POTHOS_TEST_EQUAL(
        testAFilepath,
        ldpcBitFlipDecoderH.call<std::string>("afilePath"));
    POTHOS_TEST_EQUAL(
        matrixType,
        ldpcBitFlipDecoderH.call<std::string>("matrixType"));
    POTHOS_TEST_EQUAL(
        gap,
        ldpcBitFlipDecoderH.call<unsigned int>("gap"));
    POTHOS_TEST_EQUAL(
        maxIterations,
        ldpcBitFlipDecoderH.call<size_t>("maxIterations"));
}
