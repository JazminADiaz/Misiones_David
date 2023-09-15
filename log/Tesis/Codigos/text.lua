-- Load the contents of your text file
local textFile = io.open("/home/jazmin/tuttifrutti/log/Tesis/Codigos/big_walls.txt", "r")
if textFile then
   local fileContent = textFile:read("*all")
   textFile:close()

   -- Define a local function to include the content in your Argos arena configuration
   local function includeTextContent()
      -- Start your XML element here (e.g., if it's an obstacle)
      io.write('<obstacle>')
      -- Insert the content of your text file
      io.write(fileContent)
      -- Close your XML element here
      io.write('</obstacle>')
   end

   -- Call the function
   includeTextContent()
else
   print("Error: Unable to open the text file.")
end