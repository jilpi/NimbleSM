#include "grid/BoundingBox.hpp"
#include "grid/GridCell.hpp"
#include "grid/GridIndex.hpp"

#include <unordered_map>

/** gather_into_bounding_boxes takes a list of points from a kokkos view, and
constructs a map between grid indicies and the corresponding bounding boxes.
Basically, it's finding a bounding box for all the points in a particular cell,
for every cell that has any points in it. */
using grid_box_map = std::unordered_map<GridIndex, BoundingBox>;
template<class View>
auto gather_into_bounding_boxes(View&& values, double const cell_size)
  -> grid_box_map
{
    grid_box_map boundingBoxLookup;
    size_t const count = values.extent(0) / 3;
    if (count > 0)
    {
        double const scale = 1.0 / cell_size;

        Point3d point {values(0), values(1), values(2)};

        auto current_index       = GridIndex(point, scale);
        auto current_cell_bounds = GridCellBounds(current_index, cell_size);
        auto current_box         = BoundingBox(point);

        for (size_t i = 1; i < count; i++)
        {
            point = {values(3 * i), values(3 * i + 1), values(3 * i + 2)};

            if (current_cell_bounds.contains(point, cell_size))
            {
                current_box.include(point);
            }
            else
            {
                // We include the current bounding box in the map,
                // then calculate a new bounding box, index, and cell
                current_box.includeInMap(boundingBoxLookup, current_index);
                current_box.centerAt(point);
                current_index = GridIndex(point, scale);
                current_cell_bounds.moveTo(current_index, cell_size);
            }
        }
        // Ensure that the most recent version of the current box is included in
        // the map
        current_box.includeInMap(boundingBoxLookup, current_index);
    }
    return boundingBoxLookup;
}
