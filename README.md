# COMP-3430-Assignment-3

## How to compile

---

cd to the directory of the submission and run the command "make"

## How to clean

---

cd to the directory of the submission and run the command "make clean"

## How to run

---

Use the command "./a3q1 x y"
where x is the number of CPUs
where y is the scheduling algorithm either rr, stcf or mlfq

## Analysis

---

The average priority and type times for 2 CPUs

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|    PRR    |     2      |      4939      |      4370      |      5250      |    592     |    1146    |    7869    |   10314    |
|    PRR    |     2      |      4951      |      4411      |      5230      |    558     |    1258    |    8571    |   10753    |
|    PRR    |     2      |      4990      |      4363      |      5223      |    686     |    1054    |    7847    |   10351    |
|    PRR    |     2      |      5149      |      4323      |      5097      |    648     |    1113    |    7806    |   10269    |
|    PRR    |     2      |      5002      |      4502      |      5269      |    585     |    1135    |    8056    |   10423    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     2      |     5006.2     |     4393.8     |     5213.8     |   613.8    |   1141.2   |   8029.8   |   10422    |
| Standard Deviation |     2      |     75.15      |     60.88      |     60.58      |   46.47    |   66.49    |   283.88   |   173.02   |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   STCF    |     2      |      2620      |      2468      |      2827      |     81     |    361     |    5304    |    5023    |
|   STCF    |     2      |      2600      |      2453      |      2677      |     81     |    379     |    5163    |    4856    |
|   STCF    |     2      |      2694      |      2547      |      2926      |     74     |    443     |    5685    |    4876    |
|   STCF    |     2      |      2432      |      2541      |      2949      |     86     |    368     |    5441    |    4962    |
|   STCF    |     2      |      2551      |      2463      |      2775      |     73     |    360     |    5242    |    4927    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     2      |     2579.4     |     2494.4     |     2830.8     |     79     |   382.2    |    5367    |   4928.8   |
| Standard Deviation |     2      |     86.88      |     49.82      |     99.81      |    4.85    |   31.14    |   183.19   |   60.11    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   MLFQ    |     2      |      1520      |      4933      |      9812      |    3511    |    5262    |    6883    |    8453    |
|   MLFQ    |     2      |      2013      |      4683      |      9919      |    3981    |    4563    |    7396    |    8578    |
|   MLFQ    |     2      |      1593      |      5055      |      9880      |    3643    |    5360    |    6926    |    8533    |
|   MLFQ    |     2      |      1543      |      4926      |      9920      |    3508    |    5199    |    6990    |    8613    |
|   MLFQ    |     2      |      1584      |      5202      |     10732      |    4268    |    6197    |    6794    |    8737    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     2      |     1650.6     |     4959.8     |    10052.6     |   3782.2   |   5316.2   |   6997.8   |   8582.8   |
| Standard Deviation |     2      |     183.15     |     170.99     |     341.96     |   297.87   |   521.86   |   209.04   |   93.85    |

The average priority and type times for 8 CPUs

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|    PRR    |     8      |      1255      |      1101      |      1309      |    147     |    292     |    1944    |    2628    |
|    PRR    |     8      |      1206      |      1101      |      1324      |    147     |    283     |    1940    |    2614    |
|    PRR    |     8      |      1236      |      1107      |      1322      |    148     |    287     |    1947    |    2646    |
|    PRR    |     8      |      1258      |      1116      |      1324      |    147     |    283     |    1940    |    2614    |
|    PRR    |     8      |      1236      |      1107      |      1314      |    146     |    285     |    1995    |    2615    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     8      |     1238.2     |     1106.4     |     1318.6     |    147     |    286     |   1953.2   |   2623.4   |
| Standard Deviation |     8      |     18.55      |      5.49      |      6.05      |    0.63    |    3.34    |   21.06    |   12.48    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   STCF    |     8      |      668       |      674       |      741       |     22     |     95     |    1362    |    1365    |
|   STCF    |     8      |      678       |      675       |      761       |     25     |     97     |    1388    |    1380    |
|   STCF    |     8      |      665       |      688       |      755       |     23     |    100     |    1372    |    1391    |
|   STCF    |     8      |      664       |      686       |      742       |     22     |    104     |    1384    |    1345    |
|   STCF    |     8      |      675       |      676       |      746       |     22     |     97     |    1365    |    1379    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     8      |      670       |     679.8      |      749       |    22.8    |    98.6    |   1953.2   |   1374.2   |
| Standard Deviation |     8      |      5.54      |      5.94      |      7.77      |    1.16    |    3.13    |   21.06    |   10.24    |

| Algorithm | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :-------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|   MLFQ    |     8      |      383       |      1237      |      2441      |    835     |    1299    |    1755    |    2128    |
|   MLFQ    |     8      |      390       |      1241      |      2474      |    838     |    1326    |    1767    |    2150    |
|   MLFQ    |     8      |      382       |      1236      |      2477      |    838     |    1287    |    1769    |    2182    |
|   MLFQ    |     8      |      392       |      1253      |      2436      |    868     |    1299    |    1727    |    2151    |
|   MLFQ    |     8      |      388       |      1242      |      2406      |    866     |    1290    |    1709    |    2109    |

|       Value        | No of CPUs | Priority 0 Avg | Priority 1 Avg | Priority 2 Avg | Type 0 Avg | Type 1 Avg | Type 2 Avg | Type 3 Avg |
| :----------------: | :--------: | :------------: | :------------: | :------------: | :--------: | :--------: | :--------: | :--------: |
|      Average       |     8      |      387       |     1241.8     |     2446.8     |    849     |   1300.2   |   1745.4   |    2144    |
| Standard Deviation |     8      |      3.89      |      6.04      |     26.33      |   14.75    |   13.76    |   23.57    |   24.53    |

Are the distributions generated significantly different?

The data obtained from all the algorithms are highly statistically different in terms of run time.

How did the algorithms treat the queue differently, and how is that reflected in the data?

- Round Robin: Here all tasks are executed equally and thus we do not see any trend in our average run time by any priority or type.
- STCF: Here tasks are prioritized based on their lengths. This is shown in the data, where we see that the shortest tasks were completed first.
- MLFQ: Here we use multiple queues which are handled differently. From the data, we can see that tasks with in higher priority queues complete in shorter time
  as compared to tasks with lower priorities

How does the number of “CPU”s affect each scheduling policy?

From the data, it is evident that increasing the number of CPUs reduces the average run time of all the tasks and thus, we can conclude that
the average time of completion reduces as the number of CPUs are increased.
