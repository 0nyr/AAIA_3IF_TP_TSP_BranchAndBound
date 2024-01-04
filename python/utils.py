import turtle

# Fonction pour marquer et dessiner un cercle à chaque point
def mark_point(point):
    turtle.tracer(0, 0)  # Désactivez l'animation de la tortue
    turtle.penup()
    turtle.goto(point)
    turtle.pendown()
    turtle.circle(100)  # Vous pouvez ajuster la taille du cercle ici
    turtle.penup()
    turtle.update()  # Mise à jour de l'écran
    turtle.tracer(1, 10)  # Réactivez l'animation de la tortue
