CFLAGS = -Wall -O -g
				
bin=inode
t1=practice3

obj=$(t1).o

all: $(bin)
$(bin): $(obj)
		$(CC) $(obj) -o $@

clean:
		rm -f $(bin) *.o