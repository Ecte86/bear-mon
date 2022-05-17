CC=oscar64

INCDIR=include
SRCDIR=src
OUTDIR=build
OUTNAME=$(OUTDIR)/ect-mon.prg
SRCS:=$(shell find $(SRCDIR) -name '*.c' -exec echo "{}" \;)
BUILT_FILES:=$(shell find build -maxdepth 1 -name 'ect-mon.*')
BUILT_FILES_NO_PRG:=$(shell find build -maxdepth 1 -type f \! -name 'ect-mon.prg')

.PHONY: all build run clean

all: clean build run

$(OUTNAME): build organise

build:
	$(CC) -i=$(INCDIR) $(SRCS) -o=$(OUTNAME)

run: $(OUTNAME)
	pwsh.exe /c $^

organise:
	@echo "Moving debug files to $(OUTDIR)/debug..."
	$(foreach file, $(BUILT_FILES), $(shell cp $(file) ./build/debug ;))
	$(foreach file, $(BUILT_FILES_NO_PRG), $(shell mv $(file) ./build/debug ;))
	@echo "...done!"
clean:
	find -type f -wholename $(OUTNAME) -exec rm {} \;
