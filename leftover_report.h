// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#ifndef LEFTOVER_REPORT_H
#define LEFTOVER_REPORT_H

#include <map>
#include <string>
#include <vector>

#include "leftover_record.h"
using namespace std;

class LeftoverReport {
 public:
  LeftoverReport(const vector<LeftoverRecord> &leftover_records);

  vector<string> MostCommonLeftover() const;
  vector<string> MostCostlyLeftoverProducingMeals() const;
  double TotalCostOfLeftover() const;
  vector<string> MostCommonLeftoverReasons();
  vector<string> MostCommonDisposalMechanisms() const;
  vector<string> SuggestLeftoverReductionStrategies() const;

 private:
  const vector<LeftoverRecord> &leftover_records_;
  vector<string> most_common_leftover_;
  vector<string> most_costly_leftover_producing_meals_;
  double total_cost_of_leftovers_;
  vector<string> most_common_leftover_reasons_;
  vector<string> most_common_disposal_mechanisms_;
  vector<string> suggested_strategies_to_reduce_leftovers_;
};

#endif
