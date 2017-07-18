PIODIR = .pio

INOPROJECT = .
BAUD = 115200
BOARD = noudemcudv2

MAKEFILEROOT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

.PHONY: firmware build upload monitor help clean

all: firmware

install-pip:
	wget https://bootstrap.pypa.io/get-pip.py
	sudo python get-pip.py && rm get-pip.py

install-platformio:
	which pip || $(MAKE) install-pip
	sudo pip install platformio
	sudo usermod -a -G dialout $$USER
	wget https://raw.githubusercontent.com/platformio/platformio/develop/scripts/99-platformio-udev.rules
	sudo mv -v 99-platformio-udev.rules /etc/udev/rules.d
	sudo service udev restart

firmware: build upload monitor

build:
	which platformio || $(MAKE) install-platformio
	@ echo "$$PIO_BUILD" | sh

upload:
	which platformio || $(MAKE) install-platformio
	cd $(PIODIR) && platformio run -t upload

monitor:
	platformio device monitor --baud $(BAUD)

qtmonitor:
	python3 $(MAKEFILEROOT)/../qtsermon.py -b $(BAUD)

help:
	@ echo "$$HELP_MAKEFILE"

clean:
	rm -rfv $(PIODIR)


define HELP_MAKEFILE
Usage:  make <target>   where <target> can be:

  build           Use platformio to build the firmware
  upload          Use platformio to upload to the board (rebuild if necessary)
  monitor         Use platformio serial monitor (auto-detect port)

  firmware        Perform all three steps in a row.

endef
export HELP_MAKEFILE


define PIO_BUILD
	mkdir -p $(PIODIR)
	rm -rf $(PIODIR)/src
	platformio init --board $(BOARD) -d $(PIODIR)
	cp -rf $(INOPROJECT)/* $(PIODIR)/src/
	cd $(PIODIR) && platformio run
endef
export PIO_BUILD
