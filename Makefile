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

debug :
	make compile=debug
	#sudo $(DEBUGTOOL) $(TARGET)

clean :
	-rm -f $(TARGET) $(OBJDIRS)/*

cleanresult :
	-rm -f result.out resource/network/*

cleanobj :
	-rm -f $(OBJDIRS)/*

cleanlog :
	-rm -f logInfo.log

#清理整个工程临时文件
cleanall : clean cleanresult cleanobj cleanlog

include $(MAKEFILEINCLUDE)
