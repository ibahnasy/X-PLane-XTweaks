PLUGIN=XTweaks

CC=gcc
C_SRC=src
SDK=./SDK
OUTPUT=./bin/XTweaks

CFLAGS= -c -pipe -Wall -Wextra -Wshadow -Wfloat-equal -pedantic \
		-fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector \
		-funwind-tables -fasynchronous-unwind-tables -W -fPIC -DXPLM200 \
		-shared -rdynamic -nodefaultlibs -undefined_warning \
		-I$(SDK)/CHeaders/XPLM \
		-I$(SDK)/CHeaders/Widgets \
		-I/usr/local/include \
		-I/usr/include/GL \
		-I. \
		-DAPL=0 -DIBM=0 -DLIN=1

LFLAGS= -Wl,-O1 -shared -L$(SDK)/Libraries/ -lGL -lGLU


all: XTweaks_64.xpl XTweaks_32.xpl

XTweaks_64.xpl: XTweaks_64.o
	${CC} -m64 $(LFLAGS) ${LIBS} -o $(OUTPUT)/64/lin.xpl bin/$(PLUGIN)_64.o

XTweaks_64.o:
	${CC} -m64 -c $(CFLAGS) $(C_SRC)/$(PLUGIN).c -o bin/$(PLUGIN)_64.o


XTweaks_32.xpl: XTweaks_32.o
	${CC} -m32 $(LFLAGS) ${LIBS} -o $(OUTPUT)/32/lin.xpl bin/$(PLUGIN)_32.o

XTweaks_32.o:
	${CC} -m32 -c $(CFLAGS) $(C_SRC)/$(PLUGIN).c -o bin/$(PLUGIN)_32.o

clean:
	rm -f bin/*.d bin/*o $(OUTPUT)/64/*.xpl $(OUTPUT)/32/*.xpl


# gcc -c -m32 -pipe -Wall -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables  -W -fPIC -DXPLM200 -DAPL=0 -DIBM=0 -DLIN=1 -I../SDK/CHeaders/XPLM -I../SDK/CHeaders/Widgets -I. -I/usr/local/include -o XTweaks.o XTweaks.c
# gcc -m32 -Wl,-O1 -shared -L../SDK/Libraries/ -o lin.xpl XTweaks.o