#include "optimistic_hash_join_iterator.h"

OptimisticHashJoinIterator::OptimisticHashJoinIterator(THD *thd,
                                                       unique_ptr_destroy_only<RowIterator> hash_join,
                                                       unique_ptr_destroy_only<RowIterator> sort)
  : RowIterator(thd), m_hash_join(std::move(hash_join)), m_sort(std::move(sort)) {
}

bool OptimisticHashJoinIterator::Init(){
  if(m_hash_join->Init()) {
    return true;
  }
  if (false && m_sort->Init()) {
      return true;
  }
  return false;
}

int OptimisticHashJoinIterator::Read(){
  return m_hash_join->Read();
}

bool OptimisticHashJoinIterator::WentOnDisk() const {
  return down_cast<const HashJoinIterator*>(m_hash_join->real_iterator())->WentOnDisk();
}
