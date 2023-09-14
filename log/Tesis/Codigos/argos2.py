def generate_argos_wall_and_tams(wall_length, num_tams_per_wall):
    # Calculate half the length
    half_length = wall_length / 2.0
    space=0.4
    
    # Initialize an empty string to store the XML code
    xml_code = ""

    # Create XML code for the square wall
    for i in range(11):

    #<box id="tam_02_1" movable="false" size="0.01,0.1,0.12">
    #<body orientation="0,0,0" position="0.79,0.25,0"></body>
    # #
        xml_code += f"""<!-- * Wall -->
    <box id="wall_i1" movable="false" size="0.01,{wall_length},0.09">
    <body orientation="0,0,0" position="{half_length},0,0"></body>
    </box>
<box id="wall_i2" movable="false" size="0.01,{wall_length},0.08">
  <body orientation="90,0,0" position="0,{half_length},0"></body>
</box>
<box id="wall_i3" movable="false" size="0.01,{wall_length},0.08">
  <body orientation="0,0,0" position="{-half_length},0,0"></body>
</box>
<box id="wall_i4" movable="false" size="0.01,{wall_length},0.08">
  <body orientation="90,0,0" position="0,{-half_length},0"></body>
</box>\n"""

    # Define TAMs around all four walls
    for wall_id in range(1, 5):
        for tam_id in range(1, num_tams_per_wall + 1):
            # Calculate TAM position
            x_pos = half_length if wall_id in [1, 3] else -half_length
            y_pos = (2 * tam_id - 1) * (wall_length / (2 * num_tams_per_wall)) - half_length
            z_pos = 0.0

            # Create XML code for the TAM
            xml_code += f"""<!-- * Tam {wall_id:02d}_{tam_id} -->
<box id="tam_{wall_id:02d}_{tam_id}" movable="false" size="0.01,0.1,0.12">
  <body orientation="0,0,0" position="{x_pos:.2f},{y_pos:.2f},{z_pos:.2f}"></body>
  <leds medium="leds">
    <led anchor="origin" color="green" id="led_{wall_id:02d}_{tam_id}" intensity="100.0" offset="-0.01,0,0.08"></led>
    <led anchor="origin" color="green" id="led_{wall_id:02d}_{tam_id}_2" intensity="100.0" offset="-0.01,0.04,0.08"></led>
    <led anchor="origin" color="green" id="led_{wall_id:02d}_{tam_id}_3" intensity="100.0" offset="-0.01,-0.04,0.08"></led>
  </leds>
</box>
<!-- Side walls for Tam {wall_id:02d}_{tam_id} -->
<box id="tam_{wall_id:02d}_{tam_id}_side1" movable="false" size="0.01,0.01,0.12">
  <body orientation="0,0,0" position="{x_pos:.2f},{y_pos + 0.05:.2f},{z_pos:.2f}"></body>
</box>
<box id="tam_{wall_id:02d}_{tam_id}_side2" movable="false" size="0.01,0.01,0.12">
  <body orientation="90,0,0" position="{x_pos - 0.05:.2f},{y_pos:.2f},{z_pos:.2f}"></body>
</box>
<box id="tam_{wall_id:02d}_{tam_id}_side3" movable="false" size="0.01,0.01,0.12">
  <body orientation="0,0,0" position="{x_pos:.2f},{y_pos - 0.05:.2f},{z_pos:.2f}"></body>
</box>
<box id="tam_{wall_id:02d}_{tam_id}_side4" movable="false" size="0.01,0.01,0.12">
  <body orientation="90,0,0" position="{x_pos + 0.05:.2f},{y_pos:.2f},{z_pos:.2f}"></body>
</box>\n"""

    return xml_code

# Input wall length and number of TAMs per wall
wall_length = 1.6  # Adjust this value as needed
num_tams_per_wall = 4  # Adjust this value as needed

# Generate the Argos XML code for the walls and TAMs
argos_xml = generate_argos_wall_and_tams(wall_length, num_tams_per_wall)

# Save the combined XML code to a .txt file
with open("/home/jazmin/tuttifrutti/log/Tesis/Codigos/walls_and_tams.txt", "w") as file:
    file.write(argos_xml)

print(f"Argos XML code for walls and TAMs has been saved to walls_and_tams.txt")