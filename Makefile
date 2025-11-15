CC = gcc
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LD = ld
LDFLAGS = -m elf_i386 -nostdlib

KERNEL_OBJS = boot/multiboot_header.o kernel/main.o kernel/vga.o

all: os.iso

boot/multiboot_header.o: boot/multiboot_header.S
	$(CC) $(CFLAGS) -c boot/multiboot_header.S -o boot/multiboot_header.o

kernel/main.o: kernel/main.c kernel/vga.h
	$(CC) $(CFLAGS) -c kernel/main.c -o kernel/main.o

kernel/vga.o: kernel/vga.c kernel/vga.h
	$(CC) $(CFLAGS) -c kernel/vga.c -o kernel/vga.o

kernel.bin: $(KERNEL_OBJS) linker.ld
	$(LD) $(LDFLAGS) -T linker.ld -o kernel.bin $(KERNEL_OBJS)

os.iso: kernel.bin
	mkdir -p iso/boot/grub
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "myos" { multiboot /boot/kernel.bin }' >> iso/boot/grub/grub.cfg
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o os.iso iso

run: os.iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -rf kernel.bin os.iso iso boot/*.o kernel/*.o
