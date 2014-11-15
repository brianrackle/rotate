#include <iostream>

using namespace std;

int main()
{
    using float_type = double_t;
    const float_type increment = 1.0e-2;

    std::ofstream outfile("results.markdown");

    outfile << "<a name = \"toc\"></a>"
            << "\n\n[TOC]\n\n";

    heading(outfile, 1, "Rotation");
    heading(outfile, 2, "Dot Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, rotation_iteration, dot_theta, dot_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    heading(outfile, 2, "Trig Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, rotation_iteration, trig_theta, trig_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    heading(outfile, 1, "Incremental Rotation");
    heading(outfile, 2, "Dot Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, rotation_inc_iteration, dot_theta, dot_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    heading(outfile, 2, "Trig Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, rotation_inc_iteration, trig_theta, trig_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    heading(outfile, 1, "Polar Rotation");
    heading(outfile, 2, "Dot Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, polar_iteration, dot_theta, dot_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    heading(outfile, 2, "Trig Results");
    table_header(outfile, "lcrrr", "Count", "Vector", "Calced Theta", "True Theta", "Delta");
    calculation_block(outfile, increment, polar_iteration, trig_theta, trig_clamp);
    outfile << "[back to top](#toc)" << "\n\n";

    return EXIT_SUCCESS;
}
