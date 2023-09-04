#include "file_record.h"

RecordFile::RecordFile() : File("records.kebb"), _nb_max_records(15) { read(); }
RecordFile::~RecordFile() { save(); }

/*
 * Add a new record in the array beginnig.
 * And delete old record to limit the amount of data.
 */
void RecordFile::add(Record r) {
  _records.insert(_records.begin(), r);
  while (_records.size() > _nb_max_records)
    _records.pop_back();
}

/*
 * Write the array in the file.
 */
void RecordFile::save() const {

  auto file = std::ofstream(_filename, std::ios::out | std::ios::trunc | std::ios::binary);
  for (const auto &r : _records)
    file.write((char *)&r, sizeof(Record));
}

/*
 * Fill the array with the file's data.
 */
void RecordFile::read() {

  auto file = std::ifstream(_filename, std::ios::in | std::ios::binary);

  while (true) {
    Record new_record;
    file.read((char *)&new_record, sizeof(Record));
    if (new_record.mode != 999)
      _records.emplace_back(new_record);
    else
      break;
  }
}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
const std::vector<Record> &RecordFile::records() { return _records; }
