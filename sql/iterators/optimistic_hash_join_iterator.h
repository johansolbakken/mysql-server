#ifndef SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
#define SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_

#include <stdio.h>
#include <cassert>
#include <cstdint>
#include <span>
#include <vector>

#include "my_alloc.h"
#include "my_table_map.h"
#include "prealloced_array.h"
#include "sql/item_cmpfunc.h"
#include "sql/iterators/hash_join_buffer.h"
#include "sql/iterators/row_iterator.h"
#include "sql/join_type.h"
#include "sql/mem_root_array.h"
#include "sql/table.h"
#include "sql/iterators/hash_join_iterator.h"

class Item;
class THD;
struct AccessPath;

class OptimisticHashJoinIterator final : public RowIterator {
 public:
  OptimisticHashJoinIterator(THD *thd, unique_ptr_destroy_only<RowIterator> hash_join);

  bool Init() override;

  int Read() override;

  void SetNullRowFlag(bool is_null_row) override {
    // Don't call this after Init() but before calling Read() for the first
    // time. Init() may have loaded a row that is (partially or fully) a null
    // row, so resetting the null row flags is incorrect.
    /*assert(!m_probe_row_read || m_state == State::END_OF_ROWS);*/
    /*m_build_input->SetNullRowFlag(is_null_row);*/
    /*m_probe_input->SetNullRowFlag(is_null_row);*/
    m_hash_join->SetNullRowFlag(is_null_row);
  }

  void EndPSIBatchModeIfStarted() override {
    /*m_build_input->EndPSIBatchModeIfStarted();*/
    /*m_probe_input->EndPSIBatchModeIfStarted();*/
    m_hash_join->EndPSIBatchModeIfStarted();
  }

  void UnlockRow() override {
    // Since both inputs may have been materialized to disk, we cannot unlock
    // them.
  }

  RowIterator *real_iterator() override { return this; }
  const RowIterator *real_iterator() const override { return this; }
  /*int ChunkCount() { return m_chunk_files_on_disk.size(); }*/
  /**/
  /*[[nodiscard]] bool WentOnDisk() const { return m_hash_join_type == HashJoinType::SPILL_TO_DISK; }*/
  /*[[nodiscard]] bool WasInMemory() const { return m_hash_join_type == HashJoinType::IN_MEMORY; }*/
  /**/
private:
//  const unique_ptr_destroy_only<RowIterator> m_build_input;
//  const unique_ptr_destroy_only<RowIterator> m_probe_input;
  const unique_ptr_destroy_only<RowIterator> m_hash_join;
};

#endif  // SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
