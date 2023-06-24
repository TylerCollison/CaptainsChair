// CAD design for recliner universal armrest mounts
// This mount is primarily intended to be used for mounting
// HOTAS controllers to an armrest but could be used for
// mounting other components as well. 

use <hex_grid_v2.scad>

holeDiameter = 5;
spacing = 3;
thickness = 3;
rowCount = 25;

// Top wall
topColumnCount = 21;
hex_grid(holeDiameter, spacing, thickness, topColumnCount, rowCount);

// Side walls
wallColumnCount = 8;
translate([-7, 0, -1])
{
    rotate([0, 90, 0])
    {
        hex_grid(holeDiameter, spacing, thickness, wallColumnCount, rowCount);
    }
}

translate([142, 0, -1])
{
    rotate([0, 90, 0])
    {
        hex_grid(holeDiameter, spacing, thickness, wallColumnCount, rowCount);
    }
}

// Front wall
frontRowCount = 4;
translate([-4, -6, -1])
{
    rotate([-90, 0, 0])
    {
        hex_grid(holeDiameter, spacing, thickness, topColumnCount + 1, frontRowCount);
    }
}
