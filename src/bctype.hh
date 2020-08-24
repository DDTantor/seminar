#ifndef BCTYPE_HH
#define BCTYPE_HH

#include<dune/common/fvector.hh>
#include<dune/pdelab/common/function.hh>
#include<dune/pdelab/constraints/common/constraintsparameters.hh>

const double a = 0.1305;
const double b = 0.7695;
const double D1 = 0.05;
const double D2 = 1;
const double K = 100;

template<typename GV, typename RF>
class BCExtension0
    : public Dune::PDELab::GridFunctionBase<Dune::PDELab::
                                            GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1> >, BCExtension0<GV,RF> > {
    const GV& gv;
    double time, a, b;
public:
    using Traits = Dune::PDELab::GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1>>;
    BCExtension0 (const GV& gv_, double a_, double b_) : gv(gv_), a(a_), b(b_) {}

    inline void evaluate (const typename Traits::ElementType& e,
                          const typename Traits::DomainType& xlocal,
                          typename Traits::RangeType& y) const
    {
        auto x = e.geometry().global(xlocal);

        /*  if (time == 0) {
            y = (x[0]-0.5)*(x[0]-0.5)+(x[1]-0.5)*(x[1]-0.5);
            y = std::max(0.0, 1.0-8.0*sqrt(y));
            }
            else y = 0;*/
        y = 0;
        double c1 = (x[0] - 1.0/3) * (x[0] - 1.0/3);
        double c2 = (x[1] - 0.5) * (x[1] - 0.5);
    
        if (time == 0)
            y = a + b + 1e-3 * exp(-100 * (c1 + c2));
    
        return;
    }

    inline const GV& getGridView () {return gv;}
    void setTime (double t) {time = t;}
};

//rubni i inicijalni uvjeti za u_1 = u_t
template<typename GV, typename RF>
class BCExtension1
    : public Dune::PDELab::GridFunctionBase<Dune::PDELab::
                                            GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1> >, BCExtension1<GV,RF> > {
    const GV& gv;
    double time, a, b;
public:
    using Traits = Dune::PDELab::GridFunctionTraits<GV,double,1,Dune::FieldVector<double,1>>;
    BCExtension1 (const GV& gv_, double a_, double b_) : gv(gv_), a(a_), b(b_) {}

    inline void evaluate (const typename Traits::ElementType& e,
                          const typename Traits::DomainType& xlocal,
                          typename Traits::RangeType& y) const
    {
        auto x = e.geometry().global(xlocal);
        y = 0;
        if (time == 0)
            y = b / ((a + b)*(a + b));

        return;
    }
    inline const GV& getGridView () {return gv;}
    void setTime (double t) {time = t;}
};

//Klasa koja određuje Dirichletove rubne uvjete
template <typename GV>
class BCTypeParam : public Dune::PDELab::DirichletConstraintsParameters
{
    double time;
    const GV& gv;
public:
    BCTypeParam(const GV& gv_) : gv(gv_) {}
public:
    template<typename I>
    bool isDirichlet(const I & intersection,
                     const Dune::FieldVector<typename I::ctype, I::coorddimension-1> & coord
        ) const
    {
        return false;
    }
    inline const GV& getGridView () {return gv;}
    void setTime (double t) {time = t;}
};
#endif
