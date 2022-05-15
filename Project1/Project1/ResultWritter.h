#pragma once

#include<PlacementSelection.h>

#include <vector>
#include <string>

class ResultWritter
{
public:
    static ResultWritter* GetInstanse();


    void SaveNewValue(const PlacementSelection& placement);
    void CleanResult() { m_Result.clear(); }
    void WriteResult(int generationNumber, int individualIndex, int fitness, bool succesfull);
    const std::vector<PlacementSelection> GetPlacementsBoxes() const { return m_Result; }

private:
    std::string  GenerateFileName(int generationNumber, int individualIndex, int fitness, bool succesfull);

    static ResultWritter* m_ResultWritter;

    std::vector<PlacementSelection> m_Result;
    std::string m_FileName;

    ResultWritter() = default;
    ~ResultWritter() = default;
};