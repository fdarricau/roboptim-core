// Copyright (C) 2013 by Thomas Moulard, AIST, CNRS, INRIA.
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

#ifndef ROBOPTIM_CORE_OPERATOR_MINUS_HH
# define ROBOPTIM_CORE_OPERATOR_MINUS_HH
# include <stdexcept>
# include <vector>
# include <boost/shared_ptr.hpp>

# include <roboptim/core/detail/autopromote.hh>
# include <roboptim/core/differentiable-function.hh>

namespace roboptim
{
  /// \addtogroup roboptim_operator
  /// @{

  /// \brief Subtract two RobOptim functions.
  /// \tparam U first input function type.
  /// \tparam V second input function type.
  template <typename U, typename V>
  class Minus : public detail::PromoteTrait<U, V>::T_promote
  {
  public:
    typedef typename detail::PromoteTrait<U, V>::T_promote parentType_t;
    ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_ (parentType_t);

    typedef boost::shared_ptr<Minus> MinusShPtr_t;

    explicit Minus (boost::shared_ptr<U> left, boost::shared_ptr<V> right);
    ~Minus ();

    const boost::shared_ptr<U>& left () const
    {
      return left_;
    }

    U& left ()
    {
      return left_;
    }

    const boost::shared_ptr<V>& right () const
    {
      return right_;
    }

    V& right ()
    {
      return right_;
    }

    void impl_compute (result_ref result, const_argument_ref x)
      const;

    void impl_gradient (gradient_ref gradient,
			const_argument_ref argument,
			size_type functionId = 0)
      const;
    void impl_jacobian (jacobian_ref jacobian,
			const_argument_ref arg)
      const;
  private:
    boost::shared_ptr<U> left_;
    boost::shared_ptr<V> right_;

    mutable result_t result_;
    mutable gradient_t gradient_;
    mutable jacobian_t jacobian_;
  };

  template <typename U, typename V>
  boost::shared_ptr<Minus<U, V> >
  minus (boost::shared_ptr<U> left, boost::shared_ptr<V> right)
  {
    return boost::make_shared<Minus<U, V> > (left, right);
  }

  template <typename U, typename V>
  boost::shared_ptr<Minus<U, V> >
  operator- (boost::shared_ptr<U> left, boost::shared_ptr<V> right)
  {
    return boost::make_shared<Minus<U, V> > (left, right);
  }

  /// @}

} // end of namespace roboptim.

# include <roboptim/core/operator/minus.hxx>
#endif //! ROBOPTIM_CORE_OPERATOR_MINUS_HH
