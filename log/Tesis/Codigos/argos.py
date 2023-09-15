division=13
size_division=0.6
def generate_argos_wall(length):
    # Calculate half the length
    xml_code = ""
    half_length = length / 2.0

    move=half_length-size_division/2.0
    guarda_lat=0
    guarda_up=0
    tam_size=0.1
    adding=-tam_size-size_division
    estatic1=half_length+tam_size
    estatic2=half_length+tam_size/2.0
    # Create XML code for the square wall
    for wall_id in range(1, 5):
        move=half_length-size_division/2.0
        for wall_division in range(1,division):
            if (wall_id==1):
                if (wall_division==1):
                    move=half_length-size_division/2.0
                    t_move1=half_length-size_division-tam_size/2.0
                    t_move2=half_length-size_division
                    t_move3=half_length-size_division-tam_size
                    estatic1=half_length+tam_size
                    estatic2=half_length+tam_size/2.0

                xml_code += f"""<!-- * Wall{wall_id}_{wall_division} -->
                <box id="wall_i{wall_id}_{wall_division}" movable="false" size="0.01,{size_division},0.09">
                <body orientation="0,0,0" position="{half_length},{move},0"></body>
                </box>"""

                if (wall_division<division-1):
                    xml_code += f"""<!-- * TAMS_{wall_id}_{wall_division}-->    
                        <box id="tam_{wall_id}_{wall_division}_1" movable="false" size="0.01,0.1,0.12">
                        <body orientation="0,0,0" position="{estatic1},{t_move1},0"></body>
                        <leds medium="leds">
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}" intensity="100.0" offset="-0.01,0,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_2" intensity="100.0" offset="-0.01,0.04,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_3" intensity="100.0" offset="-0.01,-0.04,0.08"></led>
                        </leds>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_2" movable="false" size="0.01,0.11,0.12">
                        <body orientation="90,0,0" position="{estatic2},{t_move2},0"></body>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_3" movable="false" size="0.01,0.11,0.12">
                        <body orientation="90,0,0" position="{half_length+tam_size/2.0},{t_move3},0"></body>
                        </box>
                    """
                guarda_lat=move-size_division/2.0
                move+=adding
                t_move1+=adding
                t_move2+=adding
                t_move3+=adding


            if (wall_id==2):
                if (wall_division==1):
                    move=half_length-size_division/2.0
                    t_move1=half_length-size_division-tam_size/2.0
                    t_move2=half_length-size_division
                    t_move3=half_length-size_division-tam_size
                    estatic1=half_length+tam_size
                    estatic2=half_length+tam_size/2.0

                xml_code += f"""<!-- * Wall_{wall_id}_{wall_division}-->
                <box id="wall_i{wall_id}_{wall_division}" movable="false" size="0.01,{size_division},0.09">
                <body orientation="90,0,0" position="{move},{half_length},0"></body>
                </box>"""
                if (wall_division<division-1):
                    xml_code += f"""<!-- * TAMS_{wall_id}_{wall_division}-->    
                        <box id="tam_{wall_id}_{wall_division}_1" movable="false" size="0.01,0.1,0.12">
                        <body orientation="90,0,0" position="{t_move1},{estatic1},0"></body>
                        <leds medium="leds">
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}" intensity="100.0" offset="-0.01,0,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_2" intensity="100.0" offset="-0.01,0.04,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_3" intensity="100.0" offset="-0.01,-0.04,0.08"></led>
                        </leds>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_2" movable="false" size="0.01,0.11,0.12">
                        <body orientation="0,0,0" position="{t_move2},{estatic2},0"></body>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_3" movable="false" size="0.01,0.11,0.12">
                        <body orientation="0,0,0" position="{t_move3},{estatic2},0"></body>
                        </box>
                    """
                guarda_up=move-size_division/2.0
                move+=adding
                t_move1+=adding
                t_move2+=adding
                t_move3+=adding


            if (wall_id==3):
                if (wall_division==1):
                    move=half_length-size_division/2.0
                    t_move1=half_length-size_division-tam_size/2.0
                    t_move2=half_length-size_division
                    t_move3=half_length-size_division-tam_size
                    estatic1=guarda_up-tam_size
                    estatic2=guarda_up-tam_size/2.0
                xml_code += f"""<!-- * Wall{wall_id}_{wall_division} -->
                <box id="wall_i{wall_id}_{wall_division}" movable="false" size="0.01,{size_division},0.09">
                <body orientation="0,0,0" position="{guarda_lat},{move},0"></body>
                </box>"""

                if (wall_division<division-1):
                    xml_code += f"""<!-- * TAMS_{wall_id}_{wall_division}-->    
                        <box id="tam_{wall_id}_{wall_division}_1" movable="false" size="0.01,0.1,0.12">
                        <body orientation="0,0,0" position="{estatic1},{t_move1},0"></body>
                        <leds medium="leds">
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}" intensity="100.0" offset="0.01,0,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_2" intensity="100.0" offset="0.01,0.04,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_3" intensity="100.0" offset="0.01,-0.04,0.08"></led>
                        </leds>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_2" movable="false" size="0.01,0.11,0.12">
                        <body orientation="90,0,0" position="{estatic2},{t_move2},0"></body>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_3" movable="false" size="0.01,0.11,0.12">
                        <body orientation="90,0,0" position="{estatic2},{t_move3},0"></body>
                        </box>
                    """
                move+=adding
                t_move1+=adding
                t_move2+=adding
                t_move3+=adding

            if (wall_id==4):
                if (wall_division==1):
                    move=half_length-size_division/2.0
                    t_move1=half_length-size_division-tam_size/2.0
                    t_move2=half_length-size_division
                    t_move3=half_length-size_division-tam_size
                    estatic1=guarda_lat-tam_size
                    estatic2=guarda_lat-tam_size/2.0

                xml_code += f"""<!-- * Wall_{wall_id}_{wall_division}-->
                <box id="wall_i{wall_id}_{wall_division}" movable="false" size="0.01,{size_division},0.09">
                <body orientation="90,0,0" position="{move},{guarda_up},0"></body>
                </box>"""
            
                if (wall_division<division-1):
                    xml_code += f"""<!-- * TAMS_{wall_id}_{wall_division}-->    
                        <box id="tam_{wall_id}_{wall_division}_1" movable="false" size="0.01,0.1,0.12">
                        <body orientation="90,0,0" position="{t_move1},{estatic1},0"></body>
                        <leds medium="leds">
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}" intensity="100.0" offset="0.01,0,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_2" intensity="100.0" offset="0.01,0.04,0.08"></led>
                        <led anchor="origin" color="green" id="led_{wall_id}_{wall_division}_3" intensity="100.0" offset="0.01,-0.04,0.08"></led>
                        </leds>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_2" movable="false" size="0.01,0.11,0.12">
                        <body orientation="0,0,0" position="{t_move2},{estatic2},0"></body>
                        </box>
                        <box id="tam_{wall_id}_{wall_division}_3" movable="false" size="0.01,0.11,0.12">
                        <body orientation="0,0,0" position="{t_move3},{estatic2},0"></body>
                        </box>
                    """
                move+=adding
                t_move1+=adding
                t_move2+=adding
                t_move3+=adding

    return xml_code

# Input wall length
wall_length = 8  # Adjust this value as needed

# Generate the Argos XML code for the big walls
argos_xml = generate_argos_wall(wall_length)

# Save the XML code to a .txt file
with open("/home/jazmin/tuttifrutti/log/Tesis/Codigos/big_walls.txt", "w") as file:
    file.write(argos_xml)

print(f"Argos XML code for big walls has been saved to big_walls.txt")