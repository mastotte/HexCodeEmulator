PHONY: format

SRCDIR = Source_Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS= $(wildcard $(SRCDIR)/*.h)

format:
	clang-format $(SOURCES) $(HEADERS) -i --style=google 

verify-format: 
	clang-format $(HEADERS) $(SOURCES)  --dry-run --Werror --style=Google