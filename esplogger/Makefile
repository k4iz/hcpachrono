# uncomment to choose platform for building  
BOARD = nodemcuv2
# BOARD = nanoatmega328

# BAUD = 9600
BAUD = 115200

all: build monitor

build:
	rm -rf src && mkdir -p lib && mkdir -p src && cp -a esplogger/. src/
	platformio run -t upload -e $(BOARD)
	rm -rf src

monitor:
	platformio device monitor --baud $(BAUD) --port COM11

clean:
	rm -rf .pioenvs .piolibdeps src/*