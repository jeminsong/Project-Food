// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#include "leftover_record.h"
using namespace std;

bool LeftoverRecord::operator==(const LeftoverRecord &other) const {
  if (date_ == other.date_ && meal_ == other.meal_ &&
      food_name_ == other.food_name_ && qty_in_oz_ == other.qty_in_oz_ &&
      leftover_reason_ == other.leftover_reason_ &&
      disposal_mechanism_ == other.disposal_mechanism_ &&
      cost_ == other.cost_) {
    return true;
  }
  return false;
}

void LeftoverRecord::SetDate(const string &date) { date_ = date; }

void LeftoverRecord::SetMeal(const string &meal) { meal_ = meal; }

void LeftoverRecord::SetFoodName(const string &food_name) {
  food_name_ = food_name;
}

void LeftoverRecord::SetQuantityInOz(double qty_in_oz) {
  qty_in_oz_ = qty_in_oz;
}

void LeftoverRecord::SetLeftoverReason(const string &leftover_reason) {
  leftover_reason_ = leftover_reason;
}

void LeftoverRecord::SetDisposalMechanism(const string &disposal_mechanism) {
  disposal_mechanism_ = disposal_mechanism;
}

void LeftoverRecord::SetCost(double cost) { cost_ = cost; }

// Getters
string LeftoverRecord::GetDate() const { return date_; }

string LeftoverRecord::GetMeal() const { return meal_; }

string LeftoverRecord::GetFoodName() const { return food_name_; }

double LeftoverRecord::GetQuantityInOz() const { return qty_in_oz_; }

string LeftoverRecord::GetLeftoverReason() const { return leftover_reason_; }

string LeftoverRecord::GetDisposalMechanism() const {
  return disposal_mechanism_;
}

double LeftoverRecord::GetCost() const { return cost_; }
