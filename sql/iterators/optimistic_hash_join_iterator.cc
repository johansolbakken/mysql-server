#include "optimistic_hash_join_iterator.h"
#include "sql/iterators/hash_join_iterator.h"
#include "sql/iterators/sorting_iterator.h"

OptimisticHashJoinIterator::OptimisticHashJoinIterator(
    THD *thd, unique_ptr_destroy_only<RowIterator> hash_join,
    unique_ptr_destroy_only<RowIterator> sort)
    : RowIterator(thd),
      m_hash_join(std::move(hash_join)),
      m_sort(std::move(sort)) {}

bool OptimisticHashJoinIterator::Init() {
  if (m_hash_join->Init()) {
    return true;
  }

  m_read_iterator = &m_hash_join;

  // The hash join can spill to disk if the estimates are completely wrong.
  if (WentOnDisk()) {
    auto* sort = down_cast<SortingIterator *>(m_sort->real_iterator());
    sort->DoNotInitSource();
    sort->SetSourceIterator(std::move(m_hash_join));
    m_hash_join_is_moved = true;

    if (sort->Init()) {
      return true;
    }

    m_read_iterator = &m_sort;
  }

  return false;
}

int OptimisticHashJoinIterator::Read(){
  if (m_read_iterator == nullptr) {
    return 0;
  }

  return (*m_read_iterator)->Read();
}

[[nodiscard]] const HashJoinIterator* OptimisticHashJoinIterator::hash_join_iterator() const noexcept {
  if (m_hash_join_is_moved) {
    return down_cast<const HashJoinIterator*>(
        sorting_iterator()->SourceIterator()->real_iterator());
  }

  return down_cast<const HashJoinIterator*>(m_hash_join->real_iterator());
}

[[nodiscard]] const SortingIterator* OptimisticHashJoinIterator::sorting_iterator() const noexcept {
  return down_cast<const SortingIterator*>(m_sort->real_iterator());
}

bool OptimisticHashJoinIterator::WentOnDisk() const noexcept {
  // We have moved the hash join into the sort if we have
  // gone on disk.
  if (m_hash_join_is_moved) {
    return true;
  }
  return down_cast<const HashJoinIterator*>(m_hash_join->real_iterator())->WentOnDisk();
}

[[nodiscard]] double OptimisticHashJoinIterator::BufferFillRatio() const noexcept {
  return hash_join_iterator()->BufferFillRatio();
}
