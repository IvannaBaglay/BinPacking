
#define _CRT_SECURE_NO_WARNINGS

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream> // stringstream
#include <stdio.h>

#include "ResultWritter.h"




ResultWritter* ResultWritter::m_ResultWritter = nullptr;

namespace fs = std::filesystem;
using json = nlohmann::json;

ResultWritter* ResultWritter::GetInstanse()
{
    if (m_ResultWritter == nullptr)
    {
        m_ResultWritter = new ResultWritter();
    }

    return m_ResultWritter;
}

std::string ResultWritter::GenerateFileName(int generationNumber, int individualIndex, int fitness, bool successful)
{
    std::string generationNumberString ( "Generation" + std::to_string(generationNumber));
    std::string individualNumberString ( "Individual" + std::to_string(individualIndex));
    std::string fitnessString( "Fitness" + std::to_string(fitness));

    std::string succesfullstr (successful ? "true" : "false");

    std::string succesfullString("Succesfull" + succesfullstr);

   return generationNumberString + individualNumberString + fitnessString + succesfullString;
}

std::string ResultWritter::GenerateDataTimeFolder()
{

    return m_StartDataTime;

}

void ResultWritter::SaveNewValue(const PlacementSelection& placement)
{
    m_Result.push_back(placement);
}

void ResultWritter::WriteResult(int generationNumber, int individualIndex, int fitness, bool succesfull)
{

    std::string fileNameGeneration = GenerateFileName(generationNumber, individualIndex, fitness, succesfull) + ".json";
    std::string fileName = "result/" + m_StartDataTime;

    if (!fs::is_directory(fileName) || !fs::exists(fileName)) { // Check if src folder exists
        fs::create_directory(fileName); // create src folder
    }

    std::string PathfileName = fileName.c_str() + fileNameGeneration;

    std::ofstream file(PathfileName);

    json jResultArray = json::array();

    json jsonValue;

    for (const auto& placement : m_Result)
    {
        jsonValue["index"] = placement.index;
        jsonValue["container"] = placement.containerIndex;
        jsonValue["coordination"] = { placement.coordination.x, placement.coordination.y, placement.coordination.z };
        jsonValue["size"] = { placement.size.lenght_x, placement.size.width_y, placement.size.height_z };

        jResultArray.push_back(jsonValue);
    }

    file << std::setw(4) << jResultArray << std::endl;
}

void ResultWritter::SaveDataTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    errno_t buf;

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y%m%d_%H%M/", localtime(&now));

    m_StartDataTime = s;

    //return s;
    //return ss.str();
}
