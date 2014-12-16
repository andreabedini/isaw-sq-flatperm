/*
 * $Id: nearest_neighbour.hpp,v 1.1 2012/01/11 07:32:53 abedini Exp $
 *
 * $Log: nearest_neighbour.hpp,v $
 * Revision 1.1  2012/01/11 07:32:53  abedini
 * Initial revision
 *
 *
 */

#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

 namespace features {
  class nearest_neighbour {
    int _m = 0;

  public:
    template<typename Walk>
    void register_step(Walk const& walk)
    {
      // fetch the last point
      auto const& x = walk.back();

      if (walk.has_point(x) > 1) {
        // if stepping into a multiply visited site, erase a contact
        // because we just stepped over it
        _m -= 1;
      } else {
        // iterate over the neighbours looking for new contacts
        for (auto const& y : Walk::lattice_type::get_neighbours(x)) {
          if (walk.has_point(y) and not walk.has_bond(x, y))
            _m += 1;
        }
      }
    }

    template<typename Walk>
    void unregister_step(Walk const& walk)
    {
      // fetch the last point
      auto const& x = walk.back();

      if (walk.has_point(x) > 1) {
        // if stepping away from multiply visited site, we are
        // creating a contact.
        _m += 1;
      } else {
        // iterate over its neighbours
        for (auto const& y : Walk::lattice_type::get_neighbours(x)) {
          if (walk.has_point(y) and not walk.has_bond(x, y))
            _m -= 1;
        }
      }
    }

    int get() const { return _m; }
  };
}

#endif
