 // Copyright (c) 2009  GeometryFactory (France)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Laurent Rineau


#ifndef CGAL_TRIANGULATION_2_FILTERED_PROJECTION_TRAITS_3_H
#define CGAL_TRIANGULATION_2_FILTERED_PROJECTION_TRAITS_3_H

#include <CGAL/Triangulation_2_projection_traits_3.h>
#include <CGAL/Filtered_predicate.h>

namespace CGAL {

template < class Filtered_kernel >
class Triangulation_2_filtered_projection_traits_3
  : public Triangulation_2_projection_traits_3<Filtered_kernel>
{
  typedef Filtered_kernel K;
  typedef Triangulation_2_filtered_projection_traits_3<K> Self;
  typedef Triangulation_2_projection_traits_3<K> Base;

  typedef typename K::Exact_kernel Exact_kernel;
  typedef typename K::Approximate_kernel Approximate_kernel;
  typedef typename K::C2E C2E;
  typedef typename K::C2F C2F;

public:
  typedef Triangulation_2_projection_traits_3<Exact_kernel> Exact_traits;
  typedef Triangulation_2_projection_traits_3<Approximate_kernel> Filtering_traits;

public:
  Triangulation_2_filtered_projection_traits_3(const typename K::Vector_3& n)
    : Base(n)
  {
  }

  Triangulation_2_filtered_projection_traits_3(const Self& other)
    : Base(other)
  {
    CGAL_PROFILER("Copy of the filtered traits")
    CGAL_TIME_PROFILER("Copy of the filtered traits")
//     std::cerr << "Copy of the filtered traits.\n";
  }

  Self& operator=(const Self& other)
  {
    std::cerr << "Assignement of the filtered traits.\n";
    if(this != &other) {
      Base::operator=(other);
    }
    return *this;
  }

#define CGAL_TRIANGULATION_2_PROJ_TRAITS_FILTER_PRED(P, Pf, obj)    \
  typedef  Filtered_predicate< \
    typename Exact_traits::P, \
    typename Filtering_traits::P, \
    C2E, \
    C2F > P; \
  P Pf() const { \
    return P(this->normal()); \
  }
  // std::cerr << #P << "_object()\n";
  CGAL_TRIANGULATION_2_PROJ_TRAITS_FILTER_PRED(Orientation_2,
                                               orientation_2_object,
                                               orientation)
  CGAL_TRIANGULATION_2_PROJ_TRAITS_FILTER_PRED(Side_of_oriented_circle_2,
                                               side_of_oriented_circle_2_object,
                                               side_of_oriented_circle)
}; // end class Triangulation_2_projection_traits_3<Filtered_kernel>

} // end namespace CGAL


#endif // CGAL_TRIANGULATION_2_FILTERED_PROJECTION_TRAITS_3_H