/*
 * square.hpp
 *
 */

#ifndef SQUARE_HPP__
#define SQUARE_HPP__

#include <boost/functional/hash.hpp>
#include <algorithm>
#include <array>
#include <numeric>

namespace lattices {
  template<unsigned int N, typename T = int>
  struct point : public std::array<T, N> {
    template<typename U>
    struct rebind { typedef point<N, U> result_type; };

    using std::array<T, N>::begin;
    using std::array<T, N>::end;

    point() {
      std::fill(begin(), end(), 0);
    }

    template<typename U>
    point(std::initializer_list<U> list) {
      std::copy_n(list.begin(), N, begin());
    }

    template<typename U>
    point(const point<N, U>& other) {
      std::copy_n(other.begin(), N, begin());
    }

    point& operator+=(const point& rhs) {
      std::transform(begin(), end(), rhs.begin(), begin(),
        std::plus<T>());
      return *this;
    }

    const point operator+(const point& rhs) const {
      point result(*this);
      result += rhs;
      return result;
    }

    point& operator-=(const point& rhs) {
      std::transform(begin(), end(), rhs.begin(), begin(),
        std::minus<T>());
      return *this;
    }

    const point operator-(const point& rhs) const {
      point result(*this);
      result -= rhs;
      return result;
    }
  };

  template<unsigned int N, typename T>
  std::ostream& operator<<(std::ostream& o, const point<N, T>& rhs) {
    auto i = std::begin(rhs);
    while (true) {
      o << *i++;
      if (i == std::end(rhs))
        break;
      else
        o << " ";
    }
    return o;
  }

  template<unsigned int N, typename T>
  T sum(const point<N, T>& p)
  {
    return std::accumulate(p.begin(), p.end(), T(0));
  }

  template<unsigned int N, typename T>
  T norm_square(const point<N, T>& p)
  {
    return std::inner_product(p.begin(), p.end(), p.begin(), T(0));
  }

  template<typename T>
  T cross(const point<2, T>& lhs, const point<2, T>& rhs)
  {
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
  }

  template<unsigned N>
  std::size_t hash_value(point<N> const& p)
  {
    std::size_t hash = 12345;
    boost::hash_range(hash, p.begin(), p.end());
    return hash;
  }

  //////////////////////////////////////////////////////////////////////

  struct square {
    static const std::size_t dimensionality = 2;
    static const std::size_t coordination = 4;

    typedef lattices::point<2> point;

    static std::vector<point> get_neighbours(point const& c)
    {
      std::vector<point> neighbours = { c + point{1,0}, c + point{0,1} };
      auto l = c + point{-1,0};
      if (l[0] + l[1] >= 0)
        neighbours.push_back(l);

      auto d = c + point{0,-1};
      if (d[0] + d[1] >= 0)
        neighbours.push_back(d);

      return neighbours;
    }

    static const point origin() { return point{0, 0}; };
  };
}

#endif // SQUARE_HPP__

/* vim: set et fenc=utf-8 ff=unix sts=2 sw=2 ts=2 : */
