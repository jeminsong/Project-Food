// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#include "leftover_report.h"

#include <algorithm>
#include <string>
#include <unordered_map>

#include "leftover_record.h"
using namespace std;

LeftoverReport::LeftoverReport(const vector<LeftoverRecord> &leftover_records)
    : leftover_records_(leftover_records) {}

vector<string> LeftoverReport::MostCommonLeftover() const {
  map<string, int> leftovers;
  vector<string> most_common_leftover;
  int leftover_frequency = 0;
  for (LeftoverRecord record : leftover_records_) {
    string food_name = record.GetFoodName();
    if (leftovers.find(food_name) == leftovers.end()) {
      leftovers[food_name] = 1;
    } else {
      leftovers[food_name] += 1;
    }
    if (leftovers[food_name] > leftover_frequency) {
      leftover_frequency = leftovers[food_name];
    }
  }
  for (pair<string, int> pair : leftovers) {
    if (pair.second == leftover_frequency) {
      most_common_leftover.push_back(pair.first);
    }
  }
  return most_common_leftover;
}
vector<string> LeftoverReport::MostCostlyLeftoverProducingMeals() const {
  map<string, double> costly_meals;
  vector<string> most_costly_leftover;
  double mostly_costly = 0.0;
  for (LeftoverRecord record : leftover_records_) {
    string meal = record.GetMeal();
    if (costly_meals.find(meal) == costly_meals.end()) {
      costly_meals[meal] = record.GetCost();
    } else {
      if (record.GetCost() > costly_meals[meal]) {
        costly_meals[meal] = record.GetCost();
      }
    }
    if (costly_meals[meal] > mostly_costly) {
      mostly_costly = costly_meals[meal];
    }
  }
  for (pair<string, double> pair : costly_meals) {
    if (pair.second == mostly_costly) {
      most_costly_leftover.push_back(pair.first);
    }
  }
  return most_costly_leftover;
}

double LeftoverReport::TotalCostOfLeftover() const {
  double totalCost = 0.0;
  for (const auto &record : leftover_records_) {
    totalCost += record.GetCost();
  }
  return totalCost;
}

vector<string> LeftoverReport::MostCommonLeftoverReasons() {
  map<string, int> common_leftover;
  vector<string> most_common_leftover_reasons;
  int most_common = 0;

  for (LeftoverRecord record : leftover_records_) {
    string reasons = record.GetLeftoverReason();
    if (common_leftover.find(reasons) == common_leftover.end()) {
      common_leftover[reasons] = 1;
    } else {
      common_leftover[reasons] += 1;
    }
    if (common_leftover[reasons] > most_common) {
      most_common = common_leftover[reasons];
    }
  }

  for (pair<string, int> pair : common_leftover) {
    if (pair.second == most_common) {
      most_common_leftover_reasons.push_back(pair.first);
    }
  }
  most_common_leftover_reasons_ = most_common_leftover_reasons;
  return most_common_leftover_reasons;
}

vector<string> LeftoverReport::MostCommonDisposalMechanisms() const {
  map<string, int> most_common_disposal;
  vector<string> most_common_disposal_mechanisms;
  int most_disposal = 0;

  for (LeftoverRecord record : leftover_records_) {
    string mechanisms = record.GetDisposalMechanism();
    if (most_common_disposal.find(mechanisms) == most_common_disposal.end()) {
      most_common_disposal[mechanisms] = 1;
    } else {
      most_common_disposal[mechanisms] += 1;
    }
    if (most_common_disposal[mechanisms] > most_disposal) {
      most_disposal = most_common_disposal[mechanisms];
    }
  }

  for (pair<string, int> pair : most_common_disposal) {
    if (pair.second == most_disposal) {
      most_common_disposal_mechanisms.push_back(pair.first);
    }
  }
  return most_common_disposal_mechanisms;
}

vector<string> LeftoverReport::SuggestLeftoverReductionStrategies() const {
  vector<string> strategies;
  vector<string> common_reasons = most_common_leftover_reasons_;

  if (common_reasons.empty()) {
    return strategies;
  }

  for (const string &reason : common_reasons) {
    if (reason == "Expired") {
      if (find(strategies.begin(), strategies.end(),
               "Donate before expiration") == strategies.end()) {
        strategies.push_back("Donate before expiration");
      }
    }
    if (reason == "Tastes bad") {
      if (find(strategies.begin(), strategies.end(), "Try buying less food") ==
          strategies.end()) {
        strategies.push_back("Buy less food");
      }
    }
    if (reason == "Too much left overs") {
      if (find(strategies.begin(), strategies.end(), "Buy less food") ==
          strategies.end()) {
        strategies.push_back("Buy less food");
      }
      if (find(strategies.begin(), strategies.end(), "Cook small servings") ==
          strategies.end()) {
        strategies.push_back("Cook small servings");
      }
    }
  }
  if (find(strategies.begin(), strategies.end(), "Donate before expiration") ==
      strategies.end()) {
    strategies.push_back("Recycle left overs");
  }
  return strategies;
}