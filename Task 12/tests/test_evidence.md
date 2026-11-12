# Task 12 Test Evidence

| Test | Input / condition | Expected | Observed |
|---|---|---|---|
| 1 | 0 50000 17:45 | 50,000 Wh, NORMAL | See execution_output.txt |
| 2 | 50000 150000 18:00 | 100,000 Wh, PEAK | See execution_output.txt |
| 3 | 150000 160000 22:00 | 10,000 Wh, NORMAL | See execution_output.txt |
| 4 | 160000 170000 21:45 | 10,000 Wh, PEAK | See execution_output.txt |
| 5 | PEAK boundary | 18:00 is peak; 22:00 is normal | Verified by execution |
| 6 | Runtime tariff | Change tariff.conf without recompilation | Configuration is read at startup |
