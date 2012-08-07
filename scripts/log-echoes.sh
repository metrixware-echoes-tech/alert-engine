#!/bin/bash
#<165>1 2003-10-11T22:14:15Z mymachine.example.com echoes-alert-probe 3216 ID47 [prop@IANA ver=1 probe=ID_PRO][res@IANA offset=15 ID_PLG-ID_ASS-ID_SRC-ID_SE-ID_SUB_SE="543" ID_PLG-ID_ASS-ID_SRC-ID_SE-ID_SUB_SE="546"]

echo '<165>1 2003-10-11T22:14:15Z mymachine.example.com echoes-alert-probe 3216 ID47 [prop@5875 ver=1 probe=12][res2@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"][res1@5875 offset=15 8-4-5-6-2="543" 8-4-5-6-1="54546"]' | nc 172.16.3.101 514
