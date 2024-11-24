#include "Facility.h"

// FacilityType
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, 
                           const int lifeQuality_score, const int economy_score, const int environment_score)
    : name(name), category(category), price(price), 
      lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score) {}

const string &FacilityType::getName() const {
    return name; // Placeholder
}

int FacilityType::getCost() const {
    return price; // Placeholder
}

int FacilityType::getLifeQualityScore() const {
    return lifeQuality_score; // Placeholder
}

int FacilityType::getEnvironmentScore() const {
    return environment_score; // Placeholder
}

int FacilityType::getEconomyScore() const {
    return economy_score; // Placeholder
}

FacilityCategory FacilityType::getCategory() const {
    return category; // Placeholder
}

// Facility
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, 
                   const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), 
      settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price) {}

Facility::Facility(FacilityType &type, const string &settlementName)
    : FacilityType(type), settlementName(settlementName), 
      status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost()) {}

const string &Facility::getSettlementName() const {
    return settlementName; // Placeholder
}

const int Facility::getTimeLeft() const {
    return timeLeft; // Placeholder
}

FacilityStatus Facility::step() {
    return status; // Placeholder
}

void Facility::setStatus(FacilityStatus status) {
    this->status = status; // Placeholder
}

const FacilityStatus& Facility::getStatus() const {
    return status; // Placeholder
}

const string Facility::toString() const {
    return ""; // Placeholder
}
