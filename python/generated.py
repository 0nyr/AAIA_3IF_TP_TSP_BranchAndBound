import turtle

from utils import mark_point

def draw_path_permutations(turtle_speed):
    # Configuration initiale
    turtle.setworldcoordinates(0, 0, 20000, 20100)
    p0=(17923,17709)
    p1=(4440,18165)
    p2=(4492,3042)
    p3=(7987,2503)


    # Affichage des points
    def mark_all_points():
        mark_point(p0)
        mark_point(p1)
        mark_point(p2)
        mark_point(p3)

    turtle.speed(turtle_speed)
    mark_all_points()

    wait = input("Enter return to start")

    # path permutation
    turtle.clear()
    mark_all_points()
    turtle.penup()
    turtle.goto(p0)
    turtle.pendown()
    turtle.goto(p1)
    turtle.goto(p2)
    turtle.goto(p3)
    turtle.goto(p0)
    turtle.update()
    wait = input("Enter return to continue")

