#ifndef LEFTOVER_TRACKER_H_
#define LEFTOVER_TRACKER_H_

// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "leftover_record.h"
#include "leftover_report.h"

class LeftoverTracker {
  public:
  bool AddRecord(const LeftoverRecord& record) {
    for (const auto& live_record : leftover_records_) {
      if (live_record.GetDate() == record.GetDate() &&
          live_record.GetMeal() == record.GetMeal() &&
          live_record.GetFoodName() == record.GetFoodName() &&
          live_record.GetReason() == record.GetReason() &&
          live_record.GetDisposal() == record.GetDisposal() &&
          live_record.GetOunces() == record.GetOunces() &&
          live_record.GetCost() == record.GetCost()) {
          return false; // Not added
      }
    }
    
    std::cout << "Adding new record: " << record.GetDate() << " - " << record.GetFoodName() 
              << " - " << record.GetCost() << " - " << record.GetOunces()
              << " - " << record.GetMeal() << " - " <<  record.GetReason()
              << std::endl;
    leftover_records_.push_back(record);
    return true; // Added
  }


  const std::vector<LeftoverRecord>& GetRecords() const { // check const
  return leftover_records_;
  };


//  LeftoverReport GetLeftoverReport() const { return LeftoverReport(leftover_records_); };
    // ======================= YOUR CODE HERE =======================
      // Write the LeftoverTracker class here. Refer to your class design for the
      // member variables, constructors, and member functions needed.
      //
      // Note: mark functions that do not modify the member variables
      // as const, by writing `const` after the parameter list.
      // Pass objects by const reference when appropriate.
      // Remember that std::string is an object!
      // ===============================================================
 private:
  std::vector<LeftoverRecord> leftover_records_;
};

#endif
