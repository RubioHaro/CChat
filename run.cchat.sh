## Script to compile and run the chat program

# Compile the program
echo "Compiling the client program..."
gcc client.c -o client
echo "Compiling the server program..."
gcc server.c -o server

## Show an ANSI big text of the program name

echo " __   __  ___  ___  ___"
echo "                       " 
echo " __   __            ___" 
echo "/  ` /  ` |__|  /\   | " 
echo "\__, \__, |  | /~~\  | " 
echo "                       " 
echo " __   __  ___  ___  ___"

echo " by Rodrigo Rubio"
                           


# Run the program
clear 

echo "Starting server..."

# esxecute the server and the client at the same time but in different terminals (any linux distro) for a better experience
gnome-terminal -e "./server" & gnome-terminal -e "./client"


# deepin-terminal -m fullscreen -e sh -c "./server; bash" & deepin-terminal -m fullscreen -e sh -c "./client; bash"

# deepin-terminal -e "./server" 
# deepin-terminal -e "./client"