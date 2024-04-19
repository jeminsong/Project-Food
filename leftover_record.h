#ifndef LEFTOVER_RECORD_H_
#define LEFTOVER_RECORD_H_

// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <string>



class LeftoverRecord {
 public:
  LeftoverRecord() {};
  LeftoverRecord(const std::string& date, const std::string& meal,
                 const std::string& name, const std::string& disposal,
                 const std::string& reason, const double& oz,
                 const double& cost) : date_(date), meal_(meal), food_name_(name),
                 disposal_mechanism_(disposal), leftover_reason_(reason),
                 qty_in_oz_(oz), cost_(cost) {};

  void SetDate(const std::string& date) { date_ = date; }
  void SetMeal(const std::string& meal) { meal_ = meal; }
  void SetFoodName(const std::string& name) { food_name_ = name; }
  void SetDisposal(const std::string& disposal) { disposal_mechanism_ = disposal; }
  void SetReason(const std::string& reason) { leftover_reason_ = reason; }
  void SetOunces(const double& oz) { qty_in_oz_ = oz; }
  void SetCost(const double& cost) { cost_ = cost; }

  std::string GetDate() const { return date_; };
  std::string GetMeal() const { return meal_; };
  std::string GetFoodName() const { return food_name_; };
  std::string GetReason() const { return leftover_reason_; };
  std::string GetDisposal() const { return disposal_mechanism_; };
  double GetOunces() const { return qty_in_oz_; };
  double GetCost() const { return cost_; };

 private:
  std::string date_;
  std::string meal_;
  std::string food_name_;
  std::string leftover_reason_;
  std::string disposal_mechanism_;
  double qty_in_oz_;
  double cost_;
};

#endif