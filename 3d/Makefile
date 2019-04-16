NAME = fractol

FLAGS = -c -g #-O3
MLXFLAGS = -lmlx -framework OpenGL -framework OpenCL -framework AppKit #-fsanitize=address -g

SOURCES = main.c \
		  math_vec.c \
		  initialisation.c \
		  initialisationCL.c \
		  sphere.c \
		  utilits.c

#events.c \
#main.c \

INCLUDES = $(addprefix -I, ./includes)

LIB = libft/libft.a

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(LIB) $(NAME)

$(LIB):
			@echo "\x1b[35;01mCompilation Lib and binary\x1b[32;01m"
			@make -C ./libft

$(NAME):	$(OBJS)
			gcc -I /usr/local/include $(OBJS) $(LIB) -L /usr/local/lib/ $(MLXFLAGS) -o $(NAME)

$(OBJS):	$(DIR_O)/%.o: $(DIR_S)/%.c includes/config.h
			@mkdir -p $(DIR_O)
			gcc $(FLAGS) $(INCLUDES) -o $@ $<

clean:
			@echo "\x1b[36;01mDeliting .o files\x1b[31;01m"
			@/bin/rm -rf $(DIR_O)
			@make clean --directory ./libft

fclean: clean
			@echo "\x1b[36;01mDeliting execute file\x1b[31;01m"
			@/bin/rm -f $(NAME)
			@make fclean --directory ./libft

re: fclean all
