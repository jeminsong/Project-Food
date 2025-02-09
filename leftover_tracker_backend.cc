#include "leftover_tracker_backend.h"

#include <filesystem>

#include "leftover_record.h"
#include "leftover_report.h"
#include "leftover_tracker.h"
#include "server_utils/rapidjson/document.h"      // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"
using namespace std;

// Util function to convert a LeftoverRecord class object into a serialized
// JSON object.
void SerializeLeftoverRecordToJSON(
    const LeftoverRecord &record,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->String("date_");  // DO NOT MODIFY
  string date;
  date = record.GetDate();
  writer->String(date.c_str());

  writer->String("meal_");  // DO NOT MODIFY
  string meal;
  meal = record.GetMeal();
  writer->String(meal.c_str());

  writer->String("food_name_");  // DO NOT MODIFY
  string food_name;
  food_name = record.GetFoodName();
  writer->String(food_name.c_str());

  writer->String("qty_in_oz_");
  double quantity;
  quantity = record.GetQuantityInOz();

  writer->Double(quantity);

  writer->String("leftover_reason_");  // DO NOT MODIFY
  string leftover_reason;

  leftover_reason = record.GetLeftoverReason();

  writer->String(leftover_reason.c_str());

  writer->String("disposal_mechanism_");  // DO NOT MODIFY
  string disposal_mechanism;
  disposal_mechanism = record.GetDisposalMechanism();
  writer->String(disposal_mechanism.c_str());

  writer->String("cost_");  // DO NOT MODIFY
  double cost;
  cost = record.GetCost();
  writer->Double(cost);

  writer->EndObject();
}

// Util function to convert a serialized JSON object in to a LeftoverRecord
// class object.
LeftoverRecord DeserializeLeftoverRecordFromJSON(
    const rapidjson::Value &json_obj) {
  LeftoverRecord record;

  record.SetDate(json_obj["date_"].GetString());

  record.SetMeal(json_obj["meal_"].GetString());

  record.SetFoodName(json_obj["food_name_"].GetString());

  record.SetQuantityInOz(json_obj["qty_in_oz_"].GetDouble());

  record.SetLeftoverReason(json_obj["leftover_reason_"].GetString());

  record.SetDisposalMechanism(json_obj["disposal_mechanism_"].GetString());

  record.SetCost(json_obj["cost_"].GetDouble());
  return record;
}

// Util function to convert a LeftoverRecord class object into a Crow JSON
// object.
crow::json::wvalue LeftoverRecordToCrowJSON(const LeftoverRecord &record) {
  crow::json::wvalue record_json({});

  string date;
  date = record.GetDate();
  record_json["date"] = date;

  string meal;
  meal = record.GetMeal();
  record_json["meal"] = meal;

  string food_name;
  food_name = record.GetFoodName();
  record_json["food_name"] = food_name;

  double quantity;
  quantity = record.GetQuantityInOz();
  record_json["qty_in_oz"] = quantity;

  string leftover_reason;
  leftover_reason = record.GetLeftoverReason();
  record_json["leftover_reason"] = leftover_reason;

  string disposal_mechanism;
  disposal_mechanism = record.GetDisposalMechanism();
  record_json["disposal_mechanism"] = disposal_mechanism;

  double cost;
  cost = record.GetCost();
  record_json["cost"] = cost;

  return record_json;
}

// Util function to convert a LeftoverReport object into a serialized
// JSON object.
crow::json::wvalue LeftoverReportToCrowJSON(LeftoverReport &report) {
  crow::json::wvalue report_json({});

  vector<string> most_common_disposal_mechanisms{};
  most_common_disposal_mechanisms = report.MostCommonDisposalMechanisms();
  report_json["most_common_disposal_mechanism_"] =
      most_common_disposal_mechanisms;

  vector<string> most_common_leftovers{};
  most_common_leftovers = report.MostCommonLeftover();
  report_json["most_common_leftover_"] = most_common_leftovers;

  vector<string> most_common_leftover_reasons{};
  most_common_leftover_reasons = report.MostCommonLeftoverReasons();
  report_json["most_common_leftover_reason_"] = most_common_leftover_reasons;

  vector<string> most_costly_leftover_producing_meals{};
  most_costly_leftover_producing_meals =
      report.MostCostlyLeftoverProducingMeals();
  report_json["most_leftover_producing_meal_"] =
      most_costly_leftover_producing_meals;

  vector<string> suggested_strategies_to_reduce_leftover{};
  suggested_strategies_to_reduce_leftover =
      report.SuggestLeftoverReductionStrategies();
  report_json["suggested_strategies_to_reduce_leftover_"] =
      suggested_strategies_to_reduce_leftover;

  double total_cost_of_leftover = -9999.0;
  total_cost_of_leftover = report.TotalCostOfLeftover();
  report_json["total_cost_of_leftover_"] = total_cost_of_leftover;

  return report_json;
}

// Util function to convert a crow query string into a LeftoverRecord class
// object.
LeftoverRecord QueryStringToLeftoverRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record{};

  record.SetDate(query_string.get("date"));

  record.SetMeal(query_string.get("meal"));

  record.SetFoodName(query_string.get("food_name"));

  record.SetQuantityInOz(stod(query_string.get("qty_in_oz")));

  record.SetLeftoverReason(query_string.get("leftover_reason"));

  record.SetDisposalMechanism(query_string.get("disposal_mechanism"));

  record.SetCost(stod(query_string.get("cost")));
  return record;
}

bool LeftoverTrackerBackend::LoadRecordsFromJSONFile() {
  ifstream records_file{leftover_records_filepath_};
  if (!records_file.is_open()) {
    filesystem::remove(leftover_records_filepath_);
    return false;
  }

  stringstream buffer;
  buffer << records_file.rdbuf();

  string s = buffer.str();
  rapidjson::Document doc;

  if (s.empty()) {
    filesystem::remove(leftover_records_filepath_);
    return false;
  }

  string validJson(s);

  bool doc_parse_error = doc.Parse(validJson.c_str()).HasParseError();
  if (doc_parse_error || !doc.IsArray()) {
    filesystem::remove(leftover_records_filepath_);
    return false;
  }

  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End();
       ++itr) {
    LeftoverRecord record = DeserializeLeftoverRecordFromJSON(*itr);
    tracker_.AddRecord(record);
  }
  records_file.close();
  return true;
}

bool LeftoverTrackerBackend::WriteRecordsToJSONFile() const {
  ofstream records_file{leftover_records_filepath_};
  // Get the records from leftover_tracker_, convert to JSON and
  // save to file.
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartArray();

  const vector<LeftoverRecord> &records = tracker_.GetRecords();

  for (LeftoverRecord record : records) {
    SerializeLeftoverRecordToJSON(record, &writer);
  }
  writer.EndArray();

  records_file << ss.GetString();

  records_file.flush();
  records_file.close();
  return true;
}

crow::json::wvalue LeftoverTrackerBackend::AddRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool add_result = false;
  add_result = tracker_.AddRecord(record);
  status["success"] = add_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::DeleteRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool delete_result = false;

  delete_result = tracker_.DeleteRecord(record);
  status["success"] = delete_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::GetRecords() const {
  vector<LeftoverRecord> records;
  records = tracker_.GetRecords();
  const vector<LeftoverRecord> &const_records = records;

  crow::json::wvalue records_json({});
  records_json["num_records"] = records.size();

  vector<crow::json::wvalue> record_json_vector;
  for (const LeftoverRecord &record : records) {
    record_json_vector.push_back(LeftoverRecordToCrowJSON(record));
  }
  records_json["record_array"] = move(record_json_vector);
  return records_json;
}

crow::json::wvalue LeftoverTrackerBackend::GetLeftoverReport() const {
  LeftoverReport generated_report = tracker_.GetLeftoverReport();

  return LeftoverReportToCrowJSON(generated_report);
}