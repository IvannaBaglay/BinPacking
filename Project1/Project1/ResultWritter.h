#pragma once

#include<PlacementSelection.h>

#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <time.h>
#include <filesystem>

class ResultWritter
{
public:
    static ResultWritter* GetInstanse();


    void SaveNewValue(const PlacementSelection& placement);
    void CleanResult() { m_Result.clear(); }
    void WriteResult(int generationNumber, int individualIndex, int fitness, bool succesfull);
    const std::vector<PlacementSelection> GetPlacementsBoxes() const { return m_Result; }
    void SaveDataTime();

private:
    std::string  GenerateFileName(int generationNumber, int individualIndex, int fitness, bool succesfull);
    std::string GenerateDataTimeFolder();
    static ResultWritter* m_ResultWritter;

    std::vector<PlacementSelection> m_Result;
    std::string m_FileName;

    std::chrono::system_clock startTime;
    std::chrono::system_clock EndTime;

    std::string m_StartDataTime;

    ResultWritter() = default;
    ~ResultWritter() = default;
};