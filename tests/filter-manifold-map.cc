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

#include "shared-tests/fixture.hh"

#include <iostream>

#include <roboptim/core/io.hh>
#include <roboptim/core/differentiable-function.hh>
#include <roboptim/core/util.hh>

#include <roboptim/core/function/cos.hh>
#include <roboptim/core/filter/manifold-map/instance-wrapper.hh>
#include <roboptim/core/filter/manifold-map/descriptive-wrapper.hh>

#include <manifolds/SO3.h>
#include <manifolds/S2.h>
#include <manifolds/RealSpace.h>
#include <manifolds/CartesianProduct.h>
#include <manifolds/CartesianPower.h>
#include <manifolds/ExpMapMatrix.h>

using namespace roboptim;

typedef boost::mpl::list< ::roboptim::EigenMatrixDense,
			  ::roboptim::EigenMatrixSparse> functionTypes_t;

struct F : public DifferentiableFunction
{
  F () : DifferentiableFunction (22, 10, "f_n (x) = n * x")
  {}

  void impl_compute (result_ref res, const_argument_ref argument) const
  {
    res.setZero ();
    for (size_type i = 0; i < outputSize (); ++i)
      for (size_type j = 0; j < 3; ++j)
	{
	  res[i] += (value_type)i * argument[19 + j];
	}
  }

  void impl_gradient (gradient_ref grad, const_argument_ref,
		      size_type functionId) const
  {
    grad.setZero ();
    std::cout << "functionId: " << functionId << std::endl;
    for (size_type j = 0; j < 3; ++j)
      {
	grad[19 + j] += (value_type)functionId;
	std::cout << "grad[19 + j]: " << grad[19 + j] << std::endl;
      }
  }
};

struct G : public DifferentiableFunction
{
  G () : DifferentiableFunction (3, 1, "f_n (x) = sum(x)")
  {}

  void impl_compute (result_ref res, const_argument_ref argument) const
  {
    res.setZero ();
    for (size_type i = 0; i < inputSize (); ++i)
      {
	std::cout << "argument[i]: " << argument[i] << std::endl;
	res[0] += argument[i];
      }
  }

  void impl_gradient (gradient_ref grad, const_argument_ref,
		      size_type functionId) const
  {
    grad.setZero ();
    for (size_type j = 0; j < 3; ++j)
      grad[j] = functionId * 0 + 1;
  }
};

boost::shared_ptr<boost::test_tools::output_test_stream> output;

BOOST_FIXTURE_TEST_SUITE (core, TestSuiteConfiguration)

BOOST_AUTO_TEST_CASE_TEMPLATE (manifold_map_test_0, T, functionTypes_t)
{
  output = retrievePattern("filter-manifold-map");

  boost::shared_ptr<F> f (new F());

  pgs::RealSpace pos(3);pos.name() = "position";
  pgs::SO3<pgs::ExpMapMatrix> ori; ori.name() = "orientation";
  pgs::CartesianProduct freeFlyer(pos, ori);
  pgs::RealSpace joints(10); joints.name() = "joints";
  pgs::CartesianProduct robot(freeFlyer, joints);

  pgs::CartesianProduct cartProd(joints, ori);
  pgs::CartesianProduct myFuncManifold(cartProd, pos);

  std::cout << "f->outputSize(): " << f->outputSize() << std::endl;

  boost::shared_ptr<DescriptiveWrapper<DifferentiableFunction>>
    descWrapPtr(new DescriptiveWrapper<DifferentiableFunction>(f, myFuncManifold));

  InstanceWrapper<DifferentiableFunction> instWrap(descWrapPtr, robot, myFuncManifold);

  InstanceWrapper<DifferentiableFunction>::argument_t input = Eigen::VectorXd::Zero(22);
  InstanceWrapper<DifferentiableFunction>::result_t result = Eigen::VectorXd::Zero(10);
  InstanceWrapper<DifferentiableFunction>::gradient_t gradient = Eigen::VectorXd::Zero(22);
  InstanceWrapper<DifferentiableFunction>::jacobian_t jacobian = Eigen::MatrixXd::Zero(10, 22);

  for(int i = 0; i < 3; ++i)
    {
      input(i) = 1 + i;
    }

  (*output) << instWrap;
  std::cout << instWrap << std::endl;
  std::cout << "input: " << input.transpose() << std::endl;
  instWrap(result, input);
  std::cout << "result: " << result.transpose() << std::endl << std::endl;

  for (int i = 0; i < f->outputSize(); ++i)
    {
      instWrap.gradient(gradient, input, i);
      std::cout << "gradient (main): " << gradient << std::endl << std::endl;
    }

  instWrap.jacobian(jacobian, input);
  std::cout << "jacobian: " << std::endl << jacobian << std::endl;

  std::cout << (*descWrapPtr);

  BOOST_CHECK (output->match_pattern());
}

BOOST_AUTO_TEST_CASE_TEMPLATE (manifold_map_test_1, T, functionTypes_t)
{
  output = retrievePattern("filter-manifold-map");

  boost::shared_ptr<G> g (new G());

  std::vector<pgs::RealSpace*> reals;
  pgs::CartesianProduct problemManifold;
  pgs::RealSpace descriptiveManifold(3);

  boost::shared_ptr<DescriptiveWrapper<DifferentiableFunction>>
    descWrapPtr(new DescriptiveWrapper<DifferentiableFunction>(g, descriptiveManifold));

  size_t posNumber = 15;

  for (size_t i = 0; i < posNumber; ++i)
    {
      reals.push_back(new pgs::RealSpace(3));
      reals.back()->name() = "position (" + std::to_string(i) + ")";
      problemManifold.multiply(*reals.back());
    }

  InstanceWrapper<DifferentiableFunction>::argument_t input = Eigen::VectorXd::Zero(3 * static_cast<long>(posNumber));
  InstanceWrapper<DifferentiableFunction>::result_t result = Eigen::VectorXd::Zero(1);
  InstanceWrapper<DifferentiableFunction>::gradient_t gradient = Eigen::VectorXd::Zero(3 * static_cast<long>(posNumber));
  InstanceWrapper<DifferentiableFunction>::jacobian_t jacobian = Eigen::MatrixXd::Zero(1, 3 * static_cast<long>(posNumber));

  for (int i = 0; i < input.size(); ++i)
    {
      input(i) = i;
    }

  for (size_t i = 0; i < posNumber; ++i)
    {
      InstanceWrapper<DifferentiableFunction> instWrap(descWrapPtr, problemManifold, *reals[i]);

      instWrap(result, input);

      BOOST_CHECK(result(0) == (3 * (3 * i + 1)));
      //std::cout << "Ok for pos (" << i << ")" << std::endl;
    }

  for (size_t i = 0; i < posNumber; ++i)
    {
      delete reals[i];
    }


  //BOOST_CHECK (output->match_pattern());
}

BOOST_AUTO_TEST_SUITE_END ()