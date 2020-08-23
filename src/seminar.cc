
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <iostream>
#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/exceptions.hh>
#include <dune/alugrid/grid.hh>           // koristimo ALUGrid
#include <dune/grid/io/file/gmshreader.hh> // GmshReader klasa
#include <dune/grid/common/gridinfo.hh>  
#include <dune/common/parametertree.hh>
#include <dune/common/parametertreeparser.hh>


#include"driver.hh"

int main(int argc, char** argv)
{
    Dune::MPIHelper::instance(argc, argv);

    if(argc < 2){
        std::cerr << "Usage: " << argv[0]
                  << " ime_grid_datoteke.msh" << std::endl;
        std::exit(1);
    }
    // Pročitaj ulaznu datoteku
    Dune::ParameterTree input_data;
    Dune::ParameterTreeParser ptreeparser;
    ptreeparser.readINITree("seminar.ini",input_data);
    ptreeparser.readOptions(argc,argv,input_data);

    //int refinement    = input_data.get<int>("grid.refinement");           //broj profinjenja
    //double dt            =  input_data.get<double>("fem.dt");             //vremenski korak
    //double c          =  input_data.get<double>("problem.speedofsound");  // brzina zvuka
    //double T_end      =  input_data.get<double>("problem.T");             // konačno vrijeme
    //std::string name  = input_data.get<std::string>("output.filename");

    int refinement    = input_data.get<int>("grid.refinement");           // profinjenje
    double dt         = input_data.get<double>("fem.dt");                 // vremenski korak
    double a          = input_data.get<double>("problem.a");              // vremenski korak
    double b          = input_data.get<double>("problem.b");              // vremenski korak
    double K          = input_data.get<double>("problem.K");              // vremenski korak
    double D1         = input_data.get<double>("problem.D1");              // vremenski korak
    double D2         = input_data.get<double>("problem.D2");
    double T_end      = input_data.get<double>("problem.T");
    std::string name  = input_data.get<std::string>("output.filename");
    
    //pravokutna mreža u 2D
    /*  constexpr int dim = 2;  // dimenzija mreže
        using GridType = Dune::YaspGrid<dim>;
        Dune::FieldVector<GridType::ctype,dim> L(1.0);             // Duljina stranice
        std::array<int,dim> s={10,10};          // broj ćelija po stranici
        GridType grid(L, s);*/

    using GridType =  Dune::ALUGrid<2,2,Dune::simplex,Dune::conforming>;
    using GridView =  GridType::LeafGridView;
    
    GridType* pgrid = Dune::GmshReader<GridType>::read(argv[1]);
    int no_r = std::stoi(argv[2]);

    if(refinement > 0)
        pgrid->globalRefine(refinement);

    auto gv = pgrid->leafGridView();
    driver(gv, dt, a, b, K, D1, D2, T_end, name);

    return 0;
}
