compile:
	gcc ./src/visuals.c ./src/draw.c ./src/cmd.c ./src/graph.c ./src/clock.c -lm -o visuals && ./visuals
