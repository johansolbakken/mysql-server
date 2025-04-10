#ifndef SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
#define SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_

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
    if (!m_hash_join_is_moved) {
      m_hash_join->SetNullRowFlag(is_null_row);
    } else {
      m_sort->SetNullRowFlag(is_null_row);
    }
  }

  void EndPSIBatchModeIfStarted() override {
    if (!m_hash_join_is_moved) {
      m_hash_join->EndPSIBatchModeIfStarted();
    } else {
      m_sort->EndPSIBatchModeIfStarted();
    }
  }

  void UnlockRow() override {
    // Since both inputs may have been materialized to disk, we cannot unlock
    // them.
  }

  [[nodiscard]] const HashJoinIterator* hash_join_iterator() const noexcept;
  [[nodiscard]] const SortingIterator* sorting_iterator() const noexcept;

  [[nodiscard]] bool WentOnDisk() const noexcept;
  [[nodiscard]] double BufferFillRatio() const noexcept;

private:
  bool m_hash_join_is_moved = false;
  unique_ptr_destroy_only<RowIterator> m_hash_join;
  unique_ptr_destroy_only<RowIterator> m_sort;
  unique_ptr_destroy_only<RowIterator>* m_read_iterator = nullptr;
};

#endif  // SQL_ITERATORS_OPTIMISTIC_HASH_JOIN_ITERATOR_H_
