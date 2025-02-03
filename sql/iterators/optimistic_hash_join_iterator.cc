#include "optimistic_hash_join_iterator.h"

OptimisticHashJoinIterator::OptimisticHashJoinIterator(THD *thd,
                                                       unique_ptr_destroy_only<RowIterator> hash_join)
  : RowIterator(thd), m_hash_join(std::move(hash_join)) {
}

bool OptimisticHashJoinIterator::Init(){
  return m_hash_join->Init();
}

int OptimisticHashJoinIterator::Read(){
  return m_hash_join->Read();
}

