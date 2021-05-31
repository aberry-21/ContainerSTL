.PHONY:		all re clean fclean
all:
	@mkdir -p build && cd build && cmake .. && make && mv list_test ..
clean:
	@find . -name *.o -delete
fclean:
	@rm -rf build && rm -rf list_test && rm -rf list_test.dSYM
re:			fclean all