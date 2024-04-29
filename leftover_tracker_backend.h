#ifndef LEFTOVER_TRACKER_BACKEND_H_
#define LEFTOVER_TRACKER_BACKEND_H_

#include <string>

#include "leftover_tracker.h"
#include "server_utils/crow_all.h"
using namespace std;

class LeftoverTrackerBackend {
 public:
  LeftoverTrackerBackend(const string &leftover_records_filepath)
      : leftover_records_filepath_{leftover_records_filepath} {}

  bool LoadRecordsFromJSONFile();

  bool WriteRecordsToJSONFile() const;

  crow::json::wvalue AddRecord(const crow::query_string &query_string);

  crow::json::wvalue DeleteRecord(const crow::query_string &query_string);

  crow::json::wvalue GetRecords() const;

  crow::json::wvalue GetLeftoverReport() const;

 private:
  const string &leftover_records_filepath_;
  LeftoverTracker tracker_;
};
#endif
