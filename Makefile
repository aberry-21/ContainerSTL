.PHONY:		all re clean fclean
all:
	@mkdir -p build && cd build && cmake .. && make
clean:
	@find . -name *.o -delete
fclean:
	@rm -rf build
re:			fclean all

norm:
	@cpplint --filter=-legal/copyright --recursive .