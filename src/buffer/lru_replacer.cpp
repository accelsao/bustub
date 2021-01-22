//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <algorithm>

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) { this->num_pages = num_pages; }

LRUReplacer::~LRUReplacer() {
  this->lru_replacer.clear();
  this->num_pages = 0;
};

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  if (LRUReplacer::Size() == 0) {
    return false;
  }
  *frame_id = this->lru_replacer.front();
  this->lru_replacer.pop_front();
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  auto it = std::find(this->lru_replacer.begin(), this->lru_replacer.end(), frame_id);
  if (it != this->lru_replacer.end()) {
    this->lru_replacer.erase(it);
  }
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  auto it = std::find(this->lru_replacer.begin(), this->lru_replacer.end(), frame_id);
  if (it == this->lru_replacer.end()) {
    this->lru_replacer.push_back(frame_id);

    if (LRUReplacer::Size() > this->num_pages) {
      int value;
      LRUReplacer::Victim(&value);
    }
  }
}

size_t LRUReplacer::Size() { return this->lru_replacer.size(); }

}  // namespace bustub
