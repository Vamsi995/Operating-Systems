LIBDIR := libs
OBJDIR := obj
EXEDIR := bin

EXE := $(EXEDIR)/calc
LIBS := $(addprefix $(LIBDIR)/,libiarith.a liberrhandler.a)
SRCS := $(wildcard src/*.c)
OBJS := $(addprefix $(OBJDIR)/,$(patsubst src/%.c,%.o,$(SRCS)))

vpath %.c src
vpath %.h include



all: $(EXE)
	@echo "Finished Successfully"
	
$(EXE): obj/main.o $(LIBS) | $(EXEDIR)
	gcc -o $@ -I include $< -L libs -liarith -lerrhandler

$(OBJDIR)/%.o: src/%.c calc.h error_handler.h | $(OBJDIR)
	gcc -o $@ -c -I include $<
	
$(LIBDIR)/libiarith.a: obj/add_sub.o obj/mul_div.o include/calc.h include/error_handler.h | $(LIBDIR)
	ar rcs $@ $^

$(LIBDIR)/liberrhandler.a: obj/error_handler.o | $(LIBDIR) 
	ar rcs $@ $^


$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

.PHONY: clean
clean:
	rm -rf $(EXEDIR) $(OBJDIR) $(LIBS)

