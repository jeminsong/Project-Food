// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#include "leftover_tracker.h"

#include "leftover_report.h"
using namespace std;

const vector<LeftoverRecord> &LeftoverTracker::GetRecords() const {
  return leftover_records_;
}

LeftoverReport LeftoverTracker::GetLeftoverReport() const {
  return LeftoverReport(leftover_records_);
}

bool LeftoverTracker::AddRecord(const LeftoverRecord &record) {
  for (const auto &existing_record : leftover_records_) {
    if (existing_record == record) {
      return false;
    }
  }
  leftover_records_.push_back(record);
  return true;
}

bool LeftoverTracker::DeleteRecord(const LeftoverRecord &record) {
  for (auto it = leftover_records_.begin(); it != leftover_records_.end();
       it++) {
    if (it->GetDate() == record.GetDate() &&
        it->GetMeal() == record.GetMeal() &&
        it->GetFoodName() == record.GetFoodName() &&
        it->GetQuantityInOz() == record.GetQuantityInOz() &&
        it->GetLeftoverReason() == record.GetLeftoverReason() &&
        it->GetDisposalMechanism() == record.GetDisposalMechanism() &&
        it->GetCost() == record.GetCost()) {
      leftover_records_.erase(it);
      return true;
    }
  }
  return false;
}
