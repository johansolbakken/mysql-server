#include "optimistic_hash_join_iterator.h"

OptimisticHashJoinIterator::OptimisticHashJoinIterator(THD *thd, unique_ptr_destroy_only<RowIterator> build_input,
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
                         uint64_t *hash_table_generation) : RowIterator(thd) {

}




bool OptimisticHashJoinIterator::Init(){
  assert(false && "not implemented");
  return false;
}

int OptimisticHashJoinIterator::Read(){
  assert(false && "not implemented");
  return 0;
}

