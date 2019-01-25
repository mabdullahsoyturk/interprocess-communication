SUBDIRS = psearch1a psearch1b psearch1c psearch2a psearch2aslave psearch2b psearch2bslave psearch2c psearch2cslave psearch2d psearch2dslave psearch3

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

