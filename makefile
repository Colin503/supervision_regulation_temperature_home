# --- VARIABLES ---
# Le compilateur à utiliser
CC = gcc

# Les options de compilation (avertissements)
CFLAGS = -Wall -Wextra

# Les librairies pour l'édition de liens (nécessaire pour la carte électronique)
LDFLAGS = 


# Le nom de l'exécutable final
EXEC = projet.exe

# La liste des fichiers sources (.c)
# Note : Vous devrez ajouter ici simulateur.c, visualisationT.c, etc., selon le mode (USB ou Simulation)
SRC = commande.c consigne.c regulation.c releve.c main.c visualisationT.c visualisationC.c simulateur.c

# La liste des fichiers objets (.o générés à partir des .c)
OBJ = $(SRC:.c=.o)

# --- REGLES ---
# Règle par défaut, exécutée quand on tape juste 'make'
all: $(EXEC)

# Règle pour créer l'exécutable (Édition des liens)
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC)

# Règle pour compiler chaque fichier source en fichier objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets (.o)
clean:
	rm -f *.o

# Règle pour nettoyer tout ce qui a été généré (fichiers objets + exécutable)
mrproper: clean
	rm -f $(EXEC)