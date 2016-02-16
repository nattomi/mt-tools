#!/usr/bin/env Rscript
f <- file("stdin")
open(f)
##write('ezt az R írja',stdout())
##while(length(line <- readLines(f,n=1)) > 0) {
##    write(line, stdout())
##}
##write('szia',stdout())
d <- read.table(f,header=TRUE)
plot(d$freq,d$rhoa,type="l",
     xlab="Frequency",ylab="Apparent resistivity")
