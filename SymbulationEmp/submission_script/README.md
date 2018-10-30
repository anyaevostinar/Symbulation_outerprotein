Testing different population sizes:
1. Manually change vertical transmission rate in `SymSettings.cfg`  
2. Change filepath in `submission_pop_size.py` according to the instructions in the comments
3. Run `python submission_pop_size.py` on hpcc to submit tasks  

Testing different population structures:  
1. Set `WORLD_TYPE`in `SymSettings.cfg`  
2. Manually change `GRID_X` and `GRID_Y` in `SymSettings.cfg` to get the desired population size. (`GRID_X` * `GRID_Y` = population size in a grid world)
3. Change filepath in `submission_pop_struct.py` according to the instructions in the comments
4. Run `python submission_pop_struct.py` on hpcc to submit tasks

For both of the experiments, we tested with the following parameters:
- `MUTATION_RATE` = 0.002  
- `VERTICAL_TRANSMISSION` ranging from 0.0 to 1.0 in steps of 0.1  
- `HOST_INT` = -2, `SYM_INT` = -2 (meaning both host and symbiont have a randomized interaction value during setup)
- `UPDATES` = 100000 (the program will loop through the entire population 100000 times)
