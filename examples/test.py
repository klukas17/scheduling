import os

RED = "\x1B[31m"
GREEN = "\x1B[32m"
END = "\x1B[0m"

valid_examples = 0
total_examples = 0

check_topology = True
check_path_nodes = True
check_individual = True
check_simulator_logs = True

subdirs = os.listdir(".")
subdirs.sort()

for subdir in subdirs:
    if os.path.isdir(subdir) and subdir.startswith("example_"):

        example_is_valid = True
        logs = []

        output_dir = os.path.join(subdir, "output")
        expected_output_dir = os.path.join(subdir, "output_expected")

        if check_topology:
            topology_output = os.path.join(output_dir, "topology.txt")
            expected_topology = os.path.join(expected_output_dir, "topology.txt")
            if os.path.exists(topology_output) and os.path.exists(expected_topology):
                with open(topology_output, "r") as f1, open(expected_topology, "r") as f2:
                    if f1.read().strip() == f2.read().strip():
                        logs.append(f"  {GREEN}[✔]{END} Topology")
                    else:
                        logs.append(f"  {RED}[✘]{END} Topology")
                        example_is_valid = False
            else:
                logs.append(f"  {RED}[✘]{END} Topology")
                example_is_valid = False

        if check_path_nodes:
            path_nodes_output = os.path.join(output_dir, "path_nodes.txt")
            expected_path_nodes = os.path.join(expected_output_dir, "path_nodes.txt")
            if os.path.exists(path_nodes_output) and os.path.exists(expected_path_nodes):
                with open(path_nodes_output, "r") as f1, open(expected_path_nodes, "r") as f2:
                    if f1.read().strip() == f2.read().strip():
                        logs.append(f"  {GREEN}[✔]{END} Path Nodes")
                    else:
                        logs.append(f"  {RED}[✘]{END} Path Nodes")
                        example_is_valid = False
            else:
                logs.append(f"  {RED}[✘]{END} Path Nodes")
                example_is_valid = False

        if check_individual:
            individual_output = os.path.join(output_dir, "individual.yaml")
            expected_individual_output = os.path.join(subdir, "individual.yaml")
            if os.path.exists(individual_output) and os.path.exists(expected_individual_output):
                with open(individual_output, "r") as f1, open(expected_individual_output, "r") as f2:
                    if f1.read().strip() == f2.read().strip():
                        logs.append(f"  {GREEN}[✔]{END} Individual")
                    else:
                        logs.append(f"  {RED}[✘]{END} Individual")
                        example_is_valid = False
            else:
                logs.append(f"  {RED}[✘]{END} Individual")
                example_is_valid = False

        if check_simulator_logs:

            expected_logs_dir = os.path.join(expected_output_dir, "expected_logs_per_job")
            simulator_logs_file = os.path.join(subdir, "simulator_logs.txt")

            if os.path.exists(expected_logs_dir) and os.path.exists(simulator_logs_file):

                expected_logs = os.listdir(expected_logs_dir)
                expected_logs.sort()

                simulator_logs_valid = True
                simulator_logs = []

                for expected_log_file in expected_logs:

                    job_id = int(expected_log_file.split(".")[0].split("_")[1])
                    expected_log_path = os.path.join(expected_logs_dir, expected_log_file)

                    with open(expected_log_path, "r") as f:
                        expected_contents = f.read()

                    with open(simulator_logs_file, "r") as f:
                        job_contents = "".join([line for line in f if f"Job {job_id}:" in line])

                    if expected_contents.strip() == job_contents.strip():
                        simulator_logs.append(f"    {GREEN}[✔]{END} Job {job_id}")
                    else:
                        simulator_logs.append(f"    {RED}[✘]{END} Job {job_id}")
                        simulator_logs_valid = False

                if simulator_logs_valid:
                    logs.append(f"  {GREEN}[✔]{END} Simulator Logs")
                else:
                    logs.append(f"  {RED}[✘]{END} Simulator Logs")
                    example_is_valid = False

                logs += simulator_logs

            else:
                logs.append(f"  {RED}[✘]{END} Simulator Logs")
                example_is_valid = False

        if example_is_valid:
            print(f"{GREEN}[✔]{END} Example {subdir}")
            valid_examples += 1
        else:
            print(f"{RED}[✘]{END} Example {subdir}")

        total_examples += 1

        for job_log in logs:
            print(job_log)

print(f"\nScore: {valid_examples}/{total_examples}")
