#ifndef RECORD_FILE_H
#define RECORD_FILE_H

#include "file.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

struct Record {
  uint16_t mod = 999;
  uint16_t success;
  uint16_t fail;
  uint16_t miss;
  uint16_t time;
  uint16_t difficulty;
  uint16_t level;
  uint16_t speed;
  uint16_t nb_target;
};

/*
 * Allow to read/write a file with the previous games data.
 * Read() to fill the table.
 * add() to insert the last game in the table beginning.
 * save() to write the table in the file.
 */
class RecordFile : public File {

public:
  RecordFile();
  ~RecordFile();

  void add(Record r);
  void save() const;
  void read();

  std::vector<Record> &records();

private:
  uint16_t _nb_max_records;
  std::vector<Record> _records;
};

#endif // !RECORD_FILE_H
