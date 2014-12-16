/*
 * multiplicity.hpp
 * 
 */

#ifndef MULTIPLICITY_HPP
#define MULTIPLICITY_HPP

namespace features {
  class multiplicity {
    static const unsigned int SIZE = 4;
    unsigned int _m[SIZE];
    
  public:
    multiplicity() {
      std::fill(_m, _m + SIZE, 0);
    }

    template<typename Walk>
    void register_step(Walk const& walk) {
      int k = walk.has_point(walk.back());
      assert(k > 0);
      if (walk.back() == Walk::lattice_type::origin()) {
	// assert there's no first visit to the origin
	assert(k > 1);
       	k --;
      }
      _m[k-1] --;
      _m[k] ++;
    }

    template<typename Walk>
    void unregister_step(Walk const& walk) {
      int k = walk.has_point(walk.back());
      assert(k > 0);
      if (walk.back() == Walk::lattice_type::origin()) {
	// assert there's no first visit to the origin
	assert(k > 1);
       	k --;
      }
      _m[k] --;
      _m[k-1] ++;
    }

    template<unsigned int I>
    unsigned int get() const { return _m[I]; }

    friend std::ostream& operator<<(std::ostream& o, multiplicity const& mult) {
      std::for_each(mult._m, mult._m + SIZE, [&o](int x) { o << x << " "; });
      return o;
    }
  };
}

#endif
