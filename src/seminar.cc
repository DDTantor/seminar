
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <iostream>
#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/exceptions.hh>
#include <dune/alugrid/grid.hh>           // koristimo ALUGrid
#include <dune/grid/uggrid.hh>            // koristimo UGGrid
#include <dune/grid/io/file/gmshreader.hh> // GmshReader klasa
#include <dune/grid/common/gridinfo.hh>  
#include <dune/common/parametertree.hh>
#include <dune/common/parametertreeparser.hh>


#include"driver.hh"

int main(int argc, char** argv)
{
    Dune::MPIHelper::instance(argc, argv);

    // Pročitaj ulaznu datoteku
    Dune::ParameterTree input_data;
    Dune::ParameterTreeParser ptreeparser;
    ptreeparser.readINITree("seminar.ini",input_data);
    ptreeparser.readOptions(argc,argv,input_data);

    int refinement    = input_data.get<int>("grid.refinement");           // profinjenje
    double dt         = input_data.get<double>("fem.dt");                 // vremenski korak
    double a          = input_data.get<double>("problem.a");              // vremenski korak
    double b          = input_data.get<double>("problem.b");              // vremenski korak
    double K          = input_data.get<double>("problem.K");              // vremenski korak
    double D1         = input_data.get<double>("problem.D1");              // vremenski korak
    double D2         = input_data.get<double>("problem.D2");
    double T_end      = input_data.get<double>("problem.T");
    std::string name  = input_data.get<std::string>("output.filename");


    using GridType =  Dune::ALUGrid<2,2,Dune::simplex,Dune::conforming>;
    using GridView =  GridType::LeafGridView;

    std::string filename = "circle.msh";
    
    GridType* pgrid = Dune::GmshReader<GridType>::read(filename);

    if(refinement > 0)
        pgrid->globalRefine(refinement);

    auto gv = pgrid->leafGridView();
    driver(gv, dt, a, b, K, D1, D2, T_end, name);

    return 0;
}
