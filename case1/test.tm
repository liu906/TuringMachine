; This turing machine program check if a string is ww where w is a string of 0's and 1's
; Input: a string of 0's and 1's, eg '1001001'

; the finite set of states
#Q = {0,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject1,reject2,reject3,reject4,halt_reject,reject5,continue,check,rend,cp,mr,ml,rc1,rc2,lc1,lc2,start,back,reach,odd}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_,T,r,u,e,F,a,l,s,#}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}


; the number of tapes
#N = 2

; the transition functions
0 __ __ ** accept     ; Empty input

0 0_ 00 r* 0
0 1_ 10 r* 0
0 10 11 r* 0
0 00 01 r* 0
0 01 00 r* 0
0 11 10 r* 0
0 _0 __ l* odd
odd 1* _* l* odd
odd 0* _* l* odd
odd _* _* ** reject

0 _1 __ l* continue

continue 0_ 0_ l* continue
continue 1_ 1_ l* continue

continue __ _# rr cp
cp 0_ 00 rr cp
cp 1_ 11 rr cp
cp __ _# ** rend
rend *# *# l* lc1

; left copy
lc1 0# #0 *l lc2
lc1 1# #1 *l lc2
lc2 #0 0# *l ml
lc2 #1 1# *l ml


; move left
ml *1 *1 ll ml
ml *0 *0 ll ml
ml *# *# ** rc1

; right copy
rc1 0# #0 *r rc2
rc1 1# #1 *r rc2
rc2 #0 0# rr check
rc2 #1 1# rr check

check *# *# ** reach
check *0 *0 ** mr
check *1 *1 ** mr

; move right
mr *0 *0 rr mr
mr *1 *1 rr mr
mr *# *# ** rend



reach *# *# *r back
; found middle point and first tape back to start
back 1* 1* l* back
back 0* 0* l* back
back _* _* r* start

; start compare front part and second part of string ww
start 01 _1 r* reject
start 10 _0 r* reject

start 00 _0 rr start
start 11 _1 rr start
start *_ __ r* accept
accept ** T* r* accept1
accept1 ** r* r* accept2
accept2 ** u* r* accept3
accept3 ** e* r* accept4
accept4 0* _* r* accept4
accept4 1* _* r* accept4
accept4 _* _* ** halt_accept


reject ** F* r* reject1
reject1 ** a* r* reject2
reject2 ** l* r* reject3
reject3 ** s* r* reject4
reject4 ** e* r* reject5
reject5 _* _* ** halt_reject
reject5 0* _* rr reject5
reject5 1* _* rr reject5

reject _* ** ** halt_reject





