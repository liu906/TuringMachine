; This turing machine program check if a string is 0^k where k is a fibonacci number
; Input: a string of 0's, eg '0000'

; the finite set of states
#Q = {0,accept,accept1,accept2,accept3,halt_accept,reject,reject1,reject2,reject3,reject4,halt_reject,is1,add1,add2,compare,reset0,rewrite}

; the finite set of input symbols
#S = {0}

; the complete set of tape symbols
#G = {0,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}


; the number of tapes
#N = 4

; the transition functions
; State 0: begin
0 ____ ____ **** accept     ; Empty input
0 0___ 000_ r*** is1
is1 _00_ _00_ l*** accept
is1 000_ 000_ l*** add1

; add tape1 to tape3
add1 000_ 0000 *r*r add1
add1 0_0_ 0_0_ **** add2
add2 0_0_ 0_00 **rr add2
add2 0___ 0___ **ll compare

; compare tape3 with tape0
compare 0**0 0**0 r**l compare
compare _**_ _**_ l*** accept
compare _**0 _**0 l*** reject
compare 0**_ 0**_ ***r reset0

; reset index location of tape0, make it back to most left
reset0 0*** 0*** l*** reset0
reset0 _*** _*** r*** rewrite

; rewrite tape2 by tape1
rewrite 0_00 0_00 *l** rewrite

rewrite *0** *00* *ll* rewrite
rewrite 0_** 0_** *rr* back1
back1 *0** *0** *r** back1
back1 *_** *_** **** back2
back2 **0* **0* **r* back2
back2 **_* **_* **l* rewrite1


; rewrite tape1 by tape3
rewrite1 ***0 *0*_ *l*r rewrite1
rewrite1 ***_ ***_ *r** reset2

; reset index location of tape2, make it back to most left
reset2 **0* **0* **l* reset2
reset2 **_* **_* **r* add1

; clean tape0 then write "False"

reject 0*** _*** l*** reject
reject _*** F*** r*** reject1
reject1 _*** a*** r*** reject2
reject2 _*** l*** r*** reject3
reject3 _*** s*** r*** reject4
reject4 _*** e*** r*** halt_reject

; clean tape0 then write "True"
accept 0*** _*** l*** accept
accept _*** T*** r*** accept1
accept1 _*** r*** r*** accept2
accept2 _*** u*** r*** accept3
accept3 _*** e*** r*** halt_accept


  

