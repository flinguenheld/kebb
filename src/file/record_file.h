#ifndef RECORD_FILE_H
#define RECORD_FILE_H

#include "file.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

struct Record {
  uint16_t mod = 999;
  uint16_t status;
  uint16_t success;
  uint16_t fail;
  uint16_t miss;
  int time_start;
  int time_game;
  uint16_t difficulty;
  uint16_t level;
  uint16_t speed;
  uint16_t nb_target;
};

/*
 * Allow to read/write a file with the previous games data.
 * add() to insert the last game in the array beginning.
 * The constructor reads the file to fill the array.
 * Then the destructor write the file with the (updated) array.
 */
class RecordFile : public File {

public:
  RecordFile();
  ~RecordFile();

  void add(Record r);
  const std::vector<Record> &records();

private:
  uint16_t _nb_max_records;
  std::vector<Record> _records;

  void save() const;
  void read();
};

#endif // !RECORD_FILE_H
