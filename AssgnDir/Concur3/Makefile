all: prob1 prob2 write_up

prob1:
	gcc prob1.c -o prob1 -lpthread

prob2:
	gcc -o prob2 -pthread prob2.c

write_up:
	pdflatex Concurrency3

clean:
	rm -f prob1 prob2 *.aux *.out *.log *.pdf
