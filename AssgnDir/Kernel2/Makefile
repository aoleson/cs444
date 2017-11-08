TARGET=project2
default: pdf

pdf: ps
	ps2pdf $(TARGET).ps

ps: dvi
	dvips $(TARGET).dvi

dvi: $(TARGET).tex
	latex $(TARGET).tex
	latex $(TARGET).tex
	latex $(TARGET).tex

clean:
	rm -f $(TARGET).aux
	rm -f $(TARGET).dvi
	rm -f $(TARGET).log
	rm -f $(TARGET).out
	rm -f $(TARGET).ps
	rm -f $(TARGET).blg
	rm -f $(TARGET).bbl
	rm -f $(TARGET).pdf

