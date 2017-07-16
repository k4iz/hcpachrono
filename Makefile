# uncomment to choose platform for building  
# BOARD = nodemcuv2
BOARD = uno
BAUD = 115200


all: build monitor

build:
	platformio run -t upload -e $(BOARD)

monitor:
	platformio device monitor --baud $(BAUD)

clean:
	rm -rf .pioenvs .piolibdeps