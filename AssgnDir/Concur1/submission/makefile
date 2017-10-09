concurrency1: concurrency1.c
	gcc -pthread -o concurrency1 concurrency1.c
	./changes.sh > changelog.tex
	pdflatex Assignment1.tex

clean:
	rm -f ./concurrency1
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean concurrency1 pdf
