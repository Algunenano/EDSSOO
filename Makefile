SRCF		= src/
BUILDF 		= build/
INCLUDEF	= include/
FILES 		= prac4b.c \
	uah_arch_ps.c uah_sys_calls.c uah_irq_handlers.c uah_exc_handlers.c \
	uah_set_up.c uah_pcb.c uah_scheduler.c uah_emu_session.c \
	uah_dev_manager.c uah_device0.c uah_device1.c
SOURCES		= $(FILES:%.c=$(SRCF)%.c)
OBJECTS 	= $(SOURCES:$(SRCF)%.c=$(BUILDF)%.o)
HEADERS		= $(SOURCES:$(SCRF)%.c=$(INCLUDEF)%.h)
TARGET 		= $(BUILDF)prac4b

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

