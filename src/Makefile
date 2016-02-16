CC = gcc
CFLAGS = -Wall -pedantic -std=c99

MTDIR = mt
MTFLAG = -lmt
MTLIB = $(MTDIR)libmt.a
MTC = $(MTDIR)/io.c $(MTDIR)/periods.c $(MTDIR)/filter.c
MTH = $(MTC:.c = .h)

all : print filter mtforward1d genfreqs

print : print.c $(MTDIR)/io.h $(MTLIB)
	$(CC) $(CFLAGS) -o print print.c -L$(MTDIR) $(MTFLAG) -lnetcdf

filter : print.c $(MTDIR)/io.h $(MTDIR)/periods.h $(MTDIR)/filter.h $(MTLIB)
	$(CC) $(CFLAGS) -o filter filter.c -L$(MTDIR) $(MTFLAG) -lnetcdf -lm

mtforward1d : mtforward1d.c
	$(CC) -o mtforward1d mtforward1d.c -ljson -lm

genfreqs : genfreqs.c
	$(CC) -o genfreqs genfreqs.c -ljson

$(MTLIB) : $(MTC) $(MTH)
	cd $(MTDIR); make;
clean:
	rm -f print
	rm -f filter
