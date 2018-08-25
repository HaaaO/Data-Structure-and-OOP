
#include <set>

template<class T>
std::set<T> string_intersect(std::set<T> set1, std::set<T> set2){

  std::set<T> result;

  typename std::set<T>::const_iterator it1;
    for (it1 = set1.begin(); it1 != set1.end(); ++it1) {

      typename std::set<T>::const_iterator it2;
      it2 = set2.find(*it1);

      if(it2 != set2.end()){
        result.insert(*(it1));
      }

  }
  return result;
}


template<class T>
std::set<T> string_union(std::set<T> set1, std::set<T> set2){

  std::set<T> result;

  typename std::set<T>::const_iterator it1;
    for (it1 = set1.begin(); it1 != set1.end(); ++it1) {
      result.insert(*(it1));
  }

  typename std::set<T>::const_iterator it2;
    for (it2 = set2.begin(); it2 != set2.end(); ++it2) {
      result.insert(*(it2));
  }

  return result;
}