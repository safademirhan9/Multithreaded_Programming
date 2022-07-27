Program Nasil Calisir?

gcc client.c -o client -lpthread
gcc server.c -o server -lpthread

seklinde derleyebilirsiniz.

./client
./server

seklinde de kodlari kosturabilirsiniz.


Kodumda var olan ozellikler:
Multithreaded calisir ve Mailbox kullanir.
1000 elemanlik dizi client tarafindan server'a msgsnd edilir ve server bunu msgrcv ile alir.
Random olusturulmus bu diziyi insertion sort ile azalmayan sirada siralar ve yazdirir.
Server ayni zamanda bu siralanmis diziyi PID.txt dosyasina yazar.
Bu islemler worker thread'e yaptirilir, bu sirada main thread beklemektedir.

Safa Demirhan
171101070