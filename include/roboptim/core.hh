// Copyright (C) 2010 by Thomas Moulard, AIST, CNRS, INRIA.
//
// This file is part of the roboptim.
//
// roboptim is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ROBOPTIM_CORE_HH
# define ROBOPTIM_CORE_HH
# include <roboptim/core/sys.hh>
# include <roboptim/core/debug.hh>

// Generic headers.
# include <roboptim/core/fwd.hh>
# include <roboptim/core/io.hh>
# include <roboptim/core/visualization/fwd.hh>


// Main headers.
# include <roboptim/core/result-with-warnings.hh>
# include <roboptim/core/derivable-function.hh>
# include <roboptim/core/derivable-parametrized-function.hh>
# include <roboptim/core/finite-difference-gradient.hh>
# include <roboptim/core/function.hh>
# include <roboptim/core/generic-solver.hh>
# include <roboptim/core/function/constant.hh>
# include <roboptim/core/function/identity.hh>
# include <roboptim/core/indent.hh>
# include <roboptim/core/linear-function.hh>
# include <roboptim/core/n-times-derivable-function.hh>
# include <roboptim/core/numeric-linear-function.hh>
# include <roboptim/core/numeric-quadratic-function.hh>
# include <roboptim/core/parametrized-function.hh>
# include <roboptim/core/problem.hh>
# include <roboptim/core/quadratic-function.hh>
# include <roboptim/core/result.hh>
# include <roboptim/core/solver-error.hh>
# include <roboptim/core/solver-factory.hh>
# include <roboptim/core/solver-warning.hh>
# include <roboptim/core/solver.hh>
# include <roboptim/core/twice-derivable-function.hh>
# include <roboptim/core/util.hh>


// Callbacks.
# include <roboptim/core/callback/multiplexer.hh>


// Filters.
# include <roboptim/core/filter/bind.hh>
# include <roboptim/core/filter/cached-function.hh>
# include <roboptim/core/filter/chain.hh>
# include <roboptim/core/filter/concatenate.hh>
# include <roboptim/core/filter/derivative.hh>
# include <roboptim/core/filter/map.hh>
# include <roboptim/core/filter/minus.hh>
# include <roboptim/core/filter/plus.hh>
# include <roboptim/core/filter/product.hh>
# include <roboptim/core/filter/scalar.hh>
# include <roboptim/core/filter/selection.hh>
# include <roboptim/core/filter/selection-by-id.hh>
# include <roboptim/core/filter/split.hh>


// Functions.
# include <roboptim/core/function/constant.hh>
# include <roboptim/core/function/cos.hh>
# include <roboptim/core/function/identity.hh>
# include <roboptim/core/function/polynomial.hh>
# include <roboptim/core/function/sin.hh>


// Visualization.
# include <roboptim/core/visualization/gnuplot.hh>
# include <roboptim/core/visualization/gnuplot-commands.hh>
# include <roboptim/core/visualization/gnuplot-differentiable-function.hh>
# include <roboptim/core/visualization/gnuplot-function.hh>
# include <roboptim/core/visualization/gnuplot-matrix.hh>
# include <roboptim/core/visualization/matplotlib.hh>
# include <roboptim/core/visualization/matplotlib-commands.hh>
# include <roboptim/core/visualization/matplotlib-function.hh>


#endif //! ROBOPTIM_CORE_HH
