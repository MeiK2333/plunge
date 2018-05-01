test: cpu_time_out real_time_out output_size_out stack_limit_out
	echo 'make success'

cpu_time_out: cpu_time_out.c
	gcc -o cpu_time_out.out cpu_time_out.c

real_time_out: real_time_out.c
	gcc -o real_time_out.out real_time_out.c

output_size_out: output_size_out.c
	gcc -o output_size_out.out output_size_out.c

stack_limit_out: stack_limit_out.c
	gcc -o stack_limit_out.out stack_limit_out.c

clean:
	rm -f *.o