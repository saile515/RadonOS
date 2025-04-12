#!/bin/sh

bear -- make && qemu-system-i386 -smp 2 -m 1G -machine type=q35,accel=kvm -cdrom build/radonos.iso
