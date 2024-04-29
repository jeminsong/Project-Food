// Jemin Song
// CPSC 121L-02
// 4/18/2024
// jeminsong0119@csu.fullerton.edu
// @jeminsong

#ifndef LEFTOVER_TRACKER_H_
#define LEFTOVER_TRACKER_H_

#include <vector>

#include "leftover_record.h"
#include "leftover_report.h"
using namespace std;

class LeftoverTracker {
 public:
  LeftoverTracker() {}
  bool AddRecord(const LeftoverRecord &record);
  bool DeleteRecord(const LeftoverRecord &record);
  const vector<LeftoverRecord> &GetRecords() const;
  LeftoverReport GetLeftoverReport() const;

 private:
  vector<LeftoverRecord> leftover_records_;
};

#endif
