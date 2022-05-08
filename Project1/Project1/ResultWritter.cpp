#include <nlohmann/json.hpp>
#include <fstream>
#include "ResultWritter.h"

ResultWritter* ResultWritter::m_ResultWritter = nullptr;

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

    std::string succesfullString( "Succesfull" + successful ? "true" : "false");

   return generationNumberString + individualNumberString + fitnessString + succesfullString;
}

void ResultWritter::SaveNewValue(const PlacementSelection& placement)
{
    m_Result.push_back(placement);
}

void ResultWritter::WriteResult(int generationNumber, int individualIndex, int fitness, bool succesfull)
{
    std::string fileName = "result/" + GenerateFileName(generationNumber, individualIndex, fitness, succesfull) + ".json";

    std::ofstream file(fileName);

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
