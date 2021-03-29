# COMP-3430-Assignment-3

## How to compile

---

cd to the directory of the submission and run the command "make"

## How to run

---

Use the command "./q1 executable"
where executable is a proccess for example cat

## Design Choices

---

I use a buffer with a fixed size and assumes that all input recieved will be less than the buffer size. I attempted to check for the EOF from read however it does not end when using CTRL D, so CTRL C is used to end the code.

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|    PRR    |     2      |      4939      |      4370      |      5250      |    592     |    1146    |    7869    |   10314    |
|    PRR    |     2      |      4951      |      4411      |      5230      |    558     |    1258    |    8571    |   10753    |
|    PRR    |     2      |      4990      |      4363      |      5223      |    686     |    1054    |    7847    |   10351    |
|    PRR    |     2      |      5149      |      4323      |      5097      |    648     |    1113    |    7806    |   10269    |
|    PRR    |     2      |      5002      |      4502      |      5269      |    585     |    1135    |    8056    |   10423    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   STCF    |     2      |      2620      |      2468      |      2827      |     81     |    361     |    5304    |    5023    |
|   STCF    |     2      |      2600      |      2453      |      2677      |     81     |    379     |    5163    |    4856    |
|   STCF    |     2      |      2694      |      2547      |      2926      |     74     |    443     |    5685    |    4876    |
|   STCF    |     2      |      2432      |      2541      |      2949      |     86     |    368     |    5441    |    4962    |
|   STCF    |     2      |      2551      |      2463      |      2775      |     73     |    360     |    5242    |    4927    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   MLFQ    |     2      |      1520      |      4933      |      9812      |    3511    |    5262    |    6883    |   84538    |
|   MLFQ    |     2      |      2013      |      4683      |      9919      |    3981    |    4563    |    7396    |    8578    |
|   MLFQ    |     2      |      1593      |      5055      |      9880      |    3643    |    5360    |    6926    |    8533    |
|   MLFQ    |     2      |      1543      |      4926      |      9920      |    3508    |    5199    |    6990    |    8613    |
|   MLFQ    |     2      |      1584      |      5202      |     10732      |    4268    |    6197    |    6794    |    8737    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|    PRR    |     8      |      1255      |      1101      |      1309      |    147     |    292     |    1944    |    2628    |
|    PRR    |     8      |      1206      |      1101      |      1324      |    147     |    283     |    1940    |    2614    |
|    PRR    |     8      |      1236      |      1107      |      1322      |    148     |    287     |    7847    |    2646    |
|    PRR    |     8      |      1258      |      1116      |      1324      |    147     |    283     |    1940    |    2614    |
|    PRR    |     8      |      1236      |      1107      |      1314      |    146     |    285     |    1995    |    2615    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   STCF    |     8      |      668       |      674       |      741       |     22     |     95     |    1362    |    1365    |
|   STCF    |     8      |      678       |      675       |      761       |     25     |     97     |    1388    |    1380    |
|   STCF    |     8      |      665       |      688       |      755       |     23     |    100     |    1372    |    1391    |
|   STCF    |     8      |      664       |      686       |      742       |     22     |    104     |    1384    |    1345    |
|   STCF    |     8      |      675       |      676       |      746       |     22     |     97     |    1365    |    1379    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   MLFQ    |     8      |      383       |      1237      |      2441      |    835     |    1299    |    1755    |    2128    |
|   MLFQ    |     8      |      390       |      1241      |      2474      |    838     |    1326    |    1767    |    2150    |
|   MLFQ    |     8      |      382       |      1236      |      2477      |    838     |    1287    |    1769    |    2182    |
|   MLFQ    |     8      |      392       |      1253      |      2436      |    868     |    1299    |    1727    |    2151    |
|   MLFQ    |     8      |      388       |      1242      |      2406      |    866     |    1290    |    1709    |    2109    |
