# Global Makefile, build and clean all library subdirectories.
#
# All subdirectories will be built, EXCEPT for integration-tests.

SUBDIRS = avr-utils avr-alarm avr-am avr-buzzer avr-tone

.PHONY: all clean install $(INSTALLDIRS) $(CLEANDIRS)

all: install


# Installation
AVR_PREFIX=$(PREFIX)
INSTALLDIRS = $(SUBDIRS:%=install-%)

install: $(INSTALLDIRS)
$(INSTALLDIRS):
	$(MAKE) -C $(@:install-%=%) install PREFIX="$(AVR_PREFIX)/$(@:install-%=%)"

# dependencies between lib subdirs: What's on the left can ONLY be built after what's on the right
install-avr-alarm: install-avr-utils
install-avr-am: install-avr-utils
install-avr-buzzer: install-avr-utils
install-avr-tone: install-avr-alarm install-avr-utils


# Cleaning
CLEANDIRS = $(SUBDIRS:%=clean-%)

clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

