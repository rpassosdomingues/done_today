import time
import random
import matplotlib.pyplot as plt

class Stage:
    def __init__(self, name):
        self.name = name
        self.instructions = []

    def process_instruction(self, next_stage):
        if self.instructions:
            instruction = self.instructions.pop(0)
            print(f"{self.name} processing instruction: {instruction}")
            time.sleep(0.5)  # Simulating processing time
            next_stage.instructions.append(instruction)

class PipelinedProcessor:
    def __init__(self):
        self.stages = [
            Stage("IF"),  # Instruction Fetch
            Stage("ID"),  # Instruction Decode
            Stage("EX"),  # Execution
            Stage("MEM"), # Memory
            Stage("WB")   # Write Back
        ]

        self.pipeline_history = []

    def run_pipeline(self):
        for i in range(len(self.stages) - 1):
            self.stages[i].process_instruction(self.stages[i + 1])

        pipeline_snapshot = [len(stage.instructions) for stage in self.stages]
        self.pipeline_history.append(pipeline_snapshot)

    def plot_pipeline(self):
        stages = [stage.name for stage in self.stages]
        for i, stage in enumerate(stages):
            plt.plot([j[i] for j in self.pipeline_history], label=stage)

        plt.title('Pipelined Processor Simulation')
        plt.xlabel('Clock Cycles')
        plt.ylabel('Number of Instructions')
        plt.legend()
        plt.show()

    def simulate(self, num_instructions):
        for _ in range(num_instructions):
            instruction = f"Instruction-{random.randint(1, 100)}"
            self.stages[0].instructions.append(instruction)  # Add instruction to IF stage
            self.run_pipeline()
            time.sleep(1)  # Simulating clock pulse

if __name__ == "__main__":
    processor = PipelinedProcessor()
    processor.simulate(10)  # Simulate processing 10 instructions
    processor.plot_pipeline()
