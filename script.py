import turtle

try:
    # Set the world coordinates
    turtle.setworldcoordinates(0, 0, 20000, 201100)

    # Points definition
    p0 = (16807, 15249)
    p1 = (10073, 3658)
    p2 = (8930, 11272)

    # Add your drawing code here
    # Example: turtle.goto(p0)

    # Wait for a user event to close the window
    turtle.done()

except KeyboardInterrupt:
    print("Program interrupted with Ctrl+C")
    turtle.bye()  # This closes the turtle graphics window
