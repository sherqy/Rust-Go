CFLAGS = -Wall -O -g
				
bin=gugu
t1=practice1
t2=practice1_99

obj=$(t1).o $(t2).o

all: $(bin)
$(bin): $(obj)
		$(CC) $(obj) -o $@

clean:
		rm -f $(bin) *.o