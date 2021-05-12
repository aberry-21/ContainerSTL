.PHONY:		all re clean fclean
all:
	@mkdir -p build && cd build && cmake .. && make && mv vector_test ..
clean:
	@find . -name *.o -delete
fclean:
	@rm -rf build && rm -rf vector_test && rm -rf vector_test.dSYM
re:			fclean all