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
  OptimisticHashJoinIterator(THD *thd, unique_ptr_destroy_only<RowIterator> build_input,
                         const Prealloced_array<TABLE *, 4> &build_input_tables,
                         double estimated_build_rows,
                         unique_ptr_destroy_only<RowIterator> probe_input,
                         const Prealloced_array<TABLE *, 4> &probe_input_tables,
                         bool store_rowids, table_map tables_to_get_rowid_for,
                         size_t max_memory_available,
                         const std::vector<HashJoinCondition> &join_conditions,
                         bool allow_spill_to_disk, JoinType join_type,
                         const Mem_root_array<Item *> &extra_conditions,
                         std::span<AccessPath *> single_row_index_lookups,
                         HashJoinInput first_input, bool probe_input_batch_mode,
                         uint64_t *hash_table_generation);

  bool Init() override;

  int Read() override;

  void SetNullRowFlag(bool is_null_row) override {
    // Don't call this after Init() but before calling Read() for the first
    // time. Init() may have loaded a row that is (partially or fully) a null
    // row, so resetting the null row flags is incorrect.
    /*assert(!m_probe_row_read || m_state == State::END_OF_ROWS);*/
    /*m_build_input->SetNullRowFlag(is_null_row);*/
    /*m_probe_input->SetNullRowFlag(is_null_row);*/
  }

  void EndPSIBatchModeIfStarted() override {
    /*m_build_input->EndPSIBatchModeIfStarted();*/
    /*m_probe_input->EndPSIBatchModeIfStarted();*/
  }

  void UnlockRow() override {
    // Since both inputs may have been materialized to disk, we cannot unlock
    // them.
  }

  /*int ChunkCount() { return m_chunk_files_on_disk.size(); }*/
  /**/
  /*[[nodiscard]] bool WentOnDisk() const { return m_hash_join_type == HashJoinType::SPILL_TO_DISK; }*/
  /*[[nodiscard]] bool WasInMemory() const { return m_hash_join_type == HashJoinType::IN_MEMORY; }*/
  /**/
private:
//  const unique_ptr_destroy_only<RowIterator> m_build_input;
//  const unique_ptr_destroy_only<RowIterator> m_probe_input;
};

#endif  // SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
