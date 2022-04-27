CC= gcc
OBJS= AsciiArtTool.o main.o RLEList.o
EXEC= AsciiArtTool
DEBUG= -g
CFLAGS= -std=c99 -wall -werror $ (DEBUG)


AsciiArtTool: AsciiArtTool.h AsciiArtTool.c RLEList.h
	gcc 


$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o : AsciiArtTool.c RLEList.h AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
main.o : main.c RLEList.h AsciiArtTool.h	
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)
