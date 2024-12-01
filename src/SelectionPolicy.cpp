#include "SelectionPolicy.h"

// NaiveSelection Constructor
NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}

// NaiveSelection Methods
const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    return facilitiesOptions.at(lastSelectedIndex);
}

// Need to implament according to the requirements of PrintActionLog in Actions
const string NaiveSelection::toString() const
{
    return "SelectionPolicy: nve";
}

NaiveSelection *NaiveSelection::clone() const
{
    return new NaiveSelection(*this);
}

// BalancedSelection Constructor
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

// BalancedSelection Methods
const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    // Max value
    int minDistance = 2147483647;
    int minDistanceIndex = 0;
    for (unsigned int i = 0; i < facilitiesOptions.size(); i++)
    {
        int distance = computeDistance(facilitiesOptions[i]);
        if (distance < minDistance)
        {
            minDistance = distance;
            minDistanceIndex = i;
        }
    }
    LifeQualityScore += facilitiesOptions[minDistanceIndex].getLifeQualityScore();
    EconomyScore += facilitiesOptions[minDistanceIndex].getEconomyScore();
    EnvironmentScore += facilitiesOptions[minDistanceIndex].getEnvironmentScore();
    return facilitiesOptions[minDistanceIndex];
}

// Computes the abs max distance
int BalancedSelection::computeDistance(const FacilityType &facility)
{
    int distance = 0;
    int minScore = 0;
    int maxScore = 0;
    int tempLifeQualityScore = LifeQualityScore + facility.getLifeQualityScore();
    int tempEconomyScore = EconomyScore + facility.getEconomyScore();
    int tempEnvScore = EnvironmentScore + facility.getEnvironmentScore();
    minScore = min(tempLifeQualityScore, min(tempEconomyScore, tempEnvScore));
    maxScore = max(tempLifeQualityScore, max(tempEconomyScore, tempEnvScore));
    distance = maxScore - minScore;

    return distance;
}

// Need to implament according to the requirements of PrintActionLog in Actions
const string BalancedSelection::toString() const
{
    return "SelectionPolicy: bal";
}

BalancedSelection *BalancedSelection::clone() const
{
    return new BalancedSelection(*this);
}

// EconomySelection Constructor
EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

// EconomySelection Methods
const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    if (lastSelectedIndex >= facilitiesOptions.size())
    {
        lastSelectedIndex = 0;
    }
    for (unsigned int i = lastSelectedIndex; i < facilitiesOptions.size(); i++)
    {
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY)
        {
            lastSelectedIndex = i;
            break;
        }
    }

    return facilitiesOptions[lastSelectedIndex];
}
// Need to implament according to the requirements of PrintActionLog in Actions
const string EconomySelection::toString() const
{
    return "SelectionPolicy: eco";
}

EconomySelection *EconomySelection::clone() const
{
    return new EconomySelection(*this);
}

// SustainabilitySelection Constructor
SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(0) {}

// SustainabilitySelection Methods
const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex++;
    if (lastSelectedIndex >= facilitiesOptions.size())
    {
        lastSelectedIndex = 0;
    }
    for (unsigned int i = lastSelectedIndex; i < facilitiesOptions.size(); i++)
    {
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ENVIRONMENT)
        {
            lastSelectedIndex = i;
            break;
        }
    }

    return facilitiesOptions[lastSelectedIndex];
}

// Need to implament according to the requirements of PrintActionLog in Actions
const string SustainabilitySelection::toString() const
{
    return "SelectionPolicy: env";
}

SustainabilitySelection *SustainabilitySelection::clone() const
{
    return new SustainabilitySelection(*this);
}
