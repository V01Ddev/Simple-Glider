#!/bin/python3

# All lengths are based on https://www.flitetest.com/articles/what-if-i-want-to-design-an-airplane
# All measurements are in cm


# calculations done based on the wing length you would like
def calc_const(wing_span):

    # wing calculations
    wing_chord = round((1/5) * wing_span, 1)
    
    # aerofoil calculations
    aerofoil_highpoint = round(0.25 * wing_chord, 1) # where the highest point will be
    aerofoil_thickness = round(0.10 * wing_chord, 1) # the highest point of the aerofoil

    # fuselage calculations
    fuselage_length = round(0.75 * wing_span, 1)
    fuselage_height = round(0.10 * fuselage_length, 2) # fucking close enough

    # stabilizer calculations
    hoz_stab_span = round(0.35 * wing_span, 1)
    hoz_stab_chord = wing_chord
    elevator_chord = round(0.30 * wing_chord, 1)

    vert_stab_span = round(0.80 * hoz_stab_span, 1)
    vert_stab_chord = wing_chord
    rudder_chord = elevator_chord

    print()
    print("Based on online ratios.")
    print("Plane is more based on feel and look.")
    print()
    print(f"wing length --> {wing_span}")
    print(f"wing chord --> {wing_chord}")
    print()
    print(f"aerofoil highpoint --> {aerofoil_highpoint}")
    print(f"aerofoil thickness --> {aerofoil_thickness}")
    print()
    print(f"fuselage length --> {fuselage_length}")
    print(f"fuselage height --> {fuselage_height}")
    print()
    print(f"horizontal stabilizer span --> {hoz_stab_span}")
    print(f"horizontal stabilizer chord --> {hoz_stab_chord}")
    print()
    print(f"vertical stabilizer span --> {vert_stab_span}")
    print(f"vertical stabilizer chord --> {vert_stab_chord}")
    print()
    print(f"elevator chord --> {elevator_chord}")
    print(f"rudder chord --> {rudder_chord}")


def main():
    calc_const(70)


if __name__ == '__main__':
    main()
