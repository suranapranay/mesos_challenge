# mesos_challenge
Mesosphere challenge




After some thinking I realized that it is not possible to get the best scheduler, however we can get a good enough scheduling which is better than FCFS as asked int the question.
The inuition is to pick the longest task and schedule it as early as possible, on a machine which is the minimum viable machine (resource-wise) for this task.


Thus I visualized a Dijkstra's-like algorithm, where we keep picking the longest task and move onwards.

Each time a task is done, the resources are moved back to the machine of origin.
