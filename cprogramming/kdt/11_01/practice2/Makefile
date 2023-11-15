CFLAGS = -Wall -O -g
				
bin=prime
t1=practice2
t2=practice2_prime

obj=$(t1).o $(t2).o

all: $(bin)
$(bin): $(obj)
		$(CC) $(obj) -o $@

clean:
		rm -f $(bin) *.o