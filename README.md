# VM_Packing

Execution steps:

first_round_read_data.c -> sorting.c -> merge_first_new.c -> kruskal.c -> tree_sim.c -> merge.c -> other_round_read_data.c 
-> sorting.c -> other_round_merge_first.c -> kruskal.c -> tree_sim.c -> merge.c -> other_round_read_data.c 
-> sorting.c -> other_round_merge_first.c -> kruskal.c -> tree_sim.c -> merge.c ...

Until the "other_round_merge_first.c" show the result "No more nodes to be merge!!"
