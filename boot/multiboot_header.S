.section .multiboot
.align 4
.set MAGIC,     0x1BADB002
.set FLAGS,     0x00000003
.set CHECKSUM,  -(MAGIC + FLAGS)

.long MAGIC
.long FLAGS
.long CHECKSUM

.text
.global start

start:
    cli
    call kmain
hang:
    hlt
    jmp hang
