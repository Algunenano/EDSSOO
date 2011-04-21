SRCF		= src/
BUILDF 		= build/
INCLUDEF	= include/
FILES 		= main.c uah_arch_ps.c uah_sys_calls.c
SOURCES		= $(FILES:%.c=$(SRCF)%.c)
OBJECTS 	= $(SOURCES:$(SRCF)%.c=$(BUILDF)%.o)
HEADERS		= $(SOURCES:$(SCRF)%.c=$(INCLUDEF)%.h)
TARGET 		= $(BUILDF)main

CC		= gcc
PACKAGES	= 
HEADERFLAGS	= -I $(INCLUDEF) #$(shell pkg-config --cflags-only-I $(PACKAGES))
LDFLAGS 	= # $(shell pkg-config --libs $(PACKAGES))
CFLAGS		= -Wall -Wextra -g $(HEADERFLAGS)

RM		= rm -rf


$(TARGET):	$(OBJECTS)
	$(LINK.c) $(OBJECTS) -o $(TARGET)

$(BUILDF)%.o:	$(SRCF)%.c
	$(shell mkdir -p $(BUILDF))
	$(COMPILE.c) $< -o $@

clean:
	$(RM) $(TARGET) $(BUILDF)

