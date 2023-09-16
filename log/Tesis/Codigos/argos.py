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
                        <body orientation="90,0,0" position="{estatic2},{t_move3},0"></body>
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

    


    p1_x=0

    for i in range (1,6):

        if (i==1):
            p1_x=half_length-(size_division*s_island)-(tam_size*(s_island-2))
            p1_y=p1_x
            p=1
        if (i==2):
            p1_x=half_length-(size_division*s_island)-(tam_size*(s_island-2))
            p1_y=half_length+(size_division)*(s_island-division)+(tam_size)*(s_island-2-num_tam)
            p=2
        if (i==3):

            p1_x=half_length+(size_division)*(s_island-division)+(tam_size)*(s_island-2-num_tam)
            p1_y=half_length+(size_division)*(s_island-division)+(tam_size)*(s_island-2-num_tam)

            p=3
        if (i==4):
            p=4
            p1_x=half_length+(size_division)*(s_island-division)+(tam_size)*(s_island-2-num_tam)
            p1_y=half_length-(size_division*s_island)-(tam_size*(s_island-2))
        if (i==5):
            p1_x=half_length-(((division)*(size_division)+(num_tam)*(tam_size)))/2
            p1_y=half_length-(((division)*(size_division)+(num_tam)*(tam_size)))/2
            p=5

        p2_x=p1_x-tam_size/2
        p2_y=p1_y+tam_size/2
        p3_x=p1_x-tam_size
        p3_y=p1_y
        p4_x=p1_x-tam_size/2
        p4_y=p1_y-tam_size/2
 
        xml_code += f"""<!-- * TAMS_Island_{i}-->    
            <box id="island_{i}_tam_1_1" movable="false" size="0.01,0.1,0.12">
            <body orientation="0,0,0" position="{p1_x},{p1_y},0"></body>
            <leds medium="leds">
            <led anchor="origin" color="green" id="led_isla_{i}_tam1_1" intensity="100.0" offset="0.01,0,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam1_2" intensity="100.0" offset="0.01,0.04,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam1_3" intensity="100.0" offset="0.01,-0.04,0.08"></led>
            </leds>
            </box>
            <box id="island_{i}_tam_1_2" movable="false" size="0.01,0.11,0.12">
            <body orientation="90,0,0" position="{p1_x+tam_size/2},{p1_y+tam_size/2},0"></body>
            </box>
            <box id="island_{i}_tam_1_3" movable="false" size="0.01,0.11,0.12">
            <body orientation="90,0,0" position="{p1_x+tam_size/2},{p1_y-tam_size/2},0"></body>
            </box>

            <box id="island_{i}_tam_2_1" movable="false" size="0.01,0.1,0.12">
            <body orientation="90,0,0" position="{p2_x},{p2_y},0"></body>
            <leds medium="leds">
            <led anchor="origin" color="green" id="led_isla_{i}_1" intensity="100.0" offset="0.01,0,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_2" intensity="100.0" offset="0.01,0.04,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_3" intensity="100.0" offset="0.01,-0.04,0.08"></led>
            </leds>
            </box>
            <box id="island_{i}_tam_2_2" movable="false" size="0.01,0.11,0.12">
            <body orientation="0,0,0" position="{p2_x+tam_size/2},{p2_y+tam_size/2},0"></body>
            </box>
            <box id="island_{i}_tam_2_3" movable="false" size="0.01,0.11,0.12">
            <body orientation="0,0,0" position="{p2_x-tam_size/2},{p2_y+tam_size/2},0"></body>
            </box>

            <box id="island_{i}_tam_3_1" movable="false" size="0.01,0.1,0.12">
            <body orientation="0,0,0" position="{p3_x},{p3_y},0"></body>
            <leds medium="leds">
            <led anchor="origin" color="green" id="led_isla_{i}_tam2_1" intensity="100.0" offset="-0.01,0,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam2_2" intensity="100.0" offset="-0.01,0.04,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam2_3" intensity="100.0" offset="-0.01,-0.04,0.08"></led>
            </leds>
            </box>
            <box id="island_{i}_tam_3_2" movable="false" size="0.01,0.11,0.12">
            <body orientation="90,0,0" position="{p3_x-tam_size/2},{p3_y+tam_size/2},0"></body>
            </box>
            <box id="island_{i}_tam_3_3" movable="false" size="0.01,0.11,0.12">
            <body orientation="90,0,0" position="{p3_x-tam_size/2},{p3_y-tam_size/2},0"></body>
            </box>

            <box id="island_{i}_tam_4_1" movable="false" size="0.01,0.1,0.12">
            <body orientation="90,0,0" position="{p4_x},{p4_y},0"></body>
            <leds medium="leds">
            <led anchor="origin" color="green" id="led_isla_{i}_tam3_1" intensity="100.0" offset="-0.01,0,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam3_2" intensity="100.0" offset="-0.01,0.04,0.08"></led>
            <led anchor="origin" color="green" id="led_isla_{i}_tam4_3" intensity="100.0" offset="-0.01,-0.04,0.08"></led>
            </leds>
            </box>
            <box id="island_{i}_tam_4_2" movable="false" size="0.01,0.11,0.12">
            <body orientation="0,0,0" position="{p4_x+tam_size/2},{p4_y-tam_size/2},0"></body>
            </box>
            <box id="island_{i}_tam_4_3" movable="false" size="0.01,0.11,0.12">
            <body orientation="0,0,0" position="{p4_x-tam_size/2},{p4_y-tam_size/2}+,0"></body>
            </box>
        """

    return xml_code


# Input wall length
wall_length = 5  # Adjust this value as needed
#Spaces for the islands
s_island=4
s_island_center=8
half_length = wall_length / 2.0
tam_size=0.1
division=12
size_division=0.4
num_tam=division-2

# Generate the Argos XML code for the big walls
argos_xml = generate_argos_wall(wall_length)
#argos_xml = islas()
# Save the XML code to a .txt file
with open("/home/jazmin/tuttifrutti/log/Tesis/Codigos/islas.txt", "w") as file:
    file.write(argos_xml)

print(f"Argos XML code for big walls has been saved to islas.txt")