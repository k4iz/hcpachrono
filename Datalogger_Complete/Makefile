# uncomment to choose platform for building  
BOARD = nodemcuv2
#BOARD = uno


all: build monitor

build:
	platformio run -t upload -e $(BOARD)

monitor:
	platformio device monitor