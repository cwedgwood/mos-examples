
.EXTRA_PREREQS+=$(foreach mk, ${MAKEFILE_LIST},$(abspath ${mk}))

all: fmt test01.sim test01.xex
.PHONY: all

test01.sim: test01.cc
	mos-sim-clang -Wall -o $@ $^
#	llvm-size $@.elf
#	llvm-objdump --demangle -S $@.elf > $@.txt
	@echo
	mos-sim $@
	@echo

test01.xex: test01.cc
	mos-atari8-dos-clang -Wall -Oz -o $@ $^
	llvm-size $@.elf
	llvm-nm --demangle $@.elf
	llvm-objdump --demangle -S $@.elf $@.elf > $@.txt
	-[ -e a8test ] && ./a8test $@


clean:
	rm -vf test*sim*
	rm -vf test*xex*
	rm -vf *~

fmt:
	clang-format --style="{BasedOnStyle: llvm, ColumnLimit: 120}" -i *.cc # *.c *.h

.PHONY: fmt clean
