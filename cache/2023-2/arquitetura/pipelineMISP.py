import time
import numpy as np
import matplotlib.pyplot as plt

class Instruction:
    def __init__(self, name, depends_on=None):
        self.name = name
        self.depends_on = depends_on

class PipelineStage:
    def __init__(self, name):
        self.name = name
        self.duration = 0.1
    def amdahl_law(p, n):
        """
        Calculates the theoretical speedup according to Amdahl's Law.
    
        Parameters:
        p -- fraction of the program that can be parallelized
        n -- number of processors
        """
        return 1 / ((1-p) + p/n)

class ClockCycle:
    def __init__(self):
        self.time = 0

    def tick(self):
        self.time += 1

stages = [PipelineStage(name) for name in ['Fetch', 'Decode', 'Execute', 'Memory Access', 'Write Back']]

instructions = [
    Instruction('I1'),
    Instruction('I2', depends_on='I1'),
    Instruction('I3'),
    Instruction('I4', depends_on='I2'),
    Instruction('I5')
]

instruction_stages = {instruction.name: 0 for instruction in instructions}

times = {instruction.name: [None]*len(stages) for instruction in instructions}

clock = ClockCycle()

for cycle in range(20):
    print(f"Cycle {cycle}")
    clock.tick()
    for instruction in instructions:
        current_stage = instruction_stages[instruction.name]
        if instruction.depends_on:
            if instruction_stages[instruction.depends_on] < stages.index(stages[2]) + 1:
                print(f"{instruction.name} is stalled due to data hazard with {instruction.depends_on}")
                continue
        if current_stage < len(stages):
            print(f"{instruction.name} is in {stages[current_stage].name} stage")
            if times[instruction.name][current_stage] is None:
                times[instruction.name][current_stage] = clock.time
            instruction_stages[instruction.name] += 1
    print()

for instruction in instructions:
    plt.plot(times[instruction.name], label=instruction.name)
plt.ylabel('Cycle')
plt.xlabel('Stage')
plt.xticks(range(len(stages)), [stage.name for stage in stages])
plt.legend()
plt.show()


# Let's vary the parallelizable fraction of the program from 0 to 1
p_values = np.linspace(0, 1, 100)

# Let's consider 1, 2, 4, 8, and 16 processors
processors = [1, 2, 4, 8, 16]

for n in processors:
    speedup = PipelineStage.amdahl_law(p_values, n)
    plt.plot(p_values, speedup, label=f'{n} processors')

plt.xlabel('Parallelizable fraction of the program (p)')
plt.ylabel('Speedup')
plt.title('Theoretical speedup according to Amdahl\'s Law')
plt.legend()
plt.grid(True)
plt.show()