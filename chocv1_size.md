# KAILH CHOC V1 (CPG1350) TECHNICAL SPECIFICATIONS

## 1. SWITCH PHYSICAL DIMENSIONS
- Switch Model: Kailh Choc V1 (CPG1350 series)
- Base Body Width: 13.80 mm
- Base Body Length: 13.80 mm
- Top Housing Collar (Flange): 15.00 mm x 15.00 mm
- Body Height (above PCB when installed): 5.00 mm
- Stem Type: Two-prong Choc stem
- Stem Width (outer to outer): 5.70 mm
- Travel Distance: 1.5 mm actuation, 3.0 mm total travel

---

## 2. PLATE CUTOUT & MOUNTING SPECS
- Cutout Shape: Square
- Plate Cutout Dimensions: 14.00 mm x 14.00 mm (+0.05 mm / -0.00 mm tolerance)
- Nominal Switch Clearance Gap: 0.20 mm total (0.10 mm per side)
- Plate Thickness (Critical): 1.20 mm (+0.00 mm / -0.10 mm tolerance)
- Retention Mechanism: Side plastic snaps/clips engaging under the 1.20 mm edge

---

## 3. VERTICAL STACK HEIGHTS (Z-AXIS)
- Top surface of PCB to bottom of 1.2mm plate cutout: 0.90 mm to 1.00 mm
- Top surface of PCB to top surface of plate: 2.10 mm to 2.20 mm
- Overall plate height above PCB (3D Printed Recessed Plate): 
  - Outer Plate Thickness: 2.50 mm - 3.00 mm
  - Recess Depth from underside: 1.30 mm - 1.80 mm (leaving 1.20 mm lip at cutout)
- Standoff Height (PCB to Bottom Case/Plate frame): 3.00 mm (Standard M2 standoff)

---

## 4. PCB FOOTPRINT & HOTSWAP SOCKET DRILL LOCATIONS
Origin (0,0) = Center of main center peg hole

1. Center Fixing Peg:
   - Diameter: 3.40 mm + 0.05 mm
   - Coordinates: (0.00 mm, 0.00 mm)

2. Side Mounting Pegs (Plastic 5-pin alignment posts):
   - Left Peg Diameter: 1.90 mm
   - Right Peg Diameter: 1.90 mm
   - Left Peg Coordinates: (-5.50 mm, 0.00 mm)
   - Right Peg Coordinates: (+5.50 mm, 0.00 mm)

3. Switch Pins / Kailh Hotswap Socket (CPG135001S30) Cutouts:
   - Pin 1 (Left Metal Leg / Ground): 
     - Center Coordinates: (-5.00 mm, -3.80 mm)
     - Socket Routing Hole Diameter: 3.00 mm
   - Pin 2 (Right Metal Leg / Signal): 
     - Center Coordinates: (+0.00 mm, -5.90 mm)
     - Socket Routing Hole Diameter: 3.00 mm

---

## 5. KEY MATRIX SPACING (CENTER-TO-CENTER PITCH)
- Choc Native Key Pitch:
  - X Spacing (Horizontal): 18.00 mm (or 18.60 mm for specific keycaps)
  - Y Spacing (Vertical): 17.00 mm (or 17.60 mm for specific keycaps)
- Standard MX Key Pitch (if using MX-spaced Choc keycaps):
  - X Spacing: 19.05 mm
  - Y Spacing: 19.05 mm

---

## 6. 3D PRINTING DESIGN RULES FOR PLATES & CASES
- Minimum Wall Thickness around cutouts: 1.50 mm
- Recess Geometry: 
  - Pocket around 14.0x14.0 mm hole must extend at least 1.0 mm wider on the left and right sides (x-axis) to allow clip movement.
- Print Tolerances (FDM): 
  - Horizontal expansion offset: -0.05 mm to achieve true 14.00 mm cutouts.