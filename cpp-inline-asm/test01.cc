// experiment on how we might access object members from inline assembly
//
// this version needs no specific knowledge of the c++ ABI

// https://discord.com/channels/1058149494107148399/1058150507639754762/1200509551800238080

#include <stdio.h>

// We pass in a pointer to the member and have the assembly write to
// that.  There are no absolute addresses.  Options:
//
// Indirect,X    STA ($44,X)   $81  2   6        -> write via ptr [$44 + X]
// Indirect,Y    STA ($44),Y   $91  2   6        -> write via ptr [$44] + y

class test {

// the NOPs are not required, they exist to aid in code inspection and
// debugging
public:
  char q1, q2;
  void addSomething() {
    asm volatile("nop \n"              // for inspection/debugging
                 "ldy #0 \n"           // will be using indirect Y
                 "lda %[v_q1] \n"      // a value value is passed in
                 "adc #05 \n"          //
                 "sta  (%[p_q2]),y \n" // a pointer passed in
                 "nop \n"              // for inspection/debugging
                 :
                 : [v_q1] "r"(this->q1), // pass in by value
                   [p_q2] "m"(this->q2)  // pass in pointer _of_
                 : "a", "y", "p");
  };
  void status() { printf("st: @=0x%p q1=%d q2=%d sizeof %d\n", this, this->q1, this->q2, sizeof(this)); }
  int other() { return q1; }
};

int main() {
  auto o1 = new (test);
  auto o2 = new (test);
  auto o3 = new (test);

  o1->q1 = 11;
  o2->q1 = 22;
  o3->q1 = 33;

  o1->status();
  o2->status();
  o3->status();

  o1->addSomething();
  o2->addSomething();
  o3->addSomething();

  puts("");

  o1->status();
  o2->status();
  o3->status();

#ifdef __ATARI__
  getchar();
#endif
}
