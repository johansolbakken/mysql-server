#ifndef SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
#define SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_

#include <cassert>

#include "my_alloc.h"
#include "sql/item_cmpfunc.h"
#include "sql/iterators/hash_join_buffer.h"
#include "sql/iterators/row_iterator.h"
#include "sql/table.h"
#include "sql/iterators/hash_join_iterator.h"

class Item;
class THD;
struct AccessPath;

class OptimisticHashJoinIterator final : public RowIterator {
 public:
  // TODO: Description of optimistic hash join.
  //
  // Sort iterator must be initialized with source=nullptr.
  OptimisticHashJoinIterator(THD *thd,
                             unique_ptr_destroy_only<RowIterator> hash_join,
                             unique_ptr_destroy_only<RowIterator> sort);

  bool Init() override;

  int Read() override;

  void SetNullRowFlag(bool is_null_row) override {
    m_hash_join->SetNullRowFlag(is_null_row);
    m_sort->SetNullRowFlag(is_null_row);
  }

  void EndPSIBatchModeIfStarted() override {
    m_hash_join->EndPSIBatchModeIfStarted();
    m_sort->EndPSIBatchModeIfStarted();
  }

  void UnlockRow() override {
    // Since both inputs may have been materialized to disk, we cannot unlock
    // them.
  }

  [[nodiscard]] const RowIterator* hash_join_iterator() const { return m_hash_join->real_iterator(); }

private:
  const unique_ptr_destroy_only<RowIterator> m_hash_join;
  const unique_ptr_destroy_only<RowIterator> m_sort;
};

#endif  // SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
