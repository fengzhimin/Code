DEBUGTOOL = kdbg
TARGET = exe
SUBDIRS = src
OBJECTS = 
export PROJECTPWD = $(PWD)
export MAKEFILEINCLUDE = ${PROJECTPWD}/makefile.config/Make.global
export INCLUDES = -I$(PROJECTPWD)/include 
export OBJDIRS = $(PROJECTPWD)/obj

all : subdirs $(SUBDIRS)
	$(CC) -o $(TARGET) $(OBJDIRS)/*.o $(LDFLAGS) $(INCLUDES)
#	$(CC) -o $(TARGET) $(wildcard $(OBJDIRS)/*.o) $(LDFLAGS) $(INCLUDES)

kdbg :
	$(DEBUGTOOL) $(TARGET)

clean :
	rm -f $(TARGET) $(OBJDIRS)/*

cleanobj :
	rm -f $(OBJDIRS)/*

cleanlog :
	-rm -f logInfo.log

include $(MAKEFILEINCLUDE)
