/**
 * @file 05_real_world_land_surveying.cpp
 * @brief Real-world example: Land surveying and property measurement
 * @author Magpiny
 * @date 2026
 *
 * This example demonstrates:
 * - Practical land measurement scenario
 * - Converting between units
 * - Calculating property boundaries
 * - Real estate applications
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

// be nice
#include "areaperipoly.hpp"

using namespace geometry;

// Conversion factors
constexpr double METERS_TO_FEET = 3.28084;
constexpr double SQ_METERS_TO_ACRES = 0.000247105;
constexpr double SQ_METERS_TO_SQ_FEET = 10.7639;

struct Property {
  std::string owner;
  std::string address;
  std::vector<Point2D<double>> boundaries; // In meters
};

void analyze_property(const Property &prop) {
  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║           PROPERTY SURVEY REPORT                      ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  std::cout << "\nProperty Owner: " << prop.owner << "\n";
  std::cout << "Address: " << prop.address << "\n";
  std::cout << "Number of Boundary Points: " << prop.boundaries.size() << "\n";

  // Calculate area and perimeter
  auto area_m2 = calculate_area_shoelace(prop.boundaries);
  auto perimeter_m = calculate_perimeter(prop.boundaries);

  if (!area_m2 || !perimeter_m) {
    std::cout << "\nError: Invalid property boundaries!\n";
    return;
  }

  // Display in multiple units
  std::cout << "\n--- AREA MEASUREMENTS ---\n";
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "  " << area_m2->value << " m²\n";
  std::cout << "  " << (area_m2->value * SQ_METERS_TO_SQ_FEET) << " ft²\n";
  std::cout << "  " << (area_m2->value * SQ_METERS_TO_ACRES) << " acres\n";

  std::cout << "\n--- PERIMETER MEASUREMENTS ---\n";
  std::cout << "  " << perimeter_m->value << " m\n";
  std::cout << "  " << (perimeter_m->value * METERS_TO_FEET) << " ft\n";

  // Calculate boundary segments
  std::cout << "\n--- BOUNDARY SEGMENTS ---\n";
  for (size_t i = 0; i < prop.boundaries.size(); ++i) {
    const auto &p1 = prop.boundaries[i];
    const auto &p2 = prop.boundaries[(i + 1) % prop.boundaries.size()];

    double distance = p1.distance_to(p2);
    std::cout << "  Side " << (i + 1) << ": " << distance << " m ("
              << (distance * METERS_TO_FEET) << " ft)\n";
  }

  // Coordinates
  std::cout << "\n--- BOUNDARY COORDINATES (UTM/Local) ---\n";
  for (size_t i = 0; i < prop.boundaries.size(); ++i) {
    std::cout << "  Point " << (i + 1) << ": (" << prop.boundaries[i].x.value
              << ", " << prop.boundaries[i].y.value << ")\n";
  }

  // std::cout << "\n" << std::string(57, '─') << "\n";
  std::cout << "\n" << std::format("{} ─", 57) << "\n";
}

int main() {
  std::cout << "=== Land Surveying Application ===\n";

  // Example 1: Residential lot (irregular quadrilateral)
  Property residential_lot = {"John Smith",
                              "123 Main Street, Springfield",
                              {
                                  {0.0, 0.0},   // Southwest corner
                                  {30.0, 0.0},  // Southeast corner
                                  {30.0, 40.0}, // Northeast corner
                                  {0.0, 38.0}
                                  // Northwest corner (slightly irregular)
                              }};

  analyze_property(residential_lot);

  // Example 2: Agricultural land (irregular pentagon)
  Property farm_land = {"Green Valley Farms LLC",
                        "Rural Route 5, County Road 200",
                        {{0.0, 0.0},
                         {150.0, 0.0},
                         {180.0, 120.0},
                         {90.0, 200.0},
                         {-20.0, 100.0}}};

  analyze_property(farm_land);

  // Example 3: Commercial property (L-shaped)
  Property commercial = {"ABC Corporation",
                         "456 Business Parkway",
                         {{0.0, 0.0},
                          {50.0, 0.0},
                          {50.0, 30.0},
                          {25.0, 30.0},
                          {25.0, 60.0},
                          {0.0, 60.0}}};

  analyze_property(commercial);

  std::cout << "\n=== Survey Complete ===\n";

  return 0;
}
