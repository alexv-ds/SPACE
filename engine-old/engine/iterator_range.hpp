#pragma once

namespace engine {

template<class IteratorT>
class iterator_range {
public:
  inline iterator_range(IteratorT begin_iterator, IteratorT end_iterator)
      : begin_iterator(std::move(begin_iterator)), end_iterator(std::move(end_iterator)) {}

  inline IteratorT begin() const {return this->begin_iterator;}
  inline IteratorT end() const {return this->end_iterator;}

private:
  IteratorT begin_iterator;
  IteratorT end_iterator;
};

template <class IteratorT>
inline iterator_range<IteratorT> make_range(IteratorT begin, IteratorT end) {
  return iterator_range<IteratorT>(std::move(begin), std::move(end));
}

} //namespace engine