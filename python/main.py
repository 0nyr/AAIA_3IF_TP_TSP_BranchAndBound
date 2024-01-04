import turtle

# Check if the generated file exists
try:
    from generated import *
except ImportError: 
    print("ERROR: The generated file does not exist, please run 'make run' first.")
    exit()

from generated import *

# Set speed to 0 for instant drawing
# Set speed to 1 for slow drawing, to 10 for fast drawing
TURTLE_SPEED = 10

def main():
    try:
        draw_path_permutations(TURTLE_SPEED)
        print("Reached end")

        # N'oubliez pas de fermer le programme proprement à la fin
        wait = input("Enter return to close window")
        turtle.bye()
        exit()

    except KeyboardInterrupt:
        print("Program interrupted with Ctrl+C")
        turtle.bye()  # This closes the turtle graphics window

if __name__ == "__main__":
    main()
