# uncomment to choose platform for building  
BOARD = nodemcuv2
# BOARD = uno

# BAUD = 9600
BAUD = 115200

all: build monitor

build:
	rm -rf src && mkdir -p src && cp -a hcpachrono/. src/
	platformio run -t upload -e $(BOARD)
	rm -rf src

monitor:
	platformio device monitor --baud $(BAUD)

clean:
	rm -rf .pioenvs .piolibdeps src/*