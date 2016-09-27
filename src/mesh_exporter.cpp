#include "mesh_exporter.hpp"


#include <hadoken/format/format.hpp>

#include <morpho/morpho_h5_v1.hpp>

using namespace std;
namespace fmt = hadoken::format;


namespace morpho{

const std::string gmsh_header =
"/***************************************************************\n"
" * gmsh file generated by morpho-tool\n"
"****************************************************************/\n\n";

gmsh_exporter::gmsh_exporter(const std::string & morphology_filename, const std::string & mesh_filename) :
    geo_stream(mesh_filename),
    reader(morphology_filename)
{


}


void gmsh_exporter::export_to_point_cloud(){
    serialize_header();
    serialize_points_raw();
}



void gmsh_exporter::serialize_header(){
    geo_stream << gmsh_header << "\n";


    fmt::scat(geo_stream,
              gmsh_header,
              "// converted to GEO format from ", reader.get_filename(), "\n");

    fmt::scat(geo_stream,
              "lcar1 = .1;\n",
              "lcar2 = .0005;\n",
              "lcar3 = .055;\n");

}

void gmsh_exporter::serialize_points_raw(){
    geo_stream << "// export morphology points \n";

    auto points = reader.get_points_raw();

    assert(points.size2() > 3);

    const std::size_t rows = points.size1();

    std::size_t id_point =0;

    for(std::size_t i =0; i < rows; ++i){
        fmt::scat(geo_stream,
                  "Point(", id_point, ") = {", points(i,0), ",", points(i,1), ",", points(i,2), ",", points(i,3), "} ;\n");
        id_point++;
    }

    geo_stream << "\n\n";
}


} // morpho
