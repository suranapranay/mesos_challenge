# mesos_challenge
Mesosphere challenge





After some thinking I realized that it is not possible to get the best scheduler, however we can get a good enough scheduling which is better than FCFS as asked int the question.
The inuition is to pick the longest task and schedule it as early as possible, on a machine which is the minimum viable machine (resource-wise) for this task.


Thus I visualized a Dijkstra's-like algorithm, where we keep picking the longest task and move onwards, if the longest task cannot be currently scheduled, we schedule the next longest task and so on.

Each time a task is done, the resources are moved back to the machine of origin.


Instructions:
To run: cmake . && make all && ./mesos_exec

Currently the values are not configurable, but mesos_exec.cpp in src/prog/ has the code to add more tasks.


Known Issue (Edit : fixed). I fixed an issue with set uniquness of my machines and jobs using the comparisions between id_ for their objects. I did not think of this happening on time and was fixed rougly 25 minutes after the submission time.


