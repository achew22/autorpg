autorpg: Animation.o Background_Object.o Character.o Dynamic_Object.o Graphics.o Instance.o Interact_Object.o Parser.o Point.o Sprite_Sheet.o main.o
	g++ -o autorpg Animation.o Background_Object.o Character.o Dynamic_Object.o Graphics.o Instance.o Interact_Object.o Parser.o Point.o Sprite_Sheet.o main.o -lSDL -lSDL_image

Animation.o: Animation.cpp Animation.h constants.h Sprite_Sheet.h
	g++ -c Animation.cpp -lSDL -lSDL_image

Background_Object.o: Background_Object.cpp Background_Object.h Instance.h constants.h
	g++ -c Background_Object.cpp -lSDL -lSDL_image

Character.o: Character.cpp Character.h Instance.h Graphics.h Dynamic_Object.h Animation.h Point.h
	g++ -c Character.cpp -lSDL -lSDL_image

Dynamic_Object.o: Dynamic_Object.cpp Dynamic_Object.h constants.h Animation.h Point.h
	g++ -c Dynamic_Object.cpp -lSDL -lSDL_image

Graphics.o: Graphics.cpp Graphics.h constants.h
	g++ -c Graphics.cpp -lSDL -lSDL_image

Instance.o: Instance.cpp Instance.h Background_Object.h Interact_Object.h Character.h constants.h Point.h Dynamic_Object.h Sprite_Sheet.h Graphics.h
	g++ -c Instance.cpp -lSDL -lSDL_image

Interact_Object.o: Interact_Object.cpp Interact_Object.h Dynamic_Object.h constants.h
	g++ -c Interact_Object.cpp -lSDL -lSDL_image

Parser.o: Parser.cpp
	g++ -c Parser.cpp -lSDL -lSDL_image

Point.o: Point.cpp Point.h
	g++ -c Point.cpp -lSDL -lSDL_image

Sprite_Sheet.o: Sprite_Sheet.cpp Sprite_Sheet.h constants.h Graphics.h
	g++ -c Sprite_Sheet.cpp -lSDL -lSDL_image

main.o: main.cpp constants.h Instance.h Character.h Dynamic_Object.h Graphics.h
	g++ -c main.cpp -lSDL -lSDL_image