

// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#ifndef LEFTOVER_RECORD_H_
#define LEFTOVER_RECORD_H_

#include <string>
using namespace std;

class LeftoverRecord {
 private:
  string date_;
  string meal_;
  string food_name_;
  double qty_in_oz_;
  string leftover_reason_;
  string disposal_mechanism_;
  double cost_;

 public:
  void SetDate(const string &date);
  void SetMeal(const string &meal);
  void SetFoodName(const string &food_name);
  void SetQuantityInOz(double qty_in_oz);
  void SetLeftoverReason(const string &leftover_reason);
  void SetDisposalMechanism(const string &disposal_mechanism);
  void SetCost(double cost);

  string GetDate() const;
  string GetMeal() const;
  string GetFoodName() const;
  double GetQuantityInOz() const;
  string GetLeftoverReason() const;
  string GetDisposalMechanism() const;
  double GetCost() const;

  bool operator==(const LeftoverRecord &other) const;
};

#endif