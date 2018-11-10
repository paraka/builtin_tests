LIBPBIT=library
SAMPLE=sample

all:
	(cd $(LIBPBIT); make)
	(cd $(SAMPLE); make)

clean:
	(cd $(LIBPBIT); make clean)
	(cd $(SAMPLE); make clean)
	rm -f core
