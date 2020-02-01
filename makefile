# 
MAKE = make --no-print-directory

#all: rs cs
#	@$(MAKE) -f makefile.all

cs:
	@$(MAKE) -f makefile.cs

rs:
	@$(MAKE) -f makefile.rs


clean:
	@$(MAKE) -f makefile.all clean
	@$(MAKE) -f makefile.rs clean
	@$(MAKE) -f makefile.cs clean
