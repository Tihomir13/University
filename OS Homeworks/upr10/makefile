compile:
                gcc -O0 -o init init.c -lshared
                gcc -O0 -o producer producer.c -lshared
                gcc -O0 -o consumer consumer.c -lshared

run:
                ./init
                ./producer &
                ./consumer &